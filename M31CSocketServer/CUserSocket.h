#pragma once

// CUserSocket 명령 대상

class CUserSocket : public CSocket
{
protected:
	int m_receivedData;
	int m_ack;

public:
	CUserSocket();
	virtual ~CUserSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


