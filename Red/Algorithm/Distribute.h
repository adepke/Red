/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "../Core/Definitions.h"
#include "../Math/MathCore.h"

#include <vector>

namespace Red
{
	namespace Internal
	{
		template <typename Type>
		struct RemainderType
		{
			static constexpr bool Value = false;
		};

		template <>
		struct RemainderType<float>
		{
			static constexpr bool Value = true;
		};

		template <>
		struct RemainderType<double>
		{
			static constexpr bool Value = true;
		};

		template <>
		struct RemainderType<long double>
		{
			static constexpr bool Value = true;
		};
	}  // namespace Internal

	// Destination Must Have ChunkCount * Type Bytes Allocated!
	template <typename Type>
	void Distribute(Type* Destination, Type Total, unsigned int ChunkCount, bool IncludeRemainder = true)
	{
		if (Destination)
		{
			if (Total != 0 && ChunkCount != 0)
			{
				Type ChunkSize{ Total / static_cast<Type>(ChunkCount) };

				for (unsigned int Iter = 0; Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder && Internal::RemainderType<Type>::Value == false)
					{
						Destination[Iter] = ChunkSize + (Red::Modulus(Total, static_cast<Type>(ChunkCount)));
					}

					else
					{
						Destination[Iter] = ChunkSize;
					}
				}
			}

			else
			{
				*Destination = 0;
			}
		}
	}

	template <typename Type>
	void Distribute(std::vector<Type>* Destination, Type Total, unsigned int ChunkCount, bool IncludeRemainder = true)
	{
		if (Destination)
		{
			if (Total != 0 && ChunkCount != 0)
			{
				Type ChunkSize(Total / ChunkCount);

				if (!Destination->empty())
					Destination->clear();

				for (unsigned int Iter = 0; Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder && Internal::RemainderType<Type>::Value == false)
					{
						Destination->push_back(ChunkSize + (Red::Modulus(Total, static_cast<Type>(ChunkCount))));
					}

					else
					{
						Destination->push_back(ChunkSize);
					}
				}
			}

			else
			{
				Destination->push_back(0);
			}
		}
	}
}  // namespace Red