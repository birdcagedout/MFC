
// M24DataStructureDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M24DataStructure.h"
#include "M24DataStructureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM24DataStructureDlg 대화 상자



CM24DataStructureDlg::CM24DataStructureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M24DATASTRUCTURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM24DataStructureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM24DataStructureDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CM24DataStructureDlg 메시지 처리기

BOOL CM24DataStructureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// 난수발생
	srand((unsigned int)time(NULL));

	
	// 2. int 배열 초기화
	memset(m_dataArray, 0, sizeof(m_dataArray));
	m_dataArrayLen = 0;


	// 3. int 배열 개선버전 초기화
	memset(m_dataArray, 0, sizeof(m_dataIndexedArray));
	m_dataIndexedArrayLen = 0;
	m_dataIndexedArrayIndex = 0;

	
	// 1초마다 발생
	SetTimer(1, 1000, NULL);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM24DataStructureDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// 브러시
		CGdiObject* pOldBrush = dc.SelectStockObject(DC_BRUSH);
		dc.SetDCBrushColor(RGB(0, 100, 200));
		dc.SetBkColor(RGB(0, 100, 200));				// 글자 찍힌 배경색


		CString str1, str2, str3;
		POSITION pos = m_dataList.GetHeadPosition();

		int workingIndex = m_dataIndexedArrayIndex;

		for (int i = 0; i < 10; i++) {		// 최대 10번까지만 루프 돈다

			// 1. CPtrList의 값 화면 출력
			if (pos != NULL) {
				CRect r1(160 + i * 65, 10, 220 + i * 65, 40);
				dc.Rectangle(r1);

				str1.Format(L"%02d", *(int*)m_dataList.GetNext(pos));
				dc.DrawText(str1, r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}

			// 2. int 배열의 값 화면 출력
			if (i < m_dataArrayLen) {
				CRect r2(160 + i * 65, 50, 220 + i * 65, 80);
				dc.Rectangle(r2);

				str2.Format(L"%02d", m_dataArray[i]);
				dc.DrawText(str1, r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}


			// 3. int 배열 개선버전 값 화면 출력 : workingIndex : HEAD=m_dataIndexedArrayIndex, TAIL=m_dataIndexedArrayIndex-1
			if (i < m_dataIndexedArrayLen) {
				CRect r2(160 + i * 65, 90, 220 + i * 65, 120);
				dc.Rectangle(r2);

				str2.Format(L"%02d", m_dataArray[workingIndex]);
				dc.DrawText(str1, r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				workingIndex++;
				if (workingIndex > 9) {
					workingIndex = workingIndex % 10;
				}
			}
			
		}

		dc.SelectObject(pOldBrush);

		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM24DataStructureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM24DataStructureDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);

	// m_dataList에 저장된 메모리 해제
	POSITION pos = m_dataList.GetHeadPosition();
	while (pos != NULL) {
		delete (int*)m_dataList.GetNext(pos);
	}
	m_dataList.RemoveAll();
}


void CM24DataStructureDlg::OnTimer(UINT_PTR nIDEvent)
{
	// 값을 생성 
	int element = rand() % 100;		// 0 ~ 99의 더미 데이터


	if (nIDEvent == 1) {
		
		// 1. CPtrList에 넣어줌
		int* p = new int;
		*p = element;
		m_dataList.AddTail(p);			// =======================> AddTail( &p ) 하는 바람에 버그 잡느라 한참 고생함 (2022.5.16.) : p = new로 생성된 int 변수의 주소, &p = p라는 int*형 변수의 주소

		// 11개 이상 ==> head 삭제
		if (m_dataList.GetCount() > 10) {
			delete (int*)m_dataList.GetHead();
			m_dataList.RemoveHead();
		}


		// 2. 배열에 넣어줌
		if (m_dataArrayLen >= 10) {
			for (int i = 0; i <= 8; i++) {
				//*(m_dataArray + i) = *(m_dataArray + i + 1);
				memcpy_s(m_dataArray, sizeof(int) * 9, m_dataArray + 1, sizeof(int) * 9);		// read를 한번에 떠서 write를 한번에 하는지 확인
			}
			m_dataArrayLen = 9;
		}

		m_dataArray[m_dataArrayLen] = element;
		m_dataArrayLen++;


		// 3. 배열 개선버전에 넣어줌
		// ==> 배열 값들을 이동하지 않고 workingIndex로 값이 들어갈 위치를 지정한다.
		//		m_dataIndexedArrayIndex=0: Head=0, ... Tail=9
		//		m_dataIndexedArrayIndex=1: Head=1, ... Tail=0
		//		...
		//		m_dataIndexedArrayIndex=9: Head=9, ... Tail=8
		if (m_dataIndexedArrayLen >= 10) {
			m_dataIndexedArrayLen = 9;
		}

		m_dataIndexedArray[m_dataIndexedArrayIndex] = element;
		m_dataIndexedArrayLen++;
		m_dataIndexedArrayIndex = (m_dataIndexedArrayIndex + 1) % 10;


		// 화면 갱신
		Invalidate(FALSE);
	}

	CDialogEx::OnTimer(nIDEvent);
}
