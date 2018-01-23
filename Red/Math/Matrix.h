#pragma once

#ifdef ASSERTIONS
#include <assert.h>
#endif

namespace Red
{
	template <int Rows, int Columns>
	class Matrix
	{
	public:
		float Data[Rows][Columns];

	public:
		static const Matrix<4, 4> Matrix4x4;

	public:
		Matrix();
		Matrix(const Matrix& Target);

		~Matrix();

	public:
		void ZeroOut();
		bool IsZero() const;

		bool IsSquare() const;
		bool IsRow() const;
		bool IsColumn() const;

		bool MakeIdentity();

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
	bool Matrix<Rows, Columns>::MakeIdentity()
	{
		// Early out if this is not a square matrix.
		if (Rows != Columns)
		{
			return false;
		}

		ZeroOut();

		for (int Iter = 0; Iter < Rows; ++Iter)
		{
			Data[Iter][Iter] = 1.0f;
		}

		return true;
	}

	template <>
	float Matrix<2, 2>::Determinant() const
	{
		return ((Data[0][0] * Data[1][1]) - (Data[0][1] * Data[1][0]));
	}

	template <int Rows, int Columns>
	float Matrix<Rows, Columns>::Determinant() const
	{
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
}  // namespace Red
