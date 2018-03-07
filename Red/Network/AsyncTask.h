#pragma once

#include "AsyncArgs.h"
#include <future>

namespace Red
{
	class AsyncTask
	{
	protected:
		std::future<void(void)> Handle;

	public:
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