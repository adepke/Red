#pragma once

#include "../SocketSubsystemBase.h"

#include "BSDSocket.h"

namespace Red
{
	class BSDSocketSubsystem : public ISocketSubsystem
	{
	protected:
		WSAData SubsystemData;

	public:
		BSDSocketSubsystem() {}
		virtual ~BSDSocketSubsystem() {}

		virtual bool Initialize() override;
		virtual void Shutdown() override;

		// Used for creating local sockets, not ghost sockets.
		virtual ISocket* CreateSocket(const SocketDescription& InDescription) override;

		virtual std::string GetHostName() const override;
	};
}  // namespace Red