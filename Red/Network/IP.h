/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include <string>

namespace Red
{
	enum IPVersion
	{
		IPv4,
		IPv6,
	};

	class BSDSocket;

	struct IPAddress
	{
	protected:
		friend class BSDSocket;

		IPVersion Version;

	public:
		IPAddress(IPVersion InVersion) : Version(InVersion) {}

		virtual ~IPAddress() {}

	public:
		virtual bool IsLoopbackAddress() const = 0;
		virtual bool IsMulticastAddress() const = 0;

		virtual operator std::string() const = 0;
	};

	struct IPEndPoint
	{
	protected:
		friend class BSDSocket;

		IPVersion Version;

	public:
		IPEndPoint(IPVersion InVersion) : Version(InVersion) {}

		virtual ~IPEndPoint() {}

	public:
		virtual operator std::string() const = 0;
	};
}  // namespace Red