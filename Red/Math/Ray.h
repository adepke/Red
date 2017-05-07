#pragma once

#include "Vector.h"

namespace Red
{
	namespace Math
	{
		class Ray
		{
		public:
			Vector3 Origin;
			Vector3 Direction;

		public:
			Ray() : Direction(0.0, 0.0, 1.0) {}
			Ray(const Ray& Target) : Origin(Target.Origin), Direction(Target.Direction) {}
			explicit Ray(const Vector3& Origin, const Vector3& Direction) : Origin(Origin), Direction(Direction) { Ray::Direction.Normalize(); }
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

			void ZeroOut() { Origin = Vector3::ZeroVector; }

			void Normalize() { Direction.Normalize(); }
			bool IsNormalized() const { VEC_MEMBER Magnitude_ = Direction.Magnitude(); return ((Magnitude_ >= VEC_MEMBER(0.999999)) && (Magnitude_ <= VEC_MEMBER(1.000001))); }
			bool IsNormalizedFast() const { VEC_MEMBER Magnitude_ = Direction.MagnitudeSquared(); return ((Magnitude_ >= VEC_MEMBER(0.999)) && (Magnitude_ <= VEC_MEMBER(1.001))); }
		};

		Ray& Ray::operator=(const Ray& Target)
		{
			Origin = Target.Origin;
			Direction = Target.Direction;

			return *this;
		}

		Ray& Ray::operator=(const Vector3& TargetOrigin)
		{
			Origin = TargetOrigin;

			return *this;
		}

		Ray Ray::operator+(const Ray& Target) const
		{
			Ray Result(Origin + Target.Origin, Direction + Target.Direction);
			Result.Normalize();

			return Result;
		}

		Ray Ray::operator+(const Vector3& TargetOrigin) const
		{
			return Ray(Origin + TargetOrigin, Direction);
		}

		Ray Ray::operator-(const Ray& Target) const
		{
			Ray Result(Origin - Target.Origin, Direction - Target.Direction);
			Result.Normalize();

			return Result;
		}

		Ray Ray::operator-(const Vector3& TargetOrigin) const
		{
			return Ray(Origin - TargetOrigin, Direction);
		}

		Ray& Ray::operator+=(const Ray& Target)
		{
			*this = *this + Target;

			return *this;
		}

		Ray& Ray::operator+=(const Vector3& TargetOrigin)
		{
			*this = *this + TargetOrigin;

			return *this;
		}

		Ray& Ray::operator-=(const Ray& Target)
		{
			*this = *this - Target;

			return *this;
		}

		Ray& Ray::operator-=(const Vector3& TargetOrigin)
		{
			*this = *this - TargetOrigin;

			return *this;
		}

		Ray& Ray::operator++()
		{
			++Origin;

			return *this;
		}

		Ray& Ray::operator--()
		{
			--Origin;

			return *this;
		}

		bool Ray::operator==(const Ray& Target) const
		{
			return ((Origin == Target.Origin) && (Direction == Target.Direction));
		}

		bool Ray::operator==(const Vector3& TargetOrigin) const
		{
			return (Origin == TargetOrigin);
		}

		bool Ray::operator!=(const Ray& Target) const
		{
			return !(operator==(Target));
		}

		bool Ray::operator!=(const Vector3& TargetOrigin) const
		{
			return !(operator==(TargetOrigin));
		}
	}  // namespace Math
}  // namespace Red