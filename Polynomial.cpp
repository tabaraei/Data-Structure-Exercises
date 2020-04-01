#include <iostream>
#define MAX_TERM 100

using namespace std;

class Term
{
	friend class Polynomial;
private:
	short int exp;
	int coef;
};


class Polynomial
{
public:

	int MaxExp;

	Polynomial();

	void Insert(int i, int j)
	{
		_Insert(i, j);
	}

	void Counter(int count)
	{
		_Counter(count);
	}

	int Finish()
	{
		return finish;
	}

	double Eval(int x)
	{
		return _Eval(x);
	}

private:
	int degree, start, finish;
	static Term TArray[MAX_TERM];
	static int free;

	void _Insert(int i, int j);
	void _Counter(int count);
	double _Eval(int x);
};

Polynomial::Polynomial()
{
	start = free;
	MaxExp = INT_MIN;
}

void Polynomial::_Insert(int i, int j)
{
		TArray[free].exp = i;
		TArray[free].coef = j;
		free++;
		if (i > MaxExp) MaxExp = i;
}

void Polynomial::_Counter(int count)
{
	finish = count;
}

double Polynomial::_Eval(int x)
{
	double sum = 0;
	for (int i = start; i < finish; i++)
	{
		sum += (pow(x, TArray[i].exp))*(TArray[i].coef);
	}
	return sum;
}

Term Polynomial::TArray[MAX_TERM];
int Polynomial::free = 0;

void main()
{
	//first func:
	cout << "How many terms does your polynomial include?" << endl;
	int count;
	cin >> count;

	Polynomial f;
	f.Counter(count);

	int pow, co;
	for (int x = 0; x < f.Finish(); x++)
	{
		cout << "Term" << x + 1 << ":" << endl;

		cout << "Exp = ";
		cin >> pow;
		cout << "Coef = ";
		cin >> co;

		f.Insert(pow, co);
	}

	//second func:
	cout << "How many terms does your polynomial include?" << endl;
	cin >> count;

	Polynomial g;
	g.Counter(count);

	for (int x = 0; x < g.Finish(); x++)
	{
		cout << "Term" << x + 1 << ":" << endl;

		cout << "Exp = ";
		cin >> pow;
		cout << "Coef = ";
		cin >> co;

		g.Insert(pow, co);
	}

	//LeadExp:
	cout << "LeadExp f() = " << f.MaxExp;
	cout << "LeadExp g() = " << g.MaxExp;

	//Eval first func:
	cout << "Enter a value for x" << endl;
	int x;
	cin >> x;
	cout << "Result = " << f.Eval(x);

	//Eval second func:
	cout << "Enter a value for x" << endl;
	cin >> x;
	cout << "Result = " << g.Eval(x);
}