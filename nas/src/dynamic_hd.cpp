/*****************************************************************************
 *	FILENAME:	dynamic_hd.cpp          AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for dynamic_hd lib.							 *
 *																			 *
 *****************************************************************************/

#include <assert.h> // assert
#include <string.h> // memcpy 
#include <linux/nbd.h> // nbd api
#include <arpa/inet.h> // ntohl

#include "dynamic_hd.hpp"
#include "packet.hpp"
/*********************************** api *************************************/
namespace ilrd_rd100
{

DynamicHD::DynamicHD(u_int64_t device_size) : m_storage(new char[device_size])
{
    /* empty */   
}

DynamicHD::~DynamicHD()
{
    delete[] m_storage;
}

boost::shared_ptr<DeviceRequest> DynamicHD::ProcessRequest(
    boost::shared_ptr<DeviceRequest> request)
{
    boost::shared_ptr<DeviceRequest> reply = request;
    
    switch (request->m_cmdMode)
    {
        case DeviceRequest::READ:
            DeviceRead(reply->m_buffer, request->m_offset, 
                request->m_msg_length);
            break;
        
        case DeviceRequest::WRITE:
            DeviceWrite(request->m_buffer, request->m_offset, 
                request->m_msg_length);
            break;
        
        // case DeviceRequest::EXCEPTION
        default:
            /* empty */
            break;
    }

    return reply;
}

void DynamicHD::DeviceRead(
    char *msg_to_network, u_int64_t from, u_int64_t len) const
{
    memcpy(msg_to_network, m_storage + from, len);
}

void DynamicHD::DeviceWrite(const char *msg_to_device, u_int64_t from, 
    u_int64_t len)
{
    memcpy(m_storage + from, msg_to_device, len);
}

}
/*****************************************************************************/