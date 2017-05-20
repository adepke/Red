#pragma once

// Uses Compile Time And Runtime Assertions When Possible
#define ASSERTIONS

// Vectors Allocate Double Memory To Increase Accuracy
//#define VEC_DOUBLE

// Allows Faster Ray Casting By Calculating And Storing (1.0 / Direction), Saving Execution Overhead At The Cost Of Ray Type Size Increase.
//#define PRECOMPUTED_RAY

#define byte unsigned char
#define int16 __int16
#define int32 __int32
#define int64 __int64
#define uint16 unsigned __int16
#define uint32 unsigned __int32
#define uint64 unsigned __int64