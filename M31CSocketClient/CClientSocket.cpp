// CClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "M31CSocketClient.h"
#include "CClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수


void CClientSocket::OnReceive(int nErrorCode)
{
	Receive(&m_receivedData, sizeof(int));
	AfxGetMainWnd()->SetDlgItemInt(IDC_EDIT_VALUE, m_receivedData);

	CSocket::OnReceive(nErrorCode);
}
