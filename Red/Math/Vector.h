#pragma once

#include "MathCore.h"

#ifdef ASSERTIONS
#include <assert.h>
#endif

#ifdef FORCEDINLINES
#define REDINLINE __forceinline
#else
#define REDINLINE inline
#endif

#ifdef VEC_DOUBLE
#define VEC_MEMBER double
#define VEC_ALIGN(n) __declspec(align(n * 2))
#else
#define VEC_MEMBER float
#define VEC_ALIGN(n) __declspec(align(n))
#endif

namespace Red
{
	// 8/16-Byte Aligned Vector Of 2 Components, X, Y, Determined By VEC_MEMBER
	VEC_ALIGN(8) class Vector2
	{
	public:
		VEC_MEMBER X, Y;

	public:
		static const Vector2 ZeroVector;  // ( 0, 0 )

	public:
		Vector2() {}
		Vector2(const Vector2& Target) : X(Target.X), Y(Target.Y) {}
		explicit Vector2(VEC_MEMBER X, VEC_MEMBER Y) : X(X), Y(Y) {}
		~Vector2() {}

		Vector2& operator=(const Vector2& Target);
		Vector2& operator=(VEC_MEMBER Scalar);

		Vector2 operator+(const Vector2& Target) const;
		Vector2 operator+(VEC_MEMBER Scalar) const;
		Vector2 operator-() const;
		Vector2 operator-(const Vector2& Target) const;
		Vector2 operator-(VEC_MEMBER Scalar) const;
		Vector2 operator*(const Vector2& Target) const;
		Vector2 operator*(VEC_MEMBER Scalar) const;
		Vector2 operator/(const Vector2& Target) const;
		Vector2 operator/(VEC_MEMBER Scalar) const;

		Vector2& operator+=(const Vector2& Target);
		Vector2& operator+=(VEC_MEMBER Scalar);
		Vector2& operator-=(const Vector2& Target);
		Vector2& operator-=(VEC_MEMBER Scalar);
		Vector2& operator*=(const Vector2& Target);
		Vector2& operator*=(VEC_MEMBER Scalar);
		Vector2& operator/=(const Vector2& Target);
		Vector2& operator/=(VEC_MEMBER Scalar);

		Vector2& operator++();
		Vector2& operator--();

		bool operator==(const Vector2& Target) const;
		bool operator==(VEC_MEMBER Scalar) const;
		bool operator!=(const Vector2& Target) const;
		bool operator!=(VEC_MEMBER Scalar) const;

		bool operator<(const Vector2& Target) const;
		bool operator<(VEC_MEMBER Scalar) const;
		bool operator>(const Vector2& Target) const;
		bool operator>(VEC_MEMBER Scalar) const;

		bool operator<=(const Vector2& Target) const;
		bool operator<=(VEC_MEMBER Scalar) const;
		bool operator>=(const Vector2& Target) const;
		bool operator>=(VEC_MEMBER Scalar) const;

		void ZeroOut() { X = 0; Y = 0; }
		bool IsZero() const { return((X == 0) && (Y == 0)); }
		bool IsZero(VEC_MEMBER Threshold) const { return((Abs(X) < Threshold) && (Abs(Y) < Threshold)); }

		VEC_MEMBER Magnitude() const { return VEC_MEMBER(SquareRoot((X * X) + (Y * Y))); }
		VEC_MEMBER MagnitudeSquared() const { return VEC_MEMBER((X * X) + (Y * Y)); }

		void Normalize();
		bool IsNormalized() const { VEC_MEMBER Magnitude_ = Magnitude(); return ((Magnitude_ >= VEC_MEMBER(0.999999)) && (Magnitude_ <= VEC_MEMBER(1.000001))); }
		bool IsNormalizedFast() const { VEC_MEMBER Magnitude_ = MagnitudeSquared(); return ((Magnitude_ >= VEC_MEMBER(0.999)) && (Magnitude_ <= VEC_MEMBER(1.001))); }

	private:
		/**
		* Prevent Usage Of Postfix Operators For Prevention Of
		* Temporary Object Allocation and Deallocation.
		* Credit: http://www.tantalon.com/pete/cppopt/asyougo.htm
		*/
		Vector2 operator++(int);
		Vector2 operator--(int);
	};

	REDINLINE Vector2& Vector2::operator=(const Vector2& Target)
	{
		X = Target.X;
		Y = Target.Y;

		return *this;
	}

	REDINLINE Vector2& Vector2::operator=(VEC_MEMBER Scalar)
	{
		X = Scalar;
		Y = Scalar;

		return *this;
	}

