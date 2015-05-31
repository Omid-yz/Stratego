#ifndef	BOARD_H
#define BOARD_H

#include "piece.h"

class board
{
private:
	piece * brd[10][10];
	//player * plr[2];
public:
	board();
	//bool move(int, int, int, int, piece *);   //Asan yadam nemiad bara chi in tabe ro neveshtam!:|   kheili bade ke in ghad fasele miofte beine code zadanemun! :\

	piece * getcell(int, int);         
	int ** getcell();
	bool add(int x, int y, piece * p);
	void placement(int, int, int, int);
	bool pop(int, int);
	bool can (int, int);
};

board::board()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
            brd[i][j] = NULL;
		}
	}
}

//bool board:: move(int x1, int y1, int x2, int y2, piece * p)
//{
//	if (brd[x2][y2] == NULL || brd[x2][y2]->op == 1)
//	{
//		if(y2 > 0 && y2 < 10)
//		{
//			if (x2 > 0 && x2 <10)
//			{
//				if(!(x2 == 4 && (y2 == 2 || y2 == 3 || y2 == 6 || y2 == 7)))
//				{
//					if(!(x2 == 5 && (y2 == 2 || y2 == 3 || y2 == 6 || y2 == 7)))
//					{
//						brd[x2][y2] = p;
//						pop(x1, y1);
//						return true;
//					}
//				}
//			}
//		}
//	}
//
//	return false;
//}

piece * board:: getcell(int x, int y)
{
    if(y >= 0 && y < 10)
    {
        if (x >= 0 && x <10)
        {
            if(!(x == 4 && (y == 2 || y == 3 || y == 6 || y == 7)))
            {
                if(!(x == 5 && (y == 2 || y == 3 || y == 6 || y == 7)))
                {
                    return brd[x][y];
                }
            }
        }
    }

    return NULL;
}

int ** board:: getcell()
{
	int **tmp;
	tmp = new int *[10];

	for (int i = 0; i < 10; i++)
	{
		tmp[i] = new int [10];
		for (int j = 0; j < 10; j++)
		{
			tmp[i][j] = getcell(i,j)->num;//ye tabe benevisim num az piece ro bede
		}
	}

	return tmp;
}

bool board:: add(int x, int y, piece * p)
{
    if (brd[x][y] == NULL)
	{
		brd[x][y] = p;
	}

	//operators should be overloaded. 
	/*if (*(brd[x][y]) == *(p))
	{
		return true;
	}*/

	return false;
}

void  board:: placement(int x1, int y1, int x2, int y2)
{
	brd[x2][y2] = brd[x1][y1];
    brd[x1][y1] = NULL;
	return;
}

bool board:: pop(int x, int y)
{
    brd[x][y] = NULL;
	if (!brd[x][y])
	{
		return true;
	}

	return false;
}

bool board:: can (int x, int y)
{
	if(y > 0 && y < 10)
	{
		if (x > 0 && x <10)
		{
			if(!(x==4 && (y==2 || y==3 || y==6 || y==7)))
			{
				if(!(x==5 && (y==2 || y==3 || y==6 || y==7)))
				{
					return true;
				}
			}
		}
	}

	return false;
}

#endif
