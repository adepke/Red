#pragma once

#include "SocketSubsystem.h"

#include "WSSocket.h"

// API Specific Includes
#include <WinSock2.h>

class WSSocketSubsystem : public ISocketSubsystem
{
protected:
	WSAData SubsystemData;

public:
	WSSocketSubsystem() {}
	virtual ~WSSocketSubsystem() {}

	virtual bool Initialize() override;
	virtual void Shutdown() override;

	// Used for creating local sockets, not ghost sockets.
	virtual ISocket* CreateSocket(const SocketDescription& InDescription) override;

	virtual int BindSocket(ISocket* Socket, int MaxAttempts, int FailIncrement) override;
};