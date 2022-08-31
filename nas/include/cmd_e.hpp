/*****************************************************************************
 *	FILENAME:	cmd_e.hpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:    API for cmd_e lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_CMD_E_HPP__
#define __ILRD_RD100_CMD_E_HPP__

#include <boost/shared_ptr.hpp> // shared_ptr

#include "packet.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class CMDException : public CMD
{
public:
    explicit CMDException(boost::shared_ptr<DeviceRequest> packet);
    virtual ~CMDException();

    virtual void Invoke();

private:
    void SendAck(boost::shared_ptr<DeviceRequest> device_reply) const;
    void WriteSocket(int fd, const char *buf, size_t count) const;
};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_CMD_E_HPP__