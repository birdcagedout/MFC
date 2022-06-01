// CUserSocket.cpp: 구현 파일
//

#include "pch.h"
#include "M31CSocketServer.h"
#include "CUserSocket.h"


// CUserSocket

CUserSocket::CUserSocket()
{
}

CUserSocket::~CUserSocket()
{
}


// CUserSocket 멤버 함수


void CUserSocket::OnReceive(int nErrorCode)
{
	Receive(&m_receivedData, sizeof(int));
	AfxGetMainWnd()->SetDlgItemInt(IDC_EDIT_VALUE, m_receivedData);		// 최상위 윈도 에디트 컨트롤에 다이렉트로 값 전송

	m_ack = 1;
	Send(&m_ack, sizeof(int));


	CSocket::OnReceive(nErrorCode);
}


void CUserSocket::OnClose(int nErrorCode)
{
	//ShutDown(2)						// 파일 전송중 상태 무시함
	Close();							// 클라이언트가 접속을 해제하는 경우 서버에서도 접속을 끊어준다.

	CSocket::OnClose(nErrorCode);
}
