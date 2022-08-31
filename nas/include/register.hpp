/*****************************************************************************
 *	FILENAME:	register.hpp            AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	2															 *
 *																			 *
 *	PURPOSE:    API for register lib.							             *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_REGISTER_HPP__
#define __ILRD_RD100_REGISTER_HPP__

#include <boost/core/noncopyable.hpp> // non-copyable
#include <boost/shared_ptr.hpp> // shared_ptr
#include <boost/function.hpp> // boost function

#include "factory.hpp"
#include "cmd.hpp"
#include "packet.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class Register : boost::noncopyable
{
public:
    typedef boost::function<boost::shared_ptr<CMD>(
        boost::shared_ptr<DeviceRequest>)> factory_func_t;

    static void RegisterCMD(
        DeviceRequest::Mode mode, factory_func_t factory_func);

private:
    typedef Factory<DeviceRequest::Mode, boost::shared_ptr<CMD>, 
        boost::shared_ptr<DeviceRequest> > factory_t;
};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_REGISTER_HPP__