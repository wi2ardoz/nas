/*****************************************************************************
 *	FILENAME:	cmd_r.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for cmd_r lib.							         *
 *																			 *
 *****************************************************************************/

#include <linux/nbd.h> // nbd api
#include <arpa/inet.h> // ntohl
#include <boost/shared_ptr.hpp> // shared_ptr

#include "packet.hpp"
#include "register.hpp"

#include "cmd_r.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

void __attribute__((constructor)) Construct()
{
    Register::RegisterCMD(DeviceRequest::READ, CMD::CreateR);
}

CMDRead::CMDRead(boost::shared_ptr<DeviceRequest> packet) : CMD(packet)
{
    /* empty */
}

CMDRead::~CMDRead()
{
    /* empty */
}

boost::shared_ptr<CMD> CMD::CreateR(
    boost::shared_ptr<DeviceRequest> packet)
{
    return boost::shared_ptr<CMD>(new CMDRead(packet));
}

void CMDRead::Invoke() 
{
    boost::shared_ptr<DeviceRequest> device_reply = DeliverRequest();

    SendAck(device_reply);
    SendPacket(device_reply);
}
/*********************************** utils ***********************************/
void CMDRead::SendAck(boost::shared_ptr<DeviceRequest> device_reply) const
{
    struct nbd_reply nbd_reply;

    // config reply
    nbd_reply.magic = ntohl(NBD_REPLY_MAGIC);
    nbd_reply.error = ntohl(0);
    memcpy(nbd_reply.handle, device_reply->m_handle, 
        sizeof(device_reply->m_handle));
    
    // send nbd_reply
    WriteSocket(device_reply->m_client_side_fd, (char *)&nbd_reply, 
        sizeof(struct nbd_reply));
}

void CMDRead::SendPacket(boost::shared_ptr<DeviceRequest> packet) const
{
    WriteSocket(packet->m_client_side_fd, packet->m_buffer, 
        packet->m_msg_length);
}

void CMDRead::WriteSocket(int fd, const char *buf, size_t count) const
{
    int bytes_read = 0;

    while (0 < count) 
    {
        bytes_read = write(fd, buf, count);
        assert(bytes_read > 0);
        buf += bytes_read;
        count -= bytes_read;
    }
    assert(count == 0);
}

}
/*****************************************************************************/