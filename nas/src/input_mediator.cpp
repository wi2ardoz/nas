/*****************************************************************************
 *	FILENAME:	input_mediator.cpp      AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for input_mediator lib.					     *
 *																			 *
 *****************************************************************************/

#include <boost/bind.hpp> // bind

#include "reactor.hpp"
#include "input_proxy.hpp"
#include "packet.hpp"
#include "task_tp.hpp"

#include "input_mediator.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{
    
InputMediator::InputMediator(ThreadPool *pool, InputProxy *inputProxy, int fd) :
                                m_reactor(),
                                m_pool(pool),
                                m_inputProxy(inputProxy)
{
    // bind reactor functions, ignore "this"
    boost::function<void (int)> Read(
        boost::bind(&InputMediator::ReadOp, this, _1));

    // set reactor functions
    m_reactor.Add(Read, fd, Reactor::READ);
}

InputMediator::~InputMediator()
{
    /* empty */
    /* calls m_pool, m_reactor dtors */
}

void InputMediator::Run()
{
    // start pool
    m_pool->Run();

    // start reactor
    m_reactor.Run();
}

/*
 *  this is wrapper callback to get device request and deliver to TP
 */
void InputMediator::ReadOp(int fd)
{
    // get device request via ReadOp of specific InputProxy (e.g NBD)
    boost::shared_ptr<DeviceRequest> request = m_inputProxy->ReadOp(fd);
    
    // add task to thread pool
    m_pool->Add(boost::shared_ptr<ThreadPool::Task>(new TaskTp(request)), 
        ThreadPool::HIGH);
}

}
/*****************************************************************************/
