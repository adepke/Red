#pragma once

#include "IPv4.h"

enum
{
	BIG_ENDIAN = 0x00010203ul,
	LITTLE_ENDIAN = 0x03020100ul,
	PDP_ENDIAN = 0x01000302ul,
};

static const union
{
	unsigned char Bytes[4];
	uint32_t Value;
} LocalOrder = { { 0, 1, 2, 3 } };

#define PLATFORM_ENDIANNESS (LocalOrder.Value)