/*****************************************************************************
 *	FILENAME:	dynamic_hd_test.cpp     AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for dynamic_hd lib.							      	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // cout

#include "nbd.hpp"
#include "dynamic_hd.hpp"

using namespace ilrd_rd100;
/********************************* driver ************************************/
int main(void)
{
	const u_int64_t DEVICE_SIZE = 1 << 27; // 128MB

	NBD nbd("/dev/nbd0", DEVICE_SIZE);
	DynamicHD dynamic_hd(DEVICE_SIZE);

	//dynamic_hd.ListenToSocket(nbd.GetSocket());

	return 0;
}
/*****************************************************************************/