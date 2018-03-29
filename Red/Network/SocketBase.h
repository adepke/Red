/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "IPv4.h"
#include "IPv6.h"
#include "SocketDefs.h"
#include "AsyncTask.h"
#include "AsyncArgs.h"

#include <vector>

namespace Red
{
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

		virtual bool Connect(IPEndPoint* const EndPoint) = 0;
		virtual AsyncTask* ConnectAsync(AsyncConnectArgs* Args, IPEndPoint* const EndPoint) = 0;

		// Server: Port forward through UPnP. Bind address is machine's private IP.
		virtual bool Bind(unsigned short Port) = 0;

		virtual bool Listen(int MaxBacklog) = 0;

		// Server: Accepts the first pending client in queue. The returned socket representing the connection to the client is heap-allocated. ClientAddress stores the connection's address.
		virtual ISocket* Accept(IPEndPoint* ClientAddress) = 0;
		// Server: Asynchronously accepts the first pending client in queue. The returned socket representing the connection to the client is heap-allocated. ClientAddress stores the connection's address.
		virtual AsyncTask* AcceptAsync(AsyncAcceptArgs* Args) = 0;

		// Client/Server: Transmit a buffer to the connected socket.
		virtual bool Send(const unsigned char* Data, unsigned int Length, int& BytesSent) = 0;
		// Client/Server: Transmit a buffer to a specific client or server.
		virtual bool Send(IPEndPoint* const Destination, const unsigned char* Data, unsigned int Length, int& BytesSent) = 0;
		// Client/Server: Asynchronously transmit a buffer to the connected socket.
		virtual AsyncTask* SendAsync(AsyncSendArgs* Args, const unsigned char* Data, unsigned int Length) = 0;
		// Client/Server: Asynchronously transmit a buffer to a specific client or server.
		virtual AsyncTask* SendAsync(AsyncSendArgs* Args, IPEndPoint* const Destination, const unsigned char* Data, unsigned int Length) = 0;

		// Client/Server: Copy the socket's internal receiving buffer into Data.
		virtual bool Receive(unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) = 0;
		// Client/Server: Copy the socket's internal receiving buffer into Data. Output the data's source address to Source.
		virtual bool Receive(IPAddress* Source, unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) = 0;
		// Client/Server: Asynchronously copy the socket's internal receiving buffer into Data.
		virtual AsyncTask* ReceiveAsync(AsyncReceiveArgs* Args, unsigned int MaxReceivingBytes) = 0;
		// Client/Server: Asynchronously copy the socket's internal receiving buffer into Data. Output the data's source address to Source.
		virtual AsyncTask* ReceiveAsync(AsyncReceiveFromArgs* Args, unsigned int MaxReceivingBytes) = 0;

		// Client: Join the specified multicast group.
		virtual bool JoinMulticastGroup(IPAddress* const GroupAddress) = 0;
		// Client: Leave the specified multicast group.
		virtual bool LeaveMulticastGroup(IPAddress* const GroupAddress) = 0;

		virtual bool SetSendBufferSize(unsigned int Size) = 0;
		virtual bool SetReceiveBufferSize(unsigned int Size) = 0;

		virtual bool SetSendTimeout(unsigned int TimeoutMs) = 0;
		virtual bool SetReceiveTimeout(unsigned int TimeoutMs) = 0;

		virtual bool SetBroadcastsEnabled(bool Value) = 0;

		// Server: Return the public endpoint the socket is bound to.
		virtual bool GetAddress(IPEndPoint* Output) = 0;
		// Client/Server: Return the address the socket is connected to.
		virtual bool GetPeerAddress(IPEndPoint* Output) = 0;

		SocketDescription GetDescription() const
		{
			return Description;
		}

	protected:
		// Client/Server: Updates the socket against the description. Used in Accept() to initialize sockets without constructing new sockets.
		virtual bool Configure() = 0;

	private:
		ISocket(const ISocket& Target);
		ISocket& operator=(const ISocket& Target);
	};
}  // namespace Red