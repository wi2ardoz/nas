/*****************************************************************************
 *	FILENAME:	raid.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for raid lib.							         *
 *																			 *
 *****************************************************************************/

#include "raid.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

Raid::Raid(const boost::container::vector<std::string> &devices, 
    u_int64_t min_size) : m_devices(devices),
                        m_min_size(min_size)
{
    /* empty */
}

Raid::~Raid()
{
    /* empty */
}

void Raid::SetDevices(const boost::container::vector<std::string> &devices) 
{
    m_devices = devices;
}

boost::container::vector<std::string> Raid::GetDevices() const
{
    return m_devices;
}

void Raid::SetMinSize(u_int64_t min_size) 
{
    m_min_size = min_size;
}

u_int64_t Raid::GetMinSize() const
{
    return m_min_size;}

}
/*****************************************************************************/