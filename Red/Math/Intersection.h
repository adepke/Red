#pragma once

#include "../Core/Definitions.h"
#include "Vector.h"
#include "Ray.h"
#include "LineSegment.h"
#include "OBB.h"
#include "AABB.h"

namespace Red
{
	struct HitResult
	{
		Vector3 Location;
		Vector3 Normal;
		float TValue;
	};

	REDINLINE bool Intersect(const OBB& TargetOBBA, const OBB& TargetOBBB)
	{
		return false;
	}

	REDINLINE bool Intersect(const OBB& TargetOBB, const Vector3& TargetPoint)
	{
		return false;
	}

	REDINLINE bool Intersect(const OBB& TargetOBB, const Ray& TargetRay)
	{
		return false;
	}

	REDINLINE bool Intersect(const OBB& TargetOBB, const LineSegment& TargetLineSeg)
	{
		return false;
	}

	REDINLINE bool Intersect(const AABB& TargetAABBA, const AABB& TargetAABBB)
	{
		// SIMD Optimized

		bool TestX = std::fabs(TargetAABBA.Location.X - TargetAABBB.Location.X) <= (TargetAABBA.HalfSize.X + TargetAABBB.HalfSize.X);
		bool TestY = std::fabs(TargetAABBA.Location.Y - TargetAABBB.Location.Y) <= (TargetAABBA.HalfSize.Y + TargetAABBB.HalfSize.Y);
		bool TestZ = std::fabs(TargetAABBA.Location.Z - TargetAABBB.Location.Z) <= (TargetAABBA.HalfSize.Z + TargetAABBB.HalfSize.Z);

		return (TestX && TestY && TestZ);
	}

	REDINLINE bool Intersect(const AABB& TargetAABB, const Vector3& TargetPoint)
	{
		// Slightly Faster Than SIMD Optimization (<1ms Delta Per 100,000 Calls)

		Vector3 TargetAABBMin(TargetAABB.Minimum());
		Vector3 TargetAABBMax(TargetAABB.Maximum());

		return (
			(TargetPoint.X >= TargetAABBMin.X) && (TargetPoint.X <= TargetAABBMax.X) &&
			(TargetPoint.Y >= TargetAABBMin.Y) && (TargetPoint.Y <= TargetAABBMax.Y) &&
			(TargetPoint.Z >= TargetAABBMin.Z) && (TargetPoint.Z <= TargetAABBMax.Z)
			);
	}

	REDINLINE bool Intersect(const AABB& TargetAABB, const Ray& TargetRay, HitResult* ComplexResult = nullptr)
	{
#ifdef PRECOMPUTED_RAY
		float DirectionFracX(TargetRay.DirectionInv.X);
		float DirectionFracY(TargetRay.DirectionInv.Y);
		float DirectionFracZ(TargetRay.DirectionInv.Z);
#else
		float DirectionFracX(1.0f / TargetRay.Direction.X);
		float DirectionFracY(1.0f / TargetRay.Direction.Y);
		float DirectionFracZ(1.0f / TargetRay.Direction.Z);
#endif

		Vector3 TargetAABBMin(TargetAABB.Minimum());
		Vector3 TargetAABBMax(TargetAABB.Maximum());

		float TXMin((TargetAABBMin.X - TargetRay.Origin.X) * DirectionFracX);
		float TXMax((TargetAABBMax.X - TargetRay.Origin.X) * DirectionFracX);
		float TYMin((TargetAABBMin.Y - TargetRay.Origin.Y) * DirectionFracY);
		float TYMax((TargetAABBMax.Y - TargetRay.Origin.Y) * DirectionFracY);
		float TZMin((TargetAABBMin.Z - TargetRay.Origin.Z) * DirectionFracZ);
		float TZMax((TargetAABBMax.Z - TargetRay.Origin.Z) * DirectionFracZ);

		float TMin(std::fmaxf(std::fmaxf(std::fminf(TXMin, TXMax), std::fminf(TYMin, TYMax)), std::fminf(TZMin, TZMax)));
		float TMax(std::fminf(std::fminf(std::fmaxf(TXMin, TXMax), std::fmaxf(TYMin, TYMax)), std::fmaxf(TZMin, TZMax)));

		if ((TMax < 0.0f) || (TMin > TMax))
		{
			if (ComplexResult)
			{
				ComplexResult->Location = Vector3(0.f, 0.f, 0.f);
				ComplexResult->Normal = Vector3(0.f, 0.f, 0.f);
				ComplexResult->TValue = -1.0f;
			}

			return false;
		}

		if (ComplexResult)
		{
			float T((TMin >= 0.0f) ? TMin : TMax);

			ComplexResult->Location = (TargetRay.Origin + (TargetRay.Direction * T));
			ComplexResult->Normal = Vector3(0.f, 0.f, 0.f);
			ComplexResult->TValue = T;
		}

		return true;
	}

	REDINLINE bool Intersect(const AABB& TargetAABB, const LineSegment& TargetLineSeg)
	{
		return false;
	}
}  // namespace Red