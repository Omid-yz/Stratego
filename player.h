#ifndef	PLAYER_H
#define PLAYER_H

#include "board.h"
#include <cmath>

using namespace std;

struct action_data
{
	int x1, y1;
	int x2, y2;
	double play;
	double safty;
	double board_scr;
};

class player
{
private:
    int pcount[12];         //Kare herfe e!!![zoorgooye mostabed] (mad)  :D !
	board * bord;
	vector <action_data> actions;
	//piece * pic;
	
public:
    player(board *);
	int count (int);
	int countUp(int);
	double safety (int);
	double bigSafety (int, int, int);
    bool movabale(int, int);
    void unknown();
	int board_score(player&);
	board get_board (board, action_data);
    void bestMove(int &,  int &, int &, int &, int, int);
	void chancing ();
	action_data min_max(int, player, bool);
	vector <action_data> get_action(board &, bool); //bool -- op or not! :D

	friend class Stratego;
	friend class board;
};

player::player(board * inp_board)   //Akhe chera man in karo kardam??? :| countup
{

	pcount[0] = 1;         
	pcount[1] = 1;
	pcount[2] = 2;
	pcount[3] = 3;
	pcount[5] = 4;
	pcount[6] = 4;
	pcount[7] = 5;
	pcount[8] = 8;
	pcount[9] = 1;          //Spy
	pcount[10] = 6;         //Bomb
	pcount[11] = 1;         //Flag

    bord = inp_board;

    return;
}

int player::count (int pic)
{
	int counter = 0;

	for (int i = 0; i < 10; i++)  
	{
		for (int j = 0; j < 10; j++)
		{
            if (bord->getcell(i, j) != NULL)
            {
                if (bord->getcell(i, j) -> get_num() == pic)//bord->getcell.num
                {
					if (bord->getcell(i, j) -> get_op() == 1)
					{
						counter++;
					}
                }
            }
		}
	}

	return counter;
}

int player::countUp(int pic)//!!!!!!!!!!!!!!
{
	int counter = 0;

	for (int i = 0; i < pic; i++)// = bezarim be nazare man!(i <= pic)
	{
			counter += (pcount[i] - count(i));
	} 

	if (pic == 8)
	{
		return counter;
	}

	return counter + pcount[10];// + bomb
}

double player::safety (int pic)   // x want to hit an unkhown piece
{
	return double(11 - pic) / countUp(pic);
}

