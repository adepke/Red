#pragma once

#include "IPv4.h"

#include <functional>

// Fix for Atomic Alignment of IP4EndPoint Error.
#define _ENABLE_ATOMIC_ALIGNMENT_FIX

#include <atomic>

namespace Red
{
	class ISocket;
	class BSDSocket;

	class AsyncConnectArgs
	{
	protected:
		friend class BSDSocket;

		std::function<void(AsyncConnectArgs*)> CompletedCallback;

		std::atomic<bool> Result;

	public:
		AsyncConnectArgs(std::function<void(AsyncConnectArgs*)> Callback) : CompletedCallback(Callback) { }

		virtual ~AsyncConnectArgs() {}

		bool GetResult()
		{
			return Result.load();
		}
	};

	class AsyncAcceptArgs
	{
	protected:
		friend class BSDSocket;

		std::function<void(AsyncAcceptArgs*)> CompletedCallback;

		std::atomic<ISocket*> Result;
		std::atomic<IP4EndPoint> ClientAddress{ { IP4EndPoint() } };

	public:
		AsyncAcceptArgs(std::function<void(AsyncAcceptArgs*)> Callback) : CompletedCallback(Callback) { }

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

	class AsyncSendArgs
	{
	protected:
		friend class BSDSocket;

		std::function<void(AsyncSendArgs*)> CompletedCallback;

		std::atomic<bool> Result;
		std::atomic<int> BytesSent;

	public:
		AsyncSendArgs(std::function<void(AsyncSendArgs*)> Callback) : CompletedCallback(Callback) { }

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

	class AsyncReceiveArgs
	{
	protected:
		friend class BSDSocket;

		std::function<void(AsyncReceiveArgs*)> CompletedCallback;

		std::atomic<bool> Result;
		std::atomic<unsigned char*> Data;
		std::atomic<int> BytesReceived;

	public:
		AsyncReceiveArgs(std::function<void(AsyncReceiveArgs*)> Callback) : CompletedCallback(Callback) { }

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

	class AsyncReceiveFromArgs
	{
	protected:
		friend class BSDSocket;

		std::function<void(AsyncReceiveFromArgs*)> CompletedCallback;

		std::atomic<bool> Result;
		std::atomic<unsigned char*> Data;
		std::atomic<int> BytesReceived;
		std::atomic<IP4Address> Source{ { IP4Address() } };

	public:
		AsyncReceiveFromArgs(std::function<void(AsyncReceiveFromArgs*)> Callback) : CompletedCallback(Callback) { }

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