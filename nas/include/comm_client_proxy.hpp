/*****************************************************************************
 *	FILENAME:	comm_client_proxy.hpp       AUTHOR: Liad Oz	     LAB: RD100	 *
 *																			 *
 *	VERSION:	3															 *
 *																			 *
 *	PURPOSE:    API for comm_client_proxy lib.							     *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_COMM_CLIENT_PROXY_HPP__
#define __ILRD_RD100_COMM_CLIENT_PROXY_HPP__

#include <boost/core/noncopyable.hpp> // noncopyable
#include <string> // string

#include "comm_packet.hpp" // CommPacket
/*****************************************************************************/
namespace ilrd_rd100
{

class CommClientProxy : private boost::noncopyable
{
public:
    virtual ~CommClientProxy() = 0;
    virtual void SendPacket(const CommPacket &comm_packet) = 0;
    virtual CommPacket ReceivePacket() = 0;
    virtual int GetSocket() const = 0;
}; //CommClientProxy

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_COMM_CLIENT_PROXY_HPP__