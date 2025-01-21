#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <conio.h>
using namespace std;
int score=0;
int i,j,s,key;
int p[12][22];
int prediction;//预告方块 
void pos(int x,int y)
{
	COORD coord; 
	coord.X=x;
	coord.Y=y;
	HANDLE hOutPut;
    hOutPut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutPut,coord);
}
void createmap()
{
	for(i=10;i<=36;i=i+2)
	{
		pos(i,3);
		cout<<"■";
		pos(i,26);
		cout<<"■";
	}
	for(i=4;i<=25;i++)
	{
		pos(10,i);
		cout<<"■";
		pos(36,i);
		cout<<"■";
	}
	pos(95,26);
	cout<<"Your score:"<<score;
	pos(38,4);
	cout<<"Next piece:";
}
class Map
{
	public:
		int x1,x2,x3,x4,y1,y2,y3,y4;
		int jt;//判断方块形态 
		Map()
		{x1=0;x2=0;x3=0;x4=0;y1=0;y2=0;y3=0;y4=0;jt=0;}
	void recreatemap();
	void judgescore(); 
	int judgegameover();
};
void Map::recreatemap()
{
	createmap();
	for(i=0;i<12;i++)
		for(j=0;j<22;j++)
		if(p[i][j]==1||p[i][j]==2)
		{
			pos(2*i+12,j+4);
			cout<<"■";
		}
		else if(p[i][j]==0)
		{
			pos(2*i+12,j+4);
			cout<<"  ";
		}
		for(i=41;i<=47;i=i+2)
			for(j=6;j<=8;j++)
			{
				pos(i,j);
				cout<<"  ";
			}
		if(prediction==1)
		{
			pos(43,6);
			cout<<"■";
			pos(45,6);
			cout<<"■";
			pos(43,7);
			cout<<"■";
			pos(45,7);
			cout<<"■";
		}
		else if(prediction==2)
		{
			pos(43,6);
			cout<<"■";
			pos(45,6);
			cout<<"■";
			pos(43,7);
			cout<<"■";
			pos(41,7);
			cout<<"■";
		}
		else if(prediction==3)
		{
			pos(43,6);
			cout<<"■";
			pos(41,6);
			cout<<"■";
			pos(43,7);
			cout<<"■";
			pos(45,7);
			cout<<"■";
		}
		else if(prediction==4)
		{
			pos(43,6);
			cout<<"■";
			pos(43,7);
			cout<<"■";
			pos(43,8);
			cout<<"■";
			pos(45,8);
			cout<<"■";
		}
		else if(prediction==5)
		{
			pos(45,6);
			cout<<"■";
			pos(45,7);
			cout<<"■";
			pos(45,8);
			cout<<"■";
			pos(43,8);
			cout<<"■";
		}
		else if(prediction==6)
		{
			pos(43,6);
			cout<<"■";
			pos(45,6);
			cout<<"■";
			pos(43,7);
			cout<<"■";
			pos(41,6);
			cout<<"■";
		}
		else if(prediction==7)
		{
			pos(41,7);
			cout<<"■";
			pos(43,7);
			cout<<"■";
			pos(45,7);
			cout<<"■";
			pos(47,7);
			cout<<"■";
		}
}
void Map::judgescore()
{
	int t;
	for(j=0;j<22;j++)
	{
		if(p[0][j]==2&&p[1][j]==2&&p[2][j]==2&&p[3][j]==2&&p[4][j]==2&&p[5][j]==2&&p[6][j]==2&&p[7][j]==2&&p[8][j]==2&&p[9][j]==2&&p[10][j]==2&&p[11][j]==2)
		{
			for(i=0;i<12;i++)
				p[i][j]=0;
			for(t=j;t>0;t--)
				for(i=0;i<12;i++)
					p[i][t]=p[i][t-1];
			for(i=0;i<12;i++)
				p[i][0]=0;
			score++; 
		}
	}
}
int Map::judgegameover()
{
	int t=0;
	for(i=0;i<12;i++)
		if(p[i][0]==2)
		{
			t=1;
			break;
		}
	return t;
}


class Square:public Map//方块 
{
	public:
	Square()
	{
		x1=5;y1=0;x2=6;y2=1;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
	}
	void manmademove();
	void control();
	int judgestop();
	void automove();
};
void Square::manmademove()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		x1--;x2--;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		x1++;x2++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		while(judgestop()!=1&&y1!=21&&y2!=21)
		{
			y1++;y2++;
		}
		p[x1][y1]=2;
		p[x1][y2]=2;
		p[x2][y1]=2;
		p[x2][y2]=2;
	}
}
void Square::control()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0&&p[x1-1][y2]==0)
	{
		s=1;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x1!=11&&x2!=11&&p[x2+1][y1]==0&&p[x2+1][y2]==0)
	{
		s=2;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademove();
	}
}
int Square::judgestop()
{
	int t=0;
	if(p[x1][y1+1]==2||p[x1][y2+1]==2||p[x2][y1+1]==2||p[x2][y2+1]==2)
		t=1;
	return t;
}
void Square::automove()
{
	while(1)
	{
		Sleep(500);
		if(y1==21||y2==21)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x2][y1]=2;
			p[x2][y2]=2;
			recreatemap();
			break;
		}
		if(judgestop()==1)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x2][y1]=2;
			p[x2][y2]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		y1++;y2++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		control();
	}
}



