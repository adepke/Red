#pragma once

#include <atomic>

namespace Red
{
	// Used to Retrieve Data from an Asynchronous Function
	template <typename CallbackType>
	class AsyncArgs
	{
	protected:
		friend class ISocket;

	public:
		AsyncArgs() = 0;
		virtual ~AsyncArgs() {}

		CallbackType CompletedCallback;
	};

	template <typename CallbackType>
	class AsyncConnectArgs : public AsyncArgs<CallbackType>
	{
	protected:
		std::atomic<bool> Result;

	public:
		AsyncArgs() {}
		virtual ~AsyncArgs() {}

		bool GetResult()
		{
			return Result.load();
		}
	};
}  // namespace Red