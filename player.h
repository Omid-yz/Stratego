#ifndef	PLAYER_H
#define PLAYER_H

#include "board.h"

class player
{
private:
    int pcount[12];         //Kare herfe e!!![zoorgooye mostabed] (mad)  :D !
	board * bord;
	//piece * pic;
	
public:
	player();
	int count (int);
	int countUp(int);
	double safety (int);
	double bigSafety (int, int, int);

    bool movabale(int, int);
	friend class Stratego;
	friend class board;
};

player::player()
{
	pcount[0] = 1;         
	pcount[1] = 1;
	pcount[2] = 2;
	pcount[3] = 3;
	pcount[4] = 4;
	pcount[5] = 4;
	pcount[6] = 4;
	pcount[7] = 5;
	pcount[8] = 8;
	pcount[9] = 1;          //Spy
	pcount[10] = 6;         //Bomb
	pcount[11] = 1;         //Flag
}

int player::count (int pic)
{
	int counter = 0;

	for (int i = 0; i < 10; i++)  
	{
		for (int j = 0; j < 10; j++)
		{
			if (bord->getcell(i, j) -> num == pic)//bord->getcell.num 
			{
				counter++;
			}
		}
	}

	return counter;
}

int player::countUp(int pic)
{
	int counter = 0;
	
	for (int i = 0; i < pic; i++)
	{
			counter += (pcount[i] - count(i));
	}     

	return counter;
}

double player::safety (int pic)   // x want to hit an unkhown piece
{
	return double(11 - pic) / countUp(pic);
}

double player:: bigSafety (int pic, int x, int y)   
{
	double safe[4];

    if (bord -> can (x + 1, y)) //down;
	{
        if (bord -> getcell(x + 1, y) -> get_num() == -1)   //Unkhown piece
		{
			safe[0] = safety(pic);
		}

		else  //if (bord->getcell(x + 1, y) != -1)
		{
            if (!bord -> getcell(x + 1, y)-> get_op())
			{
				safe[0] = 100;
			}

			else  //if (bord->getcell(x+1, y).op == 1)
			{
                if (bord -> getcell(x + 1, y) -> get_num() < pic)
					safe[0] = 0;

                if (bord -> getcell(x + 1, y) -> get_num() > pic)
					safe[0] = 100;
			}
		}

	}

    if (bord -> can (x - 1, y))     //Up
	{
        if (bord -> getcell(x - 1, y) -> get_num == -1)   //Unkhown piece
		{
			safe[1] = safety(pic);
		}

		else  //if (bord->getcell(x - 1, y).num != -1)
		{
            if (!bord -> getcell(x - 1, y) -> get_op())
			{
				safe[1] = 100;
			}

			else  //if (bord->getcell(x - 1, y).op == 1)
			{
                if (bord -> getcell(x - 1, y) -> get_num() < pic)
					safe[1] = 0;

                if (bord -> getcell(x - 1, y) -> get_num() > pic)
					safe[1] = 100;
			}
		}

	}

    if (bord -> can (x, y + 1))       //Right
	{
        if (bord -> getcell(x, y + 1) -> get_num()  == -1)   //Unkhown piece
		{
			safe[2] = safety(pic);
		}

		else  //if (bord->getcell(x, y + 1).num  != -1)
		{
            if (!bord -> getcell(x, y + 1) -> get_op())
			{
				safe[2] = 100;
			}

			else  //if (bord->getcell(x, y + 1).op == 1)
			{
                if (bord -> getcell(x, y + 1) -> get_num() < pic)
					safe[2] = 0;

                if (bord -> getcell(x, y + 1) -> get_num() > pic)
					safe[2] = 100;
			}
		}

	}

    if (bord -> can (x, y - 1))     //Left
	{
        if (bord -> getcell(x, y - 1) -> get_num() == -1)   //Unkhown piece
		{
			safe[3] = safety(pic);
		}

		else  //if (bord->getcell(x, y - 1).num != -1)
		{
            if (bord -> getcell(x, y - 1) -> get_op() == 0)
			{
				safe[3] = 100;
			}

			else  //if (bord->getcell(x, y - 1).op == 1)
			{
                if (bord -> getcell(x, y - 1) -> get_num() < pic)
					safe[3] = 0;

                if (bord -> getcell(x, y - 1) -> get_num() > pic)
					safe[3] = 100;
			}
		}

	}

	return safe[0] * safe[1] * safe[2] * safe[3];
}


bool player::movabale(int x, int y) //kollan beshe ye tabe move? ke taghriban yejurae mishe hamun play!
{
    data temp;
    piece * check;

    check = bord -> getcell(x + 1, y);

    if(check)
    {
        if (!check -> get_op())
        {
            temp.check = true;
            //edame taghirate temp, tavabe safty o ...
            check->add_move(temp);
        }
    }

    check = bord -> getcell(x - 1, y);

    if(check)
    {
        if (!check -> get_op())
        {
            temp.check = true;
            //edame taghirate temp, tavabe safty o ...
            check->add_move(temp);
        }
    }

    check = bord -> getcell(x, y + 1);

    if(check)
    {
        if (!check -> get_op())
        {
            temp.check = true;
            //edame taghirate temp, tavabe safty o ...
            check->add_move(temp);
        }
    }

    check = bord -> getcell(x, y - 1);

    if(check)
    {
        if (!check -> get_op())
        {
            temp.check = true;
            //edame taghirate temp, tavabe safty o ...
            check->add_move(temp);
        }
    }
}

//Khabam miad khob!!

#endif
