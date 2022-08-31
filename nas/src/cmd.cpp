/*****************************************************************************
 *	FILENAME:	cmd.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for cmd lib.							         *
 *																			 *
 *****************************************************************************/

#include "singleton.hpp"
#include "dynamic_hd.hpp"

#include "cmd.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

CMD::CMD(boost::shared_ptr<DeviceRequest> packet): m_packet(packet)
{
    /* empty */
}

CMD::~CMD()
{
    /* empty */
}

boost::shared_ptr<DeviceRequest> CMD::GetPacket() const
{
    return m_packet;
}

boost::shared_ptr<DeviceRequest> CMD::DeliverRequest()
{
    // NEXT will be replaced in Distributer using RAID API
    // and this funcion return void because input mediator invoke reply func

    // get device
    DynamicHD *dynamic_hd = Singleton<DynamicHD>::Handleton();

    // process request and get reply
    boost::shared_ptr<DeviceRequest> device_reply = 
        dynamic_hd->ProcessRequest(m_packet);

    return device_reply;
}
   
}
/*****************************************************************************/