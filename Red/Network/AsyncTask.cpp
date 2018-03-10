/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "AsyncTask.h"

#include "Socket.h"

namespace Red
{
	void AsyncTask::Abort()
	{
		Sock->Shutdown();
	}
}  // namespace Red