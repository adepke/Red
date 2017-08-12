#pragma once

#include "NetUtils.h"
#include "SocketDefs.h"

#include <vector>

// Generic Socket Interface
class ISocket
{
protected:
	SocketDescription Description;

public:
	ISocket() {}
	virtual ~ISocket() {}

	virtual bool Initialize(const SocketDescription& InDescription) = 0;
	virtual bool Shutdown() = 0;

	virtual bool Connect(const IP4EndPoint& EndPoint) = 0;

	// Server: Port forward through UPnP. Bind address is machine's private IP.
	virtual bool Bind(unsigned short Port) = 0;

	virtual bool Listen(int MaxBacklog) = 0;

	// Server: Accepts the first pending client in queue. The returned socket representing the connection to the client is heap-allocated. ClientAddress stores the connection's address.
	virtual ISocket* Accept(IP4Address& ClientAddress) = 0;

	// Client/Server: Transmit a buffre to the connected socket.
	virtual bool Send(const unsigned char* Data, unsigned int Length, int& BytesSent) = 0;
	// Client/Server: Transmit a buffer to a specific client or server.
	virtual bool Send(const IP4EndPoint& Destination, const unsigned char* Data, unsigned int Length, int& BytesSent) = 0;
	// Client/Server: Copy the socket's internal receiving buffer into Data.
	virtual bool Receive(unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) = 0;
	// Client/Server: Copy the socket's internal receiving buffer into Data. Output the data's source address to Source.
	virtual bool Receive(IP4Address& Source, unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) = 0;

	virtual bool SetSendBufferSize(unsigned int Size) = 0;
	virtual bool SetReceiveBufferSize(unsigned int Size) = 0;

	// Server: Return the public endpoint the socket is bound to.
	virtual IP4EndPoint GetAddress() = 0;
	// Client/Server: Return the address the socket is connected to.
	virtual IP4Address GetPeerAddress() = 0;

	SocketDescription GetDescription() const
	{
		return Description;
	}

private:
	ISocket(const ISocket& Target);
	ISocket& operator=(const ISocket& Target);
};