#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class node
{
	friend class tree;
private:
	int Boss;
	node *L_Employee, *M_Employee, *R_Employee;
public:
	node(int b)
	{
		Boss = b;
		L_Employee = M_Employee = R_Employee = NULL;
	}
};

class tree
{
private:
	node *MainBoss;
	node* Position(int boss);
	void DFS_Meet(vector<int> q, node *CurBoss, int &Min, int &Max);
	void Pass_Count(int &Pass, int employee, node *CurBoss, stack<int> s);

public:
	tree() {MainBoss = NULL;}
	void Insert(int boss, int L_Employee, int M_Employee, int R_Employee);
	void Meeting(int boss, int employee);
};

void tree::Insert(int boss, int L_Emp, int M_Emp, int R_Emp)
{
	node* newBoss;

	if (!MainBoss)
	{
		newBoss = new node(boss);
		MainBoss = newBoss;
	}
	else
		newBoss = Position(boss);

	if (L_Emp != -1)
	{
		node *new_L_Emp = new node(L_Emp);
		newBoss->L_Employee = new_L_Emp;
	}
	else
	{
		newBoss->L_Employee = NULL;
	}

	if (M_Emp != -1)
	{
		node *new_M_Emp = new node(M_Emp);
		newBoss->M_Employee = new_M_Emp;
	}
	else
	{
		newBoss->M_Employee = NULL;
	}

	if (R_Emp != -1)
	{
		node *new_R_Emp = new node(R_Emp);
		newBoss->R_Employee = new_R_Emp;
	}
	else
	{
		newBoss->R_Employee = NULL;
	}
}

node* tree::Position(int boss)
{
	node *cur = MainBoss;
	queue<node *> q;
	while (cur)
	{
		if (cur->Boss == boss)
		{
			while (!q.empty())
				q.pop();
			return cur;
		}

		if (cur->L_Employee)
			q.push(cur->L_Employee);
		if (cur->M_Employee)
			q.push(cur->M_Employee);
		if (cur->R_Employee)
			q.push(cur->R_Employee);

		node *temp = q.front();
		cur = temp;
		q.pop();
	}
}

void tree::Meeting(int boss, int employee)
{
	int Min = INT_MAX, Max = INT_MIN, Pass = 0;
	vector<int> q;
	stack<int> s;
	node *CurBoss = Position(boss);

	cout << "You may visit:" << endl;
	DFS_Meet(q, CurBoss, Min, Max);

	cout << endl;
	cout << "Minimum visits = " << Min;
	cout << "Maximum visits = " << Max;

	cout << endl;
	Pass_Count(Pass, employee, CurBoss, s);
	if (Pass)
		cout << "For the selected employee, you were passed " << Pass << " times";
	else
		cout << "Selected employee not found";

	while (!q.empty())
		q.pop_back();
}

void tree::DFS_Meet(vector<int> q, node *CurBoss, int &Min, int &Max)
{
	if (CurBoss)
	{
		q.push_back(CurBoss->Boss);

		if (!CurBoss->L_Employee && !CurBoss->M_Employee && !CurBoss->R_Employee)
		{
			if (q.size() < Min)
				Min = q.size();

			if (q.size() > Max)
				Max = q.size();

			for (int i = 0; i < q.size(); i++)
				cout << q[i] << " - ";
			cout << endl;

			q.pop_back();
		}

		else
		{
			DFS_Meet(q, CurBoss->L_Employee, Min, Max);
			DFS_Meet(q, CurBoss->M_Employee, Min, Max);
			DFS_Meet(q, CurBoss->R_Employee, Min, Max);
		}
	}
}

void tree::Pass_Count(int &Pass, int employee, node *CurBoss, stack<int> s)
{

	if (CurBoss)
	{
		if (CurBoss->Boss == employee)
			Pass = s.size();

		s.push(CurBoss->Boss);

		if (!CurBoss->L_Employee && !CurBoss->M_Employee && !CurBoss->R_Employee)
			s.pop();

		else
		{
			Pass_Count(Pass, employee, CurBoss->L_Employee, s);
			Pass_Count(Pass, employee, CurBoss->M_Employee, s);
			Pass_Count(Pass, employee, CurBoss->R_Employee, s);
		}

	}
}


void main()
{
	//Fuck it tomorrow!
}