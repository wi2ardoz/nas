/*****************************************************************************
 *	FILENAME:	master.hpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:    API for master lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_MASTER_HPP__
#define __ILRD_RD100_MASTER_HPP__

#include <boost/shared_ptr.hpp> // shared_ptr
#include <boost/container/vector.hpp> // vector
/*****************************************************************************/
namespace ilrd_rd100
{

struct ServerConfigs
{
    std::string device_path;
    std::string dll_path;
    boost::container::vector<std::string> minion_addrs;
    boost::container::vector<u_int64_t> minion_sizes;
};

static void ConfigFileToServerConfigs(const std::string &config_file, 
    ServerConfigs &out_configs);

static u_int64_t MBtoBit(u_int64_t mb);

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_MASTER_HPP__