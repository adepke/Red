#pragma once

#include <cmath>

#ifdef ASSERTIONS
#include <assert.h>
#endif

#define QUA_ALIGN(n) __declspec(align(n))

namespace Red
{
	namespace Math
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
			Quaternion& operator=(float Scalar);

			Quaternion operator+(const Quaternion& Target) const;
			Quaternion operator+(float Scalar) const;
			Quaternion operator-() const;
			Quaternion operator-(const Quaternion& Target) const;
			Quaternion operator-(float Scalar) const;
			Quaternion operator*(const Quaternion& Target) const;
			Quaternion operator*(float Scalar) const;
			Quaternion operator/(const Quaternion& Target) const;
			Quaternion operator/(float Scalar) const;

			Quaternion& operator+=(const Quaternion& Target);
			Quaternion& operator+=(float Scalar);
			Quaternion& operator-=(const Quaternion& Target);
			Quaternion& operator-=(float Scalar);
			Quaternion& operator*=(const Quaternion& Target);
			Quaternion& operator*=(float Scalar);
			Quaternion& operator/=(const Quaternion& Target);
			Quaternion& operator/=(float Scalar);

			bool operator==(const Quaternion& Target) const;
			bool operator==(VEC_MEMBER Scalar) const;
			bool operator!=(const Quaternion& Target) const;
			bool operator!=(VEC_MEMBER Scalar) const;

			void ZeroOut() { X = 0; Y = 0; Z = 0; W = 0; }
			bool IsZero() const { return((X == 0) && (Y == 0) && (Z == 0) && (W == 0)); }
			bool IsZero(float Threshold) const { return((std::abs(X) < Threshold) && (std::abs(Y) < Threshold) && (std::abs(Z) < Threshold) && (std::abs(W) < Threshold)); }

			float Magnitude() const { return (std::sqrt(X * X + Y * Y + Z * Z + W * W)); }
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

		Quaternion& Quaternion::operator=(float Scalar)
		{
			X = Scalar;
			Y = Scalar;
			Z = Scalar;
			W = Scalar;

			return *this;
		}

		Quaternion Quaternion::operator+(const Quaternion& Target) const
		{
			return Quaternion(X + Target.X, Y + Target.Y, Z + Target.Z, W + Target.W);
		}

		Quaternion Quaternion::operator+(float Scalar) const
		{
			return Quaternion(X + Scalar, Y + Scalar, Z + Scalar, W + Scalar);
		}

		Quaternion Quaternion::operator-() const
		{
			return Quaternion(-X, -Y, -Z, -W);
		}

		Quaternion Quaternion::operator-(const Quaternion& Target) const
		{
			return Quaternion(X - Target.X, Y - Target.Y, Z - Target.Z, W - Target.W);
		}

		Quaternion Quaternion::operator-(float Scalar) const
		{
			return Quaternion(X - Scalar, Y - Scalar, Z - Scalar, W - Scalar);
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

		Quaternion Quaternion::operator/(const Quaternion& Target) const
		{
			//return ((*this) * (operator-(Target)));

			return ZeroQuaternion;
		}

		Quaternion Quaternion::operator/(float Scalar) const
		{
			return Quaternion(X / Scalar, Y / Scalar, Z / Scalar, W / Scalar);
		}

		Quaternion& Quaternion::operator+=(const Quaternion& Target)
		{
			*this = *this + Target;

			return *this;
		}

		Quaternion& Quaternion::operator+=(float Scalar)
		{
			*this = *this + Scalar;

			return *this;
		}

		Quaternion& Quaternion::operator-=(const Quaternion& Target)
		{
			*this = *this - Target;

			return *this;
		}

		Quaternion& Quaternion::operator-=(float Scalar)
		{
			*this = *this - Scalar;

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

		Quaternion& Quaternion::operator/=(const Quaternion& Target)
		{
			*this = *this / Target;

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

		bool Quaternion::operator==(VEC_MEMBER Scalar) const
		{
			return ((X == Scalar) && (Y == Scalar) && (Z == Scalar) && (W == Scalar));
		}

		bool Quaternion::operator!=(const Quaternion& Target) const
		{
			return !(operator==(Target));
		}

		bool Quaternion::operator!=(VEC_MEMBER Scalar) const
		{
			return !(operator==(Scalar));
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
		}

	}  // namespace Math
}  // namespace Red