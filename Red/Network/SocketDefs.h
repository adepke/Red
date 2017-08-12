#pragma once

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
};

struct SocketDescription
{
public:
	SocketType Type = ST_Unknown;
	SocketProtocol Protocol = SP_Unknown;
	bool ThreadBlocking = true;
	bool ReuseAddress = true;
	unsigned int LingerTimeMs = 0;
};