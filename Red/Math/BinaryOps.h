#pragma once

#include "../Core/Definitions.h"

#include <cstdint>

// Least significant bit is 0

namespace Red
{
	template <typename Type>
	uint8_t BitRead(const Type& Target, const unsigned int Bit)
	{
		return (Target & (1 << Bit));
	}

	template <typename Type>
	void BitWrite(Type& Target, const unsigned int Bit, const uint8_t Value)
	{
		if (Value)
		{
			Base |= 1 << Bit;
		}

		else
		{
			Base &= ~(1 << Bit);
		}
	}

	template <typename Type>
	void BitFlip(Type& Target, const unsigned int Bit)
	{
		Base ^ (1 << Bit);
	}
}  // namespace Red