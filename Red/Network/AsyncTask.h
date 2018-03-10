/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "AsyncArgs.h"
#include <future>

namespace Red
{
	// Forward Declare the Socket Interface
	class ISocket;

	// Used to Manipulate and Query an Asynchronous Function
	class AsyncTask
	{
	protected:
		std::future<void> Handle;
		ISocket* Sock;

	public:
		AsyncTask(std::future<void> InHandle, ISocket* InSock) : Sock(InSock) { Handle = std::move(InHandle); }

		void WaitForCompletion()
		{
			Handle.get();
		}

		bool IsFinished()
		{
			return Handle.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
		}

		// Immediately Cancel the Task. This Will Result in the Socket being Shutdown.
		void Abort();
	};
}  // namespace Red