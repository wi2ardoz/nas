/*****************************************************************************
 *	FILENAME:	task_tp.hpp             AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:    API for task_tp lib.							             *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_TASK_TP_HPP__
#define __ILRD_RD100_TASK_TP_HPP__

#include <boost/shared_ptr.hpp> // shared_ptr

#include "factory.hpp"
#include "thread_pool.hpp"
#include "packet.hpp"
#include "cmd.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class TaskTp : public ThreadPool::Task
{
public:
    explicit TaskTp(boost::shared_ptr<DeviceRequest> packet);
    virtual ~TaskTp();
    virtual void operator()();

private:
    boost::shared_ptr<DeviceRequest> m_packet;

    typedef Factory<DeviceRequest::Mode, boost::shared_ptr<CMD>, 
        boost::shared_ptr<DeviceRequest> > factory_t;
};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_TASK_TP_HPP__