	REDINLINE Vector2 Vector2::operator+(const Vector2& Target) const
	{
		return Vector2(X + Target.X, Y + Target.Y);
	}

	REDINLINE Vector2 Vector2::operator+(VEC_MEMBER Scalar) const
	{
		return Vector2(X + Scalar, Y + Scalar);
	}

	REDINLINE Vector2 Vector2::operator-() const
	{
		return Vector2(-X, -Y);
	}

	REDINLINE Vector2 Vector2::operator-(const Vector2& Target) const
	{
		return Vector2(X - Target.X, Y - Target.Y);
	}

	REDINLINE Vector2 Vector2::operator-(VEC_MEMBER Scalar) const
	{
		return Vector2(X - Scalar, Y - Scalar);
	}

	REDINLINE Vector2 Vector2::operator*(const Vector2& Target) const
	{
		return Vector2(X * Target.X, Y * Target.Y);
	}

	REDINLINE Vector2 Vector2::operator*(VEC_MEMBER Scalar) const
	{
		return Vector2(X * Scalar, Y * Scalar);
	}

	REDINLINE Vector2 Vector2::operator/(const Vector2& Target) const
	{
		return Vector2(X / Target.X, Y / Target.Y);
	}

	REDINLINE Vector2 Vector2::operator/(VEC_MEMBER Scalar) const
	{
		return Vector2(X / Scalar, Y / Scalar);
	}

	REDINLINE Vector2& Vector2::operator+=(const Vector2& Target)
	{
		*this = *this + Target;

		return *this;
	}

	REDINLINE Vector2& Vector2::operator+=(VEC_MEMBER Scalar)
	{
		*this = *this + Scalar;

		return *this;
	}

	REDINLINE Vector2& Vector2::operator-=(const Vector2& Target)
	{
		*this = *this - Target;

		return *this;
	}

	REDINLINE Vector2& Vector2::operator-=(VEC_MEMBER Scalar)
	{
		*this = *this - Scalar;

		return *this;
	}

	REDINLINE Vector2& Vector2::operator*=(const Vector2& Target)
	{
		*this = *this * Target;

		return *this;
	}

	REDINLINE Vector2& Vector2::operator*=(VEC_MEMBER Scalar)
	{
		*this = *this * Scalar;

		return *this;
	}

	REDINLINE Vector2& Vector2::operator/=(const Vector2& Target)
	{
		*this = *this / Target;

		return *this;
	}

	REDINLINE Vector2& Vector2::operator/=(VEC_MEMBER Scalar)
	{
		*this = *this / Scalar;

		return *this;
	}

	REDINLINE Vector2& Vector2::operator++()
	{
		X += 1;
		Y += 1;

		return *this;
	}

	REDINLINE Vector2& Vector2::operator--()
	{
		X -= 1;
		Y -= 1;

		return *this;
	}

	REDINLINE bool Vector2::operator==(const Vector2& Target) const
	{
		return ((X == Target.X) && (Y == Target.Y));
	}

	REDINLINE bool Vector2::operator==(VEC_MEMBER Scalar) const
	{
		return ((X == Scalar) && (Y == Scalar));
	}

	REDINLINE bool Vector2::operator!=(const Vector2& Target) const
	{
		return !(operator==(Target));
	}

	REDINLINE bool Vector2::operator!=(VEC_MEMBER Scalar) const
	{
		return !(operator==(Scalar));
	}

	REDINLINE bool Vector2::operator<(const Vector2& Target) const
	{
		return ((X < Target.X) && (Y < Target.Y));
	}

	REDINLINE bool Vector2::operator<(VEC_MEMBER Scalar) const
	{
		return ((X < Scalar) && (Y < Scalar));
	}

	REDINLINE bool Vector2::operator>(const Vector2& Target) const
	{
		return ((X > Target.X) && (Y > Target.Y));
	}

	REDINLINE bool Vector2::operator>(VEC_MEMBER Scalar) const
	{
		return ((X > Scalar) && (Y > Scalar));
	}

	REDINLINE bool Vector2::operator<=(const Vector2& Target) const
	{
		return ((X <= Target.X) && (Y <= Target.Y));
	}

	REDINLINE bool Vector2::operator<=(VEC_MEMBER Scalar) const
	{
		return ((X <= Scalar) && (Y <= Scalar));
	}

	REDINLINE bool Vector2::operator>=(const Vector2& Target) const
	{
		return ((X >= Target.X) && (Y >= Target.Y));
	}

	REDINLINE bool Vector2::operator>=(VEC_MEMBER Scalar) const
	{
		return ((X >= Scalar) && (Y >= Scalar));
	}

