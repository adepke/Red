/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

namespace Red
{
	enum SocketVersion
	{
		SV_IPv4,
		SV_IPv6,
	};

	enum SocketType
	{
		ST_Unknown,
		ST_Client,
		ST_Server,
		ST_Both,
	};

	enum SocketProtocol
	{
		SP_Unknown,
		SP_TCP,
		SP_UDP,
		SP_IGMP,
	};

	struct SocketDescription
	{
	public:
		SocketVersion Version = SV_IPv4;
		SocketType Type = ST_Unknown;
		SocketProtocol Protocol = SP_Unknown;
		bool ReuseAddress = true;
		unsigned int LingerTimeMs = 0;
	};
}  // namespace Red