/*
 * MasterNode.cpp
 *
 *  Created on: 30 Aðu 2021
 *      Author: mahmut.yavuzer
 */

#include "MasterNode.h"

masterNode::masterNode(){

}
masterNode::~masterNode(){

}

void masterNode::Connect(){
	WORD wVersionRequested = MAKEWORD(1,1);       // Stuff for WSA functions
	WSADATA wsaData;                              // Stuff for WSA functions
	int retcode = 0;
	int recvMsgId = 0;
	// This stuff initializes winsock
	WSAStartup(wVersionRequested, &wsaData);

	// Create a welcome socket
	serverId = socket(AF_INET, SOCK_STREAM, 0);
	if (serverId < 0)
	{
		return;
	}

	// Fill-in server (my) address information and bind the welcome socket
	server_addr.sin_family = AF_INET;                 // Address family to use
	server_addr.sin_port = htons(portNum);           // Port number to use
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Listen on any IP address
	retcode = bind(serverId, (struct sockaddr *)&server_addr, sizeof(server_addr));
	printf("bind: %d\n", retcode);
	if (retcode < 0)
	{
		return;
	}

	// Listen on welcome socket for a connection
	listen(serverId, 1);
	addr_len = sizeof(server_addr);
	while(true)
	{
		printf("waiting for client connection\n");
		clientNode = accept(serverId, (struct sockaddr *)&server_addr, &addr_len);

		if (clientNode < 0)
		{
			printf("failed to accept client: %s\n", strerror(errno));
		} else {
			printf("accepted client socket\n");
			_bRunThread = true;
		}

		while(_bRunThread)
		{
			do {
				// Receive from the client
				retcode = recv(clientNode, in_buf, sizeof(in_buf), 0);
				recvMsgId = (in_buf[3] << 24) + (in_buf[2]<<16) + (in_buf[1] <<8) + (in_buf[0]);

				//aMessageControl(&kkyWholeDataStruct.a, (uint8_t*)in_buf_a1, dataIndex, a_LINE_0);
				if(recvMsgId == MSG_SGNB_ADDITION_REQUEST_ACK){
					processAckMessage((uint8_t*)in_buf);
				}
				memset(in_buf, 0, BUFFER_LENGTH);
			}while(retcode>0);

			_bRunThread = false;
		}
	}

	CloseSocket();
	WSACleanup();
}

void masterNode::processAckMessage(uint8_t *in_buf){
	SgNBAddRequestAckMsg * msgPtr = (SgNBAddRequestAckMsg*)in_buf;
	addMsg.MeNB_UE_X2AP_ID = msgPtr->MeNB_UE_X2AP_ID;
	cout<<"SgNB Addition Request Acknowledge Msg with MeNB_UE_X2AP_ID: "<<addMsg.MeNB_UE_X2AP_ID<<endl;

	recCompMsg.MeNB_UE_X2AP_ID = addMsg.MeNB_UE_X2AP_ID;

	recCompMsg.MessageType = MSG_SGNB_RECONFIGURATION_COMPLETE;
	send(clientNode, (char *) &recCompMsg, sizeof(recCompMsg), 0);
}

void masterNode::addNode(){

	addMsg.MessageType = MSG_SGNB_ADDITION_REQUEST;
	addMsg.MeNB_UE_X2AP_ID++;

	send(clientNode, (char *) &addMsg, sizeof(addMsg), 0);
}
void masterNode::CloseSocket() {
	int retcode = closesocket(serverId);
	if (retcode < 0)
	{
		exit(-1);
	}
	retcode = closesocket(clientNode);
	if (retcode < 0)
	{
		exit(-1);
	}
	// Clean-up winsock
}
