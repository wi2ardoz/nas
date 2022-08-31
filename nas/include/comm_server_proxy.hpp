/*****************************************************************************
 *	FILENAME:	comm_server_proxy.hpp       AUTHOR: Liad Oz	     LAB: RD100	 *
 *																			 *
 *	VERSION:	3															 *
 *																			 *
 *	PURPOSE:    API for comm_server_proxy lib.							     *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_COMM_SERVER_PROXY_HPP__
#define __ILRD_RD100_COMM_SERVER_PROXY_HPP__

#include <boost/core/noncopyable.hpp> // noncopyable
#include <string> // string

#include "comm_packet.hpp" // CommPacket
/*****************************************************************************/
namespace ilrd_rd100
{

class CommServerProxy : private boost::noncopyable
{
public:
    virtual ~CommServerProxy() = 0;
    virtual void SendPacket(const CommPacket &comm_packet) = 0;
    virtual CommPacket ReceivePacket() = 0;
    virtual int GetSocket() const = 0;
}; //CommServerProxy

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_COMM_SERVER_PROXY_HPP