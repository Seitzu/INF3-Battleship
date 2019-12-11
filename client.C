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

/*	int i=0;
	bool goOn=1;
	while(goOn){ // send and receive data
		if((rand() % 20) < i++){
			msg = string("BYEBYE");
			goOn = 0;
		}else{
			msg = string("client wants this");
		}*/
	while(1)
	{
		x=(rand() %10)+1;
		y=(rand() %10)+1;

		msg=coordStr(x,y);
		//cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		//cout << "got response:" << msg << endl;
		//sleep(1);

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

/*	for(x;x<10;x++)
	{
		for(y;y<10;y++)
	}
*/
	c.sendData(string("BYEBYE"));
	cout << "Anzahl der notwendigen Züge: "<< nmbShoots << endl;
}

string coordStr(int x,int y)
{
	stringstream ss;
	ss<<"COORD["<< x <<","<< y<<"]"<<endl;
	return ss.str();
}


