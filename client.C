/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <sstream>
#include <string>
#include <iostream>
#include <unistd.h> //contains various constants

#include "SIMPLESOCKET.H"

using namespace std;

string coordStr(int x,int y);

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;
	string response;
	int x,y,r;
	int nmbShoots=0;
	//connect to host
	c.conn(host , 2021);

	//Strategie 1 - Random
	for(int i=0;i<5000;i++){
		c.sendData(string("NEWGAME"));
		c.receive(32);
		nmbShoots=0;
		while(1)
		{
			x=(rand() %10)+1;
			y=(rand() %10)+1;

			msg=coordStr(x,y);

			c.sendData(msg);
			msg = c.receive(32);


			if(1!=sscanf(msg.c_str(),"RES[%d]",&r))
			{
				cout <<"unknown response: "<<msg<< endl;
			}
			else
			{
				nmbShoots ++;
			}
			if(r==TASK3::GAME_OVER)break;

		}
		cout << nmbShoots << endl;
	}

	//Strategie2 - Reihenweise
/*	for(int i=0;i<5000;i++)
	{
		c.sendData(string("NEWGAME"));
		c.receive(32);
		nmbShoots=0;

		for(y=1;y<11;y++)
		{
			for(x=1;x<11;x++)
			{

				msg=coordStr(x,y);
				c.sendData(msg);
				msg = c.receive(32);

				if(1!=sscanf(msg.c_str(),"RES[%d]",&r))
				{
					cout <<"unknown response: "<<msg<< endl;
				}
				else
				{
					nmbShoots ++;
				}
				if(r==TASK3::GAME_OVER)break;

			}
			if(r==TASK3::GAME_OVER)break;

		}
		cout << nmbShoots << endl;
	}*/
}

string coordStr(int x,int y)
{
	stringstream ss;
	ss<<"COORD["<< x <<","<< y<<"]"<<endl;
	return ss.str();
}


