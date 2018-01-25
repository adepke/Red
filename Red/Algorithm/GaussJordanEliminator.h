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

		template <int Rows, int Columns>
		void DivideRow(Matrix<Rows, Columns>& Target, int Row, float Value)
		{
#ifdef ASSERTIONS
			assert(Value != 0.f);
#endif

			for (int Iter = 0; Iter < Columns; ++Iter)
			{
				Target.Data[Row][Iter] /= Value;
			}
		}

		template <int Rows, int Columns>
		void MultiplyRowCopy(const Matrix<Rows, Columns>& Source, float* Output, int Row, float Value)
		{
#ifdef ASSERTIONS
			assert(Output);
#endif

			for (int Iter = 0; Iter < Columns; ++Iter)
			{
				Output[Iter] = Source.Data[Row][Iter] * Value;
			}
		}

		template <int Rows, int Columns>
		void AddArrayToRow(Matrix<Rows, Columns>& Target, float* Array, int Row)
		{
#ifdef ASSERTIONS
			assert(Array);
#endif

			for (int Iter = 0; Iter < Columns; ++Iter)
			{
				Target.Data[Row][Iter] += Array[Iter];
			}
		}
	}  // namespace Internal

	template <int Rows, int Columns>
	Matrix<Rows, Columns> RowEchelon(const Matrix<Rows, Columns>& Target)
	{
		Matrix<Rows, Columns> Result = Target;

		// Use Cocktail Shaker Sort

		int StartIndex = 0;
		int EndIndex = Rows - 1;

		while (StartIndex <= EndIndex)
		{
			int NewStartIndex = EndIndex;
			int NewEndIndex = StartIndex;

			for (int Iter = StartIndex; Iter < EndIndex; ++Iter)
			{
				if (Internal::RowZeroCount(Result, Iter) > Internal::RowZeroCount(Result, Iter + 1))
				{
					Internal::SwapRow(Result, Iter, Iter + 1);

					NewEndIndex = Iter;
				}
			}

			// Elements after NewEndIndex are in the correct position, subtract 1 from the max index range.
			EndIndex = NewEndIndex - 1;

			for (int Iter = EndIndex; Iter > StartIndex; --Iter)
			{
				if (Internal::RowZeroCount(Result, Iter) > Internal::RowZeroCount(Result, Iter + 1))
				{
					Internal::SwapRow(Result, Iter, Iter + 1);

					NewStartIndex = Iter;
				}
			}

			// Elements before NewStartIndex are in the correct position, add 1 to the minimum index range.
			StartIndex = NewStartIndex + 1;
		}

		for (int Row = 0; Row < Rows; ++Row)
		{
			// Get the Next Pivot Column.
			int PivotColumn = Internal::RowZeroCount(Result, Row);

			// If this Row is All Zeros, Move on.
			if (PivotColumn == Columns)
			{
				break;
			}

			// If we are on the Last Row of the Matrix.
			if (Row == Rows)
			{
				if (Result.Data[Row][PivotColumn] != 1.0f)
				{
					// Make the Pivot 1.
					Internal::DivideRow(Result, Row, Result.Data[Row][PivotColumn]);
				}

				break;
			}

			// Check to See if this is an Isolated Row.
			if (Result.Data[Row + 1][PivotColumn] != 0.f)
			{
				if (Result.Data[Row][PivotColumn] != 1.0f)
				{
					// Make the Pivot 1.
					Internal::DivideRow(Result, Row, Result.Data[Row][PivotColumn]);
				}

				// The Additive Row.
				float ResultRow[Columns];

				Internal::MultiplyRowCopy(Result, ResultRow, Row, Result.Data[Row + 1][PivotColumn]);

				// Make Sure The Pivot is the Opposite Polarity as the Leading Row's.
				if (ResultRow[PivotColumn] > 0.f)
				{
					if (Result.Data[Row + 1][PivotColumn] > 0.f)
					{
						for (int Iter = 0; Iter < Columns; ++Iter)
						{
							ResultRow[Iter] *= 1.0f;
						}
					}
				}

				else
				{
					if (Result.Data[Row + 1][PivotColumn] < 0.f)
					{
						for (int Iter = 0; Iter < Columns; ++Iter)
						{
							ResultRow[Iter] *= 1.0f;
						}
					}
				}

				// Add the Additive Row and the Leading Row Together to Cancel Out the Pivot's Lead, Leaving an Isolated Row.
				Internal::AddArrayToRow(Result, ResultRow, Row);
			}
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
