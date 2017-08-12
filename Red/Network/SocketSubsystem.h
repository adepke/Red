#pragma once

#include "Socket.h"

#include <string>

// Generic Socket Subsystem Interface
class ISocketSubsystem
{
protected:
	std::vector<ISocket*> ManagedSockets;

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
};