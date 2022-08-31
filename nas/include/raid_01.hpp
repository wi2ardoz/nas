/*****************************************************************************
 *	FILENAME:	raid_01.hpp             AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:    API for raid_01 lib.							             *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_RAID_01_HPP__
#define __ILRD_RD100_RAID_01_HPP__

#include <boost/shared_ptr.hpp> // shared_ptr
#include <boost/container/vector.hpp> // list

#include "raid.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class Raid01: public Raid
{
public:
    explicit Raid01(const boost::container::vector<std::string> &devices, 
        u_int64_t min_size);
    virtual ~Raid01();
    virtual boost::shared_ptr<RaidPackage> SelectDevices(u_int64_t offset);
    virtual u_int64_t GetMaxRange() const;
}; // Raid01

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_RAID_01_HPP__