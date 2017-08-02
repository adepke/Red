#pragma once

#include "NetUtils.h"
#include "SocketDefs.h"

#include <vector>

// Generic Socket Interface
class ISocket
{
protected:
	SocketDescription Description;

	// Client
	IP4EndPoint ConnectionEndPoint;
	// Server
	std::vector<IP4EndPoint> ConnectedClients;

	// Server: If the socket is bound to a local address and port.
	bool IsBound;

public:
	ISocket() : ConnectionEndPoint(IP4EndPoint(IP4Address(nullptr), 0)) {}
	virtual ~ISocket() {}

	virtual bool Initialize(const SocketDescription& InDescription) = 0;
	virtual void Shutdown() = 0;

	virtual bool Connect(const IP4EndPoint& EndPoint) = 0;

	// Client/Server: Terminate all connections and stop listening.
	virtual bool Close() = 0;

	// Server: Bind to a local address and port number for listening.
	virtual bool Bind(const IP4EndPoint& LocalEndPoint) = 0;

	virtual bool Listen(int MaxBacklog) = 0;

	virtual bool HasPendingConnection() = 0;

	virtual bool AcceptConnection(IP4EndPoint* ClientEndPoint) = 0;

	// Client/Server: Transmit a buffer to a specific client or server.
	virtual bool Send(const IP4EndPoint& Destination, const unsigned char* Data, unsigned int Length, unsigned int& BytesSent) = 0;
	// Server: Transmit a buffer to all connected clients.
	virtual bool Broadcast(const unsigned char* Data, unsigned int Length, unsigned int& BytesSent) = 0;
	// Client/Server: Copy the socket's internal receiving buffer into Data.
	virtual bool Receive(unsigned char* Data, unsigned int MaxReceivingBytes, unsigned int& BytesReceived) = 0;

	SocketDescription GetDescription() const
	{
		return Description;
	}

	IP4EndPoint GetConnectionEndPoint() const
	{
		return ConnectionEndPoint;
	}

	std::vector<IP4EndPoint> GetConnectedClients() const
	{
		return ConnectedClients;
	}

	bool GetIsBound() const
	{
		return IsBound;
	}
};