class Flash_r:public Map//向右闪电形 
{
	public:
	Flash_r()
	{
		x1=4;x2=5;x3=6;y1=1;y2=0;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
	}
	void manmademove();
	void control();
	int judgestop();
	void manmademovet1();
	void controlt1();
	int judgestopt1();
	void automove();
};
void Flash_r::manmademove()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		x1--;x2--;x3--; 
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		x1++;x2++;x3++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		while(judgestop()!=1&&y1!=21&&y2!=21)
		{
			y1++;y2++;
		}
		p[x1][y1]=2;
		p[x2][y1]=2;
		p[x2][y2]=2;
		p[x3][y2]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		x1=x1+1;x2=x3;y1=y2-1;y3=y2+1;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x2][y2]=1;
		p[x2][y3]=1;
		jt=1;
		recreatemap();
	}
}
void Flash_r::control()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0)
	{
		s=1;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x3!=11&&p[x3+1][y2]==0)
	{
		s=2;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x2+1][y1]==0&&p[x2][y2-1]==0)
	{
		s=4;
		manmademove();
	}
}
int Flash_r::judgestop()
{
	int t=0;
	if(p[x1][y1+1]==2||p[x2][y1+1]==2||p[x3][y2+1]==2)
		t=1;
	return t;
}
void Flash_r::manmademovet1()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x2][y2]=0;
		p[x2][y3]=0;
		x1--;x2--;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x2][y2]=1;
		p[x2][y3]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x2][y2]=0;
		p[x2][y3]=0;
		x1++;x2++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x2][y2]=1;
		p[x2][y3]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x2][y2]=0;
		p[x2][y3]=0;
		while(judgestopt1()!=1&&y3!=21)
		{
			y1++;y2++;y3++;
		}
		p[x1][y1]=2;
		p[x1][y2]=2;
		p[x2][y2]=2;
		p[x2][y3]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x2][y2]=0;
		p[x2][y3]=0;
		x1=x1-1;x3=x2;x2=x2-1;y1=y2+1;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		jt=0;
		recreatemap();
	}
}
void Flash_r::controlt1()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0&&p[x1-1][y2]==0)
	{
		s=1;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x2!=11&&p[x2+1][y2]==0&&p[x2+1][y3]==0)
	{
		s=2;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x2-1][y3]==0&&p[x2-2][y3]==0&&x1>0)
	{
		s=4;
		manmademovet1();
	}
}
int Flash_r::judgestopt1()
{
	int t=0;
	if(p[x1][y2+1]==2||p[x2][y3+1]==2)
		t=1;
	return t;
}
void Flash_r::automove()
{
	while(1)
	{
		if(jt==0)
		{
		Sleep(500);
		if(y1==21||y2==21)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x2][y2]=2;
			p[x3][y2]=2;
			recreatemap();
			break;
		}
		else if(judgestop()==1)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x2][y2]=2;
			p[x3][y2]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		y1++;y2++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		control();
		}
		if(jt==1)
		{
		Sleep(500);
		if(y3==21)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x2][y2]=2;
			p[x2][y3]=2;
			recreatemap();
			break;
		}
		if(judgestopt1()==1)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x2][y2]=2;
			p[x2][y3]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x2][y2]=0;
		p[x2][y3]=0;
		y1++;y2++;y3++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x2][y2]=1;
		p[x2][y3]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt1();
		}
	}
}



