#include "BSDSocketSubsystem.h"

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
		Socket->Close();
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

int BSDSocketSubsystem::AutoBindSocket(ISocket* Socket, int DesiredPort, int FailPortIncrement, int MaxAttempts)
{
	if (!Socket->GetIsBound())
	{
		hostent HostEnt;

		memcpy(&HostEnt, gethostbyname(GetHostName().c_str()), sizeof(HostEnt));

		unsigned int RawAddress;
		//int A = std::atoi(HostEnt.h_addr_list[0]);
		//int B = std::atoi(HostEnt.h_addr_list[1]);
		//int C = std::atoi(HostEnt.h_addr_list[2]);
		//int D = std::atoi(HostEnt.h_addr_list[3]);
		
		memcpy(&RawAddress, HostEnt.h_addr_list, HostEnt.h_length);

		IP4Address Address(RawAddress);
		IP4EndPoint EndPoint(Address, DesiredPort);

		for (int Index = 0; Index < MaxAttempts; ++Index)
		{
			if (Socket->Bind(EndPoint))
			{
				return EndPoint.Port;
			}

			else
			{
				EndPoint = IP4EndPoint(Address, EndPoint.Port + FailPortIncrement);
			}
		}
	}

	return -1;
}
