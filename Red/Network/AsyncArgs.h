#pragma once

#include "IPv4.h"

// Fix for Atomic Alignment of IP4EndPoint Error.
#define _ENABLE_ATOMIC_ALIGNMENT_FIX

#include <atomic>

namespace Red
{
	class ISocket;

	// Used to Retrieve Data from an Asynchronous Function
	template <typename CallbackType>
	class AsyncArgs
	{
	public:
		virtual ~AsyncArgs() = 0;

		CallbackType CompletedCallback;
	};

	template <typename CallbackType>
	class AsyncConnectArgs : public AsyncArgs<CallbackType>
	{
	protected:
		std::atomic<bool> Result;

	public:
		virtual ~AsyncConnectArgs() {}

		void SetResult(bool Value)
		{
			Result.store(Value);
		}

		bool GetResult()
		{
			return Result.load();
		}
	};

	template <typename CallbackType>
	class AsyncListenArgs : public AsyncArgs<CallbackType>
	{
	protected:
		std::atomic<bool> Result;

	public:
		virtual ~AsyncListenArgs() {}

		void SetResult(bool Value)
		{
			Result.store(Value);
		}

		bool GetResult()
		{
			return Result.load();
		}
	};

	template <typename CallbackType>
	class AsyncAcceptArgs : public AsyncArgs<CallbackType>
	{
	protected:
		std::atomic<ISocket*> Result;
		std::atomic<IP4EndPoint> ClientAddress;

	public:
		virtual ~AsyncAcceptArgs() {}

		void SetResult(ISocket* Value)
		{
			Result.store(Value);
		}

		ISocket* GetResult()
		{
			return Result.load();
		}

		void SetClientAddress(IP4EndPoint Value)
		{
			ClientAddress.store(Value);
		}

		IP4EndPoint GetClientAddress()
		{
			return ClientAddress.load();
		}
	};

	template <typename CallbackType>
	class AsyncSendArgs : public AsyncArgs<CallbackType>
	{
	protected:
		std::atomic<bool> Result;
		std::atomic<int> BytesSent;

	public:
		virtual ~AsyncSendArgs() {}

		void SetResult(bool Value)
		{
			Result.store(Value);
		}

		bool GetResult()
		{
			return Result.load();
		}

		void SetBytesSent(int Value)
		{
			BytesSent.store(Value);
		}

		bool GetBytesSent()
		{
			return BytesSent.load();
		}
	};

	template <typename CallbackType>
	class AsyncReceiveArgs : public AsyncArgs<CallbackType>
	{
	protected:
		std::atomic<bool> Result;
		std::atomic<unsigned char*> Data;
		std::atomic<int> BytesReceived;

	public:
		virtual ~AsyncReceiveArgs() {}

		void SetResult(bool Value)
		{
			Result.store(Value);
		}

		bool GetResult()
		{
			return Result.load();
		}

		void SetData(unsigned char* Value)
		{
			Data.store(Value);
		}

		unsigned char* GetData()
		{
			return Data.load();
		}

		void SetBytesReceived(int Value)
		{
			BytesReceived.store(Value);
		}

		int GetBytesReceived()
		{
			return BytesReceived.load();
		}
	};

	template <typename CallbackType>
	class AsyncReceiveFromArgs : public AsyncArgs<CallbackType>
	{
	protected:
		std::atomic<bool> Result;
		std::atomic<unsigned char*> Data;
		std::atomic<int> BytesReceived;
		std::atomic<IP4Address> Source;

	public:
		virtual ~AsyncReceiveFromArgs() {}

		void SetResult(bool Value)
		{
			Result.store(Value);
		}

		bool GetResult()
		{
			return Result.load();
		}

		void SetData(unsigned char* Value)
		{
			Data.store(Value);
		}

		unsigned char* GetData()
		{
			return Data.load();
		}

		void SetBytesReceived(int Value)
		{
			BytesReceived.store(Value);
		}

		int GetBytesReceived()
		{
			return BytesReceived.load();
		}

		void SetSource(IP4Address Value)
		{
			Source.store(Value);
		}

		IP4Address GetSource()
		{
			return Source.load();
		}
	};
}  // namespace Red