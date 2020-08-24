// GTF_PASSPORT_COMM_VC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern "C" __declspec(dllimport) int __stdcall OpenPort();
extern "C" __declspec(dllimport) int __stdcall Scan();
extern "C" __declspec(dllimport) int __stdcall ScanCancel();
extern "C" __declspec(dllimport) int __stdcall ReceiveData(int TimeOut);
extern "C" __declspec(dllimport) int __stdcall GetMRZ1(char *refMRZ1);
extern "C" __declspec(dllimport) int __stdcall GetMRZ2(char *refMRZ2);
extern "C" __declspec(dllimport) int __stdcall GetPassportInfo(char *refPassInfo);
extern "C" __declspec(dllimport) int __stdcall Clear();
extern "C" __declspec(dllexport) int __stdcall CheckReceiveData();
extern "C" __declspec(dllimport) int __stdcall ClosePort();
extern "C" __declspec(dllimport) int __stdcall OpenPortByNumber(int PorNum);

int main(int argc, char* argv[])
{
	int nRetry = 0;

//	while(1)
//	{
		//int nRet = OpenPortByNumber(3);
		int nRet = OpenPort();
		if(nRet){
			nRet = Scan();
			if(nRet){
				nRet = ReceiveData(10);	// Time-Out 시간 설정(초)
				printf("\n--> Return Value : %d\n", nRet);

				///////////////////////////////////////////////
				// 정상
				///////////////////////////////////////////////
				if(nRet > 0){
					char PassportInfo[65+1];

					memset(PassportInfo,	0x00,	sizeof(PassportInfo));

					GetPassportInfo(PassportInfo);

					printf("--> PassportInfo : [%d] [%s]\n", strlen(PassportInfo), PassportInfo);
				///////////////////////////////////////////////
				// Time-Out
				///////////////////////////////////////////////
				}else if(nRet == 0){
					printf("--> TimeOut!\n");
				///////////////////////////////////////////////
				// 여권정보 오류
				///////////////////////////////////////////////
				}else if(nRet < 0){
					printf("--> Passport Info error!\n");
				}
			}

			ClosePort();

		}else{
			printf("COM Port open error!\n");
			//break;
		}

//		Sleep(100*3);
//	}

	return 0;
}

