#pragma once

#include "../Core/Definitions.h"

#include "Vector.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Ray.h"
#include "LineSegment.h"
#include "OBB.h"
#include "AABB.h"

#include "Intersection.h"

namespace Red
{
	namespace Math
	{
		const Vector2 Vector2::ZeroVector(0.0, 0.0);

		const Vector3 Vector3::ZeroVector(0.0, 0.0, 0.0);
		const Vector3 Vector3::ForwardVector(1.0, 0.0, 0.0);
		const Vector3 Vector3::RightVector(0.0, 1.0, 0.0);
		const Vector3 Vector3::UpVector(0.0, 0.0, 1.0);

		const Vector4 Vector4::ZeroVector(0.0, 0.0, 0.0, 0.0);

		const Quaternion Quaternion::ZeroQuaternion(0.0, 0.0, 0.0, 0.0);
		const Quaternion Quaternion::IdentityQuaternion(0.0, 0.0, 0.0, 1.0);

		// Factorial Function
		// Recursive Stack Based Algorithm, Produces Faster Results Than Loop Based
		uint64 Factorial(uint32 Factor)
		{
			return (Factor == 1 ? 1 : Factor * Factorial(Factor - 1));
		}
	}  // namespace Math
}  // namespace Red