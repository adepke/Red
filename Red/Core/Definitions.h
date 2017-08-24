#pragma once

// Uses Compile Time And Runtime Assertions When Possible
#define ASSERTIONS

// Vectors Allocate Double Memory To Increase Accuracy
//#define VEC_DOUBLE

// Allows Faster Ray Casting By Calculating And Storing (1.0 / Direction), Saving Execution Overhead At The Cost Of Ray Type Size Increase.
//#define PRECOMPUTED_RAY