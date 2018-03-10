/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "SocketBase.h"

#include <string>

namespace Red
{
	// Generic Socket Subsystem Interface
	class ISocketSubsystem
	{
	protected:
		std::vector<ISocket*> ManagedSockets;

	public:
		ISocketSubsystem() {}
		virtual ~ISocketSubsystem() {}

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual ISocket* CreateSocket(const SocketDescription& InDescription) = 0;

		virtual std::string GetHostName() const = 0;
	};
}  // namespace Red