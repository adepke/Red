// Copyright (c) 2017 Andrew Depke, Some Rights Reserved

#pragma once

#include "../Core/Definitions.h"

#include <cstdint>

namespace Red
{
	// Function: Houses Lambda and Function Pointer Types.
	template <typename FunctionSignature>
	class Function {};

	// Function Core Class
	template <typename ReturnType, typename... ArgumentTypes>
	class Function<ReturnType(ArgumentTypes...)>
	{
	private:
		// Stores Object Type.
		enum FunctionType : uint8_t
		{
			FT_Unset,
			FT_Lambda,
			FT_FuncPtr,
		} FuncType;

		// Lambda Internals
	private:
		// Use Type Erasure To Hold The True Lambda Type
		struct LambdaConcept
		{
			virtual ~LambdaConcept() {}
			virtual ReturnType operator()(ArgumentTypes&... Arguments) const = 0;
		};

		template <typename Lambda>
		struct LambdaModel : public LambdaConcept
		{
			Lambda FunctionIn;

			LambdaModel(Lambda Func) : FunctionIn(Func) {}
			virtual ~LambdaModel() {}

			// Arguments Are LValue References To Save On Extra Static Cast
			virtual ReturnType operator()(ArgumentTypes&... Arguments) const override
			{
				return FunctionIn(std::forward<ArgumentTypes>(Arguments)...);
			}
		};

		LambdaConcept* Lambda_Internal;

		// Function Pointer Internals
	private:
		// ArgumentTypes Are RValue References. Because By Reference Condensation, Resulting Type Of Native LValue Reference Is LValue Reference
		typedef ReturnType(*FunctionPtr)(ArgumentTypes&&...);

		FunctionPtr Func_Internal;

	public:
		typedef Function<ReturnType(ArgumentTypes...)> Type;

		Function() : FuncType(FunctionType::FT_Unset) {}

		template <typename Lambda>
		Function(Lambda Func) : FuncType(FunctionType::FT_Lambda), Lambda_Internal(new LambdaModel<Lambda>(Func)) {}

		Function(FunctionPtr Func) : FuncType(FunctionType::FT_FuncPtr), Func_Internal(Func) {}

		virtual ~Function()
		{
			if (Lambda_Internal)
			{
				delete Lambda_Internal;
			}
		}

		ReturnType operator()(ArgumentTypes&&... Arguments) const
		{
			if (FuncType == FunctionType::FT_Lambda)
				return Lambda_Internal->operator ()(Arguments...);
			else if (FuncType == FunctionType::FT_FuncPtr)
				return (*Func_Internal)(std::forward<ArgumentTypes>(Arguments)...);

			return ReturnType();
		}

		// Testing For Copy Assignment

		/*
		template <typename DeducedSignature>  // Current Solution To Faking The Lambda Type. This Can't Possibly Work
		Function<ReturnType(ArgumentTypes...)>& operator=(Function<ReturnType(ArgumentTypes...)>& Source)
		{
			if (&Source != this)
			{
				if ((Source.FuncType == FunctionType::FT_Lambda) && Source.Lambda_Internal)
				{
					if (Lambda_Internal)
						delete Lambda_Internal;

					Lambda_Internal = new LambdaModel<DeducedSignature>(Source.Lambda_Internal);
				}

				else if ((Source.FuncType == FunctionType::FT_FuncPtr) && Source.Func_Internal)
					Func_Internal = Source.Func_Internal;
			}

			return *this;
		}
		*/

		template <typename Lambda>
		Function<ReturnType(ArgumentTypes...)>& operator=(Lambda Func)
		{
			FuncType = FunctionType::FT_Lambda;

			if (Lambda_Internal)
				delete Lambda_Internal;

			Lambda_Internal = new LambdaModel<Lambda>(Func);

			return *this;
		}

		Function<ReturnType(ArgumentTypes...)>& operator=(FunctionPtr Func)
		{
			FuncType = FunctionType::FT_FuncPtr;

			Func_Internal = Func;

			return *this;
		}
	};

	// Delegate: Binds a ClassType Object With Member Function Pointer
	template <typename ClassType, typename ReturnType, typename... ArgumentTypes>
	class Delegate
	{
	private:
		typedef ReturnType(ClassType::* MemberFunctionPtr)(ArgumentTypes...);

		ClassType* Owner_Internal;
		MemberFunctionPtr Func_Internal;

	public:
		typedef Delegate<ClassType, ReturnType, ArgumentTypes...> Type;

		Delegate() {}
		Delegate(ClassType& Owner, MemberFunctionPtr Func) : Owner_Internal(&Owner), Func_Internal(Func) {}
		virtual ~Delegate() {}

		ReturnType operator()(ArgumentTypes... Arguments)
		{
			if (Owner_Internal)
				return (Owner_Internal->*Func_Internal)(Arguments...);

			return ReturnType();
		}
	};
}  // namespace Red
