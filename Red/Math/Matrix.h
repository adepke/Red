#pragma once

namespace Red
{
	template <int Rows, int Columns>
	class Matrix
	{
	protected:
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
		assert(Data);

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
		assert(Data);

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
}  // namespace Red