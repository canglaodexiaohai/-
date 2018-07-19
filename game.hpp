#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<Windows.h>
using namespace std;

class FiveChess
{
public:
	FiveChess();
	~FiveChess()
	{};
	void DrawMap();
	bool CheckWin(int x,int y);
	void DownChess(int x, int y, char a);
	void Game();
	bool ComputerPos();
	bool PlayerPos();
	bool IsValidPos(int x,int y);
	//void InitParams();
private:
	const static int size = 15;
	char chessboard[size][size];
	
	bool p1table[15][15][572];
	bool p2table[15][15][572];//
	int pgrade[15][15];//玩家在棋盘上的获胜分数
	int cgrade[15][15];//计算机在棋盘上的获胜分数
	int win[2][572];//各自获胜数组中棋子的个数
	int num;
};
FiveChess::FiveChess()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			chessboard[i][j] = '-';
			//comboard[i][j] = 0;
		}
	}
	num = 0;
	int i = 0; int j = 0; int k = 0; int count = 0;
	for (i = 0; i < 2; ++i)//初始化所赢情况中棋子的个数
	{
		for (j = 0; j < 572; ++j)
			win[i][j] = 0;
	}
	for (i = 0; i < 15; ++i)//初始化每个空格的分数
	{
		for (j = 0; j < 15; ++j)
		{
			cgrade[i][j] = 0;
			pgrade[i][j] = 0;
		}
	}
	for (i = 0; i < 15; ++i)//棋子是否在获胜组合中
	{
		for (j = 0; j < 15; ++j)
		{
			for (k = 0; k < 572; ++k)
			{
				p1table[i][j][k] = false;
				p2table[i][j][k] = false;
			}
		}
	}

	for (i = 0; i < 15; ++i)
	{
		for (j = 0; j < 11; ++j)
		{
			for (k = 0; k < 5; ++k)
			{
				p1table[j + k][i][count] = true;
				p2table[j + k][i][count] = true;
			}
			count++;
		}
	}
	for (i = 0; i < 15; ++i)
	{
		for (j = 0; j < 11; ++j)
		{
			for (k = 0; k < 5; ++k)
			{
				p1table[i][j + k][count] = true;
				p2table[i][j + k][count] = true;
			}
			count++;
		}
	}
	for (i = 0; i < 11; ++i)
	{
		for (j = 0; j < 11; ++j)
		{
			for (k = 0; k < 5; ++k)
			{
				p1table[j + k][i + k][count] = true;
				p2table[j + k][i + k][count] = true;
			}
			count++;
		}
	}
	for (i = 0; i < 11; ++i)
	{
		for (j = 14; j >= 4; --j)
		{
			for (k = 0; k < 5; ++k)
			{
				p1table[j - k][i + k][count] = true;
				p2table[j - k][i + k][count] = true;
			}
			count++;
		}
	}
}

void FiveChess::DrawMap()
{
	system("cls");
	
	cout << "  ";
	for (int i = 1; i <= size; ++i)
	{
		printf("%-3d", i);
	}
	printf("\n");
	for (int i = 1; i <= size; ++i)
	{
		printf("%2d", i);
		for (int j = 1; j <= size; ++j)
		{			
			printf("%-3c", chessboard[i - 1][j - 1]);			
		}
		
		cout << endl;
	}
}
void FiveChess::DownChess(int x, int y, char a)
{
	chessboard[x - 1][y - 1] = a;
	num++;
	//更新获胜组合数组状态
	if (a == 'x')//计算机
	{
		for (int i = 0; i < 572; ++i)
		{
			if (p2table[x-1 ][y-1][i] && win[1][i] != 7)
			{
				(win[1][i])++;
			}
			if (p1table[x - 1][y - 1][i])
			{
				p1table[x - 1][y - 1][i] = false;
				win[0][i] = 7;
			}
		}
	}
	else
	{
		for (int i = 0; i < 572; ++i)
		{
			if (p1table[x - 1][y - 1][i] && win[0][i] != 7)
			{
				(win[0][i])++;
			}
			if (p2table[x - 1][y - 1][i])
			{
				p2table[x - 1][y - 1][i] = false;
				win[1][i] = 7;
			}
		}
	}
}

