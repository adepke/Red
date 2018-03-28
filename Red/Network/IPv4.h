/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "../Core/Platform.h"

#include "IP.h"

#if OS_WINDOWS
	#include <Ws2tcpip.h>  // inet_pton()
#else
	#include <arpa/inet.h>  // inet_pton()
#endif

namespace Red
{
	struct IP4Address : public IPAddress
	{
	public:
		union
		{
			// Address stored in components, maintains network byte order.
			struct
			{
#if PLATFORM_BIGENDIAN
				unsigned char A, B, C, D;
#else
				unsigned char D, C, B, A;
#endif
			};

			// Address stored in local byte order.
			unsigned int Address;
		};

	public:
		constexpr IP4Address() noexcept : Address(0) {}
		IP4Address(unsigned char InA, unsigned char InB, unsigned char InC, unsigned char InD) :
#if PLATFORM_BIGENDIAN
			A(InA),
			B(InB),
			C(InC),
			D(InD)
#else
			D(InD),
			C(InC),
			B(InB),
			A(InA)
#endif
		{}

		IP4Address(unsigned int InAddress) : Address(InAddress) {}

		IP4Address(const char* InAddress)
		{
			unsigned int NetworkAddress;

			if (inet_pton(AF_INET, InAddress, &NetworkAddress) == 1)
			{
				Address = ntohl(NetworkAddress);
			}

			else
			{
				Address = 0;
			}
		}

		virtual ~IP4Address() {}

	public:
		bool operator==(const IP4Address& Target) const
		{
			return (Address == Target.Address);
		}

		bool operator!=(const IP4Address& Target) const
		{
			return (Address != Target.Address);
		}

	public:
		// Loopback: 127.X.X.X
		bool IsLoopbackAddress() const
		{
			return (A == 127);
		}

		// LAN: 10.X.X.X
		//      172.16-31.X.X
		//      192.168.X.X
		bool IsLANAddress() const
		{
			return ((A == 10) || ((A == 172) && (B >= 16 && B <= 31)) || ((A == 192) && (B == 168)));
		}

		// Multicast: 224-239.X.X.X
		bool IsMulticastAddress() const
		{
			return ((A >= 224) && (A <= 239));
		}
	};

	struct IP4EndPoint : public IPEndPoint
	{
	public:
		IP4Address Address;
		unsigned short Port;

	public:
		constexpr IP4EndPoint() noexcept : Port(0) {}
		IP4EndPoint(const IP4Address& InAddress, unsigned short InPort) : Address(InAddress), Port(InPort) {}

		virtual ~IP4EndPoint() {}

		bool operator==(const IP4EndPoint& Target) const
		{
			return (Address == Target.Address && Port == Target.Port);
		}

		bool operator!=(const IP4EndPoint& Target) const
		{
			return (Address != Target.Address || Port != Target.Port);
		}
	};
}  // namespace Red