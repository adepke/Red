/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

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
		virtual bool operator==(const IPEndPoint& Target) const = 0;
		virtual bool operator!=(const IPEndPoint& Target) const = 0;

		virtual operator std::string() const = 0;
	};
}  // namespace Red