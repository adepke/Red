/*
	Copyright (c) 2017-2018 Andrew Depke
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
		default:
			NativeType = SOCK_RAW;
			NativeProtocol = IPPROTO_IP;
			break;
		}

		SocketHandle = socket(InDescription.Version == SV_IPv4 ? AF_INET : AF_INET6, NativeType, NativeProtocol);
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

	bool BSDSocket::Connect(IPEndPoint* const EndPoint)
	{
		if (SocketHandle != RED_INVALID_SOCKET)
		{
			if (Description.Version == SV_IPv4)
			{
				const IP4EndPoint* const EndPoint4 = static_cast<IP4EndPoint*>(EndPoint);

				sockaddr_in SocketAddress;
				SocketAddress.sin_family = AF_INET;
				SocketAddress.sin_addr.s_addr = htonl(EndPoint4->Address.Address);
				SocketAddress.sin_port = htons(EndPoint4->Port);

				if (connect(SocketHandle, (sockaddr*)&SocketAddress, sizeof(SocketAddress)) == 0)
				{
					return true;
				}
			}

			else
			{
				const IP6EndPoint* const EndPoint6 = static_cast<IP6EndPoint*>(EndPoint);

				sockaddr_in6 SocketAddress;
				SocketAddress.sin6_family = AF_INET6;
				SocketAddress.sin6_addr = EndPoint6->Address.Address.sin6_addr;
				SocketAddress.sin6_port = htons(EndPoint6->Port);

				if (connect(SocketHandle, (sockaddr*)&SocketAddress, sizeof(SocketAddress)) == 0)
				{
					return true;
				}
			}
		}

		return false;
	}

	AsyncTask* BSDSocket::ConnectAsync(AsyncConnectArgs* Args, IPEndPoint* const EndPoint)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [=]
		{
			Args->Result.store(Connect(EndPoint));
			Args->CompletedCallback(Args);
		}), this);

		return Task;
	}

	bool BSDSocket::Bind(unsigned short Port)
	{
		if (SocketHandle != RED_INVALID_SOCKET)
		{
			if (Description.Version == SV_IPv4)
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

			else
			{
				sockaddr_in6 SocketAddress;

#if OS_WINDOWS
				std::memset(&SocketAddress, 0, sizeof(SocketAddress));
#else
				memset(&SocketAddress, 0, sizeof(SocketAddress));
#endif

				SocketAddress.sin6_family = AF_INET;
				SocketAddress.sin6_addr = in6addr_any;  // Automatically determine the private IP.
				SocketAddress.sin6_port = htons(Port);

				if (bind(SocketHandle, (sockaddr*)&SocketAddress, sizeof(SocketAddress)) == 0)
				{
					return true;
				}
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

	ISocket* BSDSocket::Accept(IPEndPoint* ClientAddress)
	{
		if (Description.Version == SV_IPv4)
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

					if (ClientAddress)
					{
						*ClientAddress = IP4EndPoint(ntohl(SocketAddress.sin_addr.s_addr), ntohs(SocketAddress.sin_port));
					}

					return ClientSocket;
				}

				// Manually kill the created socket.
#if OS_WINDOWS
				closesocket(ClientHandle);
#else
				close(ClientHandle);
#endif
			}
		}

		else
		{
			SOCKET ClientHandle;
			sockaddr_in6 SocketAddress;
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

					if (ClientAddress)
					{
						*ClientAddress = IP6EndPoint(SocketAddress, ntohs(SocketAddress.sin6_port));
					}
					
					return ClientSocket;
				}

				// Manually kill the created socket.
#if OS_WINDOWS
				closesocket(ClientHandle);
#else
				close(ClientHandle);
#endif
			}
		}

		return nullptr;
	}

	AsyncTask* BSDSocket::AcceptAsync(AsyncAcceptArgs* Args)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [=]
		{
			if (Description.Version == SV_IPv4)
			{
				IP4EndPoint ClientAddressTemp;

				Args->SetResult(Accept(&ClientAddressTemp));
				Args->SetClientAddress(ClientAddressTemp);
			}

			else
			{
				IP6EndPoint ClientAddressTemp;

				Args->SetResult(Accept(&ClientAddressTemp));
				Args->SetClientAddress(ClientAddressTemp);
			}

			Args->CompletedCallback(Args);
		}), this);

		return Task;
	}

	bool BSDSocket::Send(const unsigned char* Data, unsigned int Length, int& BytesSent)
	{
		BytesSent = send(SocketHandle, (const char*)Data, Length, 0);

		return BytesSent >= 0;
	}

	bool BSDSocket::Send(IPEndPoint* const Destination, const unsigned char* Data, unsigned int Length, int& BytesSent)
	{
		if (Description.Version == SV_IPv4)
		{
			const IP4EndPoint* const EndPoint4 = static_cast<IP4EndPoint*>(Destination);

			sockaddr_in SocketAddress;
			SocketAddress.sin_family = AF_INET;
			SocketAddress.sin_addr.s_addr = htonl(EndPoint4->Address.Address);
			SocketAddress.sin_port = htons(EndPoint4->Port);

			BytesSent = sendto(SocketHandle, (const char*)Data, Length, 0, (sockaddr*)&SocketAddress, sizeof(SocketAddress));

			return BytesSent >= 0;
		}

		else
		{
			const IP6EndPoint* const EndPoint6 = static_cast<IP6EndPoint*>(Destination);

			sockaddr_in6 SocketAddress;
			SocketAddress.sin6_family = AF_INET;
			SocketAddress.sin6_addr = EndPoint6->Address.Address.sin6_addr;
			SocketAddress.sin6_port = htons(EndPoint6->Port);

			BytesSent = sendto(SocketHandle, (const char*)Data, Length, 0, (sockaddr*)&SocketAddress, sizeof(SocketAddress));

			return BytesSent >= 0;
		}
	}

	AsyncTask* BSDSocket::SendAsync(AsyncSendArgs* Args, const unsigned char* Data, unsigned int Length)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [=]
		{
			int BytesSentTemp;

			Args->SetResult(Send(Data, Length, BytesSentTemp));
			Args->SetBytesSent(BytesSentTemp);
			Args->CompletedCallback(Args);
		}), this);

		return Task;
	}

	AsyncTask* BSDSocket::SendAsync(AsyncSendArgs* Args, IPEndPoint* const Destination, const unsigned char* Data, unsigned int Length)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [=]
		{
			int BytesSentTemp;

			Args->SetResult(Send(Destination, Data, Length, BytesSentTemp));
			Args->SetBytesSent(BytesSentTemp);
			Args->CompletedCallback(Args);
		}), this);

		return Task;
	}

	bool BSDSocket::Receive(unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived)
	{
		BytesReceived = recv(SocketHandle, (char*)Data, MaxReceivingBytes, 0);

		return BytesReceived >= 0;
	}

	bool BSDSocket::Receive(IPAddress* Source, unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived)
	{
		if (Description.Version == SV_IPv4)
		{
			IP4Address* Address4 = static_cast<IP4Address*>(Source);

			sockaddr_in ClientAddress;
			int Size = sizeof(ClientAddress);

			BytesReceived = recvfrom(SocketHandle, (char*)Data, MaxReceivingBytes, 0, (sockaddr*)&ClientAddress, (socklen_t*)&Size);

			Address4->Address = ntohl(ClientAddress.sin_addr.s_addr);

			return BytesReceived >= 0;
		}

		else
		{
			IP6Address* Address6 = static_cast<IP6Address*>(Source);

			sockaddr_in6 ClientAddress;
			int Size = sizeof(ClientAddress);

			BytesReceived = recvfrom(SocketHandle, (char*)Data, MaxReceivingBytes, 0, (sockaddr*)&ClientAddress, (socklen_t*)&Size);

			Address6->Address = ClientAddress;

			return BytesReceived >= 0;
		}
	}

	AsyncTask* BSDSocket::ReceiveAsync(AsyncReceiveArgs* Args, unsigned int MaxReceivingBytes)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [=]
		{
			unsigned char* DataTemp = new unsigned char[MaxReceivingBytes];
			int BytesReceivedTemp;

			Args->SetResult(Receive(DataTemp, MaxReceivingBytes, BytesReceivedTemp));
			Args->SetData(DataTemp, MaxReceivingBytes);
			Args->SetBytesReceived(BytesReceivedTemp);
			Args->CompletedCallback(Args);

			delete[] DataTemp;
		}), this);

		return Task;
	}

	AsyncTask* BSDSocket::ReceiveAsync(AsyncReceiveFromArgs* Args, unsigned int MaxReceivingBytes)
	{
		AsyncTask* Task = new AsyncTask(std::async(std::launch::async, [=]
		{
			if (Description.Version == SV_IPv4)
			{
				unsigned char* DataTemp = new unsigned char[MaxReceivingBytes];
				int BytesReceivedTemp;
				IP4Address SourceTemp;

				Args->SetResult(Receive(&SourceTemp, DataTemp, MaxReceivingBytes, BytesReceivedTemp));
				Args->SetData(DataTemp, MaxReceivingBytes);
				Args->SetBytesReceived(BytesReceivedTemp);
				Args->SetSource(SourceTemp);

				delete[] DataTemp;
			}

			else
			{
				unsigned char* DataTemp = new unsigned char[MaxReceivingBytes];
				int BytesReceivedTemp;
				IP6Address SourceTemp;

				Args->SetResult(Receive(&SourceTemp, DataTemp, MaxReceivingBytes, BytesReceivedTemp));
				Args->SetData(DataTemp, MaxReceivingBytes);
				Args->SetBytesReceived(BytesReceivedTemp);
				Args->SetSource(SourceTemp);

				delete[] DataTemp;
			}

			Args->CompletedCallback(Args);
		}), this);

		return Task;
	}

	bool BSDSocket::JoinMulticastGroup(IPAddress* const GroupAddress)
	{
		if (Description.Version == SV_IPv4)
		{
			const IP4Address* const Address4 = static_cast<IP4Address*>(GroupAddress);

			ip_mreq Mreq;
			Mreq.imr_interface.s_addr = INADDR_ANY;
			Mreq.imr_multiaddr.s_addr = Address4->Address;

			return (setsockopt(SocketHandle, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&Mreq, sizeof(Mreq)) == 0);
		}

		else
		{
			const IP6Address* const Address6 = static_cast<IP6Address*>(GroupAddress);

			ipv6_mreq Mreq;
			Mreq.ipv6mr_interface = INADDR_ANY;
			Mreq.ipv6mr_multiaddr = Address6->Address.sin6_addr;

			return (setsockopt(SocketHandle, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&Mreq, sizeof(Mreq)) == 0);
		}
	}

	bool BSDSocket::LeaveMulticastGroup(IPAddress* const GroupAddress)
	{
		if (Description.Version == SV_IPv4)
		{
			const IP4Address* const Address4 = static_cast<IP4Address*>(GroupAddress);

			ip_mreq Mreq;
			Mreq.imr_interface.s_addr = INADDR_ANY;
			Mreq.imr_multiaddr.s_addr = Address4->Address;

			return (setsockopt(SocketHandle, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&Mreq, sizeof(Mreq)) == 0);
		}

		else
		{
			const IP6Address* const Address6 = static_cast<IP6Address*>(GroupAddress);

			ipv6_mreq Mreq;
			Mreq.ipv6mr_interface = INADDR_ANY;
			Mreq.ipv6mr_multiaddr = Address6->Address.sin6_addr;

			return (setsockopt(SocketHandle, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&Mreq, sizeof(Mreq)) == 0);
		}
	}

	bool BSDSocket::SetSendBufferSize(unsigned int Size)
	{
		return (setsockopt(SocketHandle, SOL_SOCKET, SO_SNDBUF, (char*)&Size, sizeof(Size)) == 0);
	}

	bool BSDSocket::SetReceiveBufferSize(unsigned int Size)
	{
		return (setsockopt(SocketHandle, SOL_SOCKET, SO_RCVBUF, (char*)&Size, sizeof(Size)) == 0);
	}

	bool BSDSocket::SetSendTimeout(unsigned int TimeoutMs)
	{
		return (setsockopt(SocketHandle, SOL_SOCKET, SO_SNDTIMEO, (char*)&TimeoutMs, sizeof(TimeoutMs)) == 0);
	}

	bool BSDSocket::SetReceiveTimeout(unsigned int TimeoutMs)
	{
		return (setsockopt(SocketHandle, SOL_SOCKET, SO_RCVTIMEO, (char*)&TimeoutMs, sizeof(TimeoutMs)) == 0);
	}

	bool BSDSocket::SetBroadcastsEnabled(bool Value)
	{
		return (setsockopt(SocketHandle, SOL_SOCKET, SO_BROADCAST, (char*)&Value, sizeof(Value)) == 0);
	}

	bool BSDSocket::GetAddress(IPEndPoint* Output)
	{
		if (!Output)
		{
			return false;
		}

		if (Description.Version == SV_IPv4)
		{
			sockaddr_in Address;
			int Size = sizeof(Address);

			if (getsockname(SocketHandle, (sockaddr*)&Address, (socklen_t*)&Size) == 0)
			{
				*Output = IP4EndPoint(ntohl(Address.sin_addr.s_addr), ntohs(Address.sin_port));

				return true;
			}
		}

		else
		{
			sockaddr_in6 Address;
			int Size = sizeof(Address);

			if (getsockname(SocketHandle, (sockaddr*)&Address, (socklen_t*)&Size) == 0)
			{
				*Output = IP6EndPoint(Address, ntohs(Address.sin6_port));

				return true;
			}
		}

		return false;
	}

	bool BSDSocket::GetPeerAddress(IPEndPoint* Output)
	{
		if (!Output)
		{
			return false;
		}

		if (Description.Version == SV_IPv4)
		{
			sockaddr_in Address;
			int Size = sizeof(Address);

			if (getpeername(SocketHandle, (sockaddr*)&Address, (socklen_t*)&Size) == 0)
			{
				*Output = IP4EndPoint(ntohl(Address.sin_addr.s_addr), ntohs(Address.sin_port));

				return true;
			}
		}

		else
		{
			sockaddr_in6 Address;
			int Size = sizeof(Address);

			if (getpeername(SocketHandle, (sockaddr*)&Address, (socklen_t*)&Size) == 0)
			{
				*Output = IP6EndPoint(Address, ntohs(Address.sin6_port));

				return true;
			}
		}
		
		return false;
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
				Linger.l_linger = Description.LingerTimeMs / 1000;

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
