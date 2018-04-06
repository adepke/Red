/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "../../Core/Platform.h"
#include "../SocketBase.h"


#if !OS_WINDOWS
	typedef int SOCKET;
#else
	#include <WinSock2.h>
#endif

namespace Red
{
	class BSDSocket : public ISocket
	{
	protected:
		SOCKET SocketHandle;

	public:
		BSDSocket() {}
		virtual ~BSDSocket() {}

		virtual bool Initialize(const SocketDescription& InDescription) override;
		virtual bool Shutdown() override;

		virtual bool Connect(IPEndPoint* const EndPoint) override;
		virtual AsyncTask* ConnectAsync(AsyncConnectArgs* Args, IPEndPoint* const EndPoint) override;

		virtual bool Bind(unsigned short Port) override;

		virtual bool Listen(int MaxBacklog) override;

		virtual ISocket* Accept(IPEndPoint* ClientAddress) override;
		virtual AsyncTask* AcceptAsync(AsyncAcceptArgs* Args) override;

		virtual bool Send(const unsigned char* Data, unsigned int Length, int& BytesSent) override;
		virtual bool Send(IPEndPoint* const Destination, const unsigned char* Data, unsigned int Length, int& BytesSent) override;
		virtual AsyncTask* SendAsync(AsyncSendArgs* Args, const unsigned char* Data, unsigned int Length) override;
		virtual AsyncTask* SendAsync(AsyncSendArgs* Args, IPEndPoint* const Destination, const unsigned char* Data, unsigned int Length) override;

		virtual bool Receive(unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) override;
		virtual bool Receive(IPAddress* Source, unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) override;
		virtual AsyncTask* ReceiveAsync(AsyncReceiveArgs* Args, unsigned int MaxReceivingBytes) override;
		virtual AsyncTask* ReceiveAsync(AsyncReceiveFromArgs* Args, unsigned int MaxReceivingBytes) override;

		virtual bool JoinMulticastGroup(IPAddress* const GroupAddress) override;
		virtual bool LeaveMulticastGroup(IPAddress* const GroupAddress) override;

		virtual bool SetSendBufferSize(unsigned int Size) override;
		virtual bool SetReceiveBufferSize(unsigned int Size) override;

		virtual bool SetSendTimeout(unsigned int TimeoutMs) override;
		virtual bool SetReceiveTimeout(unsigned int TimeoutMs) override;

		virtual bool SetBroadcastsEnabled(bool Value) override;

		virtual bool GetAddress(IPEndPoint* Output) override;
		virtual bool GetPeerAddress(IPEndPoint* Output) override;

	protected:
		virtual bool Configure() override;
	};

	typedef BSDSocket Socket;
}  // namespace Red
