#include <iostream>
#include <string>
#include <vector>
using namespace std;

class LongNum
{
private:
	string Num;
	vector<int> NumArray;
public:
	LongNum operator+(LongNum B);
	LongNum operator-(LongNum B);
	LongNum operator*(LongNum B);
	void operator=(LongNum B);
	bool operator==(LongNum B);
	bool operator>=(LongNum B);
	bool operator<=(LongNum B);
	bool operator>(LongNum B);
	bool operator<(LongNum B);
	bool Is_Zero();
	friend istream& operator >> (istream &in, LongNum &a)
	{
		in >> a.Num;

		for (int i = a.Num.size() - 1; i >= 0; i--)
			a.NumArray.push_back(a.Num[i] - 48);

		return in;
	}
	friend ostream &operator << (ostream &out, LongNum &a)
	{
		for (int i = a.NumArray.size() - 1; i >= 0; i--)
			out << a.NumArray[i];
		return out;
	}
};

LongNum LongNum::operator+(LongNum B)
{
	LongNum C;
	int i, total, extra = 0;

	for (i = 0; i < this->NumArray.size() && i < B.NumArray.size(); i++)
	{

		total = extra + this->NumArray[i] + B.NumArray[i];
		C.NumArray.push_back(total % 10);
		extra = total / 10;
	}

	while (i < this->NumArray.size())
	{
		total = extra + this->NumArray[i];
		C.NumArray.push_back(total % 10);
		extra = total / 10;
		i++;
	}

	while (i < B.NumArray.size())
	{
		total = extra + B.NumArray[i];
		C.NumArray.push_back(total % 10);
		extra = total / 10;
		i++;
	}

	if (extra != 0)
		C.NumArray.push_back(extra);

	return C;
}

LongNum LongNum::operator-(LongNum B)
{
	LongNum C;
	int i, total, extra = 0;

	for (i = 0; i < NumArray.size() && i < B.NumArray.size(); i++)
	{
		total = extra + NumArray[i] - B.NumArray[i];
		if (total < 0)
		{
			C.NumArray.push_back(total + 10);
			extra = -1;
		}
		else
		{
			C.NumArray.push_back(total);
			extra = 0;
		}
	}

	while (i < NumArray.size())
	{
		total = extra + NumArray[i];
		if (total < 0)
		{
			C.NumArray.push_back(total + 10);
			extra = -1;
		}
		else
		{
			C.NumArray.push_back(total);
			extra = 0;
		}
		i++;
	}

	while (i < B.NumArray.size())
	{
		total = extra + B.NumArray[i];
		if (total < 0)
		{
			C.NumArray.push_back(total + 10);
			extra = -1;
		}
		else
		{
			C.NumArray.push_back(total);
			extra = 0;
		}
		i++;
	}

	for (int i = 0; C.NumArray[C.NumArray.size() - 1 + i] == 0; i--)
		C.NumArray.erase(C.NumArray.end() + i);

	return C;
}

LongNum LongNum::operator*(LongNum B)
{
	LongNum C;

	for (int i = 0; i < B.NumArray.size(); i++)
	{
		for (int j = 0; j < NumArray.size(); j++)
		{
			C.NumArray[i + j] += B.NumArray[i] * NumArray[j];
		}
	}

	for (int i = 0; i < C.NumArray.size(); i++)
	{
		C.NumArray[i + 1] += (C.NumArray[i] / 10);
		C.NumArray[i] %= 10;
	}

	return C;
}

void LongNum::operator=(LongNum B)
{
	this->NumArray = B.NumArray;
}

bool LongNum::operator==(LongNum B)
{
	if (NumArray.size() == B.NumArray.size())
	{
		for (int i = 0; i < NumArray.size(); i++)
			if (NumArray[i] != B.NumArray[i])
				return false;
		return true;
	}

	return false;
}

bool LongNum::operator>=(LongNum B)
{
	if (this->NumArray.size() > B.NumArray.size())
		return true;

	if (this->NumArray.size() == B.NumArray.size())
	{
		for (int i = this->NumArray.size() - 1; i >= 0; i--)
			if (this->NumArray[i] < B.NumArray[i])
				return false;
		return true;
	}

	return false;
}

bool LongNum::operator<=(LongNum B)
{
	if (this->NumArray.size() < B.NumArray.size())
		return true;

	if (this->NumArray.size() == B.NumArray.size())
	{
		for (int i = this->NumArray.size() - 1; i >= 0; i--)
			if (this->NumArray[i] > B.NumArray[i])
				return false;
		return true;
	}

	return false;
}

bool LongNum::operator>(LongNum B)
{
	if (this->NumArray.size() > B.NumArray.size())
		return true;

	if (this->NumArray.size() == B.NumArray.size())
	{
		for (int i = this->NumArray.size() - 1; i >= 0; i--)
		{
			if (this->NumArray[i] < B.NumArray[i])
				return false;
			if (this->NumArray[i] > B.NumArray[i])
				return true;
		}
	}

	return false;
}

bool LongNum::operator<(LongNum B)
{
	if (this->NumArray.size() < B.NumArray.size())
		return true;

	if (this->NumArray.size() == B.NumArray.size())
	{
		for (int i = this->NumArray.size() - 1; i >= 0; i--)
		{
			if (this->NumArray[i] > B.NumArray[i])
				return false;
			if (this->NumArray[i] < B.NumArray[i])
				return true;
		}
	}

	return false;
}

bool LongNum::Is_Zero()
{
	for (int i = 0; i < NumArray.size(); i++)
		if (NumArray[i] != 0)
			return false;
	return true;
}

void main()
{
	LongNum a, b, c;
	cin >> a;
	cin >> b;
	c = a + b;
	cout << c;

	if (a >= b)
		cout << "hi";
	system("pause>n");
}