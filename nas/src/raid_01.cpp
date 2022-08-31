/*****************************************************************************
 *	FILENAME:	raid_01.cpp             AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for raid_01 lib.							     *
 *																			 *
 *****************************************************************************/

#include "raid_01.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

Raid01::Raid01(const boost::container::vector<std::string> &devices, 
    u_int64_t min_size) : Raid(devices, min_size)
{
    /* empty */
}

Raid01::~Raid01() 
{
    /* empty */
}

boost::shared_ptr<Raid::RaidPackage> Raid01::SelectDevices(u_int64_t offset) 
{
    boost::shared_ptr<Raid::RaidPackage> package(new Raid::RaidPackage);

    u_int64_t devices_offset = offset / GetMinSize();
    package->m_offset = devices_offset;

    u_int64_t device_pos = offset % GetMinSize(); 
    u_int64_t mirror_pos = (offset % GetMinSize()) + (GetDevices().size() / 2);
    package->m_devices[0] = GetDevices().at(device_pos);
    package->m_devices[1] = GetDevices().at(mirror_pos);

    return package;
}

/* total size must to be pair num */ 
u_int64_t Raid01::GetMaxRange() const
{
    return (GetMinSize() * GetDevices().size()) / 2;
}

}
/*****************************************************************************/