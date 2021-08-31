/*
 * MasterNode.h
 *
 *  Created on: 30 Aðu 2021
 *      Author: mahmut.yavuzer
 */

#ifndef MASTERNODE_H_
#define MASTERNODE_H_

#include <iostream>
#include <windows.h>
#include "common.h"

#define BUFFER_LENGTH 4096

class masterNode{

public:
	masterNode();
	~masterNode();

	void Connect();
	void processAckMessage(uint8_t *in_buf);
	void addNode();
private:
	int serverId = 0;
	int  addr_len = {0};
	int  clientNode = {0};
	bool _bRunThread = false;
	uint16_t portNum = 5090;
	char   in_buf[BUFFER_LENGTH] = {0};
	struct sockaddr_in   server_addr = {0};
	//struct sockaddr_in   client_addr = {0};

	SgNBAddRequestMsg addMsg = {0};
	SgNBAddRequestAckMsg addAckMsg = {0};
	SgNBReconfigurationCompleteMsg recCompMsg = {0};
	void CloseSocket();

};

#endif /* MASTERNODE_H_ */