class Flash_l:public Map//向左闪电形 
{
	public:
	Flash_l()
	{
		x1=4;x2=5;x3=6;y1=0;y2=1;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
	}
	void manmademove();
	void control();
	int judgestop();
	void manmademovet1();
	void controlt1();
	int judgestopt1();
	void automove();
};
void Flash_l::manmademove()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		x1--;x2--;x3--;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		x1++;x2++;x3++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		while(judgestop()!=1&&y1!=21&&y2!=21)
		{
			y1++;y2++;
		}
		p[x1][y1]=2;
		p[x2][y1]=2;
		p[x2][y2]=2;
		p[x3][y2]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		x1=x1+1;x2=x2+1;y2=y1;y1=y1-1;y3=y2+1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		jt=1;
		recreatemap();
	}
}
void Flash_l::control()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0)
	{
		s=1;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x3!=11&&p[x3+1][y2]==0)
	{
		s=2;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x3][y2-1]==0&&p[x3][y2-2]==0)
	{
		s=4;
		manmademove();
	}
}
int Flash_l::judgestop()
{
	int t=0;
	if(p[x1][y1+1]==2||p[x2][y2+1]==2||p[x3][y2+1]==2)
		t=1;
	return t;
}
void Flash_l::manmademovet1()
{
	if(s==1)//左移 
	{
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		x1--;x2--;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		x1++;x2++;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		while(judgestopt1()!=1&&y3!=21)
		{
			y1++;y2++;y3++;
		}
		p[x1][y2]=2;
		p[x1][y3]=2;
		p[x2][y1]=2;
		p[x2][y2]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		x1=x1-1;x3=x2;x2=x2-1;y1=y2;y2=y3;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		jt=0;
		recreatemap();
	}
}
void Flash_l::controlt1()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y2]==0&&p[x1-1][y3]==0)
	{
		s=1;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x2!=11&&p[x2+1][y1]==0&&p[x2+1][y2]==0)
	{
		s=2;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x2][y2+1]==0&&p[x1-1][y2]==0&&x1>0)
	{
		s=4;
		manmademovet1();
	}
}
int Flash_l::judgestopt1()
{
	int t=0;
	if(p[x1][y3+1]==2||p[x2][y2+1]==2)
		t=1;
	return t;
}
void Flash_l::automove()
{
	while(1)
	{
		if(jt==0)
		{
		Sleep(500);
		if(y1==21||y2==21)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x2][y2]=2;
			p[x3][y2]=2;
			recreatemap();
			break;
		}
		else if(judgestop()==1)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x2][y2]=2;
			p[x3][y2]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		y1++;y2++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		control();
		}
		if(jt==1)
		{
		Sleep(500);
		if(y3==21)
		{
			p[x1][y2]=2;
			p[x1][y3]=2;
			p[x2][y1]=2;
			p[x2][y2]=2;
			recreatemap();
			break;
		}
		if(judgestopt1()==1)
		{
			p[x1][y2]=2;
			p[x1][y3]=2;
			p[x2][y1]=2;
			p[x2][y2]=2;
			recreatemap();
			break;
		}
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		y1++;y2++;y3++;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt1();
		}
	}
}



