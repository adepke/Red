#pragma once

#include "Matrix.h"
#include "../Algorithm/GaussJordanEliminator.h"

namespace Red
{
	template <int TargetARows, int TargetAColumns, int TargetBRows, int TargetBColumns>
	Matrix<TargetARows, TargetBColumns> operator*(const Matrix<TargetARows, TargetAColumns>& TargetA, const Matrix<TargetBRows, TargetBColumns>& TargetB)
	{
		static_assert(TargetAColumns == TargetBRows, "Dimension Error: Incompatible Operation");

		Matrix<TargetARows, TargetBColumns> Result;

		for (int Row = 0; Row < TargetARows; ++Row)
		{
			for (int Column = 0; Column < TargetBColumns; ++Column)
			{
				float ElementSum = 0.f;

				// Dot Product of Target A's Row and Target B's Column
				for (int Iter = 0; Iter < TargetARows; ++Iter)
				{
					ElementSum += TargetA.Data[Row][Iter] * TargetB.Data[Iter][Column];
				}

				Result.Data[Row][Column] = ElementSum;
			}
		}

		return Result;
	}

	template <int TargetARows, int TargetAColumns, int TargetBRows, int TargetBColumns>
	Matrix<TargetARows, TargetBColumns> operator*=(Matrix<TargetARows, TargetAColumns>& TargetA, const Matrix<TargetBRows, TargetBColumns>& TargetB)
	{
		static_assert(TargetAColumns == TargetBRows && TargetAColumns == TargetBColumns, "Dimension Error: Incompatible Operation");

		TargetA = TargetA * TargetB;

		return TargetA;
	}

	template <int Rows, int Columns>
	Matrix<Rows, Columns> Inverse() const
	{
		Matrix<Rows, Columns * 2> MatrixInterface;

		for (int Row = 0; Row < Rows; ++Row)
		{
			// Construct LHS
			for (int Column = 0; Column < Columns; ++Column)
			{
				MatrixInterface.Data[Row][Column] = Data[Row][Column];
			}

			// Construct RHS
			for (int Column = Columns; Column < Columns * 2; ++Column)
			{
				MatrixInterface.Data[Row][Column] = static_cast<float>(
					(Row % 2 == 0) ?
					(Column % 2) : (Column % 2 == 0 ? 1 : 0)
					);
			}
		}

		MatrixInterface = ReducedRowEchelon(MatrixInterface);

		// Deconstruct LHS
		for (int Row = 0; Row < Rows; ++Row)
		{

		}

		return *this;
	}
}  // namespace Red