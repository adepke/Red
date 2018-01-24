#pragma once

#ifdef ASSERTIONS
#include <assert.h>
#endif

#include "Vector.h"

namespace Red
{
	template <int Rows = 4, int Columns = 4>
	class Matrix
	{
	public:
		float Data[Rows][Columns];

	public:
		Matrix();
		Matrix(const Matrix& Target);

		~Matrix();
		
		Matrix<Rows, Columns>& operator=(const Matrix<Rows, Columns>& Target);

		Matrix<Rows, Columns> operator+(const Matrix<Rows, Columns>& Target) const;
		Matrix<Rows, Columns> operator-(const Matrix<Rows, Columns>& Target) const;
		Matrix<Rows, Columns> operator*(float Scalar) const;

		Matrix<Rows, Columns>& operator+=(const Matrix<Rows, Columns>& Target);
		Matrix<Rows, Columns>& operator-=(const Matrix<Rows, Columns>& Target);
		Matrix<Rows, Columns>& operator*=(float Scalar);

		bool operator==(const Matrix<Rows, Columns>& Target) const;
		bool operator!=(const Matrix<Rows, Columns>& Target) const;
		
		void ZeroOut();
		bool IsZero() const;

		bool IsSquare() const;
		bool IsRow() const;
		bool IsColumn() const;

		void MakeIdentity();

		float Determinant() const;
	};

	template <int Rows, int Columns>
	Matrix<Rows, Columns>::Matrix()
	{
	}

	template <int Rows, int Columns>
	Matrix<Rows, Columns>::Matrix(const Matrix<Rows, Columns>& Target)
	{
		for (int Row = 0; Row < Rows; ++Row)
		{
			for (int Column = 0; Column < Columns; ++Column)
			{
				Data[Row][Column] = Target.Data[Row][Column];
			}
		}
	}

	template <int Rows, int Columns>
	Matrix<Rows, Columns>::~Matrix()
	{
	}
	
	template <int Rows, int Columns>
	Matrix<Rows, Columns>& Matrix<Rows, Columns>::operator=(const Matrix<Rows, Columns>& Target)
	{
		for (int Row = 0; Row < Rows; ++Row)
		{
			for (int Column = 0; Column < Columns; ++Column)
			{
				Data[Row][Column] = Target.Data[Row][Column];
			}
		}

		return *this;
	}

	template <int Rows, int Columns>
	Matrix<Rows, Columns> Matrix<Rows, Columns>::operator+(const Matrix<Rows, Columns>& Target) const
	{
		Matrix<Rows, Columns> Result;

		for (int Row = 0; Row < Rows; ++Row)
		{
			for (int Column = 0; Column < Columns; ++Column)
			{
				Result.Data[Row][Column] = Data[Row][Column] + Target.Data[Row][Column];
			}
		}

		return Result;
	}

	template <int Rows, int Columns>
	Matrix<Rows, Columns> Matrix<Rows, Columns>::operator-(const Matrix<Rows, Columns>& Target) const
	{
		Matrix<Rows, Columns> Result;

		for (int Row = 0; Row < Rows; ++Row)
		{
			for (int Column = 0; Column < Columns; ++Column)
			{
				Result.Data[Row][Column] = Data[Row][Column] - Target.Data[Row][Column];
			}
		}

		return Result;
	}

	template <int Rows, int Columns>
	Matrix<Rows, Columns> Matrix<Rows, Columns>::operator*(float Scalar) const
	{
		Matrix<Rows, Columns> Result;

		for (int Row = 0; Row < Rows; ++Row)
		{
			for (int Column = 0; Column < Columns; ++Column)
			{
				Result.Data[Row][Column] = Data[Row][Column] * Scalar;
			}
		}

		return Result;
	}

	template <int Rows, int Columns>
	Matrix<Rows, Columns>& Matrix<Rows, Columns>::operator+=(const Matrix<Rows, Columns>& Target)
	{
		*this = *this + Target;

		return *this;
	}

