#include "BSDSocket.h"

bool BSDSocket::Initialize(const SocketDescription& InDescription)
{
	Description = InDescription;

	SocketHandle = socket(PF_INET, SOCK_STREAM, InDescription.Protocol == SP_TCP ? IPPROTO_TCP : IPPROTO_UDP);
	if (SocketHandle == INVALID_SOCKET)
	{
		return false;
	}

	int Value = 1;
	if ((InDescription.Protocol == SP_TCP) && (setsockopt(SocketHandle, IPPROTO_TCP, TCP_NODELAY, (char*)&Value, sizeof(Value)) != 0))
	{
		Shutdown();

		return false;
	}

	if (setsockopt(SocketHandle, SOL_SOCKET, SO_DONTLINGER, (char*)&Value, sizeof(Value)) != 0)
	{
		Shutdown();

		return false;
	}

	if (setsockopt(SocketHandle, SOL_SOCKET, SO_KEEPALIVE, (char*)&Value, sizeof(Value)) != 0)
	{
		Shutdown();

		return false;
	}

	if ((InDescription.Type == ST_Server) && (setsockopt(SocketHandle, SOL_SOCKET, SO_REUSEADDR, (char*)&Value, sizeof(Value)) != 0))
	{
		Shutdown();

		return false;
	}

	return true;
}

bool BSDSocket::Shutdown()
{
	bool Result = false;

	if (SocketHandle != INVALID_SOCKET)
	{
		shutdown(SocketHandle, 2);  // SHUT_RDWR
		Result = (closesocket(SocketHandle) == 0);
		SocketHandle = INVALID_SOCKET;
	}

	return Result;
}

bool BSDSocket::Connect(const IP4EndPoint& EndPoint)
{
	if (SocketHandle != INVALID_SOCKET)
	{
		sockaddr_in SocketAddress;
		SocketAddress.sin_family = AF_INET;
		SocketAddress.sin_addr.s_addr = htonl(EndPoint.Address.Address);
		SocketAddress.sin_port = htons(EndPoint.Port);

		if (connect(SocketHandle, (sockaddr*)&SocketAddress, sizeof(SocketAddress)) == 0)
		{
			unsigned long Value = Description.ThreadBlocking ? 0 : 1;
			ioctlsocket(SocketHandle, FIONBIO, &Value);

			return true;
		}
	}

	return false;
}

bool BSDSocket::Bind(unsigned short Port)
{
	if (SocketHandle != INVALID_SOCKET)
	{
		sockaddr_in SocketAddress;
		ZeroMemory(&SocketAddress, sizeof(SocketAddress));
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
	if (SocketHandle != INVALID_SOCKET)
	{
		if (listen(SocketHandle, MaxBacklog) == 0)
		{
			unsigned long Value = Description.ThreadBlocking ? 0 : 1;
			ioctlsocket(SocketHandle, FIONBIO, &Value);

			return true;
		}
	}

	return false;
}

ISocket* BSDSocket::Accept(IP4Address& ClientAddress)
{
	SOCKET ClientHandle;
	sockaddr_in SocketAddress;
	int SizeSmall = sizeof(SocketAddress);

	ClientHandle = accept(SocketHandle, (sockaddr*)&SocketAddress, &SizeSmall);
	if (ClientHandle != INVALID_SOCKET)
	{
		if (getpeername(ClientHandle, (sockaddr*)&SocketAddress, &SizeSmall) == 0)
		{
			BSDSocket* ClientSocket = new BSDSocket();

			// Do not Initialize(), as that will allocate a separate socket.
			ClientSocket->SocketHandle = ClientHandle;

			ClientAddress = ntohl(SocketAddress.sin_addr.s_addr);

			return ClientSocket;
		}
	}

	// Manually kill the created socket.
	closesocket(ClientHandle);

	return nullptr;
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

bool BSDSocket::Receive(unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived)
{
	BytesReceived = recv(SocketHandle, (char*)Data, MaxReceivingBytes, 0);

	return BytesReceived >= 0;
}

bool BSDSocket::Receive(IP4Address& Source, unsigned char* Data, unsigned int MaxReceivingBytes, int& BytesReceived)
{
	sockaddr_in ClientAddress;
	int Size = sizeof(ClientAddress);
	BytesReceived = recvfrom(SocketHandle, (char*)Data, MaxReceivingBytes, 0, (sockaddr*)&ClientAddress, &Size);

	Source.Address = ntohl(ClientAddress.sin_addr.s_addr);

	return BytesReceived >= 0;
}



IP4EndPoint BSDSocket::GetAddress()
{
	sockaddr_in Address;
	int Size = sizeof(Address);

	if (getsockname(SocketHandle, (sockaddr*)&Address, &Size) == 0)
	{
		return IP4EndPoint(ntohl(Address.sin_addr.s_addr), ntohs(Address.sin_port));
	}

	return IP4EndPoint();
}

IP4Address BSDSocket::GetPeerAddress()
{
	sockaddr_in Address;
	int Size = sizeof(Address);

	if (getpeername(SocketHandle, (sockaddr*)&Address, &Size) == 0)
	{
		return IP4Address(ntohl(Address.sin_addr.s_addr));
	}

	return IP4Address();
}
