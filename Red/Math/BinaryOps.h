/*
	Copyright (c) 2017-2018 Andrew Depke
*/
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

	void Swap(int TargetA, int TargetB)
	{
		if (TargetA != TargetB)
		{
			TargetA ^= TargetB;
			TargetB ^= TargetA;
			TargetA ^= TargetB;
		}
	}

	// Credit: The C Programming Language 2nd Ed. by Brian W. Kernighan and Dennis M. Ritchie
	unsigned int BitsSet(unsigned int Value)
	{
		unsigned int Result = 0;

		for (; Value; ++Result)
		{
			Value &= Value - 1;
		}

		return Result;
	}

	int GetSign(int Value)
	{
		return ((Value > 0) - (Value < 0));
	}

	bool InverseSigns(int TargetA, int TargetB)
	{
		return ((TargetA ^ TargetB) < 0);
	}

	bool IsPowerOf2(unsigned int Value)
	{
		return Value && !(Value & (Value - 1));
	}

	unsigned int RoundUpToPowerOf2(unsigned int Value)
	{
		--Value;
		Value |= Value >> 1;
		Value |= Value >> 2;
		Value |= Value >> 4;
		Value |= Value >> 8;
		Value |= Value >> 16;
		++Value;

		return Value;
	}
}  // namespace Red