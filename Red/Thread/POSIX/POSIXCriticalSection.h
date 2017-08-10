#pragma once

#include <pthread.h>

namespace Red
{
	class POSIXCriticalSection
	{
	private:
		pthread_mutex_t Handle;

	public:
		POSIXCriticalSection();
		~POSIXCriticalSection();

		bool TryLock();
		void Lock();
		void Unlock();

	private:
		POSIXCriticalSection(const POSIXCriticalSection& Target);
		POSIXCriticalSection& operator=(const POSIXCriticalSection& Target);
	};

	// Private inheritance to prevent calls to Lock() and Unlock()
	class POSIXRAIICriticalSection : private POSIXCriticalSection
	{
	public:
		POSIXRAIICriticalSection()
		{
			POSIXCriticalSection::Lock();
		}

		~POSIXRAIICriticalSection()
		{
			POSIXCriticalSection::Unlock();
		}
	};

	typedef POSIXCriticalSection CriticalSection;
	typedef POSIXRAIICriticalSection RAIICriticalSection;
}  // namespace Red