class L_r:public Map//向右L形 
{
	public:
	L_r()
	{
		x1=5;x2=6;y1=2;y2=1;y3=0;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
	}
	void manmademove();
	void control();
	int judgestop();
	void manmademovet1();
	void controlt1();
	int judgestopt1();
	void manmademovet2();
	void controlt2();
	int judgestopt2();
	void manmademovet3();
	void controlt3();
	int judgestopt3();
	void automove();
};
void L_r::manmademove()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		x1--;x2--; 
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		x1++;x2++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		while(judgestop()!=1&&y1!=21)
		{
			y1++;y2++;y3++;
		}
		p[x1][y1]=2;
		p[x2][y1]=2;
		p[x1][y2]=2;
		p[x1][y3]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		x2=x1;x3=x1+1;x1=x1-1;y1=y3;
		p[x1][y2]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		p[x3][y1]=1;
		jt=1;
		recreatemap();
	}
}
void L_r::control()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0&&p[x1-1][y2]==0&&p[x1-1][y3]==0)
	{
		s=1;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x2!=11&&p[x2+1][y1]==0&&p[x1+1][y2]==0&&p[x1+1][y3]==0)
	{
		s=2;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x2][y1-1]==0&&p[x2][y1-2]==0&&p[x1-1][y2]==0&&x1>0)
	{
		s=4;
		manmademove();
	}
}
int L_r::judgestop()
{
	int t=0;
	if(p[x1][y1+1]==2||p[x2][y1+1]==2)
		t=1;
	return t;
}
void L_r::manmademovet1()
{
	if(s==1)//左移 
	{
		p[x1][y2]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		p[x3][y1]=0;
		x1--;x2--;x3--;
		p[x1][y2]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		p[x3][y1]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y2]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		p[x3][y1]=0;
		x1++;x2++;x3++;
		p[x1][y2]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		p[x3][y1]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y2]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		p[x3][y1]=0;
		while(judgestopt1()!=1&&y2!=21)
		{
			y1++;y2++;
		}
		p[x1][y2]=2;
		p[x2][y2]=2;
		p[x3][y2]=2;
		p[x3][y1]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y2]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		p[x3][y1]=0;
		x1=x2;x2=x1-1;y1=y2+1;y3=y2-1;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y3]=1;
		jt=2;
		recreatemap();
	}
}
void L_r::controlt1()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y2]==0&&p[x3-1][y1]==0)
	{
		s=1;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x3!=11&&p[x3+1][y1]==0&&p[x3+1][y2]==0)
	{
		s=2;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x3-1][y1]==0&&p[x3-2][y1]==0&&p[x2][y2+1]==0)
	{
		s=4;
		manmademovet1();
	}
}
int L_r::judgestopt1()
{
	int t=0;
	if(p[x1][y2+1]==2||p[x2][y2+1]==2||p[x3][y2+1]==2)
		t=1;
	return t;
}
void L_r::manmademovet2()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y3]=0;
		x1--;x2--;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y3]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y3]=0;
		x1++;x2++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y3]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y3]=0;
		while(judgestopt2()!=1&&y1!=21)
		{
			y1++;y2++;y3++;
		}
		p[x1][y1]=2;
		p[x1][y2]=2;
		p[x1][y3]=2;
		p[x2][y3]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y3]=0;
		x1=x2;x2=x1+1;x3=x2+1;y1=y2;y2=y1+1;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x1][y2]=1;
		jt=3;
		recreatemap();
	}
}
void L_r::controlt2()
{
	if(GetAsyncKeyState(VK_LEFT)&&x2!=0&&p[x2-1][y3]==0&&p[x1-1][y2]==0&&p[x1-1][y1]==0)
	{
		s=1;
		manmademovet2();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x1!=11&&p[x1+1][y1]==0&&p[x1+1][y2]==0&&p[x1+1][y3]==0)
	{
		s=2;
		manmademovet2();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet2();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x2][y3+1]==0&&p[x2][y3+2]==0&&p[x1+1][y2]==0)
	{
		s=4;
		manmademovet2();
	}
}
int L_r::judgestopt2()
{
	int t=0;
	if(p[x2][y3+1]==2||p[x1][y1+1]==2)
		t=1;
	return t;
}
void L_r::manmademovet3()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x1][y2]=0;
		x1--;x2--;x3--;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x1][y2]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x1][y2]=0;
		x1++;x2++;x3++; 
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x1][y2]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x1][y2]=0;
		while(judgestopt3()!=1&&y2!=21)
		{
			y1++;y2++;
		}
		p[x1][y1]=2;
		p[x2][y1]=2;
		p[x3][y1]=2;
		p[x1][y2]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x1][y2]=0;
		x1=x1-1;x2=x1+1;y2=y1;y1=y2+1;y3=y2-1;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		jt=0;
		recreatemap();
	}
}
void L_r::controlt3()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0&&p[x1-1][y2]==0)
	{
		s=1;
		manmademovet3();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x3!=11&&p[x3+1][y1]==0&&p[x1+1][y2]==0)
	{
		s=2;
		manmademovet3();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet3();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x1+1][y1]==0&&p[x1+2][y1]==0&&p[x2][y1-1]==0&&x1<11)
	{
		s=4;
		manmademovet3();
	}
}
int L_r::judgestopt3()
{
	int t=0;
	if(p[x1][y2+1]==2||p[x2][y1+1]==2||p[x3][y1+1]==2)
		t=1;
	return t;
}
void L_r::automove()
{
	while(1)
	{
		if(jt==0)
		{
		Sleep(500);
		if(y1==21)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			recreatemap();
			break;
		}
		if(judgestop()==1)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		y1++;y2++;y3++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		control();
		}
		else if(jt==1)
		{
		Sleep(500);
		if(y2==21)
		{
			p[x1][y2]=2;
			p[x2][y2]=2;
			p[x3][y2]=2;
			p[x3][y1]=2;
			recreatemap();
			break;
		}
		if(judgestopt1()==1)
		{
			p[x1][y2]=2;
			p[x2][y2]=2;
			p[x3][y2]=2;
			p[x3][y1]=2;
			recreatemap();
			break;
		}
		p[x1][y2]=0;
		p[x2][y2]=0;
		p[x3][y2]=0;
		p[x3][y1]=0;
		y1++;y2++;y3++;
		p[x1][y2]=1;
		p[x2][y2]=1;
		p[x3][y2]=1;
		p[x3][y1]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt1();
		}
		else if(jt==2)
		{
		Sleep(500);
		if(y1==21)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			p[x2][y3]=2;
			recreatemap();
			break;
		}
		if(judgestopt2()==1)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			p[x2][y3]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y3]=0;
		y1++;y2++;y3++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y3]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt2();
		}
		else if(jt==3)
		{
		Sleep(500);
		if(y2==21)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x3][y1]=2;
			p[x1][y2]=2;
			recreatemap();
			break;
		}
		if(judgestopt3()==1)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x3][y1]=2;
			p[x1][y2]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x1][y2]=0;
		y1++;y2++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x1][y2]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt3();
		}
	}
}



