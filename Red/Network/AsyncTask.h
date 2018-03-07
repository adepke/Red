#pragma once

#include "AsyncArgs.h"
#include <future>

namespace Red
{
	// Used to Manipulate and Query an Asynchronous Function
	class AsyncTask
	{
	protected:
		std::future<void(void)>* Handle;

	public:
		AsyncTask(std::future<void(void)>* InHandle) : Handle(InHandle) {}

		void WaitForCompletion()
		{
			Handle->get();
		}

		bool IsFinished()
		{
			return Handle->wait_for(std::chrono::seconds(0)) == std::future_status::ready;
		}

		void Abort()
		{

		}

		void Cleanup()
		{
			if (Handle)
			{
				delete Handle;

				Handle = nullptr;
			}
		}
	};
}  // namespace Red