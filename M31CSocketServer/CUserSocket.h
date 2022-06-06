#pragma once



// CUserSocket 명령 대상
class CUserSocket : public CSocket
{
protected:
	//int m_receivedData = 0;
	int m_ack = 1;

	CObList* m_pUserSockList;

public:
	CUserSocket();
	CUserSocket(CObList* pList);
	virtual ~CUserSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


