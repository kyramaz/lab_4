#include <iostream>
using namespace std;

class MyVectorBool {
private:
	bool* m_value;
	int m_length;

public:
	MyVectorBool(int N)
	{
		m_length = length(N);
		m_value = new bool[m_length];

		for (int i = m_length - 1; i >= 0; i--)
		{
			m_value[i] = N % 2;
			N = N / 2;
		}
	}

	MyVectorBool()
	{
		m_length = 0;
		m_value = new bool[m_length];
		for (int i = 0; i < m_length; i++)
		{
			m_value[i] = 0;
		}
	}

	MyVectorBool(const MyVectorBool& other)
	{
		m_length = other.m_length;
		m_value = new bool[m_length];
		for (int i = 0; i < m_length; i++)
		{
			m_value[i] = other.m_value[i];
		}
	}


	~MyVectorBool()
	{
		for (int i = 0; i < m_length; i++)
		{
			delete[m_length] m_value;
			m_value = nullptr;
		}
	}

	int length(int N)
	{
		int temp{ 0 };
		int count{ 0 };
		while (N > 0)
		{
			N = N / 2;
			count += 1;
		}
		return count;
	}

	int size()
	{
		return m_length;
	}

	void add_start(bool k)
	{
		bool* new_value = new bool[m_length + 1];
		new_value[0] = k;
		for (int i = 0; i < m_length; i++)
		{
			new_value[i + 1] = m_value[i];
		}
		delete[m_length] m_value;
		m_value = nullptr;
		m_value = new_value;
		m_length++;
	}

	void add_end(bool k)
	{
		bool* new_values = new bool[m_length + 1];

		for (int i = 0; i < m_length; i++)
		{
			new_values[i] = m_value[i];
		}

		new_values[m_length] = k;

		delete[] m_value;

		m_value = new_values;
		m_length += 1;
	}

	void erase(int i)
	{
		if (i < 0 || i >= m_length)
		{
			return;
		}

		bool* new_values = new bool[m_length - 1];

		for (int j = 0; j < i; j++) {
			new_values[j] = m_value[j];
		}

		for (int j = i + 1; j < m_length; j++) {
			new_values[j - 1] = m_value[j];
		}

		delete[] m_value;

		m_value = new_values;
		m_length -= 1;
	}

	MyVectorBool operator+(const MyVectorBool& other) const
	{
		int maxLength = std::max(m_length, other.m_length);
		MyVectorBool result(maxLength);

		MyVectorBool tempThis = *this;
		MyVectorBool tempOther = other;

		// Дополняем векторы нулями до одинаковой длины
		if (tempThis.m_length < maxLength)
		{
			tempThis.add_start(0);
		}
		if (tempOther.m_length < maxLength)
		{
			tempOther.add_start(0);
		}

		bool carry = 0;

		for (int i = maxLength - 1; i >= 0; i--)
		{
			bool sum = (tempThis.m_value[i] + tempOther.m_value[i] + carry) % 2;
			carry = (tempThis.m_value[i] + tempOther.m_value[i] + carry) / 2;

			result.m_value[i] = sum;
		}

		if (carry)
		{
			cout << result;
			cout << result.size();
			result.add_start(1);
		}

		return result;
	}

	MyVectorBool& operator=(const MyVectorBool& other)
	{
		if (this == &other) {
			return *this;
		}

		delete[] m_value;

		m_length = other.m_length;
		m_value = new bool[m_length];

		for (int i = 0; i < m_length; i++) {
			m_value[i] = other.m_value[i];
		}

		return *this;
	}

	friend::ostream& operator<<(ostream &os,const MyVectorBool &temp)
	{
		for (int i = 0; i < temp.m_length; i++)
		{
			os << temp.m_value[i];	
		}
		os << endl;
		return os;
	}
};

int main()
{
	MyVectorBool el1(100);
	MyVectorBool el2(5);

	MyVectorBool vector(0);
	cout << vector;
	vector = el1 + el2;
	cout << vector;

	//MyVectorBool vector = element1 + element2;
	
}