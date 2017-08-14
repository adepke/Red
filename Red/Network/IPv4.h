#pragma once

#include <vector>
#include <sstream>

struct IP4Address
{
public:
	union
	{
		// Address stored in components, maintains network byte order.
		struct
		{
#if PLATFORM_ENDIANNESS == LITTLE_ENDIAN
			unsigned char D, C, B, A;
#else
			unsigned char A, B, C, D;
#endif
		};

		// Address stored in local byte order.
		unsigned int Address;
	};

public:
	IP4Address() : Address(0) {}
	IP4Address(unsigned char InA, unsigned char InB, unsigned char InC, unsigned char InD) :
#if PLATFORM_ENDIANNESS == LITTLE_ENDIAN
		D(InD),
		C(InC),
		B(InB),
		A(InA)
#else
		A(InA),
		B(InB),
		C(InC),
		D(InD)
#endif
	{}

	IP4Address(unsigned int InAddress) : Address(InAddress) {}

	IP4Address(const char* InAddress)
	{
		std::stringstream AddressStream(InAddress);
		std::string Component;
		std::vector<unsigned char> ComponentList;

		while (std::getline(AddressStream, Component, '.'))
		{
			ComponentList.push_back((unsigned char)std::atoi(Component.c_str()));
		}

		if (ComponentList.size() > 4)
		{
			Address = 0;
		}

		else
		{
			A = ComponentList[0];
			B = ComponentList[1];
			C = ComponentList[2];
			D = ComponentList[3];
		}
	}

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
};

struct IP4EndPoint
{
public:
	IP4Address Address;
	unsigned short Port;

public:
	IP4EndPoint() : Port(0) {}
	IP4EndPoint(const IP4Address& InAddress, unsigned short InPort) : Address(InAddress), Port(InPort) {}

	bool operator==(const IP4EndPoint& Target) const
	{
		return (Address == Target.Address && Port == Target.Port);
	}

	bool operator!=(const IP4EndPoint& Target) const
	{
		return (Address != Target.Address || Port != Target.Port);
	}
};