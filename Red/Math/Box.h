#pragma once

#include "Vector.h"

namespace Red
{
	namespace Math
	{
		class Box
		{
		public:
			Vector3 Location;
			Vector3 HalfSize;

		public:
			Box() {}
			Box(const Box& Target) : Location(Target.Location), HalfSize(Target.HalfSize) {}
			explicit Box(const Vector3& Location, const Vector3& HalfSize) : Location(Location), HalfSize(HalfSize) {}
			~Box() {}

			Box& operator=(const Box& Target);
			Box& operator=(const Vector3& TargetLocation);

			Box operator+(const Box& Target) const;
			Box operator+(const Vector3& TargetLocation) const;
			Box operator-(const Box& Target) const;
			Box operator-(const Vector3& TargetLocation) const;

			Box& operator+=(const Box& Target);
			Box& operator+=(const Vector3& TargetLocation);
			Box& operator-=(const Box& Target);
			Box& operator-=(const Vector3& TargetLocation);

			Box& operator++();
			Box& operator--();

			bool operator==(const Box& Target) const;
			bool operator==(const Vector3& TargetLocation) const;
			bool operator!=(const Box& Target) const;
			bool operator!=(const Vector3& TargetLocation) const;

			// Resets Box To Defaults
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
			Box operator++(int);
			Box operator--(int);
		};

		Box& Box::operator=(const Box& Target)
		{
			Location = Target.Location;
			HalfSize = Target.HalfSize;

			return *this;
		}

		Box& Box::operator=(const Vector3& TargetLocation)
		{
			Location = TargetLocation;

			return *this;
		}

		Box Box::operator+(const Box& Target) const
		{
			return Box(Location + Target.Location, HalfSize + Target.HalfSize);
		}

		Box Box::operator+(const Vector3& TargetLocation) const
		{
			return Box(Location + TargetLocation, HalfSize);
		}

		Box Box::operator-(const Box& Target) const
		{
			return Box(Location - Target.Location, HalfSize - Target.HalfSize);
		}

		Box Box::operator-(const Vector3& TargetLocation) const
		{
			return Box(Location - TargetLocation, HalfSize);
		}

		Box& Box::operator+=(const Box& Target)
		{
			*this = *this + Target;

			return *this;
		}

		Box& Box::operator+=(const Vector3& TargetLocation)
		{
			*this = *this + TargetLocation;

			return *this;
		}

		Box& Box::operator-=(const Box& Target)
		{
			*this = *this - Target;

			return *this;
		}
		
		Box& Box::operator-=(const Vector3& TargetLocation)
		{
			*this = *this - TargetLocation;

			return *this;
		}

		Box& Box::operator++()
		{
			++HalfSize;

			return *this;
		}

		Box& Box::operator--()
		{
			--HalfSize;

			return *this;
		}

		bool Box::operator==(const Box& Target) const
		{
			return ((Location == Target.Location) && (HalfSize == Target.HalfSize));
		}

		bool Box::operator==(const Vector3& TargetLocation) const
		{
			return (Location == TargetLocation);
		}

		bool Box::operator!=(const Box& Target) const
		{
			return !(operator==(Target));
		}

		bool Box::operator!=(const Vector3& TargetLocation) const
		{
			return !(operator==(TargetLocation));
		}
	}  // namespace Math
}  // namespace Red