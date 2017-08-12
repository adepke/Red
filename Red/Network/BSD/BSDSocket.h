#pragma once

#include "../Socket.h"

// API Specific Includes
#include <WinSock2.h>

class BSDSocket : public ISocket
{
protected:
	SOCKET SocketHandle;

public:
	BSDSocket() {}
	virtual ~BSDSocket() {}

	virtual bool Initialize(const SocketDescription& InDescription) override;
	virtual bool Shutdown() override;

	virtual bool Connect(const IP4EndPoint& EndPoint) override;

	virtual bool Bind(unsigned short Port) override;

	virtual bool Listen(int MaxBacklog) override;

	virtual ISocket* Accept(IP4Address& ClientAddress) override;

	virtual bool Send(const unsigned char* Data, unsigned int Length, int& BytesSent) override;
	virtual bool Send(const IP4EndPoint& Destination, const unsigned char* Data, unsigned int Length, int& BytesSent) override;

	virtual bool Receive(unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) override;
	virtual bool Receive(IP4Address& Source, unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) override;

	virtual bool SetSendBufferSize(unsigned int Size) override;
	virtual bool SetReceiveBufferSize(unsigned int Size) override;

	virtual IP4EndPoint GetAddress() override;
	virtual IP4Address GetPeerAddress() override;
};