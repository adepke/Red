#include "WSSocket.h"

bool WSSocket::Initialize(const SocketDescription& InDescription)
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
		Close();

		return false;
	}

	if (setsockopt(SocketHandle, SOL_SOCKET, SO_DONTLINGER, (char*)&Value, sizeof(Value)) != 0)
	{
		Close();

		return false;
	}

	if (setsockopt(SocketHandle, SOL_SOCKET, SO_KEEPALIVE, (char*)&Value, sizeof(Value)) != 0)
	{
		Close();

		return false;
	}

	if ((InDescription.Type == ST_Server) && (setsockopt(SocketHandle, SOL_SOCKET, SO_REUSEADDR, (char*)&Value, sizeof(Value)) != 0))
	{
		Close();

		return false;
	}

	return true;
}

void WSSocket::Shutdown()
{
	if (SocketHandle != INVALID_SOCKET)
	{
		//shutdown(SocketHandle, );
	}
}

bool WSSocket::Connect(const IP4EndPoint& EndPoint)
{
	if (SocketHandle != INVALID_SOCKET)
	{
		sockaddr_in SocketAddress;
		SocketAddress.sin_family = AF_INET;
		SocketAddress.sin_addr.s_addr = htonl(EndPoint.Address.Address);
		SocketAddress.sin_port = htons(EndPoint.Port);

		if (connect(SocketHandle, (sockaddr*)&SocketAddress, sizeof(SocketAddress)) == 0)
		{
			ConnectionEndPoint = EndPoint;

			unsigned long Value = Description.ThreadBlocking ? 0 : 1;
			ioctlsocket(SocketHandle, FIONBIO, &Value);

			return true;
		}
	}

	return false;
}

bool WSSocket::Close()
{
	if (SocketHandle != INVALID_SOCKET)
	{
		int Error = closesocket(SocketHandle);
		SocketHandle = INVALID_SOCKET;

		return Error == 0;
	}

	return false;
}

bool WSSocket::Bind(const IP4EndPoint& LocalEndPoint)
{
	if (SocketHandle != INVALID_SOCKET)
	{
		sockaddr_in SocketAddress;
		SocketAddress.sin_family = AF_INET;
		SocketAddress.sin_addr.s_addr = htonl(LocalEndPoint.Address.Address);
		SocketAddress.sin_port = htons(LocalEndPoint.Port);

		if (bind(SocketHandle, (sockaddr*)&SocketAddress, sizeof(SocketAddress)) == 0)
		{
			IsBound = true;

			return true;
		}
	}

	IsBound = false;

	return false;
}

bool WSSocket::Listen(int MaxBacklog)
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

bool WSSocket::HasPendingConnection()
{
	// Maybe use select() to poll the sockets if thread blocking is enabled?

	return false;
}

bool WSSocket::AcceptConnection(IP4EndPoint* ClientEndPoint)
{
	SOCKET Client;
	sockaddr_in SocketAddress;
	int SizeSmall = sizeof(SocketAddress);

	if (Client = accept(SocketHandle, (sockaddr*)&SocketAddress, &SizeSmall) == 0)
	{
		if (getpeername(Client, (sockaddr*)&SocketAddress, &SizeSmall) == 0)
		{
			IP4Address ClientAddress(ntohl(SocketAddress.sin_addr.s_addr));
			if (ClientEndPoint)
			{
				*ClientEndPoint = IP4EndPoint(ClientAddress, ntohs(SocketAddress.sin_port));

				ConnectedClients.push_back(*ClientEndPoint);
			}

			else
			{
				IP4EndPoint CEndPoint(ClientAddress, ntohs(SocketAddress.sin_port));

				ConnectedClients.push_back(CEndPoint);
			}
		}
	}

	// Manually kill the client.
	closesocket(Client);

	return false;
}

bool WSSocket::Send(const IP4EndPoint& Destination, const unsigned char* Data, unsigned int Length, unsigned int& BytesSent)
{
	sockaddr_in SocketAddress;
	SocketAddress.sin_family = AF_INET;
	SocketAddress.sin_addr.s_addr = htonl(Destination.Address.Address);
	SocketAddress.sin_port = htons(Destination.Port);

	BytesSent = sendto(SocketHandle, (const char*)Data, Length, 0, (sockaddr*)&SocketAddress, sizeof(SocketAddress));

	return BytesSent >= 0;
}

bool WSSocket::Broadcast(const unsigned char* Data, unsigned int Length, unsigned int& BytesSent)
{
	bool Result = true;
	sockaddr_in SocketAddress;
	int BytesThisIteration = 0;

	for (int Iter = 0; Iter < ConnectedClients.size(); ++Iter)
	{
		SocketAddress.sin_family = AF_INET;
		SocketAddress.sin_addr.s_addr = htonl(ConnectedClients[Iter].Address.Address);
		SocketAddress.sin_port = htons(ConnectedClients[Iter].Port);

		BytesThisIteration = sendto(SocketHandle, (const char*)Data, Length, 0, (sockaddr*)&SocketAddress, sizeof(SocketAddress));

		if (BytesThisIteration < 0)
		{
			Result = false;
			continue;
		}

		BytesSent += BytesThisIteration;
	}

	return Result;
}

bool WSSocket::Receive(unsigned char* Data, unsigned int MaxReceivingBytes, unsigned int& BytesReceived)
{
	BytesReceived = recv(SocketHandle, (char*)Data, MaxReceivingBytes, 0);

	return BytesReceived >= 0;
}
