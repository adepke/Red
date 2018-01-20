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
		float** Data;

	public:
		static const Matrix<4, 4> Matrix4x4;

	public:
		Matrix(bool ManualAllocation = false);
		Matrix(const Matrix& Target) {}

		~Matrix();

	public:
		void Empty();
		bool IsEmpty() const;

		void ZeroOut();
		bool IsZero() const;

		bool IsSquare() const;
		bool IsRow() const;
		bool IsColumn() const;

		bool MakeIdentity();

		float Determinant() const;
	};

	template <int Rows, int Columns>
	Matrix<Rows, Columns>::Matrix(bool ManualAllocation = false)
	{
		if (!ManualAllocation)
		{
			Data = new float*[Rows];

			for (int Iter = 0; Iter < Rows; ++Iter)
			{
				Data[Iter] = new float[Columns];
			}

			ZeroOut();
		}
	}

	template <int Rows, int Columns>
	Matrix<Rows, Columns>::~Matrix()
	{
		Empty();
	}

	template <int Rows, int Columns>
	void Matrix<Rows, Columns>::Empty()
	{
		if (Data)
		{
			for (int Iter = 0; Iter < Rows; ++Iter)
			{
				delete[] Data[Iter];
			}

			delete[] Data;

			Data = nullptr;
		}
	}

	template <int Rows, int Columns>
	bool Matrix<Rows, Columns>::IsEmpty() const
	{
		return !Data;
	}

	template <int Rows, int Columns>
	void Matrix<Rows, Columns>::ZeroOut()
	{
#ifdef ASSERTIONS
		assert(Data);
#endif

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
#ifdef ASSERTIONS
		assert(Data);
#endif

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
#ifdef ASSERTIONS
		assert(Data);
#endif

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
#ifdef ASSERTIONS
		assert(Data);
#endif
		
		return ((Data[0][0] * Data[1][1]) - (Data[0][1] * Data[1][0]));
	}

	template <int Rows, int Columns>
	float Matrix<Rows, Columns>::Determinant() const
	{
#ifdef ASSERTIONS
		assert(Data);
		assert(IsSquare());
#endif

		
	}
}  // namespace Red