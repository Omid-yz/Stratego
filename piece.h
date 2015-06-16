#include <vector>
using namespace std;

//struct move_data
//{
//    int x;
//    int y;
//    double safety;              //Security around our piece
//	//double hitPoint;              //
//    double play;
//	//bool check;
//};

class piece
{
private:
	//both opponent & us
	int num;                       //0: Empty area, 11: Bomb, 12: Flag, (manfi ha harif bashan, tabee getcell dar class  e board rahat tar mishe fahmidanesh)
	bool op;                       //1: Opponent, 0: Us
    double cellSafety;
	bool bomb;
	double chance[13];           
	
	//us
    //vector <move_data> move;	  //save move_data / used in unkown
	bool id;                      //Known by opponent

	//opponent
	int prob[12];                //The chance of being a piece
	//double safety;               //Security around the opponent piece in the case of its hitting

public:
	friend class board;
	friend class player;
	friend class Stratego;
	piece(int);                 //num: us, -1: opponent
	int get_num();
    bool get_op();
    bool get_id();
	double * get_chance();     //aya khoruji doroste?
    vector <move_data> & get_moves();
    void add_move(move_data);
//
    void set_mySafty(double);

//    void set_hitpoint();
//    void set_play();
//    void set_id();
};

piece:: piece(int inp)
{
	bomb = 0;
	if(inp == -1)    //Opponent
	{
		num = -1;
		op = 1;

		for (int t = 0; t < 12; t++)
		{
			prob[t] = 0;
		}

		for (int t = 0; t < 12; t++)
		{
			chance[t] = 1/40;
		}
	}

	else            //Us
	{
		num = inp;
		op = 0;
		id = 0;
	}
}

int piece::get_num()
{
	return num;
}

bool piece::get_op()
{
    return op;
}

bool piece::get_id()
{
    return id;
}

vector <move_data> & piece::get_moves()
{
    return move;
}

double * piece:: get_chance()
{
	return chance;
}

//void piece::set_mySafty(double inp_mySafty)
//{
//    mySafety = inp_mySafty;
//    return;
//}

void piece::add_move(move_data inp_data)
{
    move.push_back(inp_data);
    return;
}
