#ifndef	STRATEGO_H
#define STRATEGO_H

#include "board.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Stratego
{
private:
	board * brd;         
	player * plr[2];              //0: Us, 1: Opponent
	int lx1, ly1, lx2, ly2;       //Save our last play
    int opx1, opy1, opx2, opy2;       //Save opponnet last play
public:
	Stratego ();
	vector <string> Initialize();
	void Play(int &, int &, int &, int &);
	void Update(int, int, int, int, char);
	void capture(char);
	board * get_board();
};

Stratego::Stratego()
{
	brd = new board;

	vector <string> str(4);
	str[0] = "86898BFB48";
	str[1] = "997995B865";
	str[2] = "3566215434";
	str[3] = "9B7799S7BB";

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			piece * tmp = new piece(-1);
			brd->add(i, j, tmp);
		}
	}//op

	/*for (int i = 4; i < 6; i++)
	{
		for (int j = 0; j < 10; j++)
		{
            piece * tmp = NULL;
			brd->add(i, j, tmp);
		}
	}*/            //Empty area

//	brd.add(str);
	for (int i = 6; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (str[i - 6][j] <= '9' && str[i - 6][j] >= '1')
			{
				piece * tmp = new piece((int) (str[i - 6][j] - '0'));
				brd->add(i, j, tmp);
			}

			else if (str[i - 6][j] == 'S')
			{
				piece * tmp = new piece(10);
				brd->add(i, j, tmp);
			}

			else if (str[i - 6][j] == 'B')
			{
				piece * tmp = new piece(11);
				brd->add(i, j, tmp);
			}

			else if (str[i - 6][j] == 'F')
			{
				piece * tmp = new piece(12);
				brd->add(i, j, tmp);
			}
		}
	}//Us

    plr[0] = new player(brd);
    plr[1] = new player(brd);

    return;
}

vector <string> Stratego::Initialize()
{
	vector <string> str(4);
	str[0] = "86898BFB48";
	str[1] = "997995B865";
	str[2] = "3566215434";
	str[3] = "9B7799S7BB";

	return str;
}

void Stratego::Play(int & x1, int & y1, int & x2, int & y2)
{
    plr[0]->bestMove(x1, y1, x2, y2, opx2, opy2);

    lx1 = x1;
    ly1 = y1;
    lx2 = x2;
    ly2 = y2;  //Save last play

}

void  Stratego:: Update(int x1, int y1, int x2, int y2, char pic)
{
    opx1 = x1;
    opy1 = y1;
    opx2 = x2;
    opy2 = y2;  //Save last opponnet play

    //baraye bomb, spy joda benevis

	

    if (pic == '0')                                      //Move to an empty area
    {
        brd->placement(x1, y1, x2, y2);
        //brd->pop(x1, y1);
    }

    else
    {
        int nmb = brd->getcell(x2, y2)->num;

        if (pic == 'S')
        {
            if (nmb == 1)         //The opponnet won!
            {
                plr[1]->pcount[1 - 1] -= 1;           //1-1 :|
                brd->placement(x1, y1, x2, y2);
                brd->getcell(x2, y2)->num = 10;
            }

            if (nmb != 1)         //We won!
            {
                plr[0]->pcount[10 - 1] -= 1;
                brd->pop(x1, y1);
                brd->getcell(lx2, ly2)->id = true;
            }
        }

        if((pic - '0') < nmb)         //The opponnet won!
        {
            plr[1]->pcount[nmb - 1] -= 1;
            brd->placement(x1, y1, x2, y2);
            brd->getcell(x2, y2)->num = pic - '0';
        //	brd->pop(x1, y1);
        }

        if((pic - '0') > nmb)        //We won!
        {
            plr[0]->pcount[(pic - '0') - 1] -= 1;
            brd->pop(x1, y1);
            brd->getcell(lx2, ly2)->id = true;
        }

        if ((pic -'0') == nmb)
        {
            brd -> pop(lx1,ly1);
            brd -> pop(lx2,ly2);
            plr[0]->pcount[(pic - '0') - 1] -= 1;
            plr[1]->pcount[(pic - '0') - 1] -= 1;
        }
    }
}

void Stratego:: capture(char pic)
{
    /*Update(lx1, ly1, lx2, ly2, pic);*/

    if (pic == '0')                                      //Move to an empty area
    {
        brd->placement(lx1, ly1, lx2, ly2);
        //brd->pop(x1, y1);
    }

    else
    {
        int nmb = brd -> getcell(lx1, ly1) -> get_num();

        if (pic == 'S')
        {
            plr[0]->pcount[10 - 1] -= 1;
            brd->placement(lx1, ly1, lx2, ly2);
            brd->getcell(lx2, ly2)->id = true;
        }

        if (pic == 'B')
        {
            if (nmb != 8)              //The opponnet won!
            {
                plr[1]->pcount[nmb - 1] -= 1;
                brd->pop(lx1, ly1);
                brd->getcell(lx2, ly2)->num = 11;
            }

            if (nmb == 8)
            {
                plr[0]->pcount[11 - 1] -= 1;
                brd->placement(lx1, ly1, lx2, ly2);
                brd->getcell(lx2, ly2)->id = true;
            }
        }

        if (pic == 'F')
        {
            cout << "Winner Winner; Chicken Dinner! :P"<<endl;
        }

        if((pic - '0') < nmb)         //The opponnet won!
        {
            plr[1]->pcount[nmb - 1] -= 1;
            brd->pop(lx1, ly1);
            brd->getcell(lx2, ly2)->num = pic - '0';
        }

        if((pic - '0') > nmb)        //We won!
        {
            plr[0]->pcount[(pic - '0') - 1] -= 1;
            brd->placement(lx1, ly1, lx2, ly2);
            brd->getcell(lx2, ly2)->id = true;
        }

        if ((pic -'0') == nmb)
        {
            brd -> pop(lx1,ly1);
            brd -> pop(lx2,ly2);
            plr[0]->pcount[(pic - '0') - 1] -= 1;
            plr[1]->pcount[(pic - '0') - 1] -= 1;
        }
    }
}


board * Stratego:: get_board()
{
	return brd;
}

#endif
