#include "BSDSocketSubsystem.h"

#include <WS2tcpip.h>

bool BSDSocketSubsystem::Initialize()
{
	if (WSAStartup(0x0202, &SubsystemData) == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

void BSDSocketSubsystem::Shutdown()
{
	for (ISocket* Socket : ManagedSockets)
	{
		Socket->Shutdown();
	}

	WSACleanup();
}

ISocket* BSDSocketSubsystem::CreateSocket(const SocketDescription& InDescription)
{
	ISocket* Socket = new BSDSocket();

	Socket->Initialize(InDescription);

	ManagedSockets.push_back(Socket);

	return Socket;
}

std::string BSDSocketSubsystem::GetHostName() const
{
	char NameBuffer[256];

	gethostname(NameBuffer, 256);

	return std::string(NameBuffer);
}
