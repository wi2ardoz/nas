/*****************************************************************************
 *	FILENAME:	cmd.hpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	2															 *
 *																			 *
 *	PURPOSE:    API for cmd lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_CMD_HPP__
#define __ILRD_RD100_CMD_HPP__

#include <boost/core/noncopyable.hpp> // non-copyable
#include <boost/shared_ptr.hpp> // shared_ptr

#include "packet.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class CMD : private boost::noncopyable
{
public:
    explicit CMD(boost::shared_ptr<DeviceRequest> packet);
    virtual ~CMD() = 0;
    virtual void Invoke() = 0;

    static boost::shared_ptr<CMD> CreateR(
        boost::shared_ptr<DeviceRequest> packet);
    static boost::shared_ptr<CMD> CreateW(
        boost::shared_ptr<DeviceRequest> packet);
    static boost::shared_ptr<CMD> CreateE(
        boost::shared_ptr<DeviceRequest> packet);

    boost::shared_ptr<DeviceRequest> GetPacket() const;
    boost::shared_ptr<DeviceRequest> DeliverRequest();

private:
    boost::shared_ptr<DeviceRequest> m_packet;
};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_CMD_HPP__