	REDINLINE void Vector2::Normalize()
	{
		VEC_MEMBER Magnitude_ = Magnitude();

#ifdef ASSERTIONS
		assert(Magnitude_ != 0);
#endif

		X /= Magnitude_;
		Y /= Magnitude_;
	}

	// Unaligned Vector Of 3 Components, X, Y, Z, Determined By VEC_MEMBER
	class Vector3
	{
	public:
		VEC_MEMBER X, Y, Z;

	public:
		static const Vector3 ZeroVector;     // ( 0, 0, 0 )
		static const Vector3 ForwardVector;  // ( 1, 0, 0 )
		static const Vector3 RightVector;    // ( 0, 1, 0 )
		static const Vector3 UpVector;       // ( 0, 0, 1 )

	public:
		Vector3() {}
		Vector3(const Vector3& Target) : X(Target.X), Y(Target.Y), Z(Target.Z) {}
		Vector3(const Vector2& XY, VEC_MEMBER Z) : X(XY.X), Y(XY.Y), Z(Z) {}
		explicit Vector3(VEC_MEMBER X, VEC_MEMBER Y, VEC_MEMBER Z) : X(X), Y(Y), Z(Z) {}
		~Vector3() {}

		Vector3& operator=(const Vector3& Target);
		Vector3& operator=(VEC_MEMBER Scalar);

		Vector3 operator+(const Vector3& Target) const;
		Vector3 operator+(VEC_MEMBER Scalar) const;
		Vector3 operator-() const;
		Vector3 operator-(const Vector3& Target) const;
		Vector3 operator-(VEC_MEMBER Scalar) const;
		Vector3 operator*(const Vector3& Target) const;
		Vector3 operator*(VEC_MEMBER Scalar) const;
		Vector3 operator/(const Vector3& Target) const;
		Vector3 operator/(VEC_MEMBER Scalar) const;

		Vector3& operator+=(const Vector3& Target);
		Vector3& operator+=(VEC_MEMBER Scalar);
		Vector3& operator-=(const Vector3& Target);
		Vector3& operator-=(VEC_MEMBER Scalar);
		Vector3& operator*=(const Vector3& Target);
		Vector3& operator*=(VEC_MEMBER Scalar);
		Vector3& operator/=(const Vector3& Target);
		Vector3& operator/=(VEC_MEMBER Scalar);

		Vector3& operator++();
		Vector3& operator--();

		bool operator==(const Vector3& Target) const;
		bool operator==(VEC_MEMBER Scalar) const;
		bool operator!=(const Vector3& Target) const;
		bool operator!=(VEC_MEMBER Scalar) const;

		bool operator<(const Vector3& Target) const;
		bool operator<(VEC_MEMBER Scalar) const;
		bool operator>(const Vector3& Target) const;
		bool operator>(VEC_MEMBER Scalar) const;

		bool operator<=(const Vector3& Target) const;
		bool operator<=(VEC_MEMBER Scalar) const;
		bool operator>=(const Vector3& Target) const;
		bool operator>=(VEC_MEMBER Scalar) const;

		void ZeroOut() { X = 0; Y = 0; Z = 0; }
		bool IsZero() const { return((X == 0) && (Y == 0) && (Z == 0)); }
		bool IsZero(VEC_MEMBER Threshold) const { return((Abs(X) < Threshold) && (Abs(Y) < Threshold) && (Abs(Z) < Threshold)); }

		VEC_MEMBER Magnitude() const { return VEC_MEMBER(SquareRoot((X * X) + (Y * Y) + (Z * Z))); }
		VEC_MEMBER MagnitudeSquared() const { return VEC_MEMBER((X * X) + (Y * Y) + (Z * Z)); }

		void Normalize();
		bool IsNormalized() const { VEC_MEMBER Magnitude_ = Magnitude(); return ((Magnitude_ >= VEC_MEMBER(0.999999)) && (Magnitude_ <= VEC_MEMBER(1.000001))); }
		bool IsNormalizedFast() const { VEC_MEMBER Magnitude_ = MagnitudeSquared(); return ((Magnitude_ >= VEC_MEMBER(0.999)) && (Magnitude_ <= VEC_MEMBER(1.001))); }

	private:
		/**
		 * Prevent Usage Of Postfix Operators For Prevention Of
		 * Temporary Object Allocation and Deallocation.
		 * Credit: http://www.tantalon.com/pete/cppopt/asyougo.htm
		 */
		Vector3 operator++(int);
		Vector3 operator--(int);
	};

