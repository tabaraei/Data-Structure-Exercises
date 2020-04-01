#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

template <class MyType>
class Triangular_Matrix
{
private:
	MyType *Array;
	int Matrix_Rank;
	int TermNo;

public:
	Triangular_Matrix(int degree);
	~Triangular_Matrix();
	void Input();
	MyType Get(int row, int col);
	void Set(int row, int col, MyType value);
	Triangular_Matrix operator+(Triangular_Matrix B);
	Triangular_Matrix operator*(Triangular_Matrix B);
	void Print();

};

template <class MyType>
Triangular_Matrix<MyType>::Triangular_Matrix(int degree)
{
	if (degree >= 1)
	{
		Matrix_Rank = degree;
		//(degree*degree)-((degree*(degree-1))/2) = (degree*(degree+1))/2
		TermNo = (degree*(degree + 1)) / 2;
		Array = new MyType[TermNo];
	}

	else
		cout << "This matrix doesn't exist" << endl;
}

template <class MyType>
Triangular_Matrix<MyType>::~Triangular_Matrix()
{
	delete[] Array;
}

template <class MyType>
void Triangular_Matrix<MyType>::Input()
{
	for (int i = 0; i < TermNo; i++)
		cin >> Array[i];
}

template <class MyType>
MyType Triangular_Matrix<MyType>::Get(int row, int col)
{
	return Array[(row*Matrix_Rank) - ((row*row - 1) / 2) + col - row];
}

template <class MyType>
void Triangular_Matrix<MyType>::Set(int row, int col, MyType value)
{
	Array[(row*Matrix_Rank) - ((row*row - 1) / 2) + col - row] = value;
}

template <class MyType>
Triangular_Matrix<MyType> Triangular_Matrix<MyType>::operator+(Triangular_Matrix<MyType> B)
{
	if (this->Matrix_Rank == B.Matrix_Rank)
	{
		Triangular_Matrix C(Matrix_Rank);

		for (int i = 0; i < TermNo; i++)
			C.Array[i] = Array[i] + B.Array[i];

		return C;
	}

	else
	{
		cout << "Rank of the both matrixes should be equal!" << endl;
	}
}

template <class MyType>
Triangular_Matrix<MyType> Triangular_Matrix<MyType>::operator*(Triangular_Matrix<MyType> B)
{
	if (this->Matrix_Rank == B.Matrix_Rank)
	{
		Triangular_Matrix C(Matrix_Rank);
		MyType result;

			for (int i = 0; i < Matrix_Rank; i++)
			{
				for (int j = 0; j < Matrix_Rank; j++)
				{
					if (i <= j)
					{
						result = 0;
						for (int k = 0; k < Matrix_Rank; k++)
							result += this->Get(i, k)*B.Get(k, j);
						this->Set(i, j) = result;
					}
				}
			}
		return C;
	}

	else
	{
		cout << "Rank of the both matrixes should be equal!" << endl;
	}
}

template <class MyType>
void Triangular_Matrix<MyType>::Print()
{
	for (int i = 0; i < Matrix_Rank; i++)
	{
		for (int j = 0; j < Matrix_Rank; j++)
			(i > j) ? cout << "0 " : cout << Get(i, j) << " ";
		cout << endl;
	}
}

