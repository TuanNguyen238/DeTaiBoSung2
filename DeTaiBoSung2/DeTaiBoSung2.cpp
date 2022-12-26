#include "graphics.h"
#include <dos.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>

using namespace std;

struct Node
{
	int COEF;
	int A, B, C;
	int FLAG;
	int SPEED;
	Node* LINK;
};

Node* CreateNode();
void InsertNode(int coef, int a, int b, int c, Node* P);
void Nhap(Node* P);
int MultiABCF(Node* P);
void TakeData(Node* X1, Node* X2);
void Sort(Node* P);
void RevDuplicates(Node* P);
void PrintPow(int n);
void PrintElement(Node* P, int coef);
void PrintCircularList(Node* P);
void Addition(Node* T1, Node* T2, Node* Q1);
void Multiplication(Node* P, Node* Q, Node* Q2);
void Display(Node* P, int n);
string ConvertInttoString(int n);
void PrintGraphic(Node* T, int i, int n, int color);
bool Check(int& temp1, int& temp2, int i, int n, int speed);
void PrintPAndQ(Node* P, Node* Q);
void PrintPAndQAndADD(Node* P, Node* Q, Node* Q1);
void PrintPAndQAndMUL(Node* P, Node* Q, Node* Q2);
void SortForMulti(Node* P, Node* Y1, Node* Y2);
void CheckNull(Node* P);

int main()
{
	initgraph();
	resizeConsole(1500, 750);

	Node* P = CreateNode();
	cout << "Please enter Poly P:\n"; Nhap(P);
	cout << "Poly P: ";	PrintCircularList(P);
	
	cout << "Press any key to continue!";
	_getch();	system("cls");

	Node* Q = CreateNode();
	cout << "Please enter Poly Q:\n"; Nhap(Q);
	cout << "\nPoly Q: ";	PrintCircularList(Q);
	cout << "Poly P: ";	PrintCircularList(P);

	int choice;
	while (true)
	{
		
		cout << "Choose:\n\t1.Addition\t2.Multiplication\t3.End Program\n";
		cin >> choice;
		if (choice == 1 || choice == 2)
		{
			if (choice == 1)
			{
				Node* Q1 = CreateNode();	
				Addition(P, Q, Q1);
			}
			else if (choice == 2)
			{
				Node* Q2 = CreateNode();
				Multiplication(P, Q, Q2);
			}
			drawText(20, 600, "Press any key to continue!");
			_getch();	system("cls");
		}
		else if (choice == 3)
			break;
		else
			cout << "Wrong choosen!";
	}
	return 0;
}

Node* CreateNode()
{
	Node* T = (Node*)malloc(sizeof(Node));
	T->FLAG = -1;	T->COEF = 0;
	T->A = 0;	T->B = 0;	T->C = 1;
	T->SPEED = 0;	T->LINK = T;
	return T;
}

void InsertNode(int coef, int a, int b, int c, Node* P)
{
	Node* T = (Node*)malloc(sizeof(Node));
	T->COEF = coef;	T->FLAG = 1;
	T->A = a;	T->B = b;	T->C = c;
	if (P->LINK->FLAG == -1)
		T->LINK = P;
	else
		T->LINK = P->LINK;
	P->LINK = T;
}

void Nhap(Node* P)
{
	int coef, a, b, c, check;
	bool test1 = true, test2;
	while (test1)
	{
		cout << "Coef: ";	cin >> coef;
		cout << "Pow(x): ";	cin >> a;
		cout << "Pow(y): ";	cin >> b;
		cout << "Pow(z): ";	cin >> c;
		InsertNode(coef, a, b, c, P);	test2 = true;
		cout << "   Enter more?\n1.Yes\t\t2.No\n";
		while (test2)
		{
			cin >> check;
			if (check == 2)
			{
				test2 = false;	test1 = false;
			}
			else if (check == 1)
				test2 = false;
			else
				cout << "Error enter!(Please re-enter:)\n";
		}
	}
	Sort(P);	RevDuplicates(P);	CheckNull(P);
	cout << endl;
}

int MultiABCF(Node* P)
{
	return (P->A * 100 + P->B * 10 + P->C) * P->FLAG;
}

