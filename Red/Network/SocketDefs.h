/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

namespace Red
{
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
		SocketType Type = ST_Unknown;
		SocketProtocol Protocol = SP_Unknown;
		bool ReuseAddress = true;
		unsigned int LingerTimeMs = 0;
	};
}  // namespace Red