	REDINLINE Vector3& Vector3::operator=(const Vector3& Target)
	{
		X = Target.X;
		Y = Target.Y;
		Z = Target.Z;

		return *this;
	}

	REDINLINE Vector3& Vector3::operator=(VEC_MEMBER Scalar)
	{
		X = Scalar;
		Y = Scalar;
		Z = Scalar;

		return *this;
	}

	REDINLINE Vector3 Vector3::operator+(const Vector3& Target) const
	{
		return Vector3(X + Target.X, Y + Target.Y, Z + Target.Z);
	}

	REDINLINE Vector3 Vector3::operator+(VEC_MEMBER Scalar) const
	{
		return Vector3(X + Scalar, Y + Scalar, Z + Scalar);
	}

	REDINLINE Vector3 Vector3::operator-() const
	{
		return Vector3(-X, -Y, -Z);
	}

	REDINLINE Vector3 Vector3::operator-(const Vector3& Target) const
	{
		return Vector3(X - Target.X, Y - Target.Y, Z - Target.Z);
	}

	REDINLINE Vector3 Vector3::operator-(VEC_MEMBER Scalar) const
	{
		return Vector3(X - Scalar, Y - Scalar, Z - Scalar);
	}

	REDINLINE Vector3 Vector3::operator*(const Vector3& Target) const
	{
		return Vector3(X * Target.X, Y * Target.Y, Z * Target.Z);
	}

	REDINLINE Vector3 Vector3::operator*(VEC_MEMBER Scalar) const
	{
		return Vector3(X * Scalar, Y * Scalar, Z * Scalar);
	}

	REDINLINE Vector3 Vector3::operator/(const Vector3& Target) const
	{
		return Vector3(X / Target.X, Y / Target.Y, Z / Target.Z);
	}

	REDINLINE Vector3 Vector3::operator/(VEC_MEMBER Scalar) const
	{
		return Vector3(X / Scalar, Y / Scalar, Z / Scalar);
	}

	REDINLINE Vector3& Vector3::operator+=(const Vector3& Target)
	{
		*this = *this + Target;

		return *this;
	}

	REDINLINE Vector3& Vector3::operator+=(VEC_MEMBER Scalar)
	{
		*this = *this + Scalar;

		return *this;
	}

	REDINLINE Vector3& Vector3::operator-=(const Vector3& Target)
	{
		*this = *this - Target;

		return *this;
	}

	REDINLINE Vector3& Vector3::operator-=(VEC_MEMBER Scalar)
	{
		*this = *this - Scalar;

		return *this;
	}

	REDINLINE Vector3& Vector3::operator*=(const Vector3& Target)
	{
		*this = *this * Target;

		return *this;
	}

	REDINLINE Vector3& Vector3::operator*=(VEC_MEMBER Scalar)
	{
		*this = *this * Scalar;

		return *this;
	}

	REDINLINE Vector3& Vector3::operator/=(const Vector3& Target)
	{
		*this = *this / Target;

		return *this;
	}

	REDINLINE Vector3& Vector3::operator/=(VEC_MEMBER Scalar)
	{
		*this = *this / Scalar;

		return *this;
	}

	REDINLINE Vector3& Vector3::operator++()
	{
		X += 1;
		Y += 1;
		Z += 1;

		return *this;
	}

	REDINLINE Vector3& Vector3::operator--()
	{
		X -= 1;
		Y -= 1;
		Z -= 1;

		return *this;
	}

	REDINLINE bool Vector3::operator==(const Vector3& Target) const
	{
		return ((X == Target.X) && (Y == Target.Y) && (Z == Target.Z));
	}

	REDINLINE bool Vector3::operator==(VEC_MEMBER Scalar) const
	{
		return ((X == Scalar) && (Y == Scalar) && (Z == Scalar));
	}

	REDINLINE bool Vector3::operator!=(const Vector3& Target) const
	{
		return !(operator==(Target));
	}

	REDINLINE bool Vector3::operator!=(VEC_MEMBER Scalar) const
	{
		return !(operator==(Scalar));
	}

	REDINLINE bool Vector3::operator<(const Vector3& Target) const
	{
		return ((X < Target.X) && (Y < Target.Y) && (Z < Target.Z));
	}

	REDINLINE bool Vector3::operator<(VEC_MEMBER Scalar) const
	{
		return ((X < Scalar) && (Y < Scalar) && (Z < Scalar));
	}

	REDINLINE bool Vector3::operator>(const Vector3& Target) const
	{
		return ((X > Target.X) && (Y > Target.Y) && (Z > Target.Z));
	}

