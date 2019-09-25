#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define N 100

void nhap(int &m, int &n, int &x);
void chonLevel(int &m, int &n, int &x);

void taoBaiMin(int m, int n,int A[][N], int x, int C[], int D[], int &nC);
void taoMin(int m, int n, int A[][N]);
int KtraMin(int A[][N], int i, int j);
void taoBang(int m, int n, int A[][N], int x, int C[], int D[], int &nC);
void gioiThieu();
void choi(int m, int n, int A[][N], int x, int C[], int D[], int nC);
void lanRa(int i, int j, int m, int n, int A[][N], int a, int b, int &d);
void dieuKhien(int &a, int &b, int &i, int &j, int m, int n, int A[][N], int &s, int &d);

void veBanCo(int m, int n);
void gotoxy (int column, int line);
void TextColor (int color);

void main()
{
	int A[N][N]={0};
	int m,n,x;
	int C[N],D[N],nC=0;	
	gioiThieu();
	TextColor(14);
	
	chonLevel(m,n,x);
	system("cls");
	TextColor(15);
	
	gioiThieu();
	veBanCo(m,n);

	taoBaiMin(m,n,A,x,C,D,nC);
	
	gotoxy(2,10);
	
	choi(m,n,A,x,C,D,nC);

	getch();
}
void gioiThieu()
{
	TextColor(10);
	printf("\t\t\t\t~~GAME MINESWEEPER~~\n");
	TextColor(11);
	printf("Chu thich:\n");
	printf("\tKi hieu '%c' la qua min\n", 237);
	printf("\tPhim [w]: di len\n");
	printf("\tPhim [s]: di xuong\n");
	printf("\tPhim [a]: di qua trai\n");
	printf("\tPhim [d]: di qua phai\n");
	printf("\tPhim [k]: chon o\n");
	printf("\tPhim [l]: danh dau '?'\n");
}
void chonLevel(int &m, int &n, int &x)
{
	printf("~Level~\n");
	printf("Level 1: Qua De '5 qua min' (Nhan [1])\n");
	printf("Level 2: De  '13 qua min' (Nhan [2])\n");
	printf("Level 3: Vua  '30 qua min' (Nhan [3])\n");
	printf("Level 4: Kho  '90 qua min' (Nhan [4])\n");
	printf("Moi ban nhan chon Level\n");
	int c=getch();
	while(c<'1'||c>'4')
	{
		printf("Ban nhap sai, moi ban nhap lai:\n");
		c=getch();
	}
	if (c=='1')
	{
		m=5;n=7;x=5;
	}
	if (c=='2')
	{
		m=8;n=10;x=13;
	}
	if (c=='3')
	{
		m=10;n=15;x=30;
	}
	if (c=='4')
	{
		m=12;n=25;x=90;
	}
}
void taoBaiMin(int m, int n,int A[][N], int x, int C[], int D[], int &nC)
{
	taoBang(m,n,A,x,C,D,nC);
	taoMin(m,n,A);
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
				printf("%c %c ",179,177);	
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
			printf("%c %c ",179,177);	
	}
	printf("\n%c",192);
	for (i=0;i<n-1;i++)
		printf("%c%c%c%c",196,196,196,193);
	printf("%c%c%c",196,196,196);
	printf("%c",217);

}
void choi(int m, int n, int A[][N], int x, int C[], int D[], int nC)
{
	int a=2,b=10;
	int i=1,j=1;
	int s=0,d=0,f=0;
	while(1)
	{
		int q=0;
		dieuKhien(a,b,i,j,m,n,A,s,d);
		//	d++;
		if (s==-1)
		{
			for (int k=0;k<nC;k++)
			{
				gotoxy(D[k]*4-2,C[k]*2+8);
				TextColor(13);
				printf("%c",237);
			}
			gotoxy(37,8);
			printf("\tGAME OVER!!!!!!!!");
			break;
		}
		if (f==0&&s!=-3)
		{
			lanRa(i,j,m,n,A,a,b,d);
			f=1;q=1;
		}
		if (s==0&&q==0)
			lanRa(i,j,m,n,A,a,b,d);
		if (s!=-1&&d==(m*n-x))
		{
			for (int k=0;k<nC;k++)
			{
				gotoxy(D[k]*4-2,C[k]*2+8);
				TextColor(13);
				printf("%c",237);
			}
			gotoxy(37,8);
			TextColor(14);
			printf("\tYOU WIN!!!!!");
			break;
		}
		
	}
}
void lanRa(int i, int j, int m, int n, int A[][N], int a, int b, int &d)
{ 
	int Y[24]={-1,-1,0,1,1,1,-1,0,-2,-2,0,2,2,2,-2,0,-2,-2,-1,1,2,2,1,-1};
	int X[24]={0,-1,-1,-1,0,1,1,1,0,-2,-2,-2,0,2,2,2,-1,1,2,2,1,-1,-2,-2};
	int C[24]={-4,-4,0,4,4,4,-4,0,-8,-8,0,8,8,8,-8,0,-8,-8,-4,4,8,8,4,-4};
	int D[24]={0,-2,-2,-2,0,2,2,2,0,-4,-4,-4,0,4,4,4,-2,2,4,4,2,-2,-4,-4};
	for (int k=0;k<24;k++)
		if (A[i+X[k]][j+Y[k]]!=-2 && (i+X[k])>=1 && (i+X[k])<=m && (j+Y[k])>=1 && (j+Y[k])<=n)
		{
			gotoxy(a+C[k],b+D[k]);
			if ( A[i+X[k]][j+Y[k]]!=-1)
			{
				if (A[i+X[k]][j+Y[k]]==0)
					printf(" ");
				else
					printf("%d", A[i+X[k]][j+Y[k]]);	
				A[i+X[k]][j+Y[k]]=-2;
				d++;
			}	
		}
	gotoxy(a,b);
}
void dieuKhien(int &a, int &b, int &i, int &j, int m, int n, int A[][N], int &s, int &d)
{
	int B[N],C[N],nB=0;
	while(1)
	{
		char c=getch();	
		if (c=='a'){								//phim qua trai
			a-=4;	
			j--;
		}
		if (c=='w'){								//phim len tren
			b-=2;
			i--;
		}
		if (c=='s'){								//phim xuong duoi
			b+=2;
			i++;
		}
		if (c=='d'){								//phim qua phai
			a+=4;
			j++;
		}
		gotoxy(a,b);
		if (c=='l'&&A[i][j]!=-2)									//phim danh dau '?'
		{
			int p=0;
			for (int k=0;k<nB;k++)
				if (a==B[k]&&b==C[k])
				{
					TextColor(15);
					printf("%c", 177);
					p=1;B[k]=-5;C[k]=-5;
				}
			if (p==0)
			{
				TextColor(12);
				printf("%c",63);
				B[nB]=a;
				C[nB++]=b;			
			}
		}
		if (c=='k')									//phim chon o
		{
			if (A[i][j]==-2)
			{
				s=-2;
				break;
			}
			if (A[i][j]==-1)
			{
				TextColor(13);
				printf("%c",237);
			
			}
			else
			{
				TextColor(14);
				if (a>=4*n || b>=2*m+9)
				{
					s=-3;
					break;
				}
				if (A[i][j]!=0)
					printf("%d", A[i][j]);
				else
					printf(" ");
				d++;
			}
			
			s=A[i][j];
			A[i][j]=-2;
			
			break;
		}
	}
}


void gotoxy (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void taoBang(int m, int n, int A[][N], int x, int C[], int D[], int &nC)
{
	srand((unsigned)time(NULL));
	int d=0;
	while(d!=x)
	{

		int a=rand()%m+1;
		int b=rand()%n+1;
		if (A[a][b]!=-1)
		{
			A[a][b]=-1;
			C[nC]=a;
			D[nC++]=b;
			d++;
		}
	}
}
void taoMin(int m, int n, int A[][N])
{
	for (int i=1;i<m+1;i++)
		for (int j=1;j<n+1;j++)
		{
			if (A[i][j]==0)
				A[i][j]=KtraMin(A,i,j);
		}

}
int KtraMin(int A[][N], int i, int j)
{
	int X[8]={-1,-1,0,1,1,1,0,-1};
	int Y[8]={0,-1,-1,-1,0,1,1,1};
	int d=0;
	for (int k=0;k<8;k++)
		if(A[i+X[k]][j+Y[k]]==-1)
			d++;  
	return d;		
}

void TextColor (int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}