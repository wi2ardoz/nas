/*****************************************************************************
 *	FILENAME:	dynamic_hd.hpp          AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	2															 *
 *																			 *
 *	PURPOSE:    API for dynamic_hd lib.							             *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_DYNAMIC_HD_HPP__
#define __ILRD_RD100_DYNAMIC_HD_HPP__ 

#include <boost/core/noncopyable.hpp> // noncopyable
#include <boost/shared_ptr.hpp> // shared_ptr

#include "packet.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class DynamicHD: private boost::noncopyable
{
public:
    explicit DynamicHD(u_int64_t device_size);
    ~DynamicHD();
    boost::shared_ptr<DeviceRequest> ProcessRequest(
        boost::shared_ptr<DeviceRequest> request);

private:
    char *m_storage;
    
    void DeviceRead(char *msg_to_network, u_int64_t from, u_int64_t len) const;
    void DeviceWrite(const char *msg_to_device, u_int64_t from, u_int64_t len);
}; // DynamicHD

} // ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_DYNAMIC_HD_HPP__