/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "Vector.h"

#include <limits>

namespace Red
{
	class Ray
	{
	public:
		Vector3 Origin;
		Vector3 Direction;

#ifdef PRECOMPUTED_RAY
		Vector3 DirectionInv;
#endif  // PRECOMPUTED_RAY

	public:
		Ray() : Direction(1.0, 0.0, 0.0)
#ifdef PRECOMPUTED_RAY
			, DirectionInv(1.0, std::numeric_limits<VEC_MEMBER>::infinity(), std::numeric_limits<VEC_MEMBER>::infinity())
#endif  // PRECOMPUTED_RAY
		{}
		Ray(const Ray& Target) : Origin(Target.Origin), Direction(Target.Direction)
#ifdef PRECOMPUTED_RAY
			, DirectionInv(1.0 / Target.Direction.X, 1.0 / Target.Direction.Y, 1.0 / Target.Direction.Z)
#endif  // PRECOMPUTED_RAY
		{}
		explicit Ray(const Vector3& Origin, const Vector3& Direction) : Origin(Origin), Direction(Direction)
		{
			Ray::Direction.Normalize();

#ifdef PRECOMPUTED_RAY
			DirectionInv = (1.0 / Ray::Direction.X, 1.0 / Ray::Direction.Y, 1.0 / Ray::Direction.Z);
#endif  // PRECOMPUTED_RAY
		}
		~Ray() {}

		Ray& operator=(const Ray& Target);
		Ray& operator=(const Vector3& TargetOrigin);

		Ray operator+(const Ray& Target) const;
		Ray operator+(const Vector3& TargetOrigin) const;
		Ray operator-(const Ray& Target) const;
		Ray operator-(const Vector3& TargetOrigin) const;

		Ray& operator+=(const Ray& Target);
		Ray& operator+=(const Vector3& TargetOrigin);
		Ray& operator-=(const Ray& Target);
		Ray& operator-=(const Vector3& TargetOrigin);

		Ray& operator++();
		Ray& operator--();

		bool operator==(const Ray& Target) const;
		bool operator==(const Vector3& TargetOrigin) const;
		bool operator!=(const Ray& Target) const;
		bool operator!=(const Vector3& TargetOrigin) const;

		void ZeroOut() { Origin = Vector3(0.f, 0.f, 0.f); }

		void Normalize() { Direction.Normalize(); }
		bool IsNormalized() const { VEC_MEMBER Magnitude_ = Direction.Magnitude(); return ((Magnitude_ >= VEC_MEMBER(0.999999)) && (Magnitude_ <= VEC_MEMBER(1.000001))); }
		bool IsNormalizedFast() const { VEC_MEMBER Magnitude_ = Direction.MagnitudeSquared(); return ((Magnitude_ >= VEC_MEMBER(0.999)) && (Magnitude_ <= VEC_MEMBER(1.001))); }
	};

	REDINLINE Ray& Ray::operator=(const Ray& Target)
	{
		Origin = Target.Origin;
		Direction = Target.Direction;

#ifdef PRECOMPUTED_RAY
		DirectionInv = Vector3(1.0 / Direction.X, 1.0 / Direction.Y, 1.0 / Direction.Z);
#endif  // PRECOMPUTED_RAY

		return *this;
	}

	REDINLINE Ray& Ray::operator=(const Vector3& TargetOrigin)
	{
		Origin = TargetOrigin;

		return *this;
	}

	REDINLINE Ray Ray::operator+(const Ray& Target) const
	{
		Ray Result(Origin + Target.Origin, Direction + Target.Direction);

		return Result;
	}

	REDINLINE Ray Ray::operator+(const Vector3& TargetOrigin) const
	{
		return Ray(Origin + TargetOrigin, Direction);
	}

	REDINLINE Ray Ray::operator-(const Ray& Target) const
	{
		Ray Result(Origin - Target.Origin, Direction - Target.Direction);

		return Result;
	}

	REDINLINE Ray Ray::operator-(const Vector3& TargetOrigin) const
	{
		return Ray(Origin - TargetOrigin, Direction);
	}

	REDINLINE Ray& Ray::operator+=(const Ray& Target)
	{
		*this = *this + Target;

		return *this;
	}

	REDINLINE Ray& Ray::operator+=(const Vector3& TargetOrigin)
	{
		*this = *this + TargetOrigin;

		return *this;
	}

	REDINLINE Ray& Ray::operator-=(const Ray& Target)
	{
		*this = *this - Target;

		return *this;
	}

	REDINLINE Ray& Ray::operator-=(const Vector3& TargetOrigin)
	{
		*this = *this - TargetOrigin;

		return *this;
	}

	REDINLINE Ray& Ray::operator++()
	{
		++Origin;

		return *this;
	}

	REDINLINE Ray& Ray::operator--()
	{
		--Origin;

		return *this;
	}

	REDINLINE bool Ray::operator==(const Ray& Target) const
	{
		return ((Origin == Target.Origin) && (Direction == Target.Direction));
	}

	REDINLINE bool Ray::operator==(const Vector3& TargetOrigin) const
	{
		return (Origin == TargetOrigin);
	}

	REDINLINE bool Ray::operator!=(const Ray& Target) const
	{
		return !(operator==(Target));
	}

	REDINLINE bool Ray::operator!=(const Vector3& TargetOrigin) const
	{
		return !(operator==(TargetOrigin));
	}
}  // namespace Red