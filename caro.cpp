#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>


#define N 100
void gioiThieu();
void veBanCo(int m, int n);
void dieuKhien(char w, char s, char d, char v, char k, int x, int &a, int &b, int &i, int &j, int A[][N]);
void resizeConsole(int Width, int Height);
void TextColor (int color);

int kiemTra(int i, int j, int A[][N], int x, int y);
int xungQuanh(int X[], int Y[], int i, int j, int A[][N], int x, int y);

void gotoxy (int column, int line);
void choi(int A[][N]);
void main()
{
	//resizeConsole(600,800);
	int A[N][N]={0};
	gioiThieu();
	TextColor(15);
	veBanCo(15,25);
	gotoxy(2,8);
	//dieuKhien();
	choi(A);
	getch();
}
void gioiThieu()
{
	TextColor(14);
	printf("\t\t\t\t\tGAME CARO\n");
	TextColor(9);
	printf("Dieu khien:\n");
	printf("P1\t\t\tP2\n");
	TextColor(15);
	printf("UP:    w\t\tUP:    8\n");
	printf("DOWN:  s\t\tDOWN:  5\n");
	printf("LEFT:  a\t\tLEFT:  4\n");
	printf("RIGHT: d\t\tRIGHT: 6\n");
}

void veBanCo(int m, int n)
{
	printf("%c", 218);
	int i,j;
	for (i=0;i<n-1;i++)
		printf("%c%c%c%c",196,196,196,194);
	printf("%c%c%c",196,196,196);
	printf("%c", 191);
	printf("\n");

	for (i=0;i<m-1;i++)
	{
		for (j=0;j<n+1;j++){
			if (j==n)
				printf("%c",179);
			else
				printf("%c   ",179);	
		}
		printf("\n%c", 195);
		for (j=0;j<n-1;j++)
			printf("%c%c%c%c",196,196,196,197);
		printf("%c%c%c",196,196,196);
		printf("%c\n",180);
	}
	for (j=0;j<n+1;j++){
		if (j==n)
			printf("%c",179);
		else
			printf("%c   ",179);	
	}
	printf("\n%c",192);
	for (i=0;i<n-1;i++)
		printf("%c%c%c%c",196,196,196,193);
	printf("%c%c%c",196,196,196);
	printf("%c",217);

}
void choi(int A[][N])
{
	int t=1;
	int a=2,b=8;
	int i=0,j=0;
	while(1)
	{	
		if (t==1)
		{
			dieuKhien(119,115,100,97,102,88,a,b,i,j,A);
			if (kiemTra(i,j,A,88,79))
				break;
			t=2;
		}

		if (t==2)
		{
			dieuKhien(56,53,54,52,48,79,a,b,i,j,A);
			if (kiemTra(i,j,A,79,88))
				break;
			t=1;

		}
	}
	TextColor(14);
	if (t==1)
		printf("P1 thang");
	else
		printf("P2 thang");
}
void dieuKhien(char w, char s, char d, char v, char k, int x, int &a, int &b, int &i, int &j, int A[][N])
{

	while(1)
	{
		char c=getch();
		if (c==w)
		{
			b-=2;
			i--;
		}
		if (c==s)
		{
			b+=2;
			i++;
		}
		if (c==d)
		{
			a+=4;
			j++;
		}
		if (c==v)
		{
			a-=4;
			j--;
		}
		gotoxy(a,b);
		if (c==k)
		{
			if (x==88)
				TextColor(10);
			else
				TextColor(12);
			printf("%c", x);
			A[i][j]=x;
			break;
		}
	}
}
int kiemTra(int i, int j, int A[][N], int x, int y)
{
	int X[10]={5,4,3,2,1,-1,-2,-3,-4,-5};
	int Y[10]={-5,-4,-3,-2,-1,1,2,3,4,5};
	int Z[10]={0,0,0,0,0,0,0,0,0,0};
	if (xungQuanh(X,Y,i,j,A,x,y)==1 || xungQuanh(X,Z,i,j,A,x,y)==1 || xungQuanh(Z,X,i,j,A,x,y)==1 || xungQuanh(X,X,i,j,A,x,y)==1)
		return 1;
	return 0;

}
int xungQuanh(int X[], int Y[], int i, int j, int A[][N], int x, int y)
{
	int d=0,dau=0;
	for (int k=1;k<9;k++)
		{
			if (A[i+X[k]][j+Y[k]]==x)
			{
				if (A[i+X[k+1]][j+Y[k+1]]==y || A[i+X[k-1]][j+Y[k-1]]==y)
					dau++;
				d++;
				if (d==4)
				{
					if (dau==2)
						return 0;
					else
						return 1;
				}
			}
			if (A[i+X[k]][j+Y[k]]!=x && d!=4)
			{
				d=0;
				dau=0;
			}
		}
	return 0;
}
void gotoxy (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void resizeConsole(int Width, int Height)
{

    _COORD coord;
    coord.X = Width;
    coord.Y = Height;
 
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
 
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      
    SetConsoleScreenBufferSize(Handle, coord);            
    SetConsoleWindowInfo(Handle, TRUE, &Rect); 
}
void TextColor (int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}