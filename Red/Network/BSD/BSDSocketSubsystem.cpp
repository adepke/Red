/*
	Copyright (c) 2018 Andrew Depke
*/
#include "BSDSocketSubsystem.h"

#if OS_WINDOWS
	#include <WS2tcpip.h>
#endif

namespace Red
{
	bool BSDSocketSubsystem::Initialize()
	{
#if OS_WINDOWS
		if (WSAStartup(0x0202, &SubsystemData) == SOCKET_ERROR)
		{
			return false;
		}
#endif

		return true;
	}

	void BSDSocketSubsystem::Shutdown()
	{
		for (ISocket* Socket : ManagedSockets)
		{
			Socket->Shutdown();
		}

#if OS_WINDOWS
		WSACleanup();
#endif
	}

	ISocket* BSDSocketSubsystem::CreateSocket(const SocketDescription& InDescription)
	{
		ISocket* Socket = new BSDSocket();

		if (Socket->Initialize(InDescription))
		{
			ManagedSockets.push_back(Socket);

			return Socket;
		}

		delete Socket;
		Socket = nullptr;

		return Socket;
	}

	std::string BSDSocketSubsystem::GetHostName() const
	{
		char NameBuffer[256];

		gethostname(NameBuffer, 256);

		return std::string(NameBuffer);
	}
}  // namespace Red