void TakeData(Node* X1, Node* X2)
{
	X1->COEF = X2->COEF;
	X1->A = X2->A;	X1->B = X2->B;	X1->C = X2->C;
}

void Sort(Node* P)
{
	for (Node* T1 = P->LINK; T1->FLAG == 1; T1 = T1->LINK)
		for (Node* T2 = T1->LINK; T2->FLAG == 1; T2 = T2->LINK)
			if (MultiABCF(T1) < MultiABCF(T2))
			{
				Node* TEMP = (Node*)malloc(sizeof(Node));
				TakeData(TEMP, T1);	TakeData(T1, T2);	TakeData(T2, TEMP);
			}
}

void RevDuplicates(Node* P)
{
	Node* T1 = P->LINK, * T2, * dup;
	while (T1->FLAG == 1 && T1->LINK->FLAG == 1)
	{
		T2 = T1;
		while (T2->LINK->FLAG == 1)
		{
			if (MultiABCF(T1) == MultiABCF(T2->LINK))
			{
				T1->COEF += T2->LINK->COEF;
				dup = T2->LINK;
				T2->LINK = T2->LINK->LINK;
				delete (dup);
			}
			else
				T2 = T2->LINK;
		}
		T1 = T1->LINK;
	}
}

void PrintPow(int n)
{
	if (n != 1)
		cout << "^" << n;
}

void PrintElement(Node* P, int coef)
{
	if (coef != 1)
		cout << coef;
	if (P->A != 0)
	{
		cout << "x";	PrintPow(P->A);
	}
	if (P->B != 0)
	{
		cout << "y";	PrintPow(P->B);
	}
	if (P->C != 0)
	{
		cout << "z";	PrintPow(P->C);
	}
	if (P->A == 0 && P->B == 0 && P->C == 0)
		cout << coef;
}

void PrintCircularList(Node* P)
{
	Node* T = P->LINK;
	int coef = abs(T->COEF);
	if (T->COEF < 0)
		cout << "-";
	PrintElement(T, coef);
	T = T->LINK;
	while (T->FLAG == 1)
	{
		coef = abs(T->COEF);
		if (T->COEF > 0)
			cout << " + ";
		else
			cout << " - ";
		PrintElement(T, coef);
		T = T->LINK;
	}
	cout << "\n\n";
}

void Addition(Node* T1, Node* T2, Node* Q1)
{
	Node* P = T1->LINK, * Q = T2->LINK;
	int i = 0, i1 = 0, i2 = 0, temp1, temp2;
	int checkSpeed = T1->SPEED + T2->SPEED, speed = 20;
	if (checkSpeed > 4)
	{
		if (checkSpeed < 8)
			speed = 50;
		else
			speed = 200;
	}
	while (P->FLAG == 1 || Q->FLAG == 1)
	{
		Sleep(pow(10, 2));
		if (MultiABCF(P) < MultiABCF(Q))
		{
			temp1 = i1;	temp2 = 200;
			while(true)
			{
				PrintGraphic(Q, temp1, temp2, 3);
				Sort(Q1);	system("cls");
				PrintPAndQAndADD(T1, T2, Q1);
				if (!Check(temp1, temp2, i, 400, speed))	break;
			}
			InsertNode(Q->COEF, Q->A, Q->B, Q->C, Q1);
			Q = Q->LINK;	i1 += 200;
		}
		else if (MultiABCF(P) == MultiABCF(Q))
		{
			if (MultiABCF(P) < 0)	break;
			else
			{
				int coef = Q->COEF + P->COEF;
				PrintGraphic(Q, i1, 200, 3);
				PrintGraphic(P, i2, 0, 3);
				if (coef != 0)
				{
					temp1 = i1;	temp2 = 200;
					int temp11 = i2, temp22 = 0;
					while (true)
					{
						PrintGraphic(Q, temp1, temp2, 3);
						PrintGraphic(P, temp11, temp22, 3);
						Sort(Q1);	system("cls");
						PrintPAndQAndADD(T1, T2, Q1);
						if (!Check(temp1, temp2, i, 400, speed) && !Check(temp11, temp22, i, 400, speed))
							break;
					}
					InsertNode(coef, Q->A, Q->B, Q->C, Q1);
				}
				Q = Q->LINK;	P = P->LINK;
				i1 += 200;	i2 += 200;
			}
		}
		else
		{
			temp1 = i2;	temp2 = 0;
			while (true)
			{
				PrintGraphic(P, temp1, temp2, 3);
				Sort(Q1);	system("cls");
				PrintPAndQAndADD(T1, T2, Q1);
				if (!Check(temp1, temp2, i, 400, speed))
					break;
			}
			InsertNode(P->COEF, P->A, P->B, P->C, Q1);
			P = P->LINK;	i2 += 200;
		}
		i += 200;
	}
	system("cls");	PrintPAndQAndADD(T1, T2, Q1);
}

