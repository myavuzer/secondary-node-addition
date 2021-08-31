//============================================================================
// Name        : SecondaryAdd.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================


#include <string>
#include "MasterNode.h"

bool bMnRun = false;
bool bSnRun = false;

masterNode mn;

void MasterXmit(void * pMyId)
{
	mn.Connect();
	ThreadNr++;
}
int main(int argc, char **argv) {

	_beginthread(MasterXmit, 0, &ThreadNr);
	Sleep(2000);

	//run master node
	//string command;
	//cout<<"To add secondary node, enter 'add' " <<endl;
	do{
		/*cin >> command;
		if(command.find("add") != std::string::npos){
			mn.addNode();
		}*/
		mn.addNode();
		Sleep(2000);
	}while(true);

	return 0;
}
