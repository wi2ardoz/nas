/*****************************************************************************
 *	FILENAME:	nbd.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for nbd lib.							         *
 *																			 *
 *****************************************************************************/

#define _POSIX_C_SOURCE (200809L)

#include <iostream> // testing cout
#include <boost/thread.hpp> // threads
#include <fcntl.h> // open
#include <linux/nbd.h> // nbd api
#include <sys/ioctl.h> // ioctl
#include <sys/socket.h> // socketpair
#include <arpa/inet.h> // ntohl

#include "packet.hpp"
#include "nbd.hpp"
/*********************************** api *************************************/
namespace ilrd_rd100
{

NBD::NBD(const char *device_file, u_int64_t device_size) : m_client_side_fd(),
                                                            m_thread()
{
    // config NBD connection
    int device_fd = NBDConfig(device_file, device_size);

    // start listining thread
    m_thread = boost::thread(&NBD::NBDlisten, device_fd);
}

NBD::~NBD()
{
    m_thread.join();
    close(m_client_side_fd);
}

int NBD::GetSocket() const
{
    return m_client_side_fd;
}

void NBD::ReadSocket(int fd, char *buf, size_t count) const
{
    int bytes_read = 0;

    while (0 < count) 
    {
        bytes_read = read(fd, buf, count);
        assert(bytes_read > 0);
        buf += bytes_read;
        count -= bytes_read;
    }
    assert(count == 0);
}

int NBD::NBDConfig(const char* device_file, u_int64_t device_size)
{
    // create pipe: sp[0] - client, sp[1] - server
    int sp[2];
    int status = socketpair(AF_UNIX, SOCK_STREAM, 0, sp);
    int server_side_fd = sp[1];
    m_client_side_fd = sp[0];
    std::cout << "SOCKET_PAIR " << status << std::endl;
    
    // open device fd
    int device_fd = open(device_file, O_RDWR);
    std::cout << "NBD_FD " << device_fd << std::endl;

    // set device_size
    status = ioctl(device_fd, NBD_SET_SIZE, device_size);
    std::cout << "NBD_SET_SIZE " << status << std::endl;

    // clean device fd
    status = ioctl(device_fd, NBD_CLEAR_SOCK);
    std::cout << "NBD_CLEAR_SOCK " << status << std::endl;

    // connect device fd to our server_fd
    status = ioctl(device_fd, NBD_SET_SOCK, server_side_fd);
    std::cout << "NBD_SET_SOCK " << status << std::endl;

    // TEST ONLY: set streaming timeout
    // ioctl(nbd_fd, NBD_SET_TIMEOUT, 10);

    return device_fd;
}

u_int64_t NBD::ntohll(u_int64_t a) const
{
    #ifdef WORDS_BIGENDIAN
        return a;
    #else
        u_int32_t lo = a & 0xffffffff;
        u_int32_t hi = a >> 32U;
        lo = ntohl(lo);
        hi = ntohl(hi);
        return ((u_int64_t) lo) << 32U | hi;
    #endif
}
/******************************* thread func *********************************/
void NBD::NBDlisten(int device_fd)
{    
    // start streaming data  
    int status = ioctl(device_fd, NBD_DO_IT);
    std::cout << "NBD_DO_IT " << status << std::endl;

    // disconnect & close device
    status = ioctl(device_fd, NBD_DISCONNECT);    
    std::cout << "NBD_DISCONNECT " << status << std::endl;

    close(device_fd);
}
/******************************* Input Proxy *********************************/
InputProxy::~InputProxy()
{
    /* empty */
}

InputProxy *InputProxy::Create(const char* dev_file, u_int64_t device_size)
{
    return new NBD(dev_file, device_size);
}

boost::shared_ptr<DeviceRequest> NBD::ReadOp(int client_side_fd)
{
    boost::shared_ptr<DeviceRequest> translated_request(new DeviceRequest);
    struct nbd_request nbd_request;

    // read nbd request from socket
    if (0 < read(client_side_fd, &nbd_request, sizeof(nbd_request)))
    {
        // translate request's id, len, offset
        translated_request->m_client_side_fd = client_side_fd;
        translated_request->m_msg_length = ntohl(nbd_request.len);
        translated_request->m_offset = ntohll(nbd_request.from);
        memcpy(translated_request->m_handle, nbd_request.handle, 
            sizeof(nbd_request.handle));
        
        // get type of desired command
        switch (ntohl(nbd_request.type))
        {
            case NBD_CMD_READ:
                translated_request->m_cmdMode = DeviceRequest::READ;
                break;

            case NBD_CMD_WRITE:
                translated_request->m_cmdMode = DeviceRequest::WRITE;
                ReadSocket(client_side_fd, translated_request->m_buffer, 
                    translated_request->m_msg_length);
                break;

            // case DISK/TRIM/FLUSH
            default:
                translated_request->m_cmdMode = DeviceRequest::EXCEPTION;
                break;
        }
    }

    return translated_request;
}

}
/*****************************************************************************/