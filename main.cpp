#include <iostream>

using namespace std;

class MyVectorBool
{
private:
	bool* VectorBool;
	int NumLen;
public:
	MyVectorBool(int N)
	{
		int NumCpy = N;
		while (NumCpy != 0)
		{
			NumCpy /= 2;
			NumLen++;
		}
		VectorBool = new bool[NumLen];
		NumCpy = N;
		int Rem;
		int l = 0;
		while (NumCpy != 0)
		{
			Rem = NumCpy % 2;
			NumCpy /= 2;
			VectorBool[NumLen - l - 1] = Rem;
			l++;
		}
	}

	MyVectorBool()
	{
		NumLen = 0;
		VectorBool = nullptr;
	}

	MyVectorBool(MyVectorBool& other)
	{
		NumLen = other.NumLen;
		VectorBool = new bool[NumLen];
		for (int i = 0; i < NumLen; i++)
		{
			VectorBool[i] = other.VectorBool[i];
		}

	}

	MyVectorBool& operator = (const MyVectorBool& other)
	{
		delete[] VectorBool;
		NumLen = other.NumLen;
		VectorBool = new bool[NumLen];
		for (int i = 0; i < NumLen; i++)
		{
			VectorBool[i] = other.VectorBool[i];
		}
		return *this;
	}

	void add_start(bool k)
	{
		bool* NewVectorBool = new bool[NumLen];
		for (int i = 0; i < NumLen; i++)
		{
			NewVectorBool[i] = VectorBool[i];
		}
		delete[] VectorBool;
		NumLen++;
		VectorBool = new bool[NumLen];
		VectorBool[0] = k;
		for (int i = 1; i < (NumLen); i++)
		{
			VectorBool[i] = NewVectorBool[i - 1];
		}
		delete[] NewVectorBool;
	}

	void add_end(bool k)
	{
		bool* NewVectorBool = new bool[NumLen];
		for (int i = 0; i < NumLen; i++)
		{
			NewVectorBool[i] = VectorBool[i];
		}
		delete[] VectorBool;
		NumLen++;
		VectorBool = new bool[NumLen];
		for (int i = 0; i < (NumLen - 1); i++)
		{
			VectorBool[i] = NewVectorBool[i];
		}
		VectorBool[NumLen - 1] = k;
		delete[] NewVectorBool;
	}

	int size()
	{
		return NumLen;
	}

	void erase(int k)
	{
		for (int i = k; i < NumLen; i++)
		{
			VectorBool[i] = VectorBool[i + 1];
		}
		NumLen--;
	}

	bool& operator [] (int i)
	{
		return VectorBool[i];
	}

	friend ostream& operator << (ostream& out, const MyVectorBool& a)
	{
		for (int i = 0; i < a.NumLen; i++)
		{
			out << a.VectorBool[i];
		}
		return out;
	}

	friend MyVectorBool operator + (MyVectorBool& A, MyVectorBool& B)
	{
		int t1 = 0;
		int t2 = 0;
		if (A.NumLen < B.NumLen)
		{
			for (int i = A.NumLen; i < B.NumLen; i++)
			{
				A.add_start(0);
				t1++;
			}
		}
		else if (A.NumLen > B.NumLen)
		{
			for (int i = B.NumLen; i < A.NumLen; i++)
			{
				B.add_start(0);
				t2++;
			}
		}
		MyVectorBool temp;
		if (A.NumLen == B.NumLen)
		{
			bool Rem = 0;
			temp.NumLen = A.NumLen;
			temp.VectorBool = new bool[temp.NumLen];
			for (int i = (temp.NumLen - 1); i >= 0; i--)
			{
				if ((A.VectorBool[i] == 0) && (B.VectorBool[i] == 0) && (Rem == 0))
				{
					temp.VectorBool[i] = false;
					Rem = false;
				}
				else if (((A.VectorBool[i] == 1) && (B.VectorBool[i] == 0) && (Rem == 0)) || ((A.VectorBool[i] == 0) && (B.VectorBool[i] == 1) && (Rem == 0)) || ((A.VectorBool[i] == 0) && (B.VectorBool[i] == 0) && (Rem == 1)))
				{
					temp.VectorBool[i] = true;
					Rem = false;
				}
				else if (((A.VectorBool[i] == 1) && (B.VectorBool[i] == 1) && (Rem == 0)) || ((A.VectorBool[i] == 1) && (B.VectorBool[i] == 0) && (Rem == 1)) || ((A.VectorBool[i] == 0) && (B.VectorBool[i] == 1) && (Rem == 1)))
				{
					temp.VectorBool[i] = false;
					Rem = true;
				}
				else if ((A.VectorBool[i] == 1) && (B.VectorBool[i] == 1) && (Rem == 1))
				{
					temp.VectorBool[i] = true;
					Rem = true;
				}
				else
				{
					cout << endl << "Не вышло!" << endl;
					cout << "A: " << A.VectorBool[i] << endl << "B: " << B.VectorBool[i] << endl << "Rem: " << Rem << endl << "Summa: " << temp.VectorBool[i] << endl << endl;
				}
			}
			if (Rem == 1)
			{
				temp.add_start(1);
			}
		}
		if (t1 != 0)
		{
			for (int i = 0; i < t1; i++)
			{
				A.erase(0);
			}
		}
		else if (t2 != 0)
		{
			for (int i = 0; i < t2; i++)
			{
				B.erase(0);
			}
		}

		for (int i = 0; i < temp.NumLen; i += 0)
		{
			if (temp.VectorBool[i] == 0)
			{
				temp.erase(i);
			}
			else
			{
				break;
			}
		}

		return temp;
	}

	void removeZeros() {
		int numNonZeros = 0;

		for (int i = 0; i < NumLen; i++) {
			if (VectorBool[i] != 0) {
				numNonZeros++;
			}
		}

		bool* newVectorBool = new bool[numNonZeros];
		int index = 0;

		for (int i = 0; i < NumLen; i++) {
			if (VectorBool[i] != 0) {
				newVectorBool[index] = VectorBool[i];
				index++;
			}
		}

		delete[] VectorBool;
		VectorBool = newVectorBool;
		NumLen = numNonZeros;
	}


	~MyVectorBool()
	{
		delete[] VectorBool;
	}
};

int main()
{
	setlocale(LC_ALL, "Ru");
	int N = 8;
	int M = 3;
	MyVectorBool A(N);
	MyVectorBool B(M);

	bool k = 0;
	bool m = 1;
	A.add_start(k);
	B.add_end(m);
	cout << "Добавить k в начало A: " << A << endl;
	cout << "Добавить m в начало B: " << B << endl;

	MyVectorBool C;
	MyVectorBool D;
	C = A + B;
	cout << "C = A + B: " << C << endl;
	D = B + B;
	cout << "D = B + B: " << D << endl;

	int index = 1;
	if (C[index] == 1)
	{
		C[index] = 0;
	}
	else
	{
		C[index] = 1;
	}
	cout << "Замена значения на проивоположное: " << C << endl;

	C.erase(index);
	cout << "Удален элемент: " << C << endl << endl;

	cout << B.size() << " " << B << endl;

	for (int i = 0; i < B.size(); i++)
	{
		cout << "Hello world" << endl;
	}

	cout << endl;

}