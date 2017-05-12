#pragma once

#include <vector>

namespace Red
{
	namespace Algorithm
	{
		template <typename Type>
		void Distribute(Type* Destination, Type&& Total, int&& ChunkCount, bool IncludeRemainder = true)
		{
			if (Destination)
			{
				Type ChunkSize(Total / ChunkCount);

				for (int Iter(0); Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination[Iter] = ChunkSize + (Total % ChunkCount);
					else
						Destination[Iter] = ChunkSize;
				}
			}
		}

		template <>
		void Distribute<int>(int* Destination, int&& Total, int&& ChunkCount, bool IncludeRemainder)
		{
			if (Destination)
			{
				int ChunkSize(Total / ChunkCount);

				for (int Iter(0); Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination[Iter] = ChunkSize + (Total % ChunkCount);
					else
						Destination[Iter] = ChunkSize;
				}
			}
		}

		template <>
		void Distribute<float>(float* Destination, float&& Total, int&& ChunkCount, bool IncludeRemainder)
		{
			if (Destination)
			{
				float ChunkSize(Total / ChunkCount);

				for (int Iter(0); Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination[Iter] = ChunkSize + (std::fmodf(Total, ChunkCount));
					else
						Destination[Iter] = ChunkSize;
				}
			}
		}

		template <>
		void Distribute<double>(double* Destination, double&& Total, int&& ChunkCount, bool IncludeRemainder)
		{
			if (Destination)
			{
				float ChunkSize(Total / ChunkCount);

				for (int Iter(0); Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination[Iter] = ChunkSize + (std::fmod(Total, ChunkCount));
					else
						Destination[Iter] = ChunkSize;
				}
			}
		}

		template <>
		void Distribute <long double> (long double* Destination, long double&& Total, int&& ChunkCount, bool IncludeRemainder)
		{
			if (Destination)
			{
				float ChunkSize(Total / ChunkCount);

				for (int Iter(0); Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination[Iter] = ChunkSize + (std::fmodl(Total, ChunkCount));
					else
						Destination[Iter] = ChunkSize;
				}
			}
		}

		template <typename Type>
		void Distribute(std::vector<Type>* Destination, Type&& Total, int&& ChunkCount, bool IncludeRemainder = true)
		{
			if (Destination)
			{
				Type ChunkSize(Total / ChunkCount);

				if (!Destination->empty())
					Destination->clear();

				for (int Iter(0); Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination->push_back(ChunkSize + (Total % ChunkCount));
					else
						Destination->push_back(ChunkSize);
				}
			}
		}

		template <>
		void Distribute<int>(std::vector<int>* Destination, int&& Total, int&& ChunkCount, bool IncludeRemainder)
		{
			if (Destination)
			{
				int ChunkSize(Total / ChunkCount);

				if (!Destination->empty())
					Destination->clear();

				for (int Iter(0); Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination->push_back(ChunkSize + (Total % ChunkCount));
					else
						Destination->push_back(ChunkSize);
				}
			}
		}

		template <>
		void Distribute<float>(std::vector<float>* Destination, float&& Total, int&& ChunkCount, bool IncludeRemainder)
		{
			if (Destination)
			{
				int ChunkSize(Total / ChunkCount);

				if (!Destination->empty())
					Destination->clear();

				for (int Iter(0); Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination->push_back(ChunkSize + (std::fmodf(Total, ChunkCount)));
					else
						Destination->push_back(ChunkSize);
				}
			}
		}

		template <>
		void Distribute<double>(std::vector<double>* Destination, double&& Total, int&& ChunkCount, bool IncludeRemainder)
		{
			if (Destination)
			{
				int ChunkSize(Total / ChunkCount);

				if (!Destination->empty())
					Destination->clear();

				for (int Iter(0); Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination->push_back(ChunkSize + (std::fmod(Total, ChunkCount)));
					else
						Destination->push_back(ChunkSize);
				}
			}
		}

		template <>
		void Distribute<long double>(std::vector<long double>* Destination, long double&& Total, int&& ChunkCount, bool IncludeRemainder)
		{
			if (Destination)
			{
				int ChunkSize(Total / ChunkCount);

				if (!Destination->empty())
					Destination->clear();

				for (int Iter(0); Iter < ChunkCount; ++Iter)
				{
					if ((Iter == (ChunkCount - 1)) && IncludeRemainder)
						Destination->push_back(ChunkSize + (std::fmodl(Total, ChunkCount)));
					else
						Destination->push_back(ChunkSize);
				}
			}
		}
	}  // namespace Algorithm
}  // namespace Red