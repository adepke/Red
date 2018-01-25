#pragma once

#include "../Math/Matrix.h"

namespace Red
{
	namespace Internal
	{
		template <int Rows, int Columns>
		int RowZeroCount(const Matrix<Rows, Columns>& Target, int Row)
		{
			int Result = 0;

			for (int Iter = 0; Iter < Columns; ++Iter)
			{
				if (Target.Data[Row][Iter] == 0.f)
				{
					++Result;
				}

				else
				{
					break;
				}
			}

			return Result;
		}

		template <int Rows, int Columns>
		void SwapRow(Matrix<Rows, Columns>& Target, int RowA, int RowB)
		{
			float Swappable[Columns];

			for (int Iter = 0; Iter < Columns; ++Iter)
			{
				Swappable[Iter] = Target.Data[RowA][Iter];

				Target.Data[RowA][Iter] = Target.Data[RowB][Iter];

				Target.Data[RowB][Iter] = Swappable[Iter];
			}
		}
	}  // namespace Internal

	template <int Rows, int Columns>
	Matrix<Rows, Columns> RowEchelon(const Matrix<Rows, Columns>& Target)
	{
		Matrix<Rows, Columns> Result = Target;

		// Use Cocktail Shaker Sort

		int StartIndex = 1;
		int EndIndex = Rows - 1;

		while (StartIndex <= EndIndex)
		{
			int NewStartIndex = EndIndex;
			int NewEndIndex = StartIndex;

			for (int Iter = StartIndex; Iter < EndIndex; ++Iter)
			{
				if (Internal::RowZeroCount(Target, Iter) > Internal::RowZeroCount(Target, Iter + 1))
				{
					Internal::SwapRow(Result, Iter, Iter + 1);

					NewEndIndex = Iter;
				}
			}

			// Elements after NewEndIndex are in the correct position, subtract 1 from the max index range.
			EndIndex = NewEndIndex - 1;

			for (int Iter = EndIndex; Iter > StartIndex; --Iter)
			{
				if (Internal::RowZeroCount(Target, Iter) > Internal::RowZeroCount(Target, Iter + 1))
				{
					Internal::SwapRow(Result, Iter, Iter + 1);

					NewStartIndex = Iter;
				}
			}

			// Elements before NewStartIndex are in the correct position, add 1 to the minimum index range.
			StartIndex = NewStartIndex + 1;
		}

		return Result;
	}

	template <int Rows, int Columns>
	Matrix<Rows, Columns> ReducedRowEchelon(const Matrix<Rows, Columns>& Target)
	{
		Matrix<Rows, Columns> Result;

		Result = RowEchelon(Target);

		return Result;
	}
}  // namespace Red