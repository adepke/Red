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
		IP4Address() : IPAddress(IPv4), Address(0) {}
		IP4Address(unsigned char InA, unsigned char InB, unsigned char InC, unsigned char InD) : IPAddress(IPv4),
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

		IP4Address(unsigned int InAddress) : IPAddress(IPv4), Address(InAddress) {}

		IP4Address(const char* InAddress) : IPAddress(IPv4)
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
		virtual bool IsLoopbackAddress() const override
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
		virtual bool IsMulticastAddress() const override
		{
			return ((A >= 224) && (A <= 239));
		}

		virtual operator std::string() const override
		{
			char AddressString[64];

			in_addr InAddress;
			InAddress.s_addr = htonl(Address);

			inet_ntop(AF_INET, &InAddress, AddressString, sizeof(AddressString));

			return std::string(AddressString);
		}
	};

	struct IP4EndPoint : public IPEndPoint
	{
	public:
		IP4Address Address;
		unsigned short Port;

	public:
		IP4EndPoint() : IPEndPoint(IPv4), Port(0) {}
		IP4EndPoint(const IP4Address& InAddress, unsigned short InPort) : IPEndPoint(IPv4), Address(InAddress), Port(InPort) {}

		virtual ~IP4EndPoint() {}

		bool operator==(const IP4EndPoint& Target) const
		{
			return (Address == Target.Address && Port == Target.Port);
		}

		bool operator!=(const IP4EndPoint& Target) const
		{
			return (Address != Target.Address || Port != Target.Port);
		}

		virtual operator std::string() const override
		{
			char AddressString[64];

			in_addr InAddress;
			InAddress.s_addr = htonl(Address.Address);

			inet_ntop(AF_INET, &InAddress, AddressString, sizeof(AddressString));

			std::string AddressStringType(AddressString);

			AddressStringType += ":" + std::to_string(Port);

			return AddressStringType;
		}
	};
}  // namespace Red