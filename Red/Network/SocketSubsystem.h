#pragma once

#include "Socket.h"

#include <string>

// Generic Socket Subsystem Interface
class ISocketSubsystem
{
public:
	ISocketSubsystem() {}
	virtual ~ISocketSubsystem() {}

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;

	virtual ISocket* CreateSocket(const SocketDescription& InDescription) = 0;
	virtual bool DestroySocket(ISocket* Socket)
	{
		bool Result = Socket->Close();
		Socket->Shutdown();

		return Result;
	}

	virtual std::string GetHostName() const = 0;

	// Automatically determines a local address and port, then binds the given socket to it. Returns port, 0 on failure.
	virtual int AutoBindSocket(ISocket* Socket, int MaxAttempts, int FailPortIncrement) = 0;
};