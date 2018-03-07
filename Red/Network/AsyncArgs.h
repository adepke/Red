#pragma once

#include <future>
#include <functional>

namespace Red
{
	class AsyncArgs
	{
	protected:
		template <typename Function>
		Function CompletedCallback;

	public:
		template <typename Function>
		void SetCallback(Function Callback)
		{
			CompletedCallback = Callback;
		}

		template <typename Function>
		Function& GetCallback() const
		{
			return CompletedCallback;
		}
	};
}  // namespace Red