void Multiplication(Node* P, Node* Q, Node* Q2)
{
	Node* T1 = P->LINK, * T2 = Q->LINK;
	int i1 = 0, i2 = 0, i = 0;
	int temp1, temp2, temp3, temp4;
	int checkSpeed = P->SPEED + Q->SPEED, speed = 20;
	if (checkSpeed == 4 || checkSpeed == 5)
		speed = 100;
	else
		speed = 200;
	while (T1->FLAG == 1)
	{
		while (T2->FLAG == 1)
		{
			int coef, a, b, c, d = 0;
			coef = T1->COEF * T2->COEF;
			a = T1->A + T2->A;
			b = T1->B + T2->B;
			c = T1->C + T2->C;
			Node* T = Q2->LINK;	bool check = true;
			temp1 = i1, temp2 = 0;	temp3 = i2, temp4 = 200;
			while (T->FLAG == 1)
			{	
				if (MultiABCF(T) == (a * 100 + b * 10 + c))
				{
					bool test1 = true, test2 = true;
					while (test1 && test2)
					{
						PrintGraphic(T1, temp1, temp2, 3);
						PrintGraphic(T2, temp3, temp4, 3);
						system("cls");	PrintPAndQAndMUL(P, Q, Q2);
						if (!Check(temp1, temp2, d, 400, speed))
							test1 = false;
						if (!Check(temp3, temp4, d, 400, speed))
							test2 = false;
					}
					T->COEF += coef;
					check = false;
				}
				system("cls");	PrintPAndQAndMUL(P, Q, Q2);
				T = T->LINK;	d += 200;
			}
			if (check)
			{
				bool test = true;
				while (test)
				{
					Node* Y = Q2->LINK;	int num = 200, num1 = 0;
					while (num1 <= num)
					{
						while (Y->FLAG == 1)
						{
							if (Y->COEF != 0)
							{
								PrintGraphic(Y, num1 + num, 400, 2);
								num += 200;
							}
							Y = Y->LINK;
						}
						num1 += 10;	num = 200;	Y = Q2;
					}
					drawText(10, 440, "MUL");
					PrintGraphic(T1, temp1, temp2, 3);
					PrintGraphic(T2, temp3, temp4, 3);
					system("cls");	PrintPAndQ(P, Q);
					if (!Check(temp1, temp2, i, 400, speed) && !Check(temp3, temp4, i, 400, speed))
						test = false;
				}
				InsertNode(coef, a, b, c, Q2);
			}
			T2 = T2->LINK;
			i2 += 200;
		}
		i1 += 200;
		i2 = 0;
		T2 = Q->LINK;
		T1 = T1->LINK;
	}
	system("cls");	CheckNull(Q2);
	PrintPAndQAndMUL(P, Q, Q2);
	SortForMulti(Q2, P, Q);
}

void Display(Node* P, int n)
{
	int i = 0;
	Node* T = P->LINK;
	while (T->FLAG == 1)
	{
		if (T->COEF != 0)
		{
			PrintGraphic(T, i, n, 2);
			i += 200;
		}
		T = T->LINK;
	}
}

string ConvertInttoString(int n)
{
	ostringstream os;
	os << n;
	return os.str();
}

