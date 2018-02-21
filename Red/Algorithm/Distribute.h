#pragma once

#include "../Core/Definitions.h"
#include "../Math/MathCore.h"

#include <vector>

namespace Red
{
	template <typename Type>
	void Distribute(Type* Destination, Type Total, unsigned int ChunkCount, bool IncludeRemainder = true)
	{
		if (Destination)
		{
			Type ChunkSize(Total / ChunkCount);

			for (int Iter(0); Iter < ChunkCount; ++Iter)
			{
				if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
					Destination[Iter] = ChunkSize + (Red::Modulus(Total, ChunkCount));
				else
					Destination[Iter] = ChunkSize;
			}
		}
	}

	template <typename Type>
	void Distribute(std::vector<Type>* Destination, Type Total, unsigned int ChunkCount, bool IncludeRemainder = true)
	{
		if (Destination)
		{
			Type ChunkSize(Total / ChunkCount);

			if (!Destination->empty())
				Destination->clear();

			for (int Iter(0); Iter < ChunkCount; ++Iter)
			{
				if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
					Destination->push_back(ChunkSize + (Red::Modulus(Total, ChunkCount)));
				else
					Destination->push_back(ChunkSize);
			}
		}
	}
}  // namespace Red