/*
 * common.h
 *
 *  Created on: 31 Aðu 2021
 *      Author: mahmut.yavuzer
 */

#ifndef COMMON_H_
#define COMMON_H_


#include <process.h>
#include <thread>
#include <iostream>

using namespace std;

#define MSG_SGNB_ADDITION_REQUEST 1
#define MSG_SGNB_ADDITION_REQUEST_ACK 2
#define MSG_SGNB_RECONFIGURATION_COMPLETE 3

typedef struct{
	int FullERABLevelQoSParameters;
	int MaximumMCGadmittableERABLevelQoSParameter; //C-ifCGandSCGpresent_GBR
	int DLForwarding;
	int MeNBDLGTPTEIDatMCG;//	C-ifMCGpresent
	int S1ULGTPTunnelEndpoint;
	int RLCMode;
}PDCPpresentinSN;

typedef struct{
	int RequestedSCGERABLevelQoSParameters;
	int MeNBULGTPTEIDatPDCP;
	int SecondaryMeNBULGTPTEIDatPDCP;
	int RLCMode;
	int ULconfiguration;//-ifMCGandSCGpresent
	int ULPDCPSNLength;
	int DLPDCPSNLength;
	int Duplicationactivation;
}PDCPnotpresentinSN;

typedef struct{
	int E_RAB_ID;
	int DRB_ID;
	int EN_DC_Resource_Configuration;
	int CHOICE_Resource_Configuration;
	PDCPpresentinSN pdcpPresent;
	PDCPnotpresentinSN pdcpNotPresent;
}E_RABsToBeAddedList;

typedef struct {
	int MessageType;
	int MeNB_UE_X2AP_ID;
	int NR_UE_SecurityCapabilities;
	int SgNBSecurityKey;
	int SgNB_UE_AggregateMaximumBitRate;
	int Selected_PLMN;
	int HandoverRestrictionList;
	E_RABsToBeAddedList eRABs;

	int MeNBtoSgNBContainer;
	int SgNBUEX2APID;
	int ExpectedUEBehaviour;
	int MeNBUEX2APIDExtension;
	int RequestedsplitSRBs;
	int MeNBResourceCoordinationInformation;
	int SGNBAdditionTriggerIndication;
	int SubscriberProfileIDforRAT_Frequencypriority;
	int MeNBCellID;
}SgNBAddRequestMsg;


///////////////////////////////////////////

typedef struct{
	int S1DLGTPTEIDattheSgNB;
	int SgNBULGTPTEIDatPDCP;//	C-ifMCGpresent
	int RLCMode;//	C-ifMCGpresent
	int DLForwardingGTPTunnelEndpoint;
	int ULForwardingGTPTunnelEndpoint;
	int RequestedMCGERABLevelQoSParameters;//	C-ifMCGandSCGpresent_GBRpresent
	int ULconfiguration;//	C-ifMCGandSCGpresent
	int ULPDCPSNLength;
	int DLPDCPSNLength;
}PDCPpresentinSN_Ack;

typedef struct{
	int SgNBDLGTPTEIDatSCG;
	int SecondarySgNBDLGTPTEIDatSCG;
	int LCID;
}PDCPnotpresentinSN_Ack;

typedef struct{
	int E_RAB_ID;
	int EN_DC_Resource_Configuration;
	int CHOICE_Resource_Configuration;
	PDCPpresentinSN_Ack pdcpPresent;
	PDCPnotpresentinSN_Ack pdcpNotPresent;
}ERABsAdmittedToBeAddedList;

typedef struct {
	int MessageType;
	int MeNB_UE_X2AP_ID;
	int SgNB_UE_X2AP_ID;
	int NR_UE_SecurityCapabilities;
	int SgNBSecurityKey;
	int SgNB_UE_AggregateMaximumBitRate;
	int Selected_PLMN;
	int HandoverRestrictionList;
	ERABsAdmittedToBeAddedList eRABsAdmitted;


	int ERABsNotAdmittedList;
	int SgNBtoMeNBContainerCGConfig;
	int CriticalityDiagnostics;
	int MeNBUEX2APIDExtension;
	int AdmittedsplitSRBs;
	int SgNBResourceCoordinationInformation;
	int RRCconfigindication;
}SgNBAddRequestAckMsg;

//////////////////////
typedef struct{
	int MeNBtoSgNBContainer;
}Configurationsuccessfullyapplied;

typedef struct{
	int Cause;
}Configurationrejected;

typedef struct{
	Configurationsuccessfullyapplied applied;
	Configurationrejected rejected;
}CHOICEResponseType;

typedef struct {
	int MessageType;
	int MeNB_UE_X2AP_ID;
	int SgNB_UE_X2AP_ID;
	int ResponseInformation;
	CHOICEResponseType choice;

	int MeNBUEX2APIDExtension;

}SgNBReconfigurationCompleteMsg;

//extern int     ThreadNr;//for master and secondary nodes




#endif /* COMMON_H_ */