	REDINLINE bool Vector3::operator>(VEC_MEMBER Scalar) const
	{
		return ((X > Scalar) && (Y > Scalar) && (Z > Scalar));
	}

	REDINLINE bool Vector3::operator<=(const Vector3& Target) const
	{
		return ((X <= Target.X) && (Y <= Target.Y) && (Z <= Target.Z));
	}

	REDINLINE bool Vector3::operator<=(VEC_MEMBER Scalar) const
	{
		return ((X <= Scalar) && (Y <= Scalar) && (Z <= Scalar));
	}

	REDINLINE bool Vector3::operator>=(const Vector3& Target) const
	{
		return ((X >= Target.X) && (Y >= Target.Y) && (Z >= Target.Z));
	}

	REDINLINE bool Vector3::operator>=(VEC_MEMBER Scalar) const
	{
		return ((X >= Scalar) && (Y >= Scalar) && (Z >= Scalar));
	}

	REDINLINE void Vector3::Normalize()
	{
		VEC_MEMBER Magnitude_ = Magnitude();

#ifdef ASSERTIONS
		assert(Magnitude_ != 0);
#endif

		X /= Magnitude_;
		Y /= Magnitude_;
		Z /= Magnitude_;
	}

	// 16/32-Byte Aligned Vector Of 4 Components, X, Y, Z, W, Determined By VEC_MEMBER
	VEC_ALIGN(16) class Vector4
	{
	public:
		VEC_MEMBER X, Y, Z, W;

	public:
		static const Vector4 ZeroVector;  // ( 0, 0, 0, 0 )

	public:
		Vector4() {}
		Vector4(const Vector4& Target) : X(Target.X), Y(Target.Y), Z(Target.Z), W(Target.W) {}
		Vector4(const Vector3& XYZ, VEC_MEMBER W) : X(XYZ.X), Y(XYZ.Y), Z(XYZ.Z), W(W) {}
		Vector4(const Vector2& XY, const Vector2& ZW) : X(XY.X), Y(XY.Y), Z(ZW.X), W(ZW.Y) {}
		explicit Vector4(VEC_MEMBER X, VEC_MEMBER Y, VEC_MEMBER Z, VEC_MEMBER W) : X(X), Y(Y), Z(Z), W(W) {}
		~Vector4() {}

		Vector4& operator=(const Vector4& Target);
		Vector4& operator=(VEC_MEMBER Scalar);

		Vector4 operator+(const Vector4& Target) const;
		Vector4 operator+(VEC_MEMBER Scalar) const;
		Vector4 operator-() const;
		Vector4 operator-(const Vector4& Target) const;
		Vector4 operator-(VEC_MEMBER Scalar) const;
		Vector4 operator*(const Vector4& Target) const;
		Vector4 operator*(VEC_MEMBER Scalar) const;
		Vector4 operator/(const Vector4& Target) const;
		Vector4 operator/(VEC_MEMBER Scalar) const;

		Vector4& operator+=(const Vector4& Target);
		Vector4& operator+=(VEC_MEMBER Scalar);
		Vector4& operator-=(const Vector4& Target);
		Vector4& operator-=(VEC_MEMBER Scalar);
		Vector4& operator*=(const Vector4& Target);
		Vector4& operator*=(VEC_MEMBER Scalar);
		Vector4& operator/=(const Vector4& Target);
		Vector4& operator/=(VEC_MEMBER Scalar);

		Vector4& operator++();
		Vector4& operator--();

		bool operator==(const Vector4& Target) const;
		bool operator==(VEC_MEMBER Scalar) const;
		bool operator!=(const Vector4& Target) const;
		bool operator!=(VEC_MEMBER Scalar) const;

		bool operator<(const Vector4& Target) const;
		bool operator<(VEC_MEMBER Scalar) const;
		bool operator>(const Vector4& Target) const;
		bool operator>(VEC_MEMBER Scalar) const;

		bool operator<=(const Vector4& Target) const;
		bool operator<=(VEC_MEMBER Scalar) const;
		bool operator>=(const Vector4& Target) const;
		bool operator>=(VEC_MEMBER Scalar) const;

		void ZeroOut() { X = 0; Y = 0; Z = 0; W = 0; }
		bool IsZero() const { return((X == 0) && (Y == 0) && (Z == 0) && (W == 0)); }
		bool IsZero(VEC_MEMBER Threshold) const { return((Abs(X) < Threshold) && (Abs(Y) < Threshold) && (Abs(Z) < Threshold) && (Abs(W) < Threshold)); }

		VEC_MEMBER Magnitude() const { return VEC_MEMBER(SquareRoot((X * X) + (Y * Y) + (Z * Z) + (W * W))); }
		VEC_MEMBER MagnitudeSquared() const { return VEC_MEMBER((X * X) + (Y * Y) + (Z * Z) + (W * W)); }
		VEC_MEMBER Magnitude3() const { return VEC_MEMBER(SquareRoot((X * X) + (Y * Y) + (Z * Z))); }
		VEC_MEMBER MagnitudeSquared3() const { return VEC_MEMBER((X * X) + (Y * Y) + (Z * Z)); }

		void Normalize();
		bool IsNormalized() const { VEC_MEMBER Magnitude_ = Magnitude(); return ((Magnitude_ >= VEC_MEMBER(0.999999)) && (Magnitude_ <= VEC_MEMBER(1.000001))); }
		bool IsNormalizedFast() const { VEC_MEMBER Magnitude_ = MagnitudeSquared(); return ((Magnitude_ >= VEC_MEMBER(0.999)) && (Magnitude_ <= VEC_MEMBER(1.001))); }

	private:
		/**
		* Prevent Usage Of Postfix Operators For Prevention Of
		* Temporary Object Allocation and Deallocation.
		* Credit: http://www.tantalon.com/pete/cppopt/asyougo.htm
		*/
		Vector4 operator++(int);
		Vector4 operator--(int);
	};

