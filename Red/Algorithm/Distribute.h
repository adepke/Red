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
			if (Total != 0 && ChunkCount != 0)
			{
				Type ChunkSize(Total / ChunkCount);

				for (unsigned int Iter = 0; Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination[Iter] = ChunkSize + (Red::Modulus(Total, static_cast<Type>(ChunkCount)));
					else
						Destination[Iter] = ChunkSize;
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
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination->push_back(ChunkSize + (Red::Modulus(Total, static_cast<Type>(ChunkCount))));
					else
						Destination->push_back(ChunkSize);
				}
			}

			else
			{
				Destination->push_back(0);
			}
		}
	}
}  // namespace Red