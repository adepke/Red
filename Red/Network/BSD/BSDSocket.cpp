/*
	Copyright (c) 2018 Andrew Depke
*/
#include "BSDSocket.h"

#if OS_WINDOWS
	#pragma comment(lib, "Ws2_32.lib")

	#include <Ws2tcpip.h>

	#include <memory>

	#define RED_INVALID_SOCKET INVALID_SOCKET
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <sys/ioctl.h>
	#include <string.h>  // memset()

	#define RED_INVALID_SOCKET -1
#endif

namespace Red
{
	bool BSDSocket::Initialize(const SocketDescription& InDescription)
	{
		Description = InDescription;

		int NativeType = 0;
		int NativeProtocol = 0;
		switch (InDescription.Protocol)
		{
		case SP_TCP:
			NativeType = SOCK_STREAM;
			NativeProtocol = IPPROTO_TCP;
			break;
		case SP_UDP:
			NativeType = SOCK_DGRAM;
			NativeProtocol = IPPROTO_UDP;
			break;
		case SP_IGMP:
			NativeType = SOCK_DGRAM;
			NativeProtocol = IPPROTO_IP;  // Automatically Determine Protocol
			break;
		}

		SocketHandle = socket(AF_INET, NativeType, NativeProtocol);
		if (SocketHandle == RED_INVALID_SOCKET)
		{
			return false;
		}

		return Configure();
	}

	bool BSDSocket::Shutdown()
	{
		bool Result = false;

		if (SocketHandle != RED_INVALID_SOCKET)
		{
			shutdown(SocketHandle, 2);  // SHUT_RDWR

#if OS_WINDOWS
			Result = (closesocket(SocketHandle) == 0);
#else
			Result = (close(SocketHandle) == 0);
#endif

			SocketHandle = RED_INVALID_SOCKET;
		}

		return Result;
	}

	bool BSDSocket::Connect(const IP4EndPoint& EndPoint)
	{
		if (SocketHandle != RED_INVALID_SOCKET)
		{
			sockaddr_in SocketAddress;
			SocketAddress.sin_family = AF_INET;
			SocketAddress.sin_addr.s_addr = htonl(EndPoint.Address.Address);
			SocketAddress.sin_port = htons(EndPoint.Port);

			if (connect(SocketHandle, (sockaddr*)&SocketAddress, sizeof(SocketAddress)) == 0)
			{
				return true;
			}
		}

		return false;
	}

