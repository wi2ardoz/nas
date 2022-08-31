/*****************************************************************************
 *	FILENAME:	input_proxy.hpp         AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	4															 *
 *																			 *
 *	PURPOSE:    API for input_proxy lib.							         *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_INPUT_PROXY_HPP__
#define __ILRD_RD100_INPUT_PROXY_HPP__

#include <boost/core/noncopyable.hpp> // noncopyable
#include <boost/shared_ptr.hpp> //shared_ptr
#include "packet.hpp" //reactor
/*****************************************************************************/
namespace ilrd_rd100
{

class InputProxy : private boost::noncopyable
{
public:
    virtual ~InputProxy() = 0;
    virtual int GetSocket() const = 0;
    virtual boost::shared_ptr<DeviceRequest> ReadOp(int client_side_fd) = 0;
    static InputProxy *Create(const char* dev_file, u_int64_t device_size);
}; // end InputProxy

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_INPUT_PROXY_HPP__