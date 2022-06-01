#pragma once

// CClientSocket 명령 대상

class CClientSocket : public CSocket
{
protected:
	int m_receivedData;

public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnReceive(int nErrorCode);
};