void PrintGraphic(Node* T, int i, int n, int color)
{
	setcolor(color);
	line(70 + i, 50 + n, 220 + i, 50 + n);
	line(70 + i, 100 + n, 220 + i, 100 + n);
	line(70 + i, 150 + n, 220 + i, 150 + n);
	line(70 + i, 50 + n, 70 + i, 150 + n);
	line(220 + i, 50 + n, 220 + i, 150 + n);
	line(120 + i, 100 + n, 120 + i, 150 + n);
	line(170 + i, 100 + n, 170 + i, 150 + n);
	drawText(130 + i, 60 + n, ConvertInttoString(T->COEF));
	drawText(80 + i, 110 + n, ConvertInttoString(T->A));
	drawText(130 + i, 110 + n, ConvertInttoString(T->B));
	drawText(180 + i, 110 + n, ConvertInttoString(T->C));
}

bool Check(int &temp1, int &temp2, int i, int n, int speed)
{
	if (temp1 != i || temp2 != n)
	{
		if (temp1 < i)
			temp1 += speed;
		else if (temp1 > i)
			temp1 -= speed;
		if (temp2 < n)
			temp2 += speed;
		else if (temp2 > n)
			temp2 -= speed;
		return true;
	}
	else
		return false;
}

void PrintPAndQ(Node* P, Node* Q)
{
	drawText(10, 35, "P");
	Display(P, 0);
	drawText(10, 240, "Q");
	Display(Q, 200);
}

void PrintPAndQAndADD(Node* P, Node* Q, Node* Q1)
{
	PrintPAndQ(P, Q);
	drawText(10, 440, "Add");
	Display(Q1, 400);
}

void PrintPAndQAndMUL(Node* P, Node* Q, Node* Q2)
{
	PrintPAndQ(P, Q);
	drawText(10, 440, "MUL");
	Display(Q2, 400);
}

void SortForMulti(Node* P, Node* Y1, Node* Y2)
{
	int i1 = 0, i2 = 0, speed = 20;
	if (P->SPEED >= 3)
	{
		if (Y1->SPEED + Y2->SPEED >= 5)
			speed = 200;
		else
			speed = 50;
	}
	for (Node* T1 = P->LINK;T1->FLAG == 1 && T1->LINK->FLAG == 1; T1 = T1->LINK)
	{
		i2 = i1 + 200;
		PrintGraphic(T1, i1, 400, 3);
		for (Node* T2 = T1->LINK; T2->FLAG == 1; T2 = T2->LINK)
		{
			PrintGraphic(T2, i2, 400, 3);
			if (MultiABCF(T1) < MultiABCF(T2))
			{
				bool test1 = true, test2 = true, test3 = true, test4 = true;
				int temp1 = i1, temp2 = 400, temp3 = i2, temp4 = 400;
				while (test1 && test2)
				{
					PrintGraphic(T1, temp1, temp2, 3);
					PrintGraphic(T2, temp3, temp4, 3);
					system("cls");	PrintPAndQAndMUL(Y1, Y2, P);
					if (!Check(temp1, temp2, i1, 600, speed))
						test1 = false;
					if (!Check(temp3, temp4, i2, 600, speed))
						test2 = false;
				}
				while (test3 && test4)
				{
					PrintGraphic(T1, temp1, temp2, 3);
					PrintGraphic(T2, temp3, temp4, 3);
					system("cls");	PrintPAndQAndMUL(Y1, Y2, P);
					if (!Check(temp1, temp2, i2, 400, speed))
						test3 = false;
					if (!Check(temp3, temp4, i1, 400, speed))
						test4 = false;
				}
				Node* TEMP = (Node*)malloc(sizeof(Node));
				TakeData(TEMP, T1);	TakeData(T1, T2);	TakeData(T2, TEMP);
				system("cls");	PrintPAndQAndMUL(Y1, Y2, P);
			}
			i2 += 200;	Sleep(pow(10, 2));
		}
		i1 += 200;	Sleep(pow(10, 2));
	}
	
}

void CheckNull(Node* P)
{
	Node* T = P;
	while (T->LINK->FLAG == 1)
	{
		if (T->LINK->COEF == 0)
		{
			Node* rev = T->LINK;
			T->LINK = T->LINK->LINK;
			delete(rev);
		}
		else
		{
			P->SPEED++;
			T = T->LINK;
		}
	}
}