/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "../Core/Platform.h"

#if OS_WINDOWS
	#include <WS2tcpip.h>  // sockaddr_in6
	#include <cstring>  // memset()
#else
	#include <sys/socket.h>  // sockaddr_in6
	#include <string.h>  // memset()
#endif

namespace Red
{
	// Simple Wrapper Around sockaddr_in6
	struct IP6Address
	{
	public:
		sockaddr_in6 Address;

	public:
		constexpr IP6Address() noexcept : Address()
		{
#if OS_WINDOWS
			std::memset(&Address, 0, sizeof(Address));
#else
			memset(&Address, 0, sizeof(Address));
#endif

			Address.sin6_family = AF_INET6;
		}
	};
}  // namespace Red