	template <int Rows, int Columns>
	Matrix<Rows, Columns>& Matrix<Rows, Columns>::operator-=(const Matrix<Rows, Columns>& Target)
	{
		*this = *this - Target;

		return *this;
	}

	template <int Rows, int Columns>
	Matrix<Rows, Columns>& Matrix<Rows, Columns>::operator*=(float Scalar)
	{
		*this = *this * Scalar;

		return *this;
	}

	template <int Rows, int Columns>
	bool Matrix<Rows, Columns>::operator==(const Matrix<Rows, Columns>& Target) const
	{
		for (int Row = 0; Row < Rows; ++Row)
		{
			for (int Column = 0; Column < Columns; ++Column)
			{
				if (Data[Row][Column] != Target.Data[Row][Column])
				{
					return false;
				}
			}
		}

		return true;
	}

	template <int Rows, int Columns>
	bool Matrix<Rows, Columns>::operator!=(const Matrix<Rows, Columns>& Target) const
	{
		return !(operator==(Target));
	}

	template <int Rows, int Columns>
	void Matrix<Rows, Columns>::ZeroOut()
	{
		for (int Row = 0; Row < Rows; ++Row)
		{
			for (int Column = 0; Column < Columns; ++Column)
			{
				Data[Row][Column] = 0.f;
			}
		}
	}

	template <int Rows, int Columns>
	bool Matrix<Rows, Columns>::IsZero() const
	{
		for (int Row = 0; Row < Rows; ++Row)
		{
			for (int Column = 0; Column < Columns; ++Column)
			{
				if (Data[Row][Column] != 0.f)
				{
					return false;
				}
			}
		}

		return true;
	}

	template <int Rows, int Columns>
	bool Matrix<Rows, Columns>::IsSquare() const
	{
		return (Rows == Columns);
	}

	template <int Rows, int Columns>
	bool Matrix<Rows, Columns>::IsRow() const
	{
		return (Rows > 1 && Columns == 1);
	}

	template <int Rows, int Columns>
	bool Matrix<Rows, Columns>::IsColumn() const
	{
		return (Rows == 1 && Columns > 1);
	}

	template <int Rows, int Columns>
	void Matrix<Rows, Columns>::MakeIdentity()
	{
		static_assert(Rows == Columns, "Dimension Error: Non Square Matrix");

		ZeroOut();

		for (int Iter = 0; Iter < Rows; ++Iter)
		{
			Data[Iter][Iter] = 1.0f;
		}
	}

	template <>
	REDINLINE float Matrix<2, 2>::Determinant() const
	{
		return ((Data[0][0] * Data[1][1]) - (Data[0][1] * Data[1][0]));
	}

	template <int Rows, int Columns>
	float Matrix<Rows, Columns>::Determinant() const
	{
		static_assert(Rows == Columns, "Dimension Error: Non Square Matrix");

		float Result = 0.f;

		Matrix<Rows - 1, Rows - 1> SubMatrices[Rows];

		// Construct sub matrices.
		for (int Iter = 0; Iter < Rows; ++Iter)
		{
			for (int Row = 0; Row < Rows; ++Row)
			{
				// Whether or not to adjust column.
				bool PassedSpacer = false;

				for (int Col = 0; Col < Rows; ++Col)
				{
					// Always skip the first row.
					if (Row == 0)
					{
						continue;
					}

					// Hit the spacer column, don't copy data.
					else if (Col == Iter)
					{
						PassedSpacer = true;

						continue;
					}
					
					else
					{
						if (PassedSpacer)
						{
							SubMatrices[Iter].Data[Row - 1][Col - 1] = this->Data[Row][Col];
						}

						else
						{
							SubMatrices[Iter].Data[Row - 1][Col] = this->Data[Row][Col];
						}
					}
				}
			}
		}

		// Add sub matrices together.
		for (int Iter = 0; Iter < Rows; ++Iter)
		{
			Result += (this->Data[0][Iter] * SubMatrices[Iter].Determinant() * (Iter % 2 != 0 ? -1 : 1));
		}

		return Result;
	}

	// Matrix Operations

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
}  // namespace Red