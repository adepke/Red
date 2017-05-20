#pragma once

#include "../Core/Definitions.h"

#include "MathCore.h"

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
	const Vector2 Vector2::ZeroVector(0.0, 0.0);

	const Vector3 Vector3::ZeroVector(0.0, 0.0, 0.0);
	const Vector3 Vector3::ForwardVector(1.0, 0.0, 0.0);
	const Vector3 Vector3::RightVector(0.0, 1.0, 0.0);
	const Vector3 Vector3::UpVector(0.0, 0.0, 1.0);

	const Vector4 Vector4::ZeroVector(0.0, 0.0, 0.0, 0.0);

	const Quaternion Quaternion::ZeroQuaternion(0.0, 0.0, 0.0, 0.0);
	const Quaternion Quaternion::IdentityQuaternion(0.0, 0.0, 0.0, 1.0);
}  // namespace Red