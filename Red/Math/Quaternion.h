#pragma once

#include "MathCore.h"

#include "Vector.h"

#ifdef ASSERTIONS
#include <assert.h>
#endif

#define QUA_ALIGN(n) __declspec(align(n))

namespace Red
{
	// Forward Declaration of Vector2
	class Vector2;
	// Forward Declaration of Vector3
	class Vector3;
	// Forward Declaration of Vector4
	class Vector4;

	// 16-Byte Aligned Quaternion Containing X, Y, Z, and W
	QUA_ALIGN(16) class Quaternion
	{
	public:
		float X, Y, Z, W;

	public:
		static const Quaternion ZeroQuaternion;      // ( 0, 0, 0, 0 )
		static const Quaternion IdentityQuaternion;  // ( 0, 0, 0, 1 )

	public:
		Quaternion() {}
		Quaternion(const Quaternion& Target) : X(Target.X), Y(Target.Y), Z(Target.Z), W(Target.W) {}
		Quaternion(const Vector4& XYZW) : X(XYZW.X), Y(XYZW.Y), Z(XYZW.Z), W(XYZW.W) {}
		Quaternion(const Vector3& XYZ, float W) : X(XYZ.X), Y(XYZ.Y), Z(XYZ.Z), W(W) {}
		Quaternion(const Vector2& XY, const Vector2& ZW) : X(XY.X), Y(XY.Y), Z(ZW.X), W(ZW.Y) {}
		explicit Quaternion(float X, float Y, float Z, float W) : X(X), Y(Y), Z(Z), W(W) {}
		~Quaternion() {}

		Quaternion& operator=(const Quaternion& Target);

		Quaternion operator+(const Quaternion& Target) const;
		Quaternion operator-() const;
		Quaternion operator-(const Quaternion& Target) const;
		Quaternion operator*(const Quaternion& Target) const;
		Quaternion operator*(float Scalar) const;
		Vector3    operator*(const Vector3& Target) const;
		Quaternion operator/(float Scalar) const;

		Quaternion& operator+=(const Quaternion& Target);
		Quaternion& operator-=(const Quaternion& Target);
		Quaternion& operator*=(const Quaternion& Target);
		Quaternion& operator*=(float Scalar);
		Quaternion& operator/=(float Scalar);

		bool operator==(const Quaternion& Target) const;
		bool operator!=(const Quaternion& Target) const;

		void ToAxisAngle(Vector3& Axis, float& Angle) const;

		Vector3 RotateVector(const Vector3& Target) const;
		Vector3 UnrotateVector(const Vector3& Target) const;

		void ZeroOut() { X = 0; Y = 0; Z = 0; W = 0; }
		bool IsZero() const { return((X == 0) && (Y == 0) && (Z == 0) && (W == 0)); }
		bool IsZero(float Threshold) const { return((Abs(X) < Threshold) && (Abs(Y) < Threshold) && (Abs(Z) < Threshold) && (Abs(W) < Threshold)); }

		float Magnitude() const { return (SquareRoot(X * X + Y * Y + Z * Z + W * W)); }
		float MagnitudeSquared() const { return (X * X + Y * Y + Z * Z + W * W); }

		void Normalize();
		bool IsNormalized() const { float Magnitude_ = Magnitude(); return ((Magnitude_ >= 0.999999f) && (Magnitude_ <= 1.000001f)); }
		bool IsNormalizedFast() const { float Magnitude_ = MagnitudeSquared(); return ((Magnitude_ >= 0.999f) && (Magnitude_ <= 1.001f)); }
	};

	Quaternion& Quaternion::operator=(const Quaternion& Target)
	{
		X = Target.X;
		Y = Target.Y;
		Z = Target.Z;
		W = Target.W;

		return *this;
	}

	Quaternion Quaternion::operator+(const Quaternion& Target) const
	{
		return Quaternion(X + Target.X, Y + Target.Y, Z + Target.Z, W + Target.W);
	}

	Quaternion Quaternion::operator-() const
	{
		return Quaternion(-X, -Y, -Z, W);
	}

	Quaternion Quaternion::operator-(const Quaternion& Target) const
	{
		return Quaternion(X - Target.X, Y - Target.Y, Z - Target.Z, W - Target.W);
	}

	Quaternion Quaternion::operator*(const Quaternion& Target) const
	{
		return Quaternion(
			(W * Target.X + X * Target.W + Y * Target.Z - Z * Target.Y),
			(W * Target.Y - X * Target.Z + Y * Target.W + Z * Target.X),
			(W * Target.Z + X * Target.Y - Y * Target.X + Z * Target.W),
			(W * Target.W - X * Target.X - Y * Target.Y - Z * Target.Z)
		);
	}

	Quaternion Quaternion::operator*(float Scalar) const
	{
		return Quaternion(X * Scalar, Y * Scalar, Z * Scalar, W * Scalar);
	}

