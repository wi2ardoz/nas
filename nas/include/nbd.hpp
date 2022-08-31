/*****************************************************************************
 *	FILENAME:	nbd.hpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	4															 *
 *																			 *
 *	PURPOSE:    API for nbd lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_NBD_HPP__
#define __ILRD_RD100_NBD_HPP__ 

#include <boost/thread.hpp> //boost thread
#include <boost/core/noncopyable.hpp> // noncopyable
#include <fcntl.h> // open
#include <linux/nbd.h> // nbd api

#include "input_proxy.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class NBD : public InputProxy
{
public:
    explicit NBD(const char* dev_file, u_int64_t device_size);
    ~NBD();
    virtual int GetSocket() const;
    virtual boost::shared_ptr<DeviceRequest> ReadOp(int client_side_fd);
    
private:
    int m_client_side_fd;
    boost::thread m_thread;
    
    int NBDConfig(const char* device_file, u_int64_t device_size);
    static void NBDlisten(int device_fd); // static thread func 

    u_int64_t ntohll(u_int64_t a) const;
    void ReadSocket(int fd, char *buf, size_t count) const;
}; // end NBD

} // ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_NBD_HPP__