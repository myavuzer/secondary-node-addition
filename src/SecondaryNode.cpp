/*
 * SecondaryNode.cpp
 *
 *  Created on: 31 Aðu 2021
 *      Author: mahmut.yavuzer
 */


#include "SecondaryNode.h"

snNode::snNode(uint16_t portNum){
	m_portNumber = portNum;
}

snNode::~snNode(){

}

void ReceiveV(void * pMyId){

}


bool snNode::Init(){

	WSADATA wsa;

	//Initialize socket
	std::cout << "Initializing Winsock..." << std::endl;
	if (WSAStartup(MAKEWORD(1,1),&wsa) != 0)
	{
		std::cout << "Initializing failed. Error Code: " << WSAGetLastError() << std::endl;
		return false;
	}

	std::cout << "Winsock Initialized Successfully" << std::endl;

	//Create a socket
	if((m_socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		std::cout << "Could not create socket. Error Code: " << WSAGetLastError() << std::endl;
		return false;
	}

	std::cout << "Socket created" << std::endl;

	return true;

}
bool snNode::Connect(){
	struct sockaddr_in client;

	client.sin_addr.s_addr = inet_addr(snNode::IP_ADDRESS);
	client.sin_family = AF_INET;
	client.sin_port = htons(m_portNumber);

	//Connect to remote server
	if (connect(m_socket , (struct sockaddr *)&client , sizeof(client)) < 0)
	{
		std::cout << "Connection could not created. Error Code: " << WSAGetLastError() << std::endl;
		return false;
	}

	std::cout << "Connected to the server successfully" << std::endl;
	return true;
}

void snNode::Receive() {
	int recvMsgId = 0;
	std::string recvData;
	int retcode = 0;

	while(true) {
		retcode = recv(m_socket, in_buf, 4096, 0);

		recvMsgId = (in_buf[3] << 24) + (in_buf[2]<<16) + (in_buf[1] <<8) + (in_buf[0]);

		if(recvMsgId == MSG_SGNB_ADDITION_REQUEST){
			processAddReqMessage((uint8_t*)in_buf);
		}else if(recvMsgId == MSG_SGNB_RECONFIGURATION_COMPLETE){
			processRecCompMessage((uint8_t*)in_buf);
		}
		if(retcode < 1){
			Sleep(1000);
			Init();
			Connect();
		}
		Sleep(5);
	}
}


void snNode::processAddReqMessage(uint8_t* in_buf){
	SgNBAddRequestMsg* addMsg = (SgNBAddRequestMsg*)in_buf;

	cout<<"SgNB Addition Request with MeNB_UE_X2AP_ID: "<< addMsg->MeNB_UE_X2AP_ID<<endl;

	snAddAck.MessageType = MSG_SGNB_ADDITION_REQUEST_ACK;
	snAddAck.MeNB_UE_X2AP_ID = addMsg->MeNB_UE_X2AP_ID;

	send(m_socket, (char*) &snAddAck, sizeof(snAddAck), 0);
}

void snNode::processRecCompMessage(uint8_t* in_buf){
	SgNBReconfigurationCompleteMsg* recCompMsg = (SgNBReconfigurationCompleteMsg*)in_buf;

	cout<<"SgNB Reconfiguration Complete msg with MeNB_UE_X2AP_ID: "<< recCompMsg->MeNB_UE_X2AP_ID<<endl;
}


