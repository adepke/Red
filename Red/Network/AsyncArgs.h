/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "../Core/Platform.h"

#include "IPv4.h"
#include "IPv6.h"

#include <functional>

#if OS_WINDOWS
	#include <cstring>  // memcpy()
#else
	#include <string.h>
#endif

#include "../Thread/CriticalSection.h"

namespace Red
{
	class ISocket;
	class BSDSocket;

	// The "*Args" Classes Are RAII-Based Wrappers With Thread Protection for Managing Data Flow Between Async Operations

	class AsyncConnectArgs
	{
	protected:
		friend class BSDSocket;

		CriticalSection Lock;

		std::function<void(AsyncConnectArgs*)> CompletedCallback;

		bool Result;

		void SetResult(bool Value)
		{
			Lock.Lock();

			Result = Value;

			Lock.Unlock();
		}

	public:
		AsyncConnectArgs(std::function<void(AsyncConnectArgs*)> Callback) : CompletedCallback(Callback) { }

		virtual ~AsyncConnectArgs() {}

		bool GetResult()
		{
			Lock.Lock();

			auto ResultImage = Result;

			Lock.Unlock();

			return ResultImage;
		}
	};

	class AsyncAcceptArgs
	{
	protected:
		friend class BSDSocket;

		CriticalSection Lock;

		std::function<void(AsyncAcceptArgs*)> CompletedCallback;

		ISocket* Result;
		IPEndPoint* ClientAddress;  // Internally Managed Buffer

		void SetResult(ISocket* Value)
		{
			Lock.Lock();

			Result = Value;

			Lock.Unlock();
		}

		void SetClientAddress(IP4EndPoint Value)
		{
			Lock.Lock();

			if (!ClientAddress)
			{
				ClientAddress = new IP4EndPoint;
			}

			*ClientAddress = Value;

			Lock.Unlock();
		}

		void SetClientAddress(IP6EndPoint Value)
		{
			Lock.Lock();

			if (!ClientAddress)
			{
				ClientAddress = new IP6EndPoint;
			}

			*ClientAddress = Value;

			Lock.Unlock();
		}

	public:
		AsyncAcceptArgs(std::function<void(AsyncAcceptArgs*)> Callback) : CompletedCallback(Callback) { }

		virtual ~AsyncAcceptArgs()
		{
			if (ClientAddress)
			{
				delete ClientAddress;

				ClientAddress = nullptr;
			}
		}

		ISocket* GetResult()
		{
			Lock.Lock();

			auto ResultImage = Result;

			Lock.Unlock();

			return ResultImage;
		}

		IPEndPoint* GetClientAddress()
		{
			Lock.Lock();

			auto ClientAddressImage = ClientAddress;

			Lock.Unlock();

			return ClientAddressImage;
		}
	};

	class AsyncSendArgs
	{
	protected:
		friend class BSDSocket;

		CriticalSection Lock;

		std::function<void(AsyncSendArgs*)> CompletedCallback;

		bool Result;
		int BytesSent;

		void SetResult(bool Value)
		{
			Lock.Lock();

			Result = Value;

			Lock.Unlock();
		}

		void SetBytesSent(int Value)
		{
			Lock.Lock();

			BytesSent = Value;

			Lock.Unlock();
		}

	public:
		AsyncSendArgs(std::function<void(AsyncSendArgs*)> Callback) : CompletedCallback(Callback) { }

		virtual ~AsyncSendArgs() {}

		bool GetResult()
		{
			Lock.Lock();

			auto ResultImage = Result;

			Lock.Unlock();

			return ResultImage;
		}

		bool GetBytesSent()
		{
			Lock.Lock();

			auto BytesSentImage = BytesSent;

			Lock.Unlock();

			return BytesSentImage;
		}
	};

	class AsyncReceiveArgs
	{
	protected:
		friend class BSDSocket;

		CriticalSection Lock;

		std::function<void(AsyncReceiveArgs*)> CompletedCallback;

		bool Result;
		unsigned char* Data;  // Internally Managed Buffer
		int BytesReceived;

		void SetResult(bool Value)
		{
			Lock.Lock();

			Result = Value;

			Lock.Unlock();
		}

		void SetData(unsigned char* Value, int Size)
		{
			Lock.Lock();

			if (!Data)
			{
				Data = new unsigned char[Size];
			}

#if OS_WINDOWS
			std::memcpy(Data, Value, Size);
#else
			memcpy(Data, Value, Size);
#endif

			Lock.Unlock();
		}

		void SetBytesReceived(int Value)
		{
			Lock.Lock();

			BytesReceived = Value;

			Lock.Unlock();
		}

	public:
		AsyncReceiveArgs(std::function<void(AsyncReceiveArgs*)> Callback) : CompletedCallback(Callback) { }

		virtual ~AsyncReceiveArgs()
		{
			if (Data)
			{
				delete[] Data;

				Data = nullptr;
			}
		}

		bool GetResult()
		{
			Lock.Lock();

			auto ResultImage = Result;

			Lock.Unlock();

			return ResultImage;
		}

		unsigned char* GetData()
		{
			Lock.Lock();

			auto DataImage = Data;

			Lock.Unlock();

			return DataImage;
		}

		int GetBytesReceived()
		{
			Lock.Lock();

			auto BytesReceivedImage = BytesReceived;

			Lock.Unlock();

			return BytesReceivedImage;
		}
	};

	class AsyncReceiveFromArgs
	{
	protected:
		friend class BSDSocket;

		CriticalSection Lock;

		std::function<void(AsyncReceiveFromArgs*)> CompletedCallback;

		bool Result;
		unsigned char* Data;  // Internally Managed Buffer
		int BytesReceived;
		IPAddress* Source;  // Internally Managed Buffer

		void SetResult(bool Value)
		{
			Lock.Lock();

			Lock.Unlock();
		}

		void SetData(unsigned char* Value, int Size)
		{
			Lock.Lock();

			if (!Data)
			{
				Data = new unsigned char[Size];
			}

#if OS_WINDOWS
			std::memcpy(Data, Value, Size);
#else
			memcpy(Data, Value, Size);
#endif

			Lock.Unlock();
		}

		void SetBytesReceived(int Value)
		{
			Lock.Lock();

			Lock.Unlock();
		}

		void SetSource(IP4Address Value)
		{
			Lock.Lock();

			if (!Source)
			{
				Source = new IP4Address;
			}

			*Source = Value;

			Lock.Unlock();
		}

		void SetSource(IP6Address Value)
		{
			Lock.Lock();

			if (!Source)
			{
				Source = new IP6Address;
			}

			*Source = Value;

			Lock.Unlock();
		}

	public:
		AsyncReceiveFromArgs(std::function<void(AsyncReceiveFromArgs*)> Callback) : CompletedCallback(Callback) { }

		virtual ~AsyncReceiveFromArgs()
		{
			if (Data)
			{
				delete[] Data;

				Data = nullptr;
			}

			if (Source)
			{
				delete Source;

				Source = nullptr;
			}
		}

		bool GetResult()
		{
			Lock.Lock();

			auto ResultImage = Result;

			Lock.Unlock();

			return ResultImage;
		}

		unsigned char* GetData()
		{
			Lock.Lock();

			auto DataImage = Data;

			Lock.Unlock();

			return DataImage;
		}

		int GetBytesReceived()
		{
			Lock.Lock();

			auto BytesReceivedImage = BytesReceived;

			Lock.Unlock();

			return BytesReceivedImage;
		}

		IPAddress* GetSource()
		{
			Lock.Lock();

			auto SourceImage = Source;

			Lock.Unlock();

			return SourceImage;
		}
	};
}  // namespace Red