#include "WSSocketSubsystem.h"

bool WSSocketSubsystem::Initialize()
{
	if (WSAStartup(0x0202, &SubsystemData) == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

void WSSocketSubsystem::Shutdown()
{
	WSACleanup();
}

ISocket* WSSocketSubsystem::CreateSocket(const SocketDescription& InDescription)
{
	ISocket* Socket = new WSSocket();

	Socket->Initialize(InDescription);

	return Socket;
}

int WSSocketSubsystem::BindSocket(ISocket* Socket, int MaxAttempts, int FailIncrement)
{
	if (!Socket->GetIsBound())
	{

	}

	return 0;
}
