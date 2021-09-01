/*
 * SecondaryNode.h
 *
 *  Created on: 31 Aðu 2021
 *      Author: mahmut.yavuzer
 */

#ifndef SECONDARYNODE_H_
#define SECONDARYNODE_H_



#include <iostream>
#include <windows.h>
#include "common.h"

#define IN_BUFFER_LENGTH 4096
#define OUT_BUFFER_LENGTH 4096

class snNode{
public:
	snNode(uint16_t portNum);
	~snNode();

	bool Init();
	bool Connect();
	void Receive();
	void processAddReqMessage(uint8_t* in_buf);
	void processRecCompMessage(uint8_t* in_buf);


	SOCKET m_socket;
private:
	uint16_t m_portNumber = 5090;
	const char IP_ADDRESS[15] = "127.0.0.1";//

	char  in_buf[IN_BUFFER_LENGTH] = {0};

	SgNBAddRequestAckMsg snAddAck= {0};

};



#endif /* SECONDARYNODE_H_ */
