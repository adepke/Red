/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "Vector.h"

namespace Red
{
	class AABB
	{
	public:
		Vector3 Location;
		Vector3 HalfSize;

	public:
		AABB() {}
		AABB(const AABB& Target) : Location(Target.Location), HalfSize(Target.HalfSize) {}
		explicit AABB(const Vector3& Location, const Vector3& HalfSize) : Location(Location), HalfSize(HalfSize) {}
		~AABB() {}

		AABB& operator=(const AABB& Target);
		AABB& operator=(const Vector3& TargetLocation);

		AABB operator+(const AABB& Target) const;
		AABB operator+(const Vector3& TargetLocation) const;
		AABB operator-(const AABB& Target) const;
		AABB operator-(const Vector3& TargetLocation) const;

		AABB& operator+=(const AABB& Target);
		AABB& operator+=(const Vector3& TargetLocation);
		AABB& operator-=(const AABB& Target);
		AABB& operator-=(const Vector3& TargetLocation);

		AABB& operator++();
		AABB& operator--();

		bool operator==(const AABB& Target) const;
		bool operator==(const Vector3& TargetLocation) const;
		bool operator!=(const AABB& Target) const;
		bool operator!=(const Vector3& TargetLocation) const;

		// Resets AABB To Defaults
		void Reset() { Location = Vector3(0.f, 0.f, 0.f); HalfSize = Vector3(0.5, 0.5, 0.5); }

		Vector3 Minimum() const
		{
			Vector3 TestA(Location + HalfSize);
			Vector3 TestB(Location - HalfSize);

			return Vector3(std::fminf(TestA.X, TestB.X), std::fminf(TestA.Y, TestB.Y), std::fminf(TestA.Z, TestB.Z));
		}

		Vector3 Maximum() const
		{
			Vector3 TestA(Location + HalfSize);
			Vector3 TestB(Location - HalfSize);

			return Vector3(std::fmaxf(TestA.X, TestB.X), std::fmaxf(TestA.Y, TestB.Y), std::fmaxf(TestA.Z, TestB.Z));
		}

		float Volume() const
		{
			return (HalfSize.X * 2 * HalfSize.Y * 2 * HalfSize.Z * 2);
		}

	private:
		/**
		* Prevent Usage Of Postfix Operators For Prevention Of
		* Temporary Object Allocation and Deallocation.
		* Credit: http://www.tantalon.com/pete/cppopt/asyougo.htm
		*/
		AABB operator++(int);
		AABB operator--(int);
	};

	REDINLINE AABB& AABB::operator=(const AABB& Target)
	{
		Location = Target.Location;
		HalfSize = Target.HalfSize;

		return *this;
	}

	REDINLINE AABB& AABB::operator=(const Vector3& TargetLocation)
	{
		Location = TargetLocation;

		return *this;
	}

	REDINLINE AABB AABB::operator+(const AABB& Target) const
	{
		return AABB(Location + Target.Location, HalfSize + Target.HalfSize);
	}

	REDINLINE AABB AABB::operator+(const Vector3& TargetLocation) const
	{
		return AABB(Location + TargetLocation, HalfSize);
	}

	REDINLINE AABB AABB::operator-(const AABB& Target) const
	{
		return AABB(Location - Target.Location, HalfSize - Target.HalfSize);
	}

	REDINLINE AABB AABB::operator-(const Vector3& TargetLocation) const
	{
		return AABB(Location - TargetLocation, HalfSize);
	}

	REDINLINE AABB& AABB::operator+=(const AABB& Target)
	{
		*this = *this + Target;

		return *this;
	}

	REDINLINE AABB& AABB::operator+=(const Vector3& TargetLocation)
	{
		*this = *this + TargetLocation;

		return *this;
	}

	REDINLINE AABB& AABB::operator-=(const AABB& Target)
	{
		*this = *this - Target;

		return *this;
	}

	REDINLINE AABB& AABB::operator-=(const Vector3& TargetLocation)
	{
		*this = *this - TargetLocation;

		return *this;
	}

	REDINLINE AABB& AABB::operator++()
	{
		++HalfSize;

		return *this;
	}

	REDINLINE AABB& AABB::operator--()
	{
		--HalfSize;

		return *this;
	}

	REDINLINE bool AABB::operator==(const AABB& Target) const
	{
		return ((Location == Target.Location) && (HalfSize == Target.HalfSize));
	}

	REDINLINE bool AABB::operator==(const Vector3& TargetLocation) const
	{
		return (Location == TargetLocation);
	}

	REDINLINE bool AABB::operator!=(const AABB& Target) const
	{
		return !(operator==(Target));
	}

	REDINLINE bool AABB::operator!=(const Vector3& TargetLocation) const
	{
		return !(operator==(TargetLocation));
	}
}  // namespace Red