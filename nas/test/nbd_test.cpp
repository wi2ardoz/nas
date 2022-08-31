/*****************************************************************************
 *	FILENAME:	nbd_test.cpp            AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for nbd lib.							      	 	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // cout
#include "tester.hpp" // tester utils
#include "nbd.hpp"

using namespace ilrd_rd100;
/********************************* driver ************************************/
int main(void)
{
	// open device path with 128M size
	NBD nbd("/dev/nbd0", 1 << 27);

	std::cout << nbd.GetSocket() << std::endl;

	return 0;
}
/*****************************************************************************/