template <class MyType>
void main()
{
	while (true)
	{
		system("color 3b");

		cout << endl << endl << endl << endl;
		cout << "               *******************************************************************************************" << endl;
		cout << "               *                                        <welcome>                                        *" << endl;
		cout << "               *                                 Upper Triangular Matrix                                 *" << endl;
		cout << "               *                                Please enter your option!                                *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *    1) Input Matrixes                                                                    *" << endl;
		cout << "               *    2) Get a value of matrix                                                             *" << endl;
		cout << "               *    3) Set a new value                                                                   *" << endl;
		cout << "               *    4) Adding two matrixes                                                               *" << endl;
		cout << "               *    5) Multiplying two matrixes                                                          *" << endl;
		cout << "               *    6) Print matrix                                                                      *" << endl;
		cout << "               *    7) About Programmer                                                                  *" << endl;
		cout << "               *    8) Exit                                                                              *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *******************************************************************************************" << endl;

		switch (_getch())
		{
		case '1':
			system("cls");
			int n, m;
			cout << "Enter Rank of first matrix" << endl;
			cin >> n;
			cout << "Enter Rank of second matrix" << endl;
			cin >> m;
			Triangular_Matrix<MyType> A(n), B(m);

			system("cls");
			cout << "Now input values" << endl;
			cout << "First matrix:" << endl;
			A.Input;
			cout << "Second matrix:" << endl;
			B.Input;

			system("cls");
			cout << "Matrixes created!" << endl;
			Sleep(2000);
			system("cls");
			break;

		case '2':
			system("cls");
			cout << "Choose Matrix" << endl;
			cout << "1) First matrix" << endl << "2) Second Matrix" << endl;
			int n = _getch();

			system("cls");
			int f, g;
			cout << "Enter row" << endl;
			cin >> f;
			cout << "Enter column" << endl;
			cin >> g;

			system("cls");
			if (n == 1)
				cout << "Value is = " << A.Get(f, g);
			if (n == 2)
				cout << "Value is = " << B.Get(f, g);
			else
				cout << "Wrong character entered!" << endl;
			Sleep(2000);
			system("cls");
			break;

		case '3':
			system("cls");
			cout << "Choose Matrix" << endl;
			cout << "1) First matrix" << endl << "2) Second Matrix" << endl;
			int n = _getch();

			system("cls");
			int f, g;
			MyType h;
			cout << "Enter row" << endl;
			cin >> f;
			cout << "Enter column" << endl;
			cin >> g;
			cout << "Enter value" << endl;
			cin >> h;

			system("cls");
			if (n == 1)
			{
				A.Set(f, g, h);
				cout << "Value Set!" << endl;
			}
			if (n == 2)
			{
				B.Set(f, g, h);
				cout << "Value Set!" << endl;
			}
			else
				cout << "Wrong character entered!" << endl;
			Sleep(2000);
			system("cls");
			break;

		case '4':
			system("cls");
			Triangular_Matrix<MyType> C(n);
			C = A + B;
			cout << "result is:" << endl;
			C.Print();
			Sleep(2000);
			system("cls");
			break;

		case '5':
			system("cls");
			Triangular_Matrix<MyType> C(n);
			C = A * B;
			cout << "result is:" << endl;
			C.Print();
			Sleep(2000);
			system("cls");
			break;

		case '6':
			system("cls");
			cout << "Choose Matrix" << endl;
			cout << "1) First matrix" << endl << "2) Second Matrix" << endl;
			int n = _getch();

			system("cls");
			if (n == 1)
				A.Print();
			if (n == 2)
				B.Print();
			else
				cout << "Wrong character entered!" << endl;
			Sleep(2000);
			system("cls");
			break;

		case '7':
			system("cls");

			cout << endl;
			cout << "                                                 ********************" << endl;
			cout << "                                             ****************************" << endl;
			cout << "                                          *******                    *******" << endl;
			cout << "                                      *******   Upper Triangular Matrix   *******" << endl;
			cout << "                                    *******   Programmed by Ali Tabaraei   *******" << endl;
			cout << "                                   ******    Collegiate Number: 95440185    *******" << endl;
			cout << "                                    *******      Telegram ID: a1i_tab      *******" << endl;
			cout << "                                      ********                          ********" << endl;
			cout << "                                         ************************************" << endl;
			cout << "                                            ******************************" << endl;
			cout << endl;
			cout << "                                               Thanks for attention...!" << endl;
			cout << "                                               Press any key to go Back" << endl;

			_getch();
			system("cls");
			break;

		case '8':
			system("cls");

			cout << "                                                      _____________" << endl;
			cout << "                                                     |  Good Luck  |" << endl;
			cout << "                                                     |  Have fun!  |" << endl;
			cout << "                                                      ------------- " << endl;

			Sleep(1000);
			exit(0);
			break;
		default:
			cout << "Wrong Character entered!" << endl;
			Sleep(2000);
			break;
		}
	}
}