class L_l:public Map//向左L形 
{
	public:
	L_l()
	{
		x1=6;x2=5;y1=2;y2=1;y3=0;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
	}
	void manmademove();
	void control();
	int judgestop();
	void manmademovet1();
	void controlt1();
	int judgestopt1();
	void manmademovet2();
	void controlt2();
	int judgestopt2();
	void manmademovet3();
	void controlt3();
	int judgestopt3();
	void automove();
};
void L_l::manmademove()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		x1--;x2--; 
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		x1++;x2++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		while(judgestop()!=1&&y1!=21)
		{
			y1++;y2++;y3++;
		}
		p[x1][y1]=2;
		p[x2][y1]=2;
		p[x1][y2]=2;
		p[x1][y3]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		x2=x1;x1=x1-1;x3=x2+1;y1=y2;y2=y1+1;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x3][y2]=1;
		jt=1;
		recreatemap();
	}
}
void L_l::control()
{
	if(GetAsyncKeyState(VK_LEFT)&&x2!=0&&p[x2-1][y1]==0&&p[x1-1][y2]==0&&p[x1-1][y3]==0)
	{
		s=1;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x1!=11&&p[x1+1][y1]==0&&p[x1+1][y2]==0&&p[x1+1][y3]==0)
	{
		s=2;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x1-1][y2]==0&&p[x1+1][y2]==0&&p[x1+1][y1]==0&&x1<11)
	{
		s=4;
		manmademove();
	}
}
int L_l::judgestop()
{
	int t=0;
	if(p[x1][y1+1]==2||p[x2][y1+1]==2)
		t=1;
	return t;
}
void L_l::manmademovet1()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x3][y2]=0;
		x1--;x2--;x3--;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x3][y2]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x3][y2]=0;
		x1++;x2++;x3++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x3][y2]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x3][y2]=0;
		while(judgestopt1()!=1&&y2!=21)
		{
			y1++;y2++;
		}
		p[x1][y1]=2;
		p[x2][y1]=2;
		p[x3][y1]=2;
		p[x3][y2]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x3][y2]=0;
		x1=x2;x2=x1+1;y2=y1;y1=y2-1;y3=y2+1;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		jt=2;
		recreatemap();
	}
}
void L_l::controlt1()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0&&p[x3-1][y2]==0)
	{
		s=1;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x3!=11&&p[x3+1][y1]==0&&p[x3+1][y2]==0)
	{
		s=2;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x3-1][y2]==0&&p[x2][y1-1]==0&&p[x3][y1-1]==0)
	{
		s=4;
		manmademovet1();
	}
}
int L_l::judgestopt1()
{
	int t=0;
	if(p[x1][y1+1]==2||p[x2][y1+1]==2||p[x3][y2+1]==2)
		t=1;
	return t;
}
void L_l::manmademovet2()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		x1--;x2--;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		x1++;x2++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		while(judgestopt2()!=1&&y3!=21)
		{
			y1++;y2++;y3++;
		}
		p[x1][y1]=2;
		p[x2][y1]=2;
		p[x1][y2]=2;
		p[x1][y3]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		x2=x1;x1=x2-1;x3=x2+1;y1=y2;y2=y1-1;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x1][y2]=1;
		jt=3;
		recreatemap();
	}
}
void L_l::controlt2()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0&&p[x1-1][y2]==0&&p[x1-1][y3]==0)
	{
		s=1;
		manmademovet2();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x2!=11&&p[x2+1][y1]==0&&p[x1+1][y2]==0&&p[x1+1][y3]==0)
	{
		s=2;
		manmademovet2();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet2();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x2][y1+1]==0&&p[x1-1][y1]==0&&p[x1-1][y2]==0&&x1>0)
	{
		s=4;
		manmademovet2();
	}
}
int L_l::judgestopt2()
{
	int t=0;
	if(p[x1][y3+1]==2||p[x2][y1+1]==2)
		t=1;
	return t;
}
void L_l::manmademovet3()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x1][y2]=0;
		x1--;x2--;x3--;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x1][y2]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x1][y2]=0;
		x1++;x2++;x3++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x1][y2]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x1][y2]=0;
		while(judgestopt3()!=1&&y1!=21)
		{
			y1++;y2++;
		}
		p[x1][y1]=2;
		p[x2][y1]=2;
		p[x3][y1]=2;
		p[x1][y2]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x1][y2]=0;
		x1=x2;x2=x1-1;y2=y1;y1=y2+1;y3=y2-1;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		jt=0;
		recreatemap();
	}
}
void L_l::controlt3()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0&&p[x1-1][y2]==0)
	{
		s=1;
		manmademovet3();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x3!=11&&p[x3+1][y1]==0&&p[x1+1][y2]==0)
	{
		s=2;
		manmademovet3();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet3();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x1+1][y2]==0&&p[x1][y1+1]==0&&p[x2][y1+1]==0)
	{
		s=4;
		manmademovet3();
	}
}
int L_l::judgestopt3()
{
	int t=0;
	if(p[x1][y1+1]==2||p[x2][y1+1]==2||p[x3][y1+1]==2)
		t=1;
	return t;
}
void L_l::automove()
{
	while(1)
	{
		if(jt==0)
		{
		Sleep(500);
		if(y1==21)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			recreatemap();
			break;
		}
		if(judgestop()==1)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		y1++;y2++;y3++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		control();
		}
		else if(jt==1)
		{
		Sleep(500);
		if(y2==21)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x3][y1]=2;
			p[x3][y2]=2;
			recreatemap();
			break;
		}
		if(judgestopt1()==1)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x3][y1]=2;
			p[x3][y2]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x3][y2]=0;
		y1++;y2++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x3][y2]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt1();
		}
		else if(jt==2)
		{
		Sleep(500);
		if(y3==21)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			recreatemap();
			break;
		}
		if(judgestopt2()==1)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		y1++;y2++;y3++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt2();
		}
		else if(jt==3)
		{
		Sleep(500);
		if(y1==21)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x3][y1]=2;
			p[x1][y2]=2;
			recreatemap();
			break;
		}
		if(judgestopt3()==1)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x3][y1]=2;
			p[x1][y2]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x1][y2]=0;
		y1++;y2++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x1][y2]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt3();
		}
	}
}



