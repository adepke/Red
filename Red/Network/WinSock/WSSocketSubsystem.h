#pragma once

#include "SocketSubsystem.h"

#include "WSSocket.h"

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

	virtual std::string GetHostName() const override;

	virtual int AutoBindSocket(ISocket* Socket, int MaxAttempts, int FailPortIncrement) override;
};