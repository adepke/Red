/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include <string>

namespace Red
{
	struct IPAddress
	{
	public:
		virtual ~IPAddress() = 0;

	public:
		virtual bool IsLoopbackAddress() const = 0;
		virtual bool IsMulticastAddress() const = 0;

		virtual operator std::string() const = 0;
	};

	struct IPEndPoint
	{
	public:
		virtual ~IPEndPoint() = 0;

	public:
		virtual operator std::string() const = 0;
	};
}  // namespace Red