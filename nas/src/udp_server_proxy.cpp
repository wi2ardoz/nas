/*****************************************************************************
 *	FILENAME:	udp_server_proxy.cpp     AUTHOR: Liad Oz	 LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for udp_server_proxy lib.					     *
 *              TODO: 1. can it be any address for both client and server?   *
 *                    2. is it possible to update config automaticaly        * 
 *                       when each minion is set.                            *
 *																			 *
 *****************************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <boost/shared_ptr.hpp> // shared_ptr
#include <string> // string
#include <string.h> // memset, memcpy
#include <sys/socket.h> // socket
#include <netinet/in.h> // for sin family
#include <netinet/ip.h> // ip communication
#include <netdb.h> // addrinfo
#include <arpa/inet.h> // inet_addr

#include "comm_packet.hpp" // CommPacket

#include "udp_server_proxy.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

UDPServerProxy::UDPServerProxy(const std::string &ip, 
    const std::string &port) : m_socket_fd(ConfigUDPConn(ip, port))
{
    /* empty */
}

UDPServerProxy::~UDPServerProxy() 
{
    close(m_socket_fd);
}

void UDPServerProxy::SendPacket(const CommPacket &comm_packet)
{
    // comm_packet->dest to sockaddr_in
    struct sockaddr_in their_addr;
    memset(&their_addr, 0, sizeof (their_addr));
    their_addr.sin_family = AF_INET;
    their_addr.sin_addr.s_addr = inet_addr(comm_packet.dest.c_str());

    // send packet
    sendto(m_socket_fd, 
            comm_packet.data, 
            comm_packet.data_size, 
            0,
            (const struct sockaddr *) &their_addr, 
            sizeof(sockaddr_in));
}

CommPacket UDPServerProxy::ReceivePacket()
{
    const size_t buff_size = 100;
    char buff[buff_size];
    
    struct sockaddr_in their_addr;
    socklen_t addr_len;

    // receive data into buff
    size_t bytes_recv = recvfrom(m_socket_fd, 
                        buff, 
                        sizeof(buff_size),
                        0,
                        (struct sockaddr *)&their_addr, 
                        &addr_len);

    // convert c style packet to CommPacket
    CommPacket comm_packet;
    comm_packet.dest = inet_ntoa(their_addr.sin_addr);
    memcpy(comm_packet.data, buff, bytes_recv);
    comm_packet.data_size = bytes_recv;

    return comm_packet;
}

int UDPServerProxy::GetSocket() const
{
    return m_socket_fd;
}
/*********************************** utils ***********************************/
int UDPServerProxy::ConfigUDPConn(const std::string &ip, 
    const std::string &port)
{
    // config addrinfo to ip_ver & UDP
    struct addrinfo hints, *serv_info;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    if ("" != ip)
    {
        hints.ai_flags = 0;
        getaddrinfo(ip.c_str(), port.c_str(), &hints, &serv_info);
    }
    else
    {
        hints.ai_flags = AI_PASSIVE; // fill in my IP for me
        getaddrinfo(NULL, port.c_str(), &hints, &serv_info);
    }

    // open socket
    int udp_fd = socket(serv_info->ai_family, 
                        serv_info->ai_socktype, 
                        serv_info->ai_protocol);

    // bind socket to ip address
    if (-1 != udp_fd &&
        -1 != bind(udp_fd, serv_info->ai_addr, serv_info->ai_addrlen))
    {
        return -1;
    }
    
    freeaddrinfo(serv_info);
    return udp_fd;
}

}
/*****************************************************************************/