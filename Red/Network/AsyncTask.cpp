#include "AsyncTask.h"

#include "Socket.h"

namespace Red
{
	void AsyncTask::Abort()
	{
		Sock->Shutdown();
	}
}  // namespace Red