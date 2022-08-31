/*****************************************************************************
 *	FILENAME:	tester.hpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:    Testert header utils.    					                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_TESTER_HPP__
#define __ILRD_RD100_TESTER_HPP__

#include <iostream> // cout
#include <cstddef> // size_t
/*****************************************************************************/
namespace ilrd_rd100
{

template <typename T>
inline void Test(std::string name, int line, T real, T expected);
inline void Report(void);

static int g_tests = 0;
static int g_success = 0;

template <typename T>
inline void Test(std::string name, int line, T real, T expected)
{
	++g_tests;

	if (real != expected)
	{
		std::cout << "[" << name << " Test] " <<
		"line: " << line << ", " <<
		"real: " << real << ", " <<
		"expected: " << expected << 
		std::endl;
	}
	else
	{
		++g_success;
	}
}

inline void Report(void)
{
	if (g_success != g_tests)
	{
		std::cout << "FAILED: " << g_tests - g_success << "/" 
		<< g_tests << std::endl;
	}
}

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_TESTER_HPP__

