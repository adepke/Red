#pragma once

#include "../Core/Definitions.h"
#include "Vector.h"
#include "Ray.h"
#include "LineSegment.h"
#include "Box.h"
#include "AABB.h"

namespace Red
{
	namespace Math
	{
		struct HitResult
		{
			Vector3 Location;
			Vector3 Normal;
			float TValue;
		};

		bool Intersect(const Box& TargetBoxA, const Box& TargetBoxB)
		{
			return true;
		}

		bool Intersect(const Box& TargetBox, const Vector3& TargetPoint)
		{
			return true;
		}

		bool Intersect(const Box& TargetBox, const Ray& TargetRay)
		{
			return true;
		}

		bool Intersect(const Box& TargetBox, const LineSegment& TargetLineSeg)
		{
			return true;
		}

		bool Intersect(const AABB& TargetAABBA, const AABB& TargetAABBB)
		{
			// SIMD Optimized

			bool TestX = std::fabs(TargetAABBA.Location.X - TargetAABBB.Location.X) <= (TargetAABBA.HalfSize.X + TargetAABBB.HalfSize.X);
			bool TestY = std::fabs(TargetAABBA.Location.Y - TargetAABBB.Location.Y) <= (TargetAABBA.HalfSize.Y + TargetAABBB.HalfSize.Y);
			bool TestZ = std::fabs(TargetAABBA.Location.Z - TargetAABBB.Location.Z) <= (TargetAABBA.HalfSize.Z + TargetAABBB.HalfSize.Z);

			return (TestX && TestY && TestZ);
		}

		bool Intersect(const AABB& TargetAABB, const Vector3& TargetPoint)
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

		bool Intersect(const AABB& TargetAABB, const Ray& TargetRay, HitResult* ComplexResult = nullptr)
		{
			float DirectionFracX=(1.0 / TargetRay.Direction.X);
			float DirectionFracY=(1.0 / TargetRay.Direction.Y);
			float DirectionFracZ=(1.0 / TargetRay.Direction.Z);

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

			if ((TMax < 0.0) || (TMin > TMax))
			{
				if (ComplexResult)
				{
					ComplexResult->Location = Vector3::ZeroVector;
					ComplexResult->Normal = Vector3::ZeroVector;
					ComplexResult->TValue = -1.0;
				}

				return false;
			}

			if (ComplexResult)
			{
				ComplexResult->Location = Vector3(TargetAABB.Location.X - TMin, TargetAABB.Location.Y - TMin, TargetAABB.Location.Z - TMin);
				ComplexResult->Normal = Vector3::ZeroVector;
				ComplexResult->TValue = TMin;
			}

			return true;
		}

		bool Intersect(const AABB& TargetAABB, const LineSegment& TargetLineSeg)
		{
			return true;
		}
	}  // namespace Math
}  // namespace Red