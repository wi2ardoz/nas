/*****************************************************************************
 *	FILENAME:	packet.hpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	4															 *
 *																			 *
 *	PURPOSE:    API for packet lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_PACKET_HPP__
#define __ILRD_RD100_PACKET_HPP__

#include <boost/interprocess/mapped_region.hpp> // get page size
#include <unistd.h> // uint64_t
/*****************************************************************************/
namespace ilrd_rd100
{

struct DeviceRequest
{
    static const int MAX_PACKET_SIZE = 1 << 12; // each input proxy will need 
                                                // to configurate this value   
                                                // (max_sectors_kb)
    enum Mode
    {
        READ = 0,
        WRITE = 1,
        EXCEPTION = 2,
        NUM_MODES = 3
    };

    char m_handle[8]; // request_id
    Mode m_cmdMode;
    int m_client_side_fd;
    u_int64_t m_offset;
    u_int64_t m_msg_length;
    char m_buffer[MAX_PACKET_SIZE];
}; //end DeviceRequest

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_PACKET_HPP__