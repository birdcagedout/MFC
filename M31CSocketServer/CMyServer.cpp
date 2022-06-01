// CMyServer.cpp: 구현 파일
//

#include "pch.h"
#include "M31CSocketServer.h"
#include "CMyServer.h"


// CMyServer

CMyServer::CMyServer()
{
}

CMyServer::~CMyServer()
{
}


// CMyServer 멤버 함수


void CMyServer::OnAccept(int nErrorCode)
{
	Accept(m_userSock);

	CSocket::OnAccept(nErrorCode);
}
