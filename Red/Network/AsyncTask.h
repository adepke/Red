#pragma once

#include "AsyncArgs.h"
#include <future>

namespace Red
{
	// Used to Manipulate and Query an Asynchronous Function
	class AsyncTask
	{
	protected:
		std::future<void> Handle;

	public:
		AsyncTask(std::future<void> InHandle) { Handle = std::move(InHandle); }

		void WaitForCompletion()
		{
			Handle.get();
		}

		bool IsFinished()
		{
			return Handle.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
		}

		void Abort()
		{

		}
	};
}  // namespace Red