	AsyncTask* BSDSocket::ConnectAsync(AsyncConnectArgs<std::function<void(void)>>* Args, const IP4EndPoint& EndPoint)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [&]
		{
			Args->SetResult(Connect(EndPoint));
			Args->CompletedCallback();
		}));

		return Task;
	}

	bool BSDSocket::Bind(unsigned short Port)
	{
		if (SocketHandle != RED_INVALID_SOCKET)
		{
			sockaddr_in SocketAddress;

#if OS_WINDOWS
			std::memset(&SocketAddress, 0, sizeof(SocketAddress));
#else
			memset(&SocketAddress, 0, sizeof(SocketAddress));
#endif

			SocketAddress.sin_family = AF_INET;
			SocketAddress.sin_addr.s_addr = INADDR_ANY;  // Automatically determine the private IP.
			SocketAddress.sin_port = htons(Port);

			if (bind(SocketHandle, (sockaddr*)&SocketAddress, sizeof(SocketAddress)) == 0)
			{
				return true;
			}
		}

		return false;
	}

	bool BSDSocket::Listen(int MaxBacklog)
	{
		if (SocketHandle != RED_INVALID_SOCKET)
		{
			if (listen(SocketHandle, MaxBacklog) == 0)
			{
				return true;
			}
		}

		return false;
	}

	AsyncTask* BSDSocket::ListenAsync(AsyncListenArgs<std::function<void(void)>>* Args, int MaxBacklog)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [&]
		{
			Args->SetResult(Listen(MaxBacklog));
			Args->CompletedCallback();
		}));

		return Task;
	}

	ISocket* BSDSocket::Accept(IP4EndPoint& ClientAddress)
	{
		SOCKET ClientHandle;
		sockaddr_in SocketAddress;
		int SizeSmall = sizeof(SocketAddress);

#if OS_WINDOWS
		ClientHandle = accept(SocketHandle, (sockaddr*)&SocketAddress, &SizeSmall);
#else
		ClientHandle = accept(SocketHandle, (sockaddr*)&SocketAddress, (socklen_t*)&SizeSmall);
#endif
		if (ClientHandle != RED_INVALID_SOCKET)
		{
			if (getpeername(ClientHandle, (sockaddr*)&SocketAddress, (socklen_t*)&SizeSmall) == 0)
			{
				BSDSocket* ClientSocket = new BSDSocket();

				// Do not Initialize(), as that will allocate a separate socket.
				ClientSocket->SocketHandle = ClientHandle;
				ClientSocket->Description = Description;
				ClientSocket->Description.Type = ST_Client;

				ClientSocket->Configure();

				ClientAddress = IP4EndPoint(ntohl(SocketAddress.sin_addr.s_addr), ntohs(SocketAddress.sin_port));

				return ClientSocket;
			}

			// Manually kill the created socket.
#if OS_WINDOWS
			closesocket(ClientHandle);
#else
			close(ClientHandle);
#endif
		}

		return nullptr;
	}

	AsyncTask* BSDSocket::AcceptAsync(AsyncAcceptArgs<std::function<void(void)>>* Args)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [&]
		{
			IP4EndPoint ClientAddressTemp;

			Args->SetResult(Accept(ClientAddressTemp));
			Args->SetClientAddress(ClientAddressTemp);
			Args->CompletedCallback();
		}));

		return Task;
	}

	bool BSDSocket::Send(const unsigned char* Data, unsigned int Length, int& BytesSent)
	{
		BytesSent = send(SocketHandle, (const char*)Data, Length, 0);

		return BytesSent >= 0;
	}

	bool BSDSocket::Send(const IP4EndPoint& Destination, const unsigned char* Data, unsigned int Length, int& BytesSent)
	{
		sockaddr_in SocketAddress;
		SocketAddress.sin_family = AF_INET;
		SocketAddress.sin_addr.s_addr = htonl(Destination.Address.Address);
		SocketAddress.sin_port = htons(Destination.Port);

		BytesSent = sendto(SocketHandle, (const char*)Data, Length, 0, (sockaddr*)&SocketAddress, sizeof(SocketAddress));

		return BytesSent >= 0;
	}

	AsyncTask* BSDSocket::SendAsync(AsyncSendArgs<std::function<void(void)>>* Args, const unsigned char* Data, unsigned int Length)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [&]
		{
			int BytesSentTemp;

			Args->SetResult(Send(Data, Length, BytesSentTemp));
			Args->SetBytesSent(BytesSentTemp);
			Args->CompletedCallback();
		}));

		return Task;
	}

	AsyncTask* BSDSocket::SendAsync(AsyncSendArgs<std::function<void(void)>>* Args, const IP4EndPoint& Destination, const unsigned char* Data, unsigned int Length)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [&]
		{
			int BytesSentTemp;

			Args->SetResult(Send(Destination, Data, Length, BytesSentTemp));
			Args->SetBytesSent(BytesSentTemp);
			Args->CompletedCallback();
		}));

		return Task;
	}

	bool BSDSocket::Receive(unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived)
	{
		BytesReceived = recv(SocketHandle, (char*)Data, MaxReceivingBytes, 0);

		return BytesReceived >= 0;
	}

	bool BSDSocket::Receive(IP4Address& Source, unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived)
	{
		sockaddr_in ClientAddress;
		int Size = sizeof(ClientAddress);

		BytesReceived = recvfrom(SocketHandle, (char*)Data, MaxReceivingBytes, 0, (sockaddr*)&ClientAddress, (socklen_t*)&Size);

		Source.Address = ntohl(ClientAddress.sin_addr.s_addr);

		return BytesReceived >= 0;
	}

	AsyncTask* BSDSocket::ReceiveAsync(AsyncReceiveArgs<std::function<void(void)>>* Args, unsigned int MaxReceivingBytes)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [&]
		{
			unsigned char* DataTemp;
			int BytesReceivedTemp;

			Args->SetResult(Receive(DataTemp, MaxReceivingBytes, BytesReceivedTemp));
			Args->SetData(DataTemp);
			Args->SetBytesReceived(BytesReceivedTemp);
			Args->CompletedCallback();
		}));

		return Task;
	}

	AsyncTask* BSDSocket::ReceiveAsync(AsyncReceiveFromArgs<std::function<void(void)>>* Args, unsigned int MaxReceivingBytes)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [&]
		{
			unsigned char* DataTemp;
			int BytesReceivedTemp;
			IP4Address SourceTemp;

			Args->SetResult(Receive(SourceTemp, DataTemp, MaxReceivingBytes, BytesReceivedTemp));
			Args->SetData(DataTemp);
			Args->SetBytesReceived(BytesReceivedTemp);
			Args->SetSource(SourceTemp);
			Args->CompletedCallback();
		}));

		return Task;
	}

	bool BSDSocket::JoinMulticastGroup(const IP4Address& GroupAddress)
	{
		ip_mreq Mreq;
		Mreq.imr_interface.s_addr = INADDR_ANY;
		Mreq.imr_multiaddr.s_addr = GroupAddress.Address;

		return (setsockopt(SocketHandle, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&Mreq, sizeof(Mreq)) == 0);
	}

	bool BSDSocket::LeaveMulticastGroup(const IP4Address& GroupAddress)
	{
		ip_mreq Mreq;
		Mreq.imr_interface.s_addr = INADDR_ANY;
		Mreq.imr_multiaddr.s_addr = GroupAddress.Address;

		return (setsockopt(SocketHandle, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&Mreq, sizeof(Mreq)) == 0);
	}

	bool BSDSocket::SetSendBufferSize(unsigned int Size)
	{
		return (setsockopt(SocketHandle, SOL_SOCKET, SO_SNDBUF, (char*)&Size, sizeof(Size)) == 0);
	}

	bool BSDSocket::SetReceiveBufferSize(unsigned int Size)
	{
		return (setsockopt(SocketHandle, SOL_SOCKET, SO_RCVBUF, (char*)&Size, sizeof(Size)) == 0);
	}

	IP4EndPoint BSDSocket::GetAddress()
	{
		sockaddr_in Address;
		int Size = sizeof(Address);

#if OS_WINDOWS
		if (getsockname(SocketHandle, (sockaddr*)&Address, &Size) == 0)
#else
		if (getsockname(SocketHandle, (sockaddr*)&Address, (socklen_t*)&Size) == 0)
#endif
		{
			return IP4EndPoint(ntohl(Address.sin_addr.s_addr), ntohs(Address.sin_port));
		}

		return IP4EndPoint();
	}

	IP4EndPoint BSDSocket::GetPeerAddress()
	{
		sockaddr_in Address;
		int Size = sizeof(Address);

#if OS_WINDOWS
		if (getpeername(SocketHandle, (sockaddr*)&Address, &Size) == 0)
#else
		if (getpeername(SocketHandle, (sockaddr*)&Address, (socklen_t*)&Size) == 0)
#endif
		{
			return IP4EndPoint(ntohl(Address.sin_addr.s_addr), ntohs(Address.sin_port));
		}

		return IP4EndPoint();
	}

	bool BSDSocket::Configure()
	{
		int Value = 0;

		Value = 1;
		if ((Description.Protocol == SP_TCP) && (setsockopt(SocketHandle, IPPROTO_TCP, TCP_NODELAY, (char*)&Value, sizeof(Value)) != 0))
		{
			Shutdown();

			return false;
		}

		Value = 1;
		if ((Description.Protocol == SP_TCP) && (setsockopt(SocketHandle, SOL_SOCKET, SO_KEEPALIVE, (char*)&Value, sizeof(Value)) != 0))
		{
			Shutdown();

			return false;
		}

		Value = Description.ReuseAddress ? 1 : 0;
		if ((Description.Type == ST_Server) && (setsockopt(SocketHandle, SOL_SOCKET, SO_REUSEADDR, (char*)&Value, sizeof(Value)) != 0))
		{
			Shutdown();

			return false;
		}

		if (Description.Protocol == SP_TCP)
		{
			Value = 1;
			if (Description.LingerTimeMs > 0)
			{
				linger Linger;
				Linger.l_onoff = true;
				Linger.l_linger = Description.LingerTimeMs;

				if (setsockopt(SocketHandle, SOL_SOCKET, SO_LINGER, (char*)&Linger, sizeof(Linger)) != 0)
				{
					Shutdown();

					return false;
				}
			}

			else
			{
				if (setsockopt(SocketHandle, SOL_SOCKET, ~SO_LINGER, (char*)&Value, sizeof(Value)) != 0)
				{
					Shutdown();

					return false;
				}
			}
		}

		if (Description.Protocol == SP_IGMP)
		{
			// Disable Multicast Loopback
			Value = 1;
			if (setsockopt(SocketHandle, IPPROTO_IP, IP_MULTICAST_LOOP, (char*)&Value, sizeof(Value)) != 0)
			{
				Shutdown();

				return false;
			}
		}

		return true;
	}
}  // namespace Red
