/*****************************************************************************
 *	FILENAME:	master.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for master lib.							     *
 *																			 *
 *****************************************************************************/

#include <iostream> // cout
#include <fstream> // ifstream
#include <sstream> // stringstream
#include <algorithm> // min element
#include <boost/shared_ptr.hpp> // shared_ptr

#include "input_mediator.hpp"
#include "thread_pool.hpp"
#include "dir_monitor.hpp"

#include "distributor.hpp"
#include "udp_server_proxy.hpp"
#include "raid_01.hpp"

#include "master.hpp"

using namespace ilrd_rd100;
/*****************************************************************************/
int main(void)
 {
    // config file path
    const std::string config_file = "/home/liad/git/projects/nas/config";

    // parse server configuration from config file
    ServerConfigs out_configs;
    ConfigFileToServerConfigs(config_file, out_configs);

    // get iterator of minumum size minion
    boost::container::vector<u_int64_t>::iterator min_elem_it = 
        std::min_element(
            out_configs.minion_sizes.begin(), 
            out_configs.minion_sizes.end());

    // init raid1
    Raid01 raid(out_configs.minion_addrs, out_configs.minion_sizes.at(
        std::distance(out_configs.minion_sizes.begin(), min_elem_it)));

    // start dir monitor thread
    DirMonitor dir_monitor(out_configs.dll_path);
    DsoLoader loader(&dir_monitor);

    // wait for dll to load
    std::string buff;
    std::cout << "Are DLLs ready? [Y/N]" << std::endl;
    std::cin >> buff;

    // init thread pool
    ThreadPool pool(1);

    // open device path with 128M size
	InputProxy *input_proxy = InputProxy::Create(
        (out_configs.device_path).c_str(), MBtoBit(raid.GetMaxRange()));

    // start NBD thread
    InputMediator mediator(&pool, input_proxy, input_proxy->GetSocket());

    // start listening & handling tasks
    mediator.Run();

    return 0;
}
/*********************************** utils ***********************************/
void ilrd_rd100::ConfigFileToServerConfigs(const std::string &config_file, 
    ServerConfigs &out_configs)
{
    std::ifstream file(config_file.c_str());
    std::string line, value;

    // parse device_path
    std::getline(file, line);
    out_configs.device_path = line;

    // parse dll_path
    std::getline(file, line);
    out_configs.dll_path = line;

    // parse minions
    while(std::getline(file, line))
    {
        std::stringstream stream(line);

        // parse minion address
        std::string m_path;
        stream >> m_path;
        out_configs.minion_addrs.push_back(m_path);

        // parse minion size
        u_int64_t m_size;
        stream >> m_size;
        out_configs.minion_sizes.push_back(m_size);
    }
}

u_int64_t ilrd_rd100::MBtoBit(u_int64_t mb)
{
    return 1 << (size_t)(20 + log2(static_cast<double>(mb)));
}
/*****************************************************************************/