class T:public Map//T形 
{
	public:
	T()
	{
		x1=5;x2=6;x3=7;y1=0;y2=1;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y1]=1;
	}
	void manmademove();
	void control();
	int judgestop();
	void manmademovet1();
	void controlt1();
	int judgestopt1();
	void manmademovet2();
	void controlt2();
	int judgestopt2();
	void manmademovet3();
	void controlt3();
	int judgestopt3();
	void automove();
};
void T::manmademove()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y1]=0;
		x1--;x2--;x3--;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y1]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y1]=0;
		x1++;x2++;x3++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y1]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y1]=0;
		while(judgestop()!=1&&y2!=21)
		{
			y1++;y2++;
		}
		p[x1][y1]=2;
		p[x2][y1]=2;
		p[x2][y2]=2;
		p[x3][y1]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y1]=0;
		x1=x2;x2=x1+1;y2=y1;y1=y2-1;y3=y2+1;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y2]=1;
		jt=1;
		recreatemap();
	}
}
void T::control()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0&&p[x2-1][y2]==0)
	{
		s=1;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x3!=11&&p[x3+1][y1]==0&&p[x2+1][y2]==0)
	{
		s=2;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x2][y1-1]==0)
	{
		s=4;
		manmademove();
	}
}
int T::judgestop()
{
	int t=0;
	if(p[x1][y1+1]==2||p[x2][y2+1]==2||p[x3][y1+1]==2)
		t=1;
	return t;
}
void T::manmademovet1()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y2]=0;
		x1--;x2--;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y2]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y2]=0;
		x1++;x2++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y2]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y2]=0;
		while(judgestopt1()!=1&&y3!=21)
		{
			y1++;y2++;y3++;
		}
		p[x1][y1]=2;
		p[x1][y2]=2;
		p[x1][y3]=2;
		p[x2][y2]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y2]=0;
		x2=x1;x1=x2-1;x3=x2+1;y1=y2;y2=y1-1;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x2][y2]=1;
		jt=2;
		recreatemap();
	}
}
void T::controlt1()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0&&p[x1-1][y2]==0&&p[x1-1][y3]==0)
	{
		s=1;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x2!=11&&p[x1+1][y1]==0&&p[x2+1][y2]==0&&p[x1+1][y3]==0)
	{
		s=2;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x1-1][y2]==0&&x1>0)
	{
		s=4;
		manmademovet1();
	}
}
int T::judgestopt1()
{
	int t=0;
	if(p[x1][y3+1]==2||p[x2][y2+1]==2)
		t=1;
	return t;
}
void T::manmademovet2()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x2][y2]=0;
		x1--;x2--;x3--;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x2][y2]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x2][y2]=0;
		x1++;x2++;x3++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x2][y2]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x2][y2]=0;
		while(judgestopt2()!=1&&y1!=21)
		{
			y1++;y2++;
		}
		p[x1][y1]=2;
		p[x2][y1]=2;
		p[x3][y1]=2;
		p[x2][y2]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x2][y2]=0;
		x1=x2;x2=x1-1;y2=y1;y1=y2-1;y3=y2+1;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y2]=1;
		jt=3;
		recreatemap();
	}
}
void T::controlt2()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0&&p[x2-1][y2]==0)
	{
		s=1;
		manmademovet2();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x3!=11&&p[x3+1][y1]==0&&p[x2+1][y2]==0)
	{
		s=2;
		manmademovet2();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet2();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x2][y1+1]==0)
	{
		s=4;
		manmademovet2();
	}
}
int T::judgestopt2()
{
	int t=0;
	if(p[x1][y1+1]==2||p[x2][y1+1]==2||p[x3][y1+1]==2)
		t=1;
	return t;
}
void T::manmademovet3()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y2]=0;
		x1--;x2--;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y2]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y2]=0;
		x1++;x2++;x3++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y2]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y2]=0;
		while(judgestopt3()!=1&&y3!=21)
		{
			y1++;y2++;y3++;
		}
		p[x1][y1]=2;
		p[x1][y2]=2;
		p[x1][y3]=2;
		p[x2][y2]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y2]=0;
		x2=x1;x1=x2-1;x3=x2+1;y1=y2;y2=y1+1;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y1]=1;
		jt=0;
		recreatemap();
	}
}
void T::controlt3()
{
	if(GetAsyncKeyState(VK_LEFT)&&x2!=0&&p[x1-1][y1]==0&&p[x2-1][y2]==0&&p[x1-1][y3]==0)
	{
		s=1;
		manmademovet3();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x1!=11&&p[x1+1][y1]==0&&p[x1+1][y2]==0&&p[x1+1][y3]==0)
	{
		s=2;
		manmademovet3();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet3();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x1+1][y2]==0&&x1<11)
	{
		s=4;
		manmademovet3();
	}
}
int T::judgestopt3()
{
	int t=0;
	if(p[x2][y2+1]==2||p[x1][y3+1]==2)
		t=1;
	return t;
}
void T::automove()
{
	while(1)
	{
		if(jt==0)
		{
		Sleep(500);
		if(y2==21)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x2][y2]=2;
			p[x3][y1]=2;
			recreatemap();
			break;
		}
		if(judgestop()==1)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x2][y2]=2;
			p[x3][y1]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x2][y2]=0;
		p[x3][y1]=0;
		y1++;y2++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x2][y2]=1;
		p[x3][y1]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		control();
		}
		else if(jt==1)
		{
		Sleep(500);
		if(y3==21)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			p[x2][y2]=2;
			recreatemap();
			break;
		}
		if(judgestopt1()==1)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			p[x2][y2]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y2]=0;
		y1++;y2++;y3++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y2]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt1();
		}
		else if(jt==2)
		{
		Sleep(500);
		if(y1==21)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x3][y1]=2;
			p[x2][y2]=2;
			recreatemap();
			break;
		}
		if(judgestopt2()==1)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x3][y1]=2;
			p[x2][y2]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x2][y2]=0;
		y1++;y2++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x2][y2]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt2();
		}
		else if(jt==3)
		{
		Sleep(500);
		if(y3==21)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			p[x2][y2]=2;
			recreatemap();
			break;
		}
		if(judgestopt3()==1)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			p[x2][y2]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x2][y2]=0;
		y1++;y2++;y3++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x2][y2]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt3();
		}
	}
}



