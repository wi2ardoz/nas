/*****************************************************************************
 *	FILENAME:	cmd_w.hpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:    API for cmd_w lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_CMD_W_HPP__
#define __ILRD_RD100_CMD_W_HPP__

#include <boost/shared_ptr.hpp> // shared_ptr

#include "packet.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class CMDWrite : public CMD
{
public:
    explicit CMDWrite(boost::shared_ptr<DeviceRequest> packet);
    virtual ~CMDWrite();

    virtual void Invoke();

private:
    void SendAck(boost::shared_ptr<DeviceRequest> device_reply) const;
    void WriteSocket(int fd, const char *buf, size_t count) const;
};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_CMD_W_HPP__