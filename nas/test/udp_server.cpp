/*****************************************************************************
 *	FILENAME:	udp_server_test.cpp     AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for udp_server lib.							      	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // cout
#include <boost/shared_ptr.hpp> // shared_ptr

#include "tester.hpp" // tester utils
#include "packet.hpp" // DeviceRequest
#include "comm_packet.hpp" // comm_packet
 
#include "udp_server_proxy.hpp"

using namespace ilrd_rd100;
/*****************************************************************************/
static void StringToPacket(const std::string &buff, size_t buff_size, 
	DeviceRequest &out_request_packet);
static void DeviceRequestToCommPacket(const std::string &dest, 
	const DeviceRequest &packet, CommPacket &out_comm_packet);
/********************************* driver ************************************/
int main(void)
{
	const size_t count = 10;
	const std::string msg = "Pong!\n";
	
	DeviceRequest request_packet;
	StringToPacket(msg, msg.size(), request_packet);

	CommPacket comm_packet_send;
	CommPacket comm_packet_recv;
	DeviceRequestToCommPacket("", request_packet, comm_packet_send);

	// start UDP conn with default params
	UDPServerProxy comm; 

	// send packet count times
	for (size_t i = 0; i < count; ++i)
	{
	 	comm_packet_recv = comm.ReceivePacket();
		comm.SendPacket(comm_packet_send);
		sleep(1);
	}
	
	return 0;
}
/*********************************** utils ***********************************/
void StringToPacket(const std::string &buff, size_t buff_size, 
	DeviceRequest &out_request_packet) 
{
	out_request_packet.m_msg_length = buff_size;
	memcpy(out_request_packet.m_buffer, 
            buff.c_str(),  
            buff_size);
}

void DeviceRequestToCommPacket(const std::string &dest, 
	const DeviceRequest &request, CommPacket &out_comm_packet) 
{
    out_comm_packet.dest = dest;
    out_comm_packet.data_size = sizeof(packet);
    memcpy(out_comm_packet.data, 
            const_cast<DeviceRequest*>(&packet),  
            sizeof(packet));
}

void CommPacketToDeviceRequest(const CommPacket &comm_packet, 
	DeviceRequest &out_request_packet) 
{
    memcpy(out_packet, 
            const_cast<DeviceRequest*>(&packet),  
            sizeof(packet));
}
/*****************************************************************************/