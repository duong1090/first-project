#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define N 100

enum trangThai {UP, DOWN, LEFT, RIGHT};

struct toaDo
{
	int x,y;
};

struct snake
{
	toaDo dot[N];
	int n;
	trangThai tts;
	trangThai ttt;

};
 struct moi
{
	 toaDo td;
};


void gioiThieu();
int chonLV();
void veBien();

void khoiTao(snake &ran, moi &tc);
void choi(snake &ran, moi &tc, int lv);

void dieuKhien(snake &ran);
void hienThi(snake ran, moi &tc);
int xuLy(snake &ran, moi &tc, int &diem);

void TextColor (int color);
void gotoXY (int column, int line);

void main()
{
	srand((unsigned)time(NULL));
	gioiThieu();
	int lv=chonLV();
	system("cls");
	gioiThieu();
	veBien();
	
	snake ran;
	moi tc;
	khoiTao(ran,tc);
	choi(ran,tc,lv);
	
	getch();
}

void gioiThieu()
{
	gotoXY(85,5);
	TextColor(14);
	printf("~~SNAKE~~");
	TextColor(15);
	gotoXY(85,7);
	printf("[w]: UP");
	gotoXY(85,8);
	printf("[s]: DOWN");
	gotoXY(85,9);
	printf("[d]: RIGHT");
	gotoXY(85,10);
	printf("[a]: LEFT");
}
int chonLV()
{
	gotoXY(85,12);
	printf("Moi ban chon Level:");
	gotoXY(85,13);
	printf("Level 1: Easy");
	gotoXY(85,14);
	printf("Level 2: Medium");
	gotoXY(85,15);
	printf("Level 3: Hard");
	gotoXY(85,16);
	printf("Level 4: Very Hard");
	char c=getch();
	switch(c)
	{
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
	}
	return 0;
}

void khoiTao(snake &ran, moi &tc)
{

	
	tc.td.x=10;
	tc.td.y=10;
	ran.n=3;
	ran.dot[0].x=6;
	ran.dot[0].y=2;
	ran.dot[1].x=4;
	ran.dot[1].y=2;
	ran.dot[2].x=2;
	ran.dot[2].y=2;
	
	ran.tts=RIGHT;
	ran.ttt=RIGHT;
}
void choi(snake &ran, moi &tc, int lv)
{
	int diem=0;
	while(1)
	{
		TextColor(14);
		hienThi(ran,tc);
		dieuKhien(ran);
		int c=xuLy(ran,tc,diem);
		gotoXY(85,15);
		TextColor(12);
		printf("POINT: %d", diem);

		if (c==-1)
		{
			gotoXY(35, 12);
			TextColor(9);
			printf("GAME OVER");
			break;
		}
		if (lv==1)
			Sleep(150);
		if (lv==2)
			Sleep(100);
		if (lv==3)
			Sleep(40);
		if (lv==4)
			Sleep(30);
	}
}
void veBien()
{
	gotoXY(0,1);
	int i,j;
	printf("%c",201);
	for (i=0;i<70;i++)
		printf("%c",205);
	printf("%c",187);
	printf("\n");
	for (i=0;i<25;i++)
	{
		printf("%c",186);
		for (j=0;j<70;j++)
			printf(" ");
		printf("%c\n",186);
	}
	printf("%c",200);
	for (i=0;i<70;i++)
		printf("%c",205);
	printf("%c",188);

}

void hienThi(snake ran, moi &tc)
{
	//system("cls");
	
	gotoXY(tc.td.x,tc.td.y);
	printf("%c",36);
	gotoXY(ran.dot[ran.n].x,ran.dot[ran.n].y);
	printf(" ");
	for (int i=ran.n-1;i>0;i--)
	{
		gotoXY(ran.dot[i].x,ran.dot[i].y);
		putchar('o');
	}
	gotoXY(ran.dot[0].x,ran.dot[0].y);
	printf("%c",148);
}

void dieuKhien(snake &ran)
{
	for (int i=ran.n;i>0;i--)
		ran.dot[i]=ran.dot[i-1];

	if (kbhit())
	{
		char c=getch();
		if (c=='w')
			ran.tts=UP;
		if (c=='s')
			ran.tts=DOWN;
		if (c=='d')
			ran.tts=RIGHT;
		if (c=='a')
			ran.tts=LEFT;
	}	
	if (ran.tts==UP && ran.ttt!=DOWN)
		ran.dot[0].y--;
	if (ran.tts==DOWN && ran.ttt!=UP)
		ran.dot[0].y++;
	if (ran.tts==RIGHT && ran.ttt!=LEFT)
		ran.dot[0].x+=2;
	if (ran.tts==LEFT && ran.ttt!=RIGHT)
		ran.dot[0].x-=2;
	ran.ttt=ran.tts;
}

int xuLy(snake &ran, moi &tc, int &diem)
{
	
	if (ran.dot[0].x == tc.td.x && ran.dot[0].y == tc.td.y)
	{
		for (int i=ran.n+1;i>0;i--)
			ran.dot[i]=ran.dot[i-1];
		ran.n++;
		if (ran.tts==UP && ran.ttt!=DOWN)
			ran.dot[0].y--;
		if (ran.tts==DOWN && ran.ttt!=UP)
			ran.dot[0].y++;
		if (ran.tts==RIGHT && ran.ttt!=LEFT)
			ran.dot[0].x+=2;
		if (ran.tts==LEFT && ran.ttt!=RIGHT)
			ran.dot[0].x-=2;
		//ran.ttt=ran.tts;
		srand((unsigned)time(NULL));
		do{
		tc.td.x=rand()%68+2;
		tc.td.y=rand()%24+2;
		}while (tc.td.x%2==1);
		diem++;
	}
	for (int j=1;j<ran.n;j++)
		if (ran.dot[0].x == ran.dot[j].x && ran.dot[0].y == ran.dot[j].y)
			return -1;
	if (ran.dot[0].x <1 || ran.dot[0].x>=71 || ran.dot[0].y<2 || ran.dot[0].y>=27)
		return -1;
	return 0;
}
void gotoXY (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void TextColor (int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}