#pragma once

#include <cmath>

namespace Red
{
	template <typename Type>
	constexpr Type Abs(Type Target) noexcept
	{
		return (Target >= 0 ? Target : Target * -1);
	}

	template <>
	constexpr float Abs<float>(float Target) noexcept
	{
		return (Target >= 0.0f ? Target : Target * -1.0f);
	}

	template <>
	constexpr double Abs<double>(double Target) noexcept
	{
		return (Target >= 0.0 ? Target : Target * -1.0);
	}

	template <>
	constexpr long double Abs<long double>(long double Target) noexcept
	{
		return (Target >= 0.0L ? Target : Target * -1.0L);
	}

	template <typename Type>
	constexpr Type Min(Type TargetA, Type TargetB) noexcept
	{
		return (TargetA <= TargetB ? TargetA : TargetB);
	}

	template <typename Type>
	constexpr Type Max(Type TargetA, Type TargetB) noexcept
	{
		return (TargetA >= TargetB ? TargetA : TargetB);
	}

	// Power [Exponentiation by Squaring Algorithm]
	template <typename Type>
	Type Power(Type Base, Type Exponent) noexcept
	{
		Type Result(1);
		while (Exponent)
		{
			if (Exponent & 1)
				Result *= Base;

			Exponent >>= 1;

			Base *= Base;
		}

		return Result;
	}

	// Meta Power (Baked Expression)
	template <int32 Base, int16 Exponent>
	struct Power_MT
	{
		enum : int64 { Value = (Base * Power_MT<Base, Exponent - 1>::Value) };
	};

	template <int32 Base>
	struct Power_MT<Base, 1>
	{
		enum : int64 { Value = Base };
	};

	template <int32 Base>
	struct Power_MT<Base, 0>
	{
		enum : int64 { Value = 1 };
	};

	// Square Root [CMath Built-in]
	float SquareRoot(float Target)
	{
		return std::sqrtf(Target);
	}

	double SquareRoot(double Target)
	{
		return std::sqrt(Target);
	}

	long double SquareRoot(long double Target)
	{
		return std::sqrtl(Target);
	}

	// Modulus [CMath Built-in]
	float Modulus(float TargetA, float TargetB) noexcept
	{
		return std::fmodf(TargetA, TargetB);
	}

	double Modulus(double TargetA, double TargetB) noexcept
	{
		return std::fmod(TargetA, TargetB);
	}

	long double Modulus(long double TargetA, long double TargetB) noexcept
	{
		return std::fmodl(TargetA, TargetB);
	}

	// Factorial [Recursive Algorithm]
	constexpr uint64 Factorial(uint32 Factor) noexcept
	{
		return (Factor == 1 ? 1 : Factor * Factorial(Factor - 1));
	}

	// Meta Factorial (Baked Expression)
	template <uint32 Factor>
	struct Factorial_MT
	{
		enum : uint64 { Value = (Factor * Factorial_MT<Factor - 1>::Value) };
	};

	template <>
	struct Factorial_MT<0>
	{
		enum : uint64 { Value = 1 };
	};
}  // namespace Red