/*****************************************************************************
 *	FILENAME:	register.cpp            AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for register lib.							     *
 *																			 *
 *****************************************************************************/

#include <boost/shared_ptr.hpp> // shared_ptr

#include "singleton.hpp"
#include "factory.hpp"
#include "packet.hpp"

#include "register.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

void Register::RegisterCMD(DeviceRequest::Mode mode, 
    factory_func_t factory_func)
{
    Singleton<factory_t >::Handleton()->Add(mode, factory_func);
}

}
/*****************************************************************************/