#pragma once

#include "Socket.h"

// API Specific Includes
#include <WinSock2.h>

class WSSocket : public ISocket
{
protected:
	SOCKET SocketHandle;

public:
	WSSocket() {}
	virtual ~WSSocket() {}

	virtual bool Initialize(const SocketDescription& InDescription) override;
	virtual void Shutdown() override;

	virtual bool Connect(const IP4EndPoint& EndPoint) override;
	virtual bool Close() override;

	virtual bool Bind(const IP4EndPoint& LocalEndPoint) override;

	virtual bool Listen(int MaxBacklog) override;

	virtual bool HasPendingConnection() override;

	virtual bool AcceptConnection(IP4EndPoint* ClientEndPoint) override;

	virtual bool Send(const IP4EndPoint& Destination, const unsigned char* Data, unsigned int Length, unsigned int& BytesSent) override;
	virtual bool Broadcast(const unsigned char* Data, unsigned int Length, unsigned int& BytesSent) override;

	virtual bool Receive(unsigned char* Data, unsigned int MaxReceivingBytes, unsigned int& BytesReceived) override;
};