class I:public Map//I形 
{
	public:
	I()
	{
		x1=4;x2=5;x3=6;x4=7;y1=0;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x4][y1]=1;
	}
	void manmademove();
	void control();
	int judgestop();
	void manmademovet1();
	void controlt1();
	int judgestopt1();
	void automove();
};
void I::manmademove()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x4][y1]=0;
		x1--;x2--;x3--;x4--;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x4][y1]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x4][y1]=0;
		x1++;x2++;x3++;x4++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x4][y1]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x4][y1]=0;
		while(judgestop()!=1&&y1!=21)
		{
			y1++;
		}
		p[x1][y1]=2;
		p[x2][y1]=2;
		p[x3][y1]=2;
		p[x4][y1]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x4][y1]=0;
		x1=x3;y3=y1;y4=y3+1;y2=y3-1;y1=y3-2;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x1][y4]=1;
		jt=1;
		recreatemap();
	}
}
void I::control()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0)
	{
		s=1;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x4!=11&&p[x4+1][y1]==0)
	{
		s=2;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademove();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x3][y1-1]==0&&p[x3][y1-2]==0&&p[x3][y1+1]==0)
	{
		s=4;
		manmademove();
	}
}
int I::judgestop()
{
	int t=0;
	if(p[x1][y1+1]==2||p[x2][y1+1]==2||p[x3][y1+1]==2||p[x4][y1+1]==2)
		t=1;
	return t;
}
void I::manmademovet1()
{
	if(s==1)//左移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x1][y4]=0;
		x1--;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x1][y4]=1;
		recreatemap();
	}
	if(s==2)//右移 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x1][y4]=0;
		x1++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x1][y4]=1;
		recreatemap();
	}
	if(s==3)//快速触底 
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x1][y4]=0;
		while(judgestopt1()!=1&&y4!=21)
		{
			y1++;y2++;y3++;y4++;
		}
		p[x1][y1]=2;
		p[x1][y2]=2;
		p[x1][y3]=2;
		p[x1][y4]=2;
		recreatemap();
	}
	if(s==4)
	{
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x1][y4]=0;
		x3=x1;x4=x3+1;x2=x3-1;x1=x3-2;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x4][y1]=1;
		jt=0;
		recreatemap();
	}
}
void I::controlt1()
{
	if(GetAsyncKeyState(VK_LEFT)&&x1!=0&&p[x1-1][y1]==0&&p[x1-1][y2]==0&&p[x1-1][y3]==0&&p[x1-1][y4]==0)
	{
		s=1;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_RIGHT)&&x1!=11&&p[x1+1][y1]==0&&p[x1+1][y2]==0&&p[x1+1][y3]==0&&p[x1+1][y4]==0)
	{
		s=2;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		s=3;
		manmademovet1();
	}
	else if(GetAsyncKeyState(VK_SPACE)&&p[x1-1][y3]==0&&p[x1-2][y3]==0&&p[x1+1][y3]==0&&x1>1&&x1<11)
	{
		s=4;
		manmademovet1();
	}
}
int I::judgestopt1()
{
	int t=0;
	if(p[x1][y4+1]==2)
		t=1;
	return t;
}
void I::automove()
{
	while(1)
	{
		if(jt==0)
		{
		Sleep(500);
		if(y1==21)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x3][y1]=2;
			p[x4][y1]=2;
			recreatemap();
			break;
		}
		if(judgestop()==1)
		{
			p[x1][y1]=2;
			p[x2][y1]=2;
			p[x3][y1]=2;
			p[x4][y1]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x2][y1]=0;
		p[x3][y1]=0;
		p[x4][y1]=0;
		y1++;
		p[x1][y1]=1;
		p[x2][y1]=1;
		p[x3][y1]=1;
		p[x4][y1]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		control();
		}
		else if(jt==1)
		{
		Sleep(500);
		if(y4==21)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			p[x1][y4]=2;
			recreatemap();
			break;
		}
		if(judgestopt1()==1)
		{
			p[x1][y1]=2;
			p[x1][y2]=2;
			p[x1][y3]=2;
			p[x1][y4]=2;
			recreatemap();
			break;
		}
		p[x1][y1]=0;
		p[x1][y2]=0;
		p[x1][y3]=0;
		p[x1][y4]=0;
		y1++;y2++;y3++;y4++;
		p[x1][y1]=1;
		p[x1][y2]=1;
		p[x1][y3]=1;
		p[x1][y4]=1;
		recreatemap();
		key=kbhit();
		if(key==1)
		controlt1();
		}
	}
}

