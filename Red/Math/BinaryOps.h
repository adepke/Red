#pragma once

#include "../Core/Definitions.h"

// Least significant bit is 0

template <typename Type>
byte BitRead(const Type& Target, const uint32 Bit)
{
	return (Target & (1 << Bit));
}

template <typename Type>
void BitWrite(Type& Target, const uint32 Bit, const byte Value)
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
void BitFlip(Type& Target, const uint32 Bit)
{
	Base ^ (1 << Bit);
}