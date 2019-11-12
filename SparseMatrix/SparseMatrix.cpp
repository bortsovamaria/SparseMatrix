using namespace std;
#include <stdio.h>
#include <map>;

class SparseMatrix
{
private:
	int height, width; // количество строк и столбоцов матрицы
	map<pair<int, int>, int> data; //каждый элемент матрицы
								   // представлен своими координатами и значением
public:
	SparseMatrix(int h, int w) : height(h), width(w) {}

	int Height() const { return height; }
	int Width() const { return width; }

	//записать элемент
	void SetElement(int row, int col, int element)
	{
		data[pair<int, int>(row, col)] = element;
	}

	//прочитать значение элемента
	int GetElement(int row, int col) const
	{
		map<pair<int, int>, int>::const_iterator p =
			data.find(pair<int, int>(row, col));
		// если элемент (row, col) не существует, вернуть нуль
		// иначе - значение элемента
		return (p == data.end()) ? 0 : p->second;
	}

	SparseMatrix operator*(const SparseMatrix& rhs) const;
	SparseMatrix operator*(const SparseMatrix& rhs) const;



	//-------------------------------------------------------
	//SparseMatrix::operator* if in any class
	SparseMatrix operator*(const SparseMatrix& rhs) const
	{
		// копируем левую матрицу в результат
		SparseMatrix result = *this;

		for (map<pair<int, int>, int>::const_iterator p = rhs.data.begin();
			p != rhs.data.end(); p++)
		{
			// извлекаем координаты и значение очередного элемента
			// правой матрицы
			int row = p->first.first;
			int col = p->first.second;
			int value = p->second;

			// прибавляем значение к элементу результата
			// с теми же координатами
			result.SetElement(row, col, value + result.GetElement(row, col));
		}
		return result;
	}
	//-------------------------------------------------------

	SparseMatrix operator*(const SparseMatrix& rhs) const
	{
		// результирующая матрица содержит столько строк сколько левая
		// и столько столбцов, сколько правая
		SparseMatrix result(Height(), rhs.Width());

		//цикл по элементам левой матрицы
		for (map<pair<int, int>, int>::const_iterator p = data.begin();
			p != data.end(); p++)
		{
			// значение элемента по адресу (i, k) равно m
			int i = p->first.first;
			int k = p->first.second;
			int m = p->second;

			// цикл по элементам правой матрицы
			for (map<pair<int, int>, int>::const_iterator rp = rhs.data.begin();
				rp != rhs.data.end(); rp++)
			{
				// значение очередного элемента по адресу (b_k, j) равно n
				int b_k = rp->first.first;
				int j = rp->first.second;
				int n = rp->second;

				// если строка k равна столбцу b_k
				// увеличиваем сумму по адресу (i, j)
				if (k == b_k)
					result.SetElement(i, j, result.GetElement(i, j) + m * n);
			}
		}
		return result;
	}
};

