/*****************************************************************************
 *	FILENAME:	distributor.hpp         AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:    API for distributor lib.							         *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_DISTRIBUTOR_HPP__
#define __ILRD_RD100_DISTRIBUTOR_HPP__

#include <boost/core/noncopyable.hpp> // noncopyable
#include <boost/shared_ptr.hpp> // shared_ptr

#include "packet.hpp" // packet
#include "raid.hpp" // raid
#include "comm_server_proxy.hpp" // comm_proxy
/*****************************************************************************/
namespace ilrd_rd100
{

class Distributor: private boost::noncopyable
{
public:
    explicit Distributor(Raid *raid, CommServerProxy *comm_proxy);
    void Deliver(boost::shared_ptr<DeviceRequest> request);

private:
    Raid *m_raid;
    CommServerProxy *m_comm_proxy;

    static void DeviceRequestToCommPacket(const std::string &dest,
        const DeviceRequest &request, CommPacket &out_packet);
}; // Distributor

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_DISTRIBUTOR_HPP__