#pragma once

#include <cmath>

#ifdef FORCEDINLINES
#define REDINLINE __forceinline
#else
#define REDINLINE inline
#endif

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
	template <int Base, short int Exponent>
	struct Power_MT
	{
		enum : long int { Value = (Base * Power_MT<Base, Exponent - 1>::Value) };
	};

	template <int Base>
	struct Power_MT<Base, 1>
	{
		enum : long int { Value = Base };
	};

	template <int Base>
	struct Power_MT<Base, 0>
	{
		enum : long int { Value = 1 };
	};

	// Square Root [CMath Built-in]
	REDINLINE float SquareRoot(float Target)
	{
		return std::sqrtf(Target);
	}

	REDINLINE double SquareRoot(double Target)
	{
		return std::sqrt(Target);
	}

	REDINLINE long double SquareRoot(long double Target)
	{
		return std::sqrtl(Target);
	}

	// Modulus [CMath Built-in]
	REDINLINE float Modulus(float TargetA, float TargetB) noexcept
	{
		return std::fmodf(TargetA, TargetB);
	}

	REDINLINE double Modulus(double TargetA, double TargetB) noexcept
	{
		return std::fmod(TargetA, TargetB);
	}

	REDINLINE long double Modulus(long double TargetA, long double TargetB) noexcept
	{
		return std::fmodl(TargetA, TargetB);
	}

	// Factorial [Recursive Algorithm]
	constexpr unsigned long int Factorial(unsigned int Factor) noexcept
	{
		return (Factor == 1 ? 1 : Factor * Factorial(Factor - 1));
	}

	// Meta Factorial (Baked Expression)
	template <unsigned int Factor>
	struct Factorial_MT
	{
		enum : unsigned long int { Value = (Factor * Factorial_MT<Factor - 1>::Value) };
	};

	template <>
	struct Factorial_MT<0>
	{
		enum : unsigned long int { Value = 1 };
	};
}  // namespace Red