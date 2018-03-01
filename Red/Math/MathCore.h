#pragma once

#include <cmath>

#include "../Core/Platform.h"

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

	// Power [CMath Built-in]
	REDINLINE float Power(float Target, float Exponent)
	{
#if OS_WINDOWS
		return std::powf(Target, Exponent);
#else
		return powf(Target);
#endif
	}

	REDINLINE double Power(double Target, double Exponent)
	{
#if OS_WINDOWS
		return std::pow(Target, Exponent);
#else
		return pow(Target);
#endif
	}

	REDINLINE long double Power(long double Target, long double Exponent)
	{
#if OS_WINDOWS
		return std::powl(Target, Exponent);
#else
		return powl(Target);
#endif
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
#if OS_WINDOWS
		return std::sqrtf(Target);
#else
		return sqrtf(Target);
#endif
	}

	REDINLINE double SquareRoot(double Target)
	{
#if OS_WINDOWS
		return std::sqrt(Target);
#else
		return sqrt(Target);
#endif
	}

	REDINLINE long double SquareRoot(long double Target)
	{
#if OS_WINDOWS
		return std::sqrtl(Target);
#else
		return sqrtl(Target);
#endif
	}

	// Modulus
	REDINLINE int Modulus(int TargetA, int TargetB) noexcept
	{
		return TargetA % TargetB;
	}

	// Modulus [CMath Built-in]
	REDINLINE float Modulus(float TargetA, float TargetB) noexcept
	{
#if OS_WINDOWS
		return std::fmodf(TargetA, TargetB);
#else
		return fmodf(TargetA, TargetB);
#endif
	}

	REDINLINE double Modulus(double TargetA, double TargetB) noexcept
	{
#if OS_WINDOWS
		return std::fmod(TargetA, TargetB);
#else
		return fmod(TargetA, TargetB);
#endif
	}

	REDINLINE long double Modulus(long double TargetA, long double TargetB) noexcept
	{
#if OS_WINDOWS
		return std::fmodl(TargetA, TargetB);
#else
		return fmodl(TargetA, TargetB);
#endif
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
