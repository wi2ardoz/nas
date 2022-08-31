/*****************************************************************************
 *	FILENAME:	distributor.cpp         AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for distributor lib.							 *
 *																			 *
 *****************************************************************************/

#include <boost/shared_ptr.hpp> // shared_ptr

#include "raid.hpp" // RaidPacket
#include "comm_server_proxy.hpp" // CommPacket

#include "distributor.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{
    
Distributor::Distributor(Raid *raid, 
    CommServerProxy *comm_proxy) : m_raid(raid),
                                   m_comm_proxy(comm_proxy)
{
    /* empty */
}

void Distributor::Deliver(boost::shared_ptr<DeviceRequest> request) 
{
    // calculate input_proxy's offset with raid and override it inside packet
    boost::shared_ptr<Raid::RaidPackage> raid_pack = 
        m_raid->SelectDevices(request->m_offset);
    request->m_offset = raid_pack->m_offset;

    // loop thru devices (including mirrored) and send them the packet
    CommPacket comm_packet;
    for (size_t i = 0; i < raid_pack->m_devices.size(); ++i)
    {
        DeviceRequestToCommPacket(raid_pack->m_devices[i], *request, 
            comm_packet);

        m_comm_proxy->SendPacket(comm_packet);
    }
}
/*********************************** utils ***********************************/
void Distributor::DeviceRequestToCommPacket(const std::string &dest,
    const DeviceRequest &request, CommPacket &out_packet) 
{
    out_packet.dest = dest;
    out_packet.data_size = sizeof(request);
    memcpy(out_packet.data, 
            const_cast<DeviceRequest*>(&request),  
            sizeof(request));
}

}
/*****************************************************************************/