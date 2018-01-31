#pragma once

#include "../../Core/Platform.h"
#include "../SocketBase.h"

// API Specific Includes
#if OS_WINDOWS
	#include <WinSock2.h>
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netinet/in.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>

	typedef int SOCKET;
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

		virtual bool Bind(unsigned short Port) override;

		virtual bool Listen(int MaxBacklog) override;

		virtual ISocket* Accept(IP4EndPoint& ClientAddress) override;

		virtual bool Send(const unsigned char* Data, unsigned int Length, int& BytesSent) override;
		virtual bool Send(const IP4EndPoint& Destination, const unsigned char* Data, unsigned int Length, int& BytesSent) override;

		virtual bool Receive(unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) override;
		virtual bool Receive(IP4Address& Source, unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived) override;

		virtual bool SetSendBufferSize(unsigned int Size) override;
		virtual bool SetReceiveBufferSize(unsigned int Size) override;

		virtual IP4EndPoint GetAddress() override;
		virtual IP4EndPoint GetPeerAddress() override;

	protected:
		virtual bool Configure() override;
	};

	typedef BSDSocket Socket;
}  // namespace Red