void hidecursor()
{
    CONSOLE_CURSOR_INFO cursor_info={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
void play()
{
	hidecursor();
	int c=rand()%70+1;
	int d;
	while(1)
	{
		int d=rand()%70+1;
		if(d>=1&&d<=10)
		{
			prediction=1;
		}
		else if(d>=11&&d<=20)
		{
			prediction=2;
		}
		else if(d>=21&&d<=30)
		{
			prediction=3;
		}
		else if(d>=31&&d<=40)
		{
			prediction=4;
		}
		else if(d>=41&&d<=50)
		{
			prediction=5;
		}
		else if(d>=51&&d<=60)
		{
			prediction=6;
		}
		else if(d>=61&&d<=70)
		{
			prediction=7;
		}
		if(c>=1&&c<=10)
		{
			Square a;
			a.automove();
			a.judgescore();
			if(a.judgegameover()==1)
			break;
		}
		else if(c>=11&&c<=20)
		{
			Flash_r a;
			a.automove();
			a.judgescore();
			if(a.judgegameover()==1)
			break;
		}
		else if(c>=21&&c<=30)
		{
			Flash_l a;
			a.automove();
			a.judgescore();
			if(a.judgegameover()==1)
			break;
		}
		else if(c>=31&&c<=40)
		{
			L_r a;
			a.automove();
			a.judgescore();
			if(a.judgegameover()==1)
			break;
		}
		else if(c>=41&&c<=50)
		{
			L_l a;
			a.automove();
			a.judgescore();
			if(a.judgegameover()==1)
			break;
		}
		else if(c>=51&&c<=60)
		{
			T a;
			a.automove();
			a.judgescore();
			if(a.judgegameover()==1)
			break;
		}
		else if(c>=61&&c<=70)
		{
			I a;
			a.automove();
			a.judgescore();
			if(a.judgegameover()==1)
			break;
		}
		c=d;
	}
}
int main()
{
	system("mode con cols=65 lines=35");
	system("color F4");
	here:
	createmap();
	pos(20,12);
	cout<<"Tetris Game";
	pos(13,16);
	cout<<"Play-1 How to play-2:";
	int choice;
	cin>>choice;
	switch(choice)
	{
		case 1:goto there;
		case 2:{
			system("cls");
			pos(4,10);
			cout<<"由小方块组成的不同形状的板块陆续从屏幕上方落下来，通过方向键调整板块的位置和方向，使它们在屏幕底部拼出完整的一条或几条。这些完整的横条会随即消失，给新落下来的板块腾出空间，与此同时，玩家得到分数奖励。没有被消除掉的方块不断堆积起来，一旦堆到屏幕顶端，则游戏结束。";
			pos(4,23);
			cout<<"Press any key to back to the main menu...";
			system("pause");
			system("cls");
			goto here;
			break;
		}
		default:goto here; 
	}
	there:
	srand(time(0));
	play();
	int choice1;
	pos(18,28);
	cout<<"GAME OVER";
	pos(13,30);
	cout<<"Aother game-1 Back at the main menu -2 Exit-3:";
	cin>>choice1;
	switch(choice1)
	{
		case 1:{
			for(i=0;i<12;i++)
				for(j=0;j<22;j++)
				p[i][j]=0;
			pos(18,28);
			cout<<"         ";
			pos(18,30);
			cout<<"                       ";
			goto there;
			break;}
		case 2:system("cls");goto here;break;
		case 3:return 0;
		default:return 0;
	}
	return 0;
}
