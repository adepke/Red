#pragma once

#include "Vector.h"

namespace Red
{
	class OBB
	{
	public:
		Vector3 Location;
		Vector3 HalfSize;

	public:
		OBB() {}
		OBB(const OBB& Target) : Location(Target.Location), HalfSize(Target.HalfSize) {}
		explicit OBB(const Vector3& Location, const Vector3& HalfSize) : Location(Location), HalfSize(HalfSize) {}
		~OBB() {}

		OBB& operator=(const OBB& Target);
		OBB& operator=(const Vector3& TargetLocation);

		OBB operator+(const OBB& Target) const;
		OBB operator+(const Vector3& TargetLocation) const;
		OBB operator-(const OBB& Target) const;
		OBB operator-(const Vector3& TargetLocation) const;

		OBB& operator+=(const OBB& Target);
		OBB& operator+=(const Vector3& TargetLocation);
		OBB& operator-=(const OBB& Target);
		OBB& operator-=(const Vector3& TargetLocation);

		OBB& operator++();
		OBB& operator--();

		bool operator==(const OBB& Target) const;
		bool operator==(const Vector3& TargetLocation) const;
		bool operator!=(const OBB& Target) const;
		bool operator!=(const Vector3& TargetLocation) const;

		// Resets OBB To Defaults
		void Reset() { Location = Vector3::ZeroVector; HalfSize = Vector3(0.5, 0.5, 0.5); }

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
		OBB operator++(int);
		OBB operator--(int);
	};

	OBB& OBB::operator=(const OBB& Target)
	{
		Location = Target.Location;
		HalfSize = Target.HalfSize;

		return *this;
	}

	OBB& OBB::operator=(const Vector3& TargetLocation)
	{
		Location = TargetLocation;

		return *this;
	}

	OBB OBB::operator+(const OBB& Target) const
	{
		return OBB(Location + Target.Location, HalfSize + Target.HalfSize);
	}

	OBB OBB::operator+(const Vector3& TargetLocation) const
	{
		return OBB(Location + TargetLocation, HalfSize);
	}

	OBB OBB::operator-(const OBB& Target) const
	{
		return OBB(Location - Target.Location, HalfSize - Target.HalfSize);
	}

	OBB OBB::operator-(const Vector3& TargetLocation) const
	{
		return OBB(Location - TargetLocation, HalfSize);
	}

	OBB& OBB::operator+=(const OBB& Target)
	{
		*this = *this + Target;

		return *this;
	}

	OBB& OBB::operator+=(const Vector3& TargetLocation)
	{
		*this = *this + TargetLocation;

		return *this;
	}

	OBB& OBB::operator-=(const OBB& Target)
	{
		*this = *this - Target;

		return *this;
	}

	OBB& OBB::operator-=(const Vector3& TargetLocation)
	{
		*this = *this - TargetLocation;

		return *this;
	}

	OBB& OBB::operator++()
	{
		++HalfSize;

		return *this;
	}

	OBB& OBB::operator--()
	{
		--HalfSize;

		return *this;
	}

	bool OBB::operator==(const OBB& Target) const
	{
		return ((Location == Target.Location) && (HalfSize == Target.HalfSize));
	}

	bool OBB::operator==(const Vector3& TargetLocation) const
	{
		return (Location == TargetLocation);
	}

	bool OBB::operator!=(const OBB& Target) const
	{
		return !(operator==(Target));
	}

	bool OBB::operator!=(const Vector3& TargetLocation) const
	{
		return !(operator==(TargetLocation));
	}
}  // namespace Red