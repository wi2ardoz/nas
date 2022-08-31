/*****************************************************************************
 *	FILENAME:	input_mediator.hpp      AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	3															 *
 *																			 *
 *	PURPOSE:    API for input_mediator lib.							         *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_INPUT_MEDIATOR_HPP__
#define __ILRD_RD100_INPUT_MEDIATOR_HPP__

#include "reactor.hpp"
#include "input_proxy.hpp"
#include "packet.hpp"
#include "thread_pool.hpp"
#include "factory.hpp"
#include "cmd.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class InputMediator : private boost::noncopyable
{
public:
    explicit InputMediator(ThreadPool *pool, InputProxy *inputProxy, int fd);
    ~InputMediator();
    void Run();

private:
    Reactor m_reactor;
    ThreadPool *m_pool;
    InputProxy *m_inputProxy;

    void ReadOp(int fd);
}; // end InputMediator

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_INPUT_MEDIATOR_HPP__