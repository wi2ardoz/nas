/*****************************************************************************
 *	FILENAME:	comm_packet.hpp         AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:    API for comm_packet lib.							         *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_COMM_PACKET_HPP__
#define __ILRD_RD100_COMM_PACKET_HPP__  

#include <string> // string
/*****************************************************************************/
namespace ilrd_rd100
{

struct CommPacket
{
    std::string dest;
    void *data;
    size_t data_size;
}; // enf of CommPacket

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_COMM_PACKET_HPP__