// CServerSocket.cpp: 구현 파일
//

#include "pch.h"
#include "M31CSocketServer.h"
#include "CServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
	CUserSocket* pUserSock;
	POSITION prevPos, pos = m_userSockList.GetHeadPosition();
	while (pos != NULL) {
		prevPos = pos;
		pUserSock = (CUserSocket*)m_userSockList.GetNext(pos);
		delete pUserSock;
		m_userSockList.RemoveHead();
	}
}


// 접속 생성시
void CServerSocket::OnAccept(int nErrorCode)
{
	// userSocket 생성
	CUserSocket* pUserSock = new CUserSocket(&m_userSockList);
	m_userSockList.AddTail(pUserSock);

	Accept(*pUserSock);

	CSocket::OnAccept(nErrorCode);
}
