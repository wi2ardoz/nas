/*****************************************************************************
 *	FILENAME:	udp_client_proxy.hpp        AUTHOR: Liad Oz	     LAB: RD100	 *
 *																			 *
 *	VERSION:	3															 *
 *																			 *
 *	PURPOSE:    API for udp_client_proxy lib. Supports IPv4 only.		     *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_UDP_CLIENT_PROXY_HPP__
#define __ILRD_RD100_UDP_CLIENT_PROXY_HPP__

#include <boost/core/noncopyable.hpp> // noncopyable

#include "comm_packet.hpp" // CommPacket

#include "comm_client_proxy.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class UDPClientProxy : public CommClientProxy
{
public:
    explicit UDPClientProxy(const std::string &ip = "", 
        const std::string &port = "8000");
    virtual ~UDPClientProxy();
    virtual void SendPacket(const CommPacket &comm_packet);
    virtual CommPacket ReceivePacket();
    virtual int GetSocket() const;
    
private:
    int m_socket_fd;

    int ConfigUDPConn(const std::string &ip, const std::string &port);
}; // UDPClientrProxy

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_UDP_CLIENT_PROXY_HPP__