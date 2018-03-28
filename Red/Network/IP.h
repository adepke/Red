/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

namespace Red
{
	struct IPAddress
	{
		virtual ~IPAddress() = 0;
	};

	struct IPEndPoint
	{
		virtual ~IPEndPoint() = 0;
	};
}  // namespace Red