	REDINLINE Vector4& Vector4::operator=(const Vector4& Target)
	{
		X = Target.X;
		Y = Target.Y;
		Z = Target.Z;
		W = Target.W;

		return *this;
	}

	REDINLINE Vector4& Vector4::operator=(VEC_MEMBER Scalar)
	{
		X = Scalar;
		Y = Scalar;
		Z = Scalar;
		W = Scalar;

		return *this;
	}

	REDINLINE Vector4 Vector4::operator+(const Vector4& Target) const
	{
		return Vector4(X + Target.X, Y + Target.Y, Z + Target.Z, W + Target.W);
	}

	REDINLINE Vector4 Vector4::operator+(VEC_MEMBER Scalar) const
	{
		return Vector4(X + Scalar, Y + Scalar, Z + Scalar, W + Scalar);
	}

	REDINLINE Vector4 Vector4::operator-() const
	{
		return Vector4(-X, -Y, -Z, -W);
	}

	REDINLINE Vector4 Vector4::operator-(const Vector4& Target) const
	{
		return Vector4(X - Target.X, Y - Target.Y, Z - Target.Z, W - Target.W);
	}

	REDINLINE Vector4 Vector4::operator-(VEC_MEMBER Scalar) const
	{
		return Vector4(X - Scalar, Y - Scalar, Z - Scalar, W - Scalar);
	}

	REDINLINE Vector4 Vector4::operator*(const Vector4& Target) const
	{
		return Vector4(X * Target.X, Y * Target.Y, Z * Target.Z, W * Target.W);
	}

	REDINLINE Vector4 Vector4::operator*(VEC_MEMBER Scalar) const
	{
		return Vector4(X * Scalar, Y * Scalar, Z * Scalar, W * Scalar);
	}

	REDINLINE Vector4 Vector4::operator/(const Vector4& Target) const
	{
		return Vector4(X / Target.X, Y / Target.Y, Z / Target.Z, W / Target.W);
	}

	REDINLINE Vector4 Vector4::operator/(VEC_MEMBER Scalar) const
	{
		return Vector4(X / Scalar, Y / Scalar, Z / Scalar, W / Scalar);
	}

	REDINLINE Vector4& Vector4::operator+=(const Vector4& Target)
	{
		*this = *this + Target;

		return *this;
	}

	REDINLINE Vector4& Vector4::operator+=(VEC_MEMBER Scalar)
	{
		*this = *this + Scalar;

		return *this;
	}

	REDINLINE Vector4& Vector4::operator-=(const Vector4& Target)
	{
		*this = *this - Target;

		return *this;
	}

	REDINLINE Vector4& Vector4::operator-=(VEC_MEMBER Scalar)
	{
		*this = *this - Scalar;

		return *this;
	}

	REDINLINE Vector4& Vector4::operator*=(const Vector4& Target)
	{
		*this = *this * Target;

		return *this;
	}

	REDINLINE Vector4& Vector4::operator*=(VEC_MEMBER Scalar)
	{
		*this = *this * Scalar;

		return *this;
	}

	REDINLINE Vector4& Vector4::operator/=(const Vector4& Target)
	{
		*this = *this / Target;

		return *this;
	}

