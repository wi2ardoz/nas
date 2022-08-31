/*****************************************************************************
 *	FILENAME:	cmd_r.hpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:    API for cmd_r lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_CMD_R_HPP__
#define __ILRD_RD100_CMD_R_HPP__

#include <boost/shared_ptr.hpp> // shared_ptr

#include "packet.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class CMDRead : public CMD
{
public:
    explicit CMDRead(boost::shared_ptr<DeviceRequest> packet);
    virtual ~CMDRead();

    virtual void Invoke();

private:
    void SendAck(boost::shared_ptr<DeviceRequest> device_reply) const;
    void SendPacket(boost::shared_ptr<DeviceRequest> packet) const;
    void WriteSocket(int fd, const char *buf, size_t count) const;
};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_CMD_R_HPP__