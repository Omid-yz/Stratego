//khoruG getcell & e! havasemun bashe kolly!!!

#ifndef	STRATEGO
#define STRATEGO

#include <iostream>
#include <vector>
#include <string>
#include "board.h"
#include "stratego.h"

using namespace std;

int main()
{
	/*player *p[2];
	board b() ;*/

    int x1, y1, x2, y2;
//	int x11 = 5,y11 = 4,x22 = 4,y22 = 4;
	vector <string> temp(4);

	Stratego test;
	temp = test.Initialize();

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if(test.get_board()->getcell(i,j))
				cout << test.get_board()->getcell(i,j)->get_num() << '\t';
			else
				cout << '0' << '\t';
		}

		cout << endl;
	}

    for (int i = 0; i < 5; i++)
    {
        test.Play(x1,y1,x2,y2);
        test.capture('0');
        cout << endl << endl;

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if(test.get_board()->getcell(i,j))
                    cout << test.get_board()->getcell(i,j)->get_num() << '\t';
                else
                    cout << '0' << '\t';
            }

            cout << endl;
        }
    }

//    test.Play(x1,y1,x2,y2);
//    test.capture('0');
//    cout << endl << endl;

//    for (int i = 0; i < 10; i++)
//    {
//        for (int j = 0; j < 10; j++)
//        {
//            if(test.get_board()->getcell(i,j))
//                cout << test.get_board()->getcell(i,j)->get_num() << '\t';
//            else
//                cout << '0' << '\t';
//        }

//        cout << endl;
//    }




	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		if(test.get_board()->getcell(i,j))
	//			cout << test.get_board()->getcell(i,j)->get_num() << '\t';
	//		else
	//			cout << '0' << '\t';
	//	}

	//	cout << endl;
	//}

	//test.Update(3,4,4,4,'0');

	//	cout << endl << endl;

	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		if(test.get_board()->getcell(i,j))
	//			cout << test.get_board()->getcell(i,j)->get_num() << '\t';
	//		else
	//			cout << '0' << '\t';
	//	}

	//	cout << endl;
	//}

	//test.Play(x11,y11,x22,y22);
	//test.capture('8');

	//cout << endl << endl;

	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		if(test.get_board()->getcell(i,j))
	//			cout << test.get_board()->getcell(i,j)->get_num() << '\t';
	//		else
	//			cout << '0' << '\t';
	//	}

	//	cout << endl;
	//}

	system("pause");
	return 0;
}

#endif
