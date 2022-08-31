/*****************************************************************************
 *	FILENAME:	task_tp.cpp             AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for task_tp lib.							     *
 *																			 *
 *****************************************************************************/

#include <boost/thread/mutex.hpp> // mutex
#include <boost/interprocess/sync/scoped_lock.hpp> // scope_lock

#include "singleton.hpp"
#include "factory.hpp"
#include "cmd.hpp"
#include "task_tp.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

TaskTp::TaskTp(boost::shared_ptr<DeviceRequest> packet): m_packet(packet)
{
    /* empty */
}

TaskTp::~TaskTp()
{
    /* empty */
}

void TaskTp::operator()() 
{
    static size_t io_counter = 1;
    static boost::mutex factory_lock;
    boost::shared_ptr<CMD> cmd;
    
    // thread safe factory block
    {
        boost::mutex::scoped_lock scope_factory_lock(factory_lock);

        // create cmd by commend mode (KEY) and packet (PARAM)
        cmd = Singleton<factory_t >::Handleton()->Create(
            m_packet->m_cmdMode, m_packet);

        // NEXT sync shouldn't be here !! we may sync deliver
        // invoke command
        cmd->Invoke();
    }

    std::cout << ++io_counter << " Invoke " 
            << ((m_packet->m_cmdMode == 0) ? "READ" : "WRITE") << std::endl;
}

}
/*****************************************************************************/