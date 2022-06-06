#pragma once
#include "CUserSocket.h"
// CServerSocket 명령 대상

class CServerSocket : public CSocket
{
protected:
	//CUserSocket m_userSock;
	CObList m_userSockList;

public:
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);
};