double player:: bigSafety (int pic, int x, int y)   
{
	double safe[4];

	for (int i = 0; i < 4; i++)
	{
        safe[i] = 110;
	}

    if (bord -> can (x + 1, y)) //down;
	{
        if (bord -> getcell(x + 1, y) == NULL)
        {
            safe[0] = 90;
        }

        else if (bord -> getcell(x + 1, y) -> get_num() == -1)   //Unkhown piece
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
        if (bord -> getcell(x - 1, y) == NULL)
        {
            safe[1] = 90;
        }

        else if (bord -> getcell(x - 1, y) -> get_num() == -1)   //Unkhown piece
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
        if (bord -> getcell(x, y + 1) == NULL)
        {
            safe[2] = 90;
        }

        else if (bord -> getcell(x, y + 1) -> get_num()  == -1)   //Unkhown piece
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
        if (bord -> getcell(x, y - 1) == NULL)
        {
            safe[3] = 90;
        }

        else if (bord -> getcell(x, y - 1) -> get_num() == -1)   //Unkhown piece
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

	double res = (log10(safe[0] + 1) + log10(safe[1] + 1) + log10(safe[2] + 1) + log10(safe[3] + 1));
	return res;
}

bool player::movabale(int x, int y)
{
    if(y >= 0 && y < 10)
    {
        if (x >= 0 && x < 10)
        {
            if(!(x == 4 && (y == 2 || y == 3 || y == 6 || y == 7)))
            {
                if(!(x == 5 && (y == 2 || y == 3 || y == 6 || y == 7)))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int player::board_score(player& inp)//bomb, flag, spy
{
	piece *temp;
	int op_point = 0;
	int us_point = 0;
	int op_kn_point = 0;
	int us_kn_point = 0;
	int op_be_point = 0;
	int us_be_point = 0;
	int us_safty_point = 0;
	int tpoint;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			temp = bord -> getcell (i, j);
			if (temp != NULL)
			{
				if (temp -> get_num() != -1)
				{
					if (temp -> get_op())
					{
						op_kn_point += (11 - temp -> get_num());
					}

					else				//us
					{
						us_be_point += (11 - temp -> get_num());
						if (temp -> get_id())
						{
							us_kn_point -= (11 - temp -> get_num());
						}

						us_safty_point += bigSafety(temp -> get_num(), i, j);
					}
				}
			}
		}
	}

	for (int i = 0; i < 12; i++)
	{
		op_be_point -= pcount[i] * (11 - i + 1);
	}

	tpoint = (us_be_point + op_be_point) * 2 + (us_kn_point + op_kn_point) * 1.5+ (us_safty_point);

	
	return tpoint;
}

board player::get_board (board inp, action_data action)
{
	if (action.x2 == -1)
	{
		inp.pop(action.x1, action.y1);
		return inp;
	}

	inp.placement(action.x1, action.y1, action.x2, action.y2);
	return inp;
}

action_data player::min_max(int l, player inp, bool op)
{
	if (l != 1)
	{
		vector <action_data> action;
		action = get_action(*inp.bord, op);
		int size = action.size();
		action_data *temp;
		temp = new action_data[size];

		for (int i = 0; i < size; i++)
		{
			*inp.bord = get_board(*inp.bord, action[i]);
			temp[i] = min_max(l - 1, inp, !op);
		}

		if (op)
		{
			action_data max;
			max.board_scr = 0;

			for (int i = 0; i < size; i++)
			{
				if (temp[i].board_scr > max.board_scr)
				{
					max.board_scr = temp[i].board_scr;
				}
			}

			return max;
		}

		if (!op)
		{
			action_data min;
			min.board_scr = 0;

			for (int i = 0; i < size; i++)
			{
				if (temp[i].board_scr < min.board_scr)
				{
					min.board_scr = temp[i].board_scr;
				}
			}

			return min;
		}
	}

	else
	{
		action_data temp;
		inp.bord = get_board
		temp.board_scr = board_score(
	}
}

//vector <action_data>  player::get_action(board inp, bool op)
//{
//	piece * temp;
//	action_data tmp;
//	vector <action_data> res;
//
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 10; j++)
//		{
//			temp = bord -> getcell (i, j);
//			if (temp != NULL)
//			{
//				if (!op)
//				{
//					if (!temp -> get_op())
//					{
//
//					}
//				}
//			}
//		}
//	}
//}

vector <action_data> player::get_action(board & inp, bool op) //kollan beshe ye tabe move? ke taghriban yejurae mishe hamun play!
{
    action_data temp;
    piece * check;
	double scape = 0;

	//check = inp.getcell(x + 1, y);

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
			temp.x1 = i;
			temp.y1 = j;
            check = inp.getcell(i, j);
            int check_num;
		
            if (check != NULL && !check -> get_op() && !op)
			{
				check_num = check -> get_num();
				if (check_num != 11 && check_num != 12)
				{	
					int thisSafety = bigSafety(check_num, i, j);

					if (thisSafety < 2.354)
					{
						scape = 8 - thisSafety + check_num / 10;

						if (thisSafety == 0)
						{
							scape = (11 - check_num) * 2;
						}
					}

					if(movabale(i - 1, j)) //up
					{
						if (!bord ->getcell(i - 1, j))
						{
							temp.x2 = i - 1;
							temp.y2 = j;
                            temp.play = (bigSafety(check_num, i - 1, j)) - (thisSafety) + ((10 - i) / 10);

							if (check_num == 9)
							{
								temp.play = (thisSafety) - (bigSafety(check_num, i - 1, j)) + ((10 - i) / 10);
							}

						   /* if (check_num < 4)
							{
								temp.play += ((11 - inp.getcell(i -1, j) -> get_num()) * 10);
							}*/

							temp.play += scape;
							actions.push_back(temp);
						}

						else  //not empty.
						{
							piece * check_up = inp.getcell(i -1, j);
							if(check_up -> get_op())
							{
								if(check_up -> get_num() != -1)//known piece
								{
									if (check_up -> get_num() > check_num)
									{
										temp.x2 = i - 1;
										temp.y2 = j;
										temp.play = ((11 - check_up -> get_num()) * 10) + (bigSafety(check_num, i - 1, j))
                                                  - (thisSafety) - ((check -> get_id() - 1) * (11 - check_num)) + ((10 - i) / 10);

										if (check_num == 9)
										{
											temp.play = 0;
										}

										temp.play += scape;
										actions.push_back(temp);
									}
								}

								else //unknown
								{
									temp.x2 = i - 1;
									temp.y2 = j;
									temp.play = ((11 - check_num) * 10) + (bigSafety(check_num, i - 1, j))
                                              - (thisSafety) - ((check -> get_id() - 1) * (11 - check_num)) + ((10 - i) / 10);

									if (check_num == 9)
									{
										temp.play = 2.174;
									}

									temp.play += scape;
									actions.push_back(temp);

									action_data temp_2;
									temp_2.x1 = i;
									temp_2.y1 = j;
									temp_2.x2 = -1;
									temp_2.y2 = -1;
									// -1 yani az bord hazf mishavad.
									// bayad ehtemal mohasebe va zakhire shavad.
									actions.push_back(temp_2);
								}
							}
						}
					}

					if(movabale(i + 1, j)) //down
					{
						if (!bord ->getcell(i + 1, j))
						{
							temp.x2 = i + 1;
							temp.y2 = j;
                            temp.play = (bigSafety(check_num, i + 1, j)) - (thisSafety) + ((10 - i) / 10);

							if (check_num == 9)
							{
								temp.play = (thisSafety) - (bigSafety(check_num, i - 1, j)) + ((10 - i) / 10);
							}

							/*if (check_num < 4)
							{
								temp.play += ((11 - inp.getcell(i + 1, j) -> get_num()) * 10);
							}*/

							temp.play += scape;
							actions.push_back(temp);
						}

						else
						{
							piece * check_down = inp.getcell(i + 1, j);
							if(check_down -> get_op())
							{
								if(check_down -> get_num() != -1)//known piece
								{
									if (check_down -> get_num() > check_num)
									{
										temp.x2 = i + 1;
										temp.y2 = j;
										temp.play = ((11 - check_down -> get_num()) * 10) + (bigSafety(check_num, i + 1, j))
                                                  - (thisSafety) - ((check -> get_id() - 1) * (11 - check_num)) + ((10 - i) / 10);

										if (check_num == 9)
										{
											temp.play = 0;
										}

										temp.play += scape;
										actions.push_back(temp);
									}
								}

								else
								{
									temp.x2 = i + 1;
									temp.y2 = j;
									temp.play = ((11 - check_num) * 10) + (bigSafety(check_num, i + 1, j))
                                              - (thisSafety) - ((check -> get_id() - 1) * (11 - check_num)) + ((10 - i) / 10);

									if (check_num == 9)
									{
										temp.play = 2.174;
									}

									temp.play += scape;
									actions.push_back(temp);

									action_data temp_2;
									temp_2.x1 = i;
									temp_2.y1 = j;
									temp_2.x2 = -1;
									temp_2.y2 = -1;
									// -1 yani az bord hazf mishavad.
									// bayad ehtemal mohasebe va zakhire shavad.
									actions.push_back(temp_2);
								}
							}
						}
					}

					if(movabale(i, j - 1)) //left
					{
						if (!bord ->getcell(i, j - 1))
						{
							temp.x2 = i;
							temp.y2 = j - 1;
                            temp.play = (bigSafety(check_num, i, j - 1)) - (thisSafety) + ((10 - i) / 10);

							if (check_num == 9)
							{
								temp.play = (thisSafety) - (bigSafety(check_num, i - 1, j)) + ((10 - i) / 10);
							}

						   /* if (check_num < 4)
							{
								temp.play += ((11 - inp.getcell(i, j - 1) -> get_num()) * 10);
							}*/

							temp.play += scape;
							actions.push_back(temp);
						}

						else
						{
							piece * check_left = inp.getcell(i, j - 1);
							if(check_left -> get_op())
							{
								if(check_left -> get_num() != -1)//known piece
								{
									if (check_left -> get_num() > check_num)
									{
										temp.x2 = i;
										temp.y2 = j - 1;
										temp.play = ((11 - check_left -> get_num()) * 10) + (bigSafety(check_num, i, j - 1))
                                                  - (thisSafety) - ((check -> get_id() - 1) * (11 - check_num)) + ((10 - i) / 10);

										if (check_num == 9)
										{
											temp.play = 0;
										}

										temp.play += scape;
										actions.push_back(temp);
									}
								}

								else
								{
									temp.x2 = i;
									temp.y2 = j - 1;
									temp.play = ((11 - check_num) * 10) + (bigSafety(check_num, i, j - 1))
                                              - (thisSafety) - ((check -> get_id() - 1) * (11 - check_num)) + ((10 - i) / 10);

									if (check_num == 9)
									{
										temp.play = 2.174;
									}

									temp.play += scape;
									actions.push_back(temp);

									action_data temp_2;
									temp_2.x1 = i;
									temp_2.y1 = j;
									temp_2.x2 = -1;
									temp_2.y2 = -1;
									// -1 yani az bord hazf mishavad.
									// bayad ehtemal mohasebe va zakhire shavad.
									actions.push_back(temp_2);
								}
							}
						}
					}

					if(movabale(i, j + 1)) //right
					{
						if (!(bord ->getcell(i, j + 1)))//yani akhare suti dadane !!! :|||
						{
							temp.x2 = i;
							temp.y2 = j + 1;
                            temp.play = (bigSafety(check_num, i, j + 1)) - (thisSafety) + ((10 - i) / 10);
						/*    if (check_num < 4)
							{
								temp.play += ((11 - inp.getcell(i, j + 1) -> get_num()) * 10);
							}*/

							temp.play += scape;
							actions.push_back(temp);
						}

						else
						{
							piece * check_right = inp.getcell(i, j + 1);
							if(check_right -> get_op())
							{
								if(check_right -> get_num() != -1)//known piece
								{
									if (check_right -> get_num() > check_num)
									{
										temp.x2 = i;
										temp.y2 = j + 1;
										temp.play = ((11 - check_right -> get_num()) * 10) + (bigSafety(check_num, i, j + 1))
                                                  - (thisSafety) - ((check -> get_id() - 1) * (11 - check_num)) + ((10 - i) / 10);

										
										if (check_num == 9)
										{
											temp.play = 0;
										}

										temp.play += scape;
										actions.push_back(temp);
									}
								}

								else
								{
									temp.x2 = i;
									temp.y2 = j + 1;
									temp.play = ((11 - check_num) * 10) + (bigSafety(check_num, i, j + 1))
                                              - (thisSafety) - ((check -> get_id() - 1) * (11 - check_num)) + ((10 - i) / 10);

									if (check_num == 9)
									{
										temp.play = 2.174;
									}

									temp.play += scape;
									actions.push_back(temp);

									action_data temp_2;
									temp_2.x1 = i;
									temp_2.y1 = j;
									temp_2.x2 = -1;
									temp_2.y2 = -1;
									// -1 yani az bord hazf mishavad.
									// bayad ehtemal mohasebe va zakhire shavad.
									actions.push_back(temp_2);
								}
							}
						}
					}
				}
			}

			if (check != NULL && check -> get_op() && op)
			{
				//bayad ehtemal ha mohasebe shavad ta beshe in ghesmat ro nevesht!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				check_num = check -> get_num();
				
				if(movabale(i - 1, j)) //up
				{
					if (!bord ->getcell(i - 1, j))		//empty area
					{
						temp.x2 = i - 1;
						temp.y2 = j;
						actions.push_back(temp);
					}

					else  //not empty.
					{
						piece * check_up = inp.getcell(i -1, j);
						if(!check_up -> get_op())
						{
							if(check_num != -1)//known piece
							{
								if (check_up -> get_num() > check_num)
								{
									temp.x2 = i - 1;
									temp.y2 = j;
									actions.push_back(temp);
								}
							}

							else //unknown
							{
								temp.x2 = i - 1;
								temp.y2 = j;
								actions.push_back(temp);

								action_data temp_2;
								temp_2.x1 = i;
								temp_2.y1 = j;
								temp_2.x2 = -1;
								temp_2.y2 = -1;
								// -1 yani az bord hazf mishavad.
								// bayad ehtemal mohasebe va zakhire shavad.
								actions.push_back(temp_2);
							}
						}
					}
				}

				if(movabale(i + 1, j)) //down
				{
					if (!bord ->getcell(i + 1, j))		//empty area
					{
						temp.x2 = i + 1;
						temp.y2 = j;
						actions.push_back(temp);
					}

					else  //not empty.
					{
						piece * check_down = inp.getcell(i + 1, j);
						if(!check_down -> get_op())
						{
							if(check_num != -1)//known piece
							{
								if (check_down -> get_num() > check_num)
								{
									temp.x2 = i + 1;
									temp.y2 = j;
									actions.push_back(temp);
								}
							}

							else //unknown
							{
								temp.x2 = i + 1;
								temp.y2 = j;
								actions.push_back(temp);

								action_data temp_2;
								temp_2.x1 = i;
								temp_2.y1 = j;
								temp_2.x2 = -1;
								temp_2.y2 = -1;
								// -1 yani az bord hazf mishavad.
								// bayad ehtemal mohasebe va zakhire shavad.
								actions.push_back(temp_2);
							}
						}
					}
				}

				if(movabale(i, j - 1)) //Left
				{
					if (!bord ->getcell(i, j - 1))		//empty area
					{
						temp.x2 = i;
						temp.y2 = j - 1;
						actions.push_back(temp);
					}

					else  //not empty.
					{
						piece * check_left = inp.getcell(i, j - 1);
						if(!check_left -> get_op())
						{
							if(check_num != -1)//known piece
							{
								if (check_left -> get_num() > check_num)
								{
									temp.x2 = i;
									temp.y2 = j - 1;
									actions.push_back(temp);
								}
							}

							else //unknown
							{
								temp.x2 = i;
								temp.y2 = j - 1;
								actions.push_back(temp);

								action_data temp_2;
								temp_2.x1 = i;
								temp_2.y1 = j;
								temp_2.x2 = -1;
								temp_2.y2 = -1;
								// -1 yani az bord hazf mishavad.
								// bayad ehtemal mohasebe va zakhire shavad.
								actions.push_back(temp_2);
							}
						}
					}
				}

				if(movabale(i, j + 1)) //Right
				{
					if (!bord ->getcell(i, j + 1))		//empty area
					{
						temp.x2 = i;
						temp.y2 = j + 1;
						actions.push_back(temp);
					}

					else  //not empty.
					{
						piece * check_right = inp.getcell(i, j + 1);
						if(!check_right -> get_op())
						{
							if(check_num != -1)//known piece
							{
								if (check_right -> get_num() > check_num)
								{
									temp.x2 = i;
									temp.y2 = j + 1;
									actions.push_back(temp);
								}
							}

							else //unknown
							{
								temp.x2 = i;
								temp.y2 = j + 1;
								actions.push_back(temp);

								action_data temp_2;
								temp_2.x1 = i;
								temp_2.y1 = j;
								temp_2.x2 = -1;
								temp_2.y2 = -1;
								// -1 yani az bord hazf mishavad.
								// bayad ehtemal mohasebe va zakhire shavad.
								actions.push_back(temp_2);
							}
						}
					}
				}

			}
        }
	}

    return;
}

void player::bestMove(int & x1, int & y1, int & x2, int & y2, int opx2, int opy2)
{
    int max = 0;
    move_data temp;
    unknown(opx2, opy2);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int k = 0;

            if (bord -> getcell(i, j) != NULL)
            {
                while(k != bord -> getcell(i, j) -> get_moves().size())
                {
                    temp = bord -> getcell(i, j) -> get_moves()[k];

                    if(temp.play >= max)
                    {
                        max = temp.play;
                        x1 = i;
                        y1 = j;
                        x2 = temp.x;
                        y2 = temp.y;
                    }

                    k++;
                }
            }
        }
    }

    return;
}

void player::chancing ()
{
	for (int i = 0; i < 10; i++)  
	{
		for (int j = 0; j < 10; j++)
		{
            if (bord->getcell(i, j) != NULL)
            {
                if (bord->getcell(i, j) -> get_op() == 1) //Opponent
                {
					double * ch = bord->getcell(i, j) -> get_chance();
					//if harekat nakone
					if (ch[12] != 0) //hanuz harekat nakarde
					{

					}
                }
            }
		}
	}

	//if harekat nakone
	//if bishtar az 2 khune bere
	//if az mohre ye knowne ma farar kone
	//(if samte bomb known bere)
}

#endif