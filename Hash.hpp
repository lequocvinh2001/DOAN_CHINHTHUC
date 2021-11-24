#pragma once
#include <string>

#ifndef __HASH_HDR__
#define __HASH_HDR__
template<class T>
unsigned int DJBHash(T str)
{
	unsigned int hash = 5381;//5381 la mot so nguyen to lon dung trong ham bam de trai rong gia tri, kha nang trung thap

	for (std::size_t i = 0; i < str.length(); i++)
	{
		hash = ((hash << 5) + hash) + str[i];
	}
	return hash;
}

#endif /* __HASH_HDR__ */