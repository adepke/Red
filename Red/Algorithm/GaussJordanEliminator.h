#pragma once

#include "../Math/Matrix.h"

namespace Red
{
	namespace Internal
	{
		template <int Rows, int Columns>
		void CocktailShakerSort(Matrix<Rows, Columns>& Target)
		{
			int StartIndex = 0;
			int EndIndex = Rows - 1;

			while (StartIndex <= EndIndex)
			{
				int NewStartIndex = EndIndex;
				int NewEndIndex = StartIndex;

				for (int Iter = StartIndex; Iter < EndIndex; ++Iter)
				{
					if (Internal::RowZeroCount(Target, Iter) > Internal::RowZeroCount(Target, Iter + 1))
					{
						Internal::SwapRow(Target, Iter, Iter + 1);

						NewEndIndex = Iter;
					}
				}

				// Elements after NewEndIndex are in the correct position, subtract 1 from the max index range.
				EndIndex = NewEndIndex - 1;

				for (int Iter = EndIndex; Iter > StartIndex; --Iter)
				{
					if (Internal::RowZeroCount(Target, Iter) > Internal::RowZeroCount(Target, Iter + 1))
					{
						Internal::SwapRow(Target, Iter, Iter + 1);

						NewStartIndex = Iter;
					}
				}

				// Elements before NewStartIndex are in the correct position, add 1 to the minimum index range.
				StartIndex = NewStartIndex + 1;
			}
		}
		
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
		Matrix<Rows, Columns> Result(Target);

		Internal::CocktailShakerSort(Result);

		for (int BaseRow = 0; BaseRow < Rows; ++BaseRow)
		{
			int PivotColumn = -1;

			for (int Column = 0; Column < Columns; ++Column)
			{
				if (Result.Data[BaseRow][Column] != 0.f)
				{
					if (Result.Data[BaseRow][Column] != 1.f)
					{
						Internal::DivideRow(Result, BaseRow, Result.Data[BaseRow][Column]);
					}

					PivotColumn = Column;

					break;
				}
			}

			// If the Matrix is Finished.
			if (PivotColumn == -1)
			{
				break;
			}

			// Check if There's Any Rows to Reduce Below the Base Row.
			if (Result.Data[BaseRow + 1][PivotColumn] != 0.f)
			{
				// Reduce Rows in Pivot Column Following Base Row.
				for (int SubRow = BaseRow + 1; SubRow < Rows; ++SubRow)
				{
					float Additive[Columns];

					Internal::MultiplyRowCopy(Result, Additive, BaseRow, Result.Data[SubRow][PivotColumn]);

					if (Additive[PivotColumn] > 0.f)
					{
						if (Result.Data[SubRow][PivotColumn] > 0.f)
						{
							for (int Iter = 0; Iter < Columns; ++Iter)
							{
								Additive[Iter] *= -1.0f;
							}
						}
					}

					else
					{
						if (Result.Data[SubRow][PivotColumn] < 0.f)
						{
							for (int Iter = 0; Iter < Columns; ++Iter)
							{
								Additive[Iter] *= -1.0f;
							}
						}
					}

					Internal::AddArrayToRow(Result, Additive, SubRow);
				}
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