	Vector3 Quaternion::operator*(const Vector3& Target) const
	{
		return RotateVector(Target);
	}

	Quaternion Quaternion::operator/(float Scalar) const
	{
		float ScalarInv = 1.0f / Scalar;

		return Quaternion(X * ScalarInv, Y * ScalarInv, Z * ScalarInv, W * ScalarInv);
	}

	Quaternion& Quaternion::operator+=(const Quaternion& Target)
	{
		*this = *this + Target;

		return *this;
	}

	Quaternion& Quaternion::operator-=(const Quaternion& Target)
	{
		*this = *this - Target;

		return *this;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& Target)
	{
		*this = *this * Target;

		return *this;
	}

	Quaternion& Quaternion::operator*=(float Scalar)
	{
		*this = *this * Scalar;

		return *this;
	}

	Quaternion& Quaternion::operator/=(float Scalar)
	{
		*this = *this / Scalar;

		return *this;
	}

	bool Quaternion::operator==(const Quaternion& Target) const
	{
		return ((X == Target.X) && (Y == Target.Y) && (Z == Target.Z) && (W == Target.W));
	}

	bool Quaternion::operator!=(const Quaternion& Target) const
	{
		return !(operator==(Target));
	}

	void Quaternion::ToAxisAngle(Vector3& Axis, float& Angle) const
	{
		const float SafeW = SquareRoot(Max(1.0f - (W * W), 0.0f));
		if (SafeW >= 0.0001f)
		{
			Axis = Vector3(X / SafeW, Y / SafeW, Z / SafeW);
		}

		else
		{
			Axis = Vector3(1.0f, 0.0f, 0.0f);
		}

		Angle = 2.0f * std::acos(W);
	}

	Vector3 Quaternion::RotateVector(const Vector3& Target) const
	{
		const Vector3 Q(X, Y, Z);
		Vector3 T;
		Vector3 U;
		Cross(&T, Q, Target);
		T *= 2.0f;
		Cross(&U, Q, T);

		return Vector3(Target + (T * W) + U);
	}

	Vector3 Quaternion::UnrotateVector(const Vector3& Target) const
	{
		const Vector3 Q(-X, -Y, -Z);
		Vector3 T;
		Vector3 U;
		Cross(&T, Q, Target);
		T *= 2.0f;
		Cross(&U, Q, T);

		return Vector3(Target + (T * W) + U);
	}

	void Quaternion::Normalize()
	{
		float Magnitude_ = Magnitude();

#ifdef ASSERTIONS
		assert(Magnitude_ != 0);
#endif

		X /= Magnitude_;
		Y /= Magnitude_;
		Z /= Magnitude_;
		W /= Magnitude_;
	}

	// Quaternion Operations

	float Dot(const Quaternion& TargetA, const Quaternion& TargetB)
	{
		return (TargetA.X * TargetB.X + TargetA.Y * TargetB.Y + TargetA.Z * TargetB.Z + TargetA.W * TargetB.W);
	}

	// Unnormalized Linear Interpolation
	void Lerp(Quaternion& Result, const Quaternion& TargetA, const Quaternion& TargetB, float Alpha)
	{
		Result = Quaternion((TargetB * Alpha) + (TargetA * ((Dot(TargetA, TargetB) >= 0.0f ? 1.0f : 0.0f) * (1.0f - Alpha))));
	}

	// Unnormalized Spherical Interpolation
	void Slerp(Quaternion& Result, const Quaternion& TargetA, const Quaternion& TargetB, float Alpha)
	{
		const float Magnitude_ = TargetA.X * TargetB.X + TargetA.Y * TargetB.Y + TargetA.Z * TargetB.Z + TargetA.W * TargetB.W;
		const float Mag = Magnitude_ >= 0 ? Magnitude_ : -Magnitude_;

		float Scale0, Scale1;

		if (Mag < 0.9999f)
		{
			const float Omega = std::acos(Mag);
			const float InvSin = 1.0f / std::sin(Omega);
			Scale0 = std::sin((1.0f - Alpha) * Omega) * InvSin;
			Scale1 = std::sin(Alpha * Omega) * InvSin;
		}

		else
		{
			// Revert to linear interpolation
			Scale0 = 1.0f - Alpha;
			Scale1 = Alpha;
		}

		Scale1 = Magnitude_ >= 0.0f ? Scale1 : -Scale1;

		Result = Quaternion(
			Scale0 * TargetA.X + Scale1 * TargetB.X,
			Scale0 * TargetA.Y + Scale1 * TargetB.Y,
			Scale0 * TargetA.Z + Scale1 * TargetB.Z,
			Scale0 * TargetA.W + Scale1 * TargetB.W
		);
	}

}  // namespace Red