	REDINLINE Vector4& Vector4::operator/=(VEC_MEMBER Scalar)
	{
		*this = *this / Scalar;

		return *this;
	}

	REDINLINE Vector4& Vector4::operator++()
	{
		X += 1;
		Y += 1;
		Z += 1;
		W += 1;

		return *this;
	}

	REDINLINE Vector4& Vector4::operator--()
	{
		X -= 1;
		Y -= 1;
		Z -= 1;
		W -= 1;

		return *this;
	}

	REDINLINE bool Vector4::operator==(const Vector4& Target) const
	{
		return ((X == Target.X) && (Y == Target.Y) && (Z == Target.Z) && (W == Target.W));
	}

	REDINLINE bool Vector4::operator==(VEC_MEMBER Scalar) const
	{
		return ((X == Scalar) && (Y == Scalar) && (Z == Scalar) && (W == Scalar));
	}

	REDINLINE bool Vector4::operator!=(const Vector4& Target) const
	{
		return !(operator==(Target));
	}

	REDINLINE bool Vector4::operator!=(VEC_MEMBER Scalar) const
	{
		return !(operator==(Scalar));
	}

	REDINLINE bool Vector4::operator<(const Vector4& Target) const
	{
		return ((X < Target.X) && (Y < Target.Y) && (Z < Target.Z) && (W < Target.W));
	}

	REDINLINE bool Vector4::operator<(VEC_MEMBER Scalar) const
	{
		return ((X < Scalar) && (Y < Scalar) && (Z < Scalar) && (W < Scalar));
	}

	REDINLINE bool Vector4::operator>(const Vector4& Target) const
	{
		return ((X > Target.X) && (Y > Target.Y) && (Z > Target.Z) && (W > Target.W));
	}

	REDINLINE bool Vector4::operator>(VEC_MEMBER Scalar) const
	{
		return ((X > Scalar) && (Y > Scalar) && (Z > Scalar) && (W > Scalar));
	}

	REDINLINE bool Vector4::operator<=(const Vector4& Target) const
	{
		return ((X <= Target.X) && (Y <= Target.Y) && (Z <= Target.Z) && (W <= Target.W));
	}

	REDINLINE bool Vector4::operator<=(VEC_MEMBER Scalar) const
	{
		return ((X <= Scalar) && (Y <= Scalar) && (Z <= Scalar) && (W <= Scalar));
	}

	REDINLINE bool Vector4::operator>=(const Vector4& Target) const
	{
		return ((X >= Target.X) && (Y >= Target.Y) && (Z >= Target.Z) && (W >= Target.W));
	}

	REDINLINE bool Vector4::operator>=(VEC_MEMBER Scalar) const
	{
		return ((X >= Scalar) && (Y >= Scalar) && (Z >= Scalar) && (W >= Scalar));
	}

	REDINLINE void Vector4::Normalize()
	{
		VEC_MEMBER Magnitude_ = Magnitude();

#ifdef ASSERTIONS
		assert(Magnitude_ != 0);
#endif

		X /= Magnitude_;
		Y /= Magnitude_;
		Z /= Magnitude_;
		W /= Magnitude_;
	}

	// Vector Operations

	REDINLINE VEC_MEMBER Dot(const Vector2& TargetA, const Vector2& TargetB)
	{
		return VEC_MEMBER(TargetA.X * TargetB.X + TargetA.Y * TargetB.Y);
	}

	REDINLINE VEC_MEMBER Dot(const Vector3& TargetA, const Vector3& TargetB)
	{
		return VEC_MEMBER(TargetA.X * TargetB.X + TargetA.Y * TargetB.Y + TargetA.Z * TargetB.Z);
	}

	REDINLINE VEC_MEMBER Dot(const Vector4& TargetA, const Vector4& TargetB)
	{
		return VEC_MEMBER(TargetA.X * TargetB.X + TargetA.Y * TargetB.Y + TargetA.Z * TargetB.Z + TargetA.W * TargetB.W);
	}

	REDINLINE void Cross(Vector3* Result, const Vector3& TargetA, const Vector3& TargetB)
	{
		*Result = Vector3(
			TargetA.Y * TargetB.Z - TargetA.Z * TargetB.Y,
			TargetA.Z * TargetB.X - TargetA.X * TargetB.Z,
			TargetA.X * TargetB.Y - TargetA.Y * TargetB.X
		);
	}

