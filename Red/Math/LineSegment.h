/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "Vector.h"

namespace Red
{
	class LineSegment
	{
	public:
		Vector3 Origin;
		Vector3 Destination;

	public:
		LineSegment() {}
		LineSegment(const LineSegment& Target) : Origin(Target.Origin), Destination(Target.Destination) {}
		explicit LineSegment(const Vector3& Origin, const Vector3& Destination) : Origin(Origin), Destination(Destination) {}
		~LineSegment() {}

		LineSegment& operator=(const LineSegment& Target);

		LineSegment operator+(const LineSegment& Target) const;
		LineSegment operator-(const LineSegment& Target) const;

		LineSegment& operator+=(const LineSegment& Target);
		LineSegment& operator-=(const LineSegment& Target);

		bool operator==(const LineSegment& Target) const;
		bool operator!=(const LineSegment& Target) const;

		float Length() const
		{
			float DeltaX(Destination.X - Origin.X);
			float DeltaY(Destination.Y - Origin.Y);
			float DeltaZ(Destination.Z - Origin.Z);

			return (std::sqrt((DeltaX * DeltaX) + (DeltaY * DeltaY) + (DeltaZ * DeltaZ)));
		}
	};

	REDINLINE LineSegment& LineSegment::operator=(const LineSegment& Target)
	{
		Origin = Target.Origin;
		Destination = Target.Destination;

		return *this;
	}

	REDINLINE LineSegment LineSegment::operator+(const LineSegment& Target) const
	{
		return LineSegment(Origin + Target.Origin, Destination + Target.Destination);
	}

	REDINLINE LineSegment LineSegment::operator-(const LineSegment& Target) const
	{
		return LineSegment(Origin - Target.Origin, Destination - Target.Destination);
	}

	REDINLINE LineSegment& LineSegment::operator+=(const LineSegment& Target)
	{
		*this = *this + Target;

		return *this;
	}

	REDINLINE LineSegment& LineSegment::operator-=(const LineSegment& Target)
	{
		*this = *this - Target;

		return *this;
	}

	REDINLINE bool LineSegment::operator==(const LineSegment& Target) const
	{
		return ((Origin == Target.Origin) && (Destination == Target.Destination));
	}

	REDINLINE bool LineSegment::operator!=(const LineSegment& Target) const
	{
		return !(operator==(Target));
	}
}  // namespace Red