#pragma once

#include "IPv4.h"

// Fix for Atomic Alignment of IP4EndPoint Error.
#define _ENABLE_ATOMIC_ALIGNMENT_FIX

#include <atomic>

namespace Red
{
	class ISocket;
	class BSDSocket;

	// Used to Retrieve Data from an Asynchronous Function
	template <typename CallbackType>
	class AsyncArgs
	{
	protected:
		friend class BSDSocket;

		CallbackType CompletedCallback;

	public:
		AsyncArgs(CallbackType Callback) : CompletedCallback(Callback) {}
		virtual ~AsyncArgs() = 0;
	};

	template <typename CallbackType>
	class AsyncConnectArgs : public AsyncArgs<CallbackType>
	{
	protected:
		friend class BSDSocket;

		std::atomic<bool> Result;

	public:
		virtual ~AsyncConnectArgs() {}

		bool GetResult()
		{
			return Result.load();
		}
	};

	template <typename CallbackType>
	class AsyncListenArgs : public AsyncArgs<CallbackType>
	{
	protected:
		friend class BSDSocket;

		std::atomic<bool> Result;

	public:
		virtual ~AsyncListenArgs() {}

		bool GetResult()
		{
			return Result.load();
		}
	};

	template <typename CallbackType>
	class AsyncAcceptArgs : public AsyncArgs<CallbackType>
	{
	protected:
		friend class BSDSocket;

		std::atomic<ISocket*> Result;
		std::atomic<IP4EndPoint> ClientAddress;

	public:
		virtual ~AsyncAcceptArgs() {}

		ISocket* GetResult()
		{
			return Result.load();
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
		friend class BSDSocket;

		std::atomic<bool> Result;
		std::atomic<int> BytesSent;

	public:
		virtual ~AsyncSendArgs() {}

		bool GetResult()
		{
			return Result.load();
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
		friend class BSDSocket;

		std::atomic<bool> Result;
		std::atomic<unsigned char*> Data;
		std::atomic<int> BytesReceived;

	public:
		virtual ~AsyncReceiveArgs() {}

		bool GetResult()
		{
			return Result.load();
		}

		unsigned char* GetData()
		{
			return Data.load();
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
		friend class BSDSocket;

		std::atomic<bool> Result;
		std::atomic<unsigned char*> Data;
		std::atomic<int> BytesReceived;
		std::atomic<IP4Address> Source;

	public:
		virtual ~AsyncReceiveFromArgs() {}

		bool GetResult()
		{
			return Result.load();
		}

		unsigned char* GetData()
		{
			return Data.load();
		}

		int GetBytesReceived()
		{
			return BytesReceived.load();
		}

		IP4Address GetSource()
		{
			return Source.load();
		}
	};
}  // namespace Red