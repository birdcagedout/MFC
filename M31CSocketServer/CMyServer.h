#pragma once

#include "CUserSocket.h"

// CMyServer 명령 대상

class CMyServer : public CSocket
{
protected:
	CUserSocket m_userSock;

public:
	CMyServer();
	virtual ~CMyServer();
	virtual void OnAccept(int nErrorCode);
};