	REDINLINE void Cross(Vector4* Result, const Vector4& TargetA, const Vector4& TargetB)
	{
		*Result = Vector4(
			TargetA.Y * TargetB.Z - TargetA.Z * TargetB.Y,
			TargetA.Z * TargetB.X - TargetA.X * TargetB.Z,
			TargetA.X * TargetB.Y - TargetA.Y * TargetB.X,
			0
		);
	}

	REDINLINE void Clamp(Vector2* Result, const Vector2& Target, VEC_MEMBER MinX, VEC_MEMBER MinY, VEC_MEMBER MaxX, VEC_MEMBER MaxY)
	{
		*Result = (
			((Target.X > MinX) ? ((Target.X < MaxX) ? Target.X : MaxX) : MinX),
			((Target.Y > MinY) ? ((Target.Y < MaxY) ? Target.Y : MaxY) : MinY)
			);
	}

	REDINLINE void Clamp(Vector2* Result, const Vector2& Target, const Vector2& Min, const Vector2& Max)
	{
		*Result = (
			((Target.X > Min.X) ? ((Target.X < Max.X) ? Target.X : Max.X) : Min.X),
			((Target.Y > Min.Y) ? ((Target.Y < Max.Y) ? Target.Y : Max.Y) : Min.Y)
			);
	}

	REDINLINE void Clamp(Vector3* Result, const Vector3& Target, VEC_MEMBER MinX, VEC_MEMBER MinY, VEC_MEMBER MinZ, VEC_MEMBER MaxX, VEC_MEMBER MaxY, VEC_MEMBER MaxZ)
	{
		*Result = (
			((Target.X > MinX) ? ((Target.X < MaxX) ? Target.X : MaxX) : MinX),
			((Target.Y > MinY) ? ((Target.Y < MaxY) ? Target.Y : MaxY) : MinY),
			((Target.Z > MinZ) ? ((Target.Z < MaxZ) ? Target.Z : MaxZ) : MinZ)
			);
	}

	REDINLINE void Clamp(Vector3* Result, const Vector3& Target, const Vector3& Min, const Vector3& Max)
	{
		*Result = (
			((Target.X > Min.X) ? ((Target.X < Max.X) ? Target.X : Max.X) : Min.X),
			((Target.Y > Min.Y) ? ((Target.Y < Max.Y) ? Target.Y : Max.Y) : Min.Y),
			((Target.Z > Min.Z) ? ((Target.Z < Max.Z) ? Target.Z : Max.Z) : Min.Z)
			);
	}

	REDINLINE void Clamp(Vector4* Result, const Vector4& Target, VEC_MEMBER MinX, VEC_MEMBER MinY, VEC_MEMBER MinZ, VEC_MEMBER MinW, VEC_MEMBER MaxX, VEC_MEMBER MaxY, VEC_MEMBER MaxZ, VEC_MEMBER MaxW)
	{
		*Result = (
			((Target.X > MinX) ? ((Target.X < MaxX) ? Target.X : MaxX) : MinX),
			((Target.Y > MinY) ? ((Target.Y < MaxY) ? Target.Y : MaxY) : MinY),
			((Target.Z > MinZ) ? ((Target.Z < MaxZ) ? Target.Z : MaxZ) : MinZ),
			((Target.W > MinW) ? ((Target.W < MaxW) ? Target.W : MaxW) : MinW)
			);
	}

	REDINLINE void Clamp(Vector4* Result, const Vector4& Target, const Vector4& Min, const Vector4& Max)
	{
		*Result = (
			((Target.X > Min.X) ? ((Target.X < Max.X) ? Target.X : Max.X) : Min.X),
			((Target.Y > Min.Y) ? ((Target.Y < Max.Y) ? Target.Y : Max.Y) : Min.Y),
			((Target.Z > Min.Z) ? ((Target.Z < Max.Z) ? Target.Z : Max.Z) : Min.Z),
			((Target.W > Min.W) ? ((Target.W < Max.W) ? Target.W : Max.W) : Min.W)
			);
	}

	REDINLINE void Lerp(Vector2* Result, const Vector2& Source, const Vector2& Target, float Alpha)
	{
		Vector2 DeltaVec(Target - Source);

		*Result = Source + (DeltaVec * Alpha);
	}

	REDINLINE void Lerp(Vector3* Result, const Vector3& Source, const Vector3& Target, float Alpha)
	{
		Vector3 DeltaVec(Target - Source);

		*Result = Source + (DeltaVec * Alpha);
	}

	REDINLINE void Lerp(Vector4* Result, const Vector4& Source, const Vector4& Target, float Alpha)
	{
		Vector4 DeltaVec(Target - Source);

		*Result = Source + (DeltaVec * Alpha);
	}
}  // namespace Red