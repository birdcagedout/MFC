// CUserSocket.cpp: 구현 파일
//

#include "pch.h"
#include "M31CSocketServer.h"
#include "CUserSocket.h"
#include "M31CSocketServerDlg.h"

// CUserSocket

CUserSocket::CUserSocket()
{
}

CUserSocket::CUserSocket(CObList* pList)
{
	m_pUserSockList = pList;
}

CUserSocket::~CUserSocket()
{
}


// CUserSocket 멤버 함수


void CUserSocket::OnReceive(int nErrorCode)
{
	// 데이터 수신 처리
	wchar_t receivedData[100] = { 0, };
	Receive(&receivedData, 200);

	((CM31CSocketServerDlg*)AfxGetMainWnd())->AddEventString(receivedData);

	// ack 보내기
	//Send(&m_ack, sizeof(int));

	CSocket::OnReceive(nErrorCode);
}


void CUserSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
	ShutDown(2);
	Close();

	CUserSocket* p = NULL;
	POSITION prevPos, pos = m_pUserSockList->GetHeadPosition();
	while (pos != NULL) {
		prevPos = pos;
		p = (CUserSocket*)m_pUserSockList->GetNext(pos);
		if (p == this) {
			//delete p; 
			m_pUserSockList->RemoveAt(prevPos);
			break;
		}
	}

	if (p != NULL) {
		delete p;
	}
}
