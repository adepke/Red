#pragma once

#include "../Core/Definitions.h"

#include <cstdint>

// Least significant bit is 0

namespace Red
{
	template <typename Type>
	uint8_t BitRead(const Type& Target, const unsigned int Bit)
	{
		return (Target >> Bit) & 1;
	}

	template <typename Type>
	void BitWrite(Type& Target, const unsigned int Bit, const uint8_t Value)
	{
		if (Value)
		{
			Target |= 1 << Bit;
		}

		else
		{
			Target &= ~(1 << Bit);
		}
	}

	template <typename Type>
	void BitFlip(Type& Target, const unsigned int Bit)
	{
		Target ^= (1 << Bit);
	}
}  // namespace Red