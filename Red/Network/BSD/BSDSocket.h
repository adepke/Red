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

		virtual bool Connect(const IP4EndPoint& EndPoint) override;
		virtual AsyncTask* ConnectAsync(AsyncConnectArgs* Args, const IP4EndPoint& EndPoint) override;

		virtual bool Bind(unsigned short Port) override;

		virtual bool Listen(int MaxBacklog) override;

		virtual ISocket* Accept(IP4EndPoint& ClientAddress) override;
		virtual AsyncTask* AcceptAsync(AsyncAcceptArgs* Args) override;

		virtual bool Send(const unsigned char* Data, unsigned int Length, int& BytesSent) override;
		virtual bool Send(const IP4EndPoint& Destination, const unsigned char* Data, unsigned int Length, int& BytesSent) override;
		virtual AsyncTask* SendAsync(AsyncSendArgs* Args, const unsigned char* Data, unsigned int Length) override;
		virtual AsyncTask* SendAsync(AsyncSendArgs* Args, const IP4EndPoint& Destination, const unsigned char* Data, unsigned int Length) override;

		virtual bool Receive(unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) override;
		virtual bool Receive(IP4Address& Source, unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) override;
		virtual AsyncTask* ReceiveAsync(AsyncReceiveArgs* Args, unsigned int MaxReceivingBytes) override;
		virtual AsyncTask* ReceiveAsync(AsyncReceiveFromArgs* Args, unsigned int MaxReceivingBytes) override;

		virtual bool JoinMulticastGroup(const IP4Address& GroupAddress) override;
		virtual bool LeaveMulticastGroup(const IP4Address& GroupAddress) override;

		virtual bool SetSendBufferSize(unsigned int Size) override;
		virtual bool SetReceiveBufferSize(unsigned int Size) override;

		virtual bool SetSendTimeout(unsigned int TimeoutMs) override;
		virtual bool SetReceiveTimeout(unsigned int TimeoutMs) override;

		virtual bool SetBroadcastsEnabled(bool Value) override;

		virtual IP4EndPoint GetAddress() override;
		virtual IP4EndPoint GetPeerAddress() override;

	protected:
		virtual bool Configure() override;
	};

	typedef BSDSocket Socket;
}  // namespace Red
