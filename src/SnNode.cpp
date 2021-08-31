//============================================================================
// Name        : SnNode.cpp
// Author      : Mahmut Yavuzer
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include "SecondaryNode.h"

using namespace std;

snNode sn(5090);


int main() {
	sn.Init();
	sn.Connect();
	//_beginthread(SecondaryReceiver, 0, ThreadNr);
	sn.Receive();
	return 0;
}