bool FiveChess::CheckWin(int x,int y)
{
	char cur = chessboard[x - 1][y - 1] == 'x' ? 'x' : 'o';
	int winflag = 1;
	int i, j;
	int count = 0;
	//////////////////////////////
	//竖直判断
	for (i = x - 1, j = y; i > 0 && count++ < 5; --i)
	{
		if (chessboard[i - 1][j - 1] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	for (i = x + 1,j = y; i <= size&&count++ < 5; ++i)
	{
		if (chessboard[i - 1][j - 1] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	if (winflag >= 5)
		return true;
	else
		winflag = 1;
	//水平方向
	for (i = x, j = y + 1; j <= size && count++ < 5; j++)
	{
		if (chessboard[i-1][j-1] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	 
	for (i = x, j = y - 1; j > 0 && count++ < 5; j--)
	{
		if (chessboard[i-1][j-1] == cur)
			winflag++;
		else
			break;  
	}
	count = 0;
	 
	if (winflag >= 5)
		return true;
	else
		winflag = 1;
	//2，4
	for (i = x + 1, j = y + 1; i <= size && j <= size && count++ < 5; i++, j++)
	{
		if (chessboard[i-1][j-1] == cur)
			winflag++;
		else
			break;  
	}
	count = 0;
	
	for (i = x - 1, j = y - 1; i > 0 && j > 0 && count++ < 5; i--, j--)
	{
		if (chessboard[i-1][j-1] == cur)
			winflag++;
		else
			break; 
	}
	count = 0;
	 
	if (winflag >= 5) 
		return true;
	else
		winflag = 1;
	//1,3
	for (i = x - 1, j = y + 1; i > 0 && j <=size && count++ < 5; i--, j++)
	{
		if (chessboard[i-1][j-1] == cur)
			winflag++;
		else
			break;  
	}
	count = 0;
	 
	for (i = x + 1, j = y - 1; i <= size && y > 0 && count++ < 5; i++, j--)
	{
		if (chessboard[i-1][j-1] == cur)
			winflag++;
		else
			break; 
	}
	count = 0;
	 
	if (winflag >= 5)  
		return true;
	else
		winflag = 1;
	return false;
}
bool FiveChess::ComputerPos()
{
	//计算玩家分数
	int i = 0; int j = 0; int k = 0;
	int cgrades = 0; int pgrades = 0;
	int mat = 0; int nat = 0;
	int mde = 0; int nde = 0;
	int m = 0; int n = 0;
	for (i = 0; i < 15; ++i)
	{
		for (j = 0; j < 15; ++j)
		{
			pgrade[i][j] = 0;
			if (chessboard[i][j] == '-')
			{
				for (k = 0; k < 572; ++k)
				{
					if (p1table[i][j][k])
					{
						switch (win[0][k])
						{
						case 1:pgrade[i][j] += 5; break;
						case 2:pgrade[i][j] += 50; break; 
						case 3:pgrade[i][j] += 300; break;
						case 4:pgrade[i][j] += 900; break;
						default:break;
						}
					}
				}
			}
		}
	}
	//计算玩家分数
	for (i = 0; i < 15; ++i)
	{
		for (j = 0; j < 15; ++j)
		{
			cgrade[i][j] = 0;
			if (chessboard[i][j] == '-')
			{
				for (k = 0; k < 572; ++k)
				{
					if (p2table[i][j][k])
					{
						switch (win[1][k])
						{
						case 1:cgrade[i][j] += 5; break;
						case 2:cgrade[i][j] += 50; break;
						case 3:cgrade[i][j] += 300; break;
						case 4:cgrade[i][j] += 900; break;
						default:break;
						}
					}
				}
			}
		}
	}
	//确定计算机落子位置
	for (i = 0; i < 15; ++i)
	{
		for (j = 0; j < 15; ++j)
		{
			if (chessboard[i][j] == '-')
			{
				if (cgrade[i][j] >= cgrades)
				{
					cgrades = cgrade[i][j];
					mat = i; 
					nat = j;
				}
				if (pgrade[i][j] >= pgrades)
				{
					pgrades = pgrade[i][j];
					mde = i;
					nde = j;
				}
			}
		}
	}
	if (cgrades >= pgrades)
	{
		m = mat;
		n = nat;
	}
	else
	{
		m = mde;
		n = nde;
	}
	DownChess(m + 1, n + 1, 'x');
	DrawMap();
	if (num >= 225)
	{
		cout << "平局" << endl;
		return true;
	}
	if (CheckWin(m+1, n+1))
	{
		cout << "你竟然输给了这个愚蠢的算法！！！！(￣▽￣)" << endl;
		return true;
	}
	return false;
}
bool FiveChess::PlayerPos()
{
	int x, y;
	do
	{
		cout << "输入坐标（行 列）:";
		cin >> x >> y;
		if (IsValidPos(x, y))
			break;
		else
			cout << "输入错误！" << endl;
	} while (1);
	DownChess(x, y, 'o');
	DrawMap();
	if (num >= 225)
	{
		cout << "平局" << endl;
		return true;
	}
	if (CheckWin(x, y))
	{
		cout << "恭喜玩家取得胜利！(*^▽^*)" << endl;
		return true;
	}
	return false;

}
bool FiveChess::IsValidPos(int x, int y)
{
	if (x <= 0 || x > size || y <= 0 || y > size)
		return false;
	if (chessboard[x - 1][y - 1] != '-')
		return false;
	return true;
}
void FiveChess::Game()
{
	FiveChess a;
	//a.InitParams();
	a.DrawMap();
	cout << "玩家先走，电脑后走" << endl;
	while (1)
	{
		if (a.PlayerPos())
			break;
		if (a.ComputerPos())
			break;
	}
}
