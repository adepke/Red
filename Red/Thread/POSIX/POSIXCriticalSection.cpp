/*
	Copyright (c) 2018 Andrew Depke
*/
#include "POSIXCriticalSection.h"

namespace Red
{
	POSIXCriticalSection::POSIXCriticalSection()
	{
		pthread_mutexattr_t HandleAttributes;
		pthread_mutexattr_init(&HandleAttributes);
		pthread_mutexattr_settype(&HandleAttributes, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&Handle, &HandleAttributes);
		pthread_mutexattr_destroy(&HandleAttributes);
	}

	POSIXCriticalSection::~POSIXCriticalSection()
	{
		pthread_mutex_destroy(&Handle);
	}

	bool POSIXCriticalSection::TryLock()
	{
		return (pthread_mutex_trylock(&Handle) == 0);
	}

	void POSIXCriticalSection::Lock()
	{
		pthread_mutex_lock(&Handle);
	}

	void POSIXCriticalSection::Unlock()
	{
		pthread_mutex_unlock(&Handle);
	}
}  // namespace Red