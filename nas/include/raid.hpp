/*****************************************************************************
 *	FILENAME:	raid.hpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	2															 *
 *																			 *
 *	PURPOSE:    API for RAID interface.						                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_RAID_HPP__
#define __ILRD_RD100_RAID_HPP__

#include <boost/core/noncopyable.hpp> // noncopyable
#include <boost/shared_ptr.hpp> // shared_ptr
#include <boost/container/vector.hpp> // vector
/*****************************************************************************/
namespace ilrd_rd100
{

class Raid: private boost::noncopyable
{
public:
    struct RaidPackage
    {
        boost::container::vector<std::string> m_devices;
        u_int64_t m_offset;
    };

    explicit Raid(const boost::container::vector<std::string> &devices, 
        u_int64_t min_size);
    virtual ~Raid() = 0;
    virtual boost::shared_ptr<RaidPackage> SelectDevices(u_int64_t offset) = 0;
    virtual u_int64_t GetMaxRange() const = 0;

    boost::container::vector<std::string> GetDevices() const;
    void SetDevices(const boost::container::vector<std::string> &devices);
    
    u_int64_t GetMinSize() const;
    void SetMinSize(u_int64_t min_size);

private:
    boost::container::vector<std::string> m_devices;
    u_int64_t m_min_size;
}; // Raid

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_RAID_HPP__