
// M23ObjectRegionPairingCardsDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M23ObjectRegionPairingCards.h"
#include "M23ObjectRegionPairingCardsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM23ObjectRegionPairingCardsDlg 대화 상자



CM23ObjectRegionPairingCardsDlg::CM23ObjectRegionPairingCardsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M23OBJECTREGIONPAIRINGCARDS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM23ObjectRegionPairingCardsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_TIME, m_progressTime);
}

BEGIN_MESSAGE_MAP(CM23ObjectRegionPairingCardsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_HINT, &CM23ObjectRegionPairingCardsDlg::OnBnClickedButtonHint)
END_MESSAGE_MAP()


// CM23ObjectRegionPairingCardsDlg 메시지 처리기

BOOL CM23ObjectRegionPairingCardsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	
	// 카드 보여주기 = true
	m_bShow = true;

	// 첫번째, 두번째 선택 = false
	m_bPicked1 = false;
	m_bPicked2 = false;

	// 첫번째 선택한 카드의 index 초기화 (어느 카드와도 같을 수 없다)
	m_cardIndex1 = -1;

	// 카드쌍 남은 수
	m_pairLeft = 18;

	// 힌트 남은 수
	m_hintLeft = 3;


	// 카드 이미지 파일에서 불러오기 : 000 ~ 018 (이미지 19개)
	CString strPath;
	for (int i = 0; i < 19; i++) {
		strPath.Format(L".\\cards\\%03d.bmp", i);
		m_img[i].Load(strPath);
	}
	m_imgW = m_img[0].GetWidth();
	m_imgH = m_img[0].GetHeight();


	// 카드맵에 값 순서대로 채워넣기 : 0 ~ 36
	for (int j = 0; j < 18; j++) {
		m_cardMap[j] = j + 1;
		m_cardMap[j + 18] = j + 1;
	}


	// 카드 shuffle 섞기
	srand((unsigned int)time(NULL));
	for (int k = 0; k < 200; k++) {
		int pick1 = rand() % 36;
		int pick2 = rand() % 36;
		
		if (pick1 == pick2) {
			continue;
		}
		else {
			int temp = m_cardMap[pick1];
			m_cardMap[pick1] = m_cardMap[pick2];
			m_cardMap[pick2] = temp;
		}
	}

	// 전체 창 크기 조절
	CRect r(0, 0, m_imgW*6, m_imgH*8);
	AdjustWindowRect(r, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(NULL, 0, 0, r.Width(), r.Height(), SWP_NOMOVE);

	// 버튼 위치 조절
	CRect br;
	GetDlgItem(IDC_BUTTON_HINT)->GetWindowRect(br);
	ScreenToClient(br);
	int margin_xb = m_imgW / 2;
	int margin_yb = m_imgH * 6 + 10;
	int width_b = m_imgW * 5;
	int height_b = int(m_imgH * 0.5);
	GetDlgItem(IDC_BUTTON_HINT)->MoveWindow(margin_xb, margin_yb, width_b, height_b);

	// 프로그레스바 위치 조절
	CRect pr;
	GetDlgItem(IDC_PROGRESS_TIME)->GetWindowRect(pr);
	ScreenToClient(pr);
	int margin_xp = m_imgW / 2;
	int margin_yp = m_imgH * 7;
	int width_p = m_imgW * 5;
	int height_p = int(m_imgH * 0.5);
	GetDlgItem(IDC_PROGRESS_TIME)->MoveWindow(margin_xp, margin_yp, width_p, height_p);


	// 프로그레스바 초기화 ==> 타이머는 최초 카드가 보여지는 3초 후부터 진행하는 것이 바람직하므로
	// 타이머1번을 힌트와 분리하고, 분리된 1번에서 프로그레스바 타이머 시작해야 함. ==> But 귀찮아서 그만둠
	m_progressTime.SetRange(0, 60);		// 0부터 60까지 (1분 기준)
	m_progressTime.SetPos(60);			// 가득찬 상태부터 시작
	SetTimer(10, 1000, NULL);			// 10번 타이머는 1초마다 발생


	// 최초 타이머
	SetTimer(1, 3000, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM23ObjectRegionPairingCardsDlg::OnPaint()
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
		// 카드 이미지 36장 출력
		for (int i = 0; i < 36; i++) {

			// 카드 보여주기(=앞면) / 안보여주기(=뒷면)
			int cardIndex = 0;
			if (m_bShow == true) {
				cardIndex = m_cardMap[i];
			}

			// 제거된 카드 ==> 그리지 않음
			if (m_cardMap[i] == 0) {
				continue;
			}
			// 나머지 카드 ==> 그리기
			else {
				m_img[cardIndex].Draw(dc, (i % 6) * m_imgW, (i / 6) * m_imgH, m_imgW, m_imgH);

				// 디버그용 : 카드번호 숫자로 출력
				CString strNum;
				strNum.Format(L"%02d", m_cardMap[i]);
				dc.TextOut(5 + (i % 6) * m_imgW, 5 + (i / 6) * m_imgH, strNum);
			}
			
		}

		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM23ObjectRegionPairingCardsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM23ObjectRegionPairingCardsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// 최초 카드 보여주기 + 힌트보기 타이머 (3초)
	if (nIDEvent == 1) {
		m_bShow = false;
		KillTimer(nIDEvent);
		Invalidate();
	}
	// 첫번째 카드 선택 후 두번째 카드 기다리기 타이머 (3초)
	// ==> timeout되었다면 두번째 선택을 안 한 것이므로 처음상태로 초기화
	else if (nIDEvent == 2) {
		m_bPicked1 = false;		// 이때 m_bPicked는 true상태 ==> false로
		m_cardIndex1 = -1;
		KillTimer(nIDEvent);
		Invalidate();
	}
	// 프로그레스바
	else if (nIDEvent == 10) {
		int pos = m_progressTime.GetPos() - 1;
		if (pos == 0) {
			// 패배(게임종료)
			KillTimer(nIDEvent);
			int response = MessageBox(L"패배하였습니다.\n다시하시겠습니까?", L"게임 종료", MB_OKCANCEL | MB_ICONQUESTION);
			if (response == IDOK) {
				InitGame();
				Invalidate();
			}
			else {
				PostQuitMessage(0);
			}
		}
		else {
			m_progressTime.SetPos(pos);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CM23ObjectRegionPairingCardsDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 최초 실행시 앞면인 상태에서의 클릭은 무효처리
	if (m_bShow == true) {
		return;
	}

	// 유효영역 처리
	if (point.x < m_imgW * 6 && point.y < m_imgH * 6) {

		// cardMap 인덱스 찾기
		int x = point.x / m_imgW;
		int y = point.y / m_imgH;
		int cardIndexNow = y * 6 + x;		// 0 ~ 35


		// 이미 제거된 카드 위치에 클릭된 경우 ==> 클릭 무효화
		if (m_cardMap[cardIndexNow] == 0) {
			return;
		}


		// 두번째 선택까지 끝난 상태에서 다시 클릭된 경우 ==> 클릭 무효화
		if (m_bPicked1 == true && m_bPicked2 == true) {
			return;
		}

		// 현재 클릭이 두번째 선택된 카드: 일단 첫번째 카드 flag reset, 타이머2 제거, 두번째 카드 보여줌
		// 1) match 성공 ==> m_cardMap에서 제거(=0), Invalidate
		// 2) match 실패 ==> m_cardIndex1 초기화, Invalidate
		else if (m_bPicked1 == true && m_bPicked2 == false) {

			// 두번째 카드 flag set ==> 더이상 클릭을 무력화
			m_bPicked2 = true;

			// 타이머2 제거
			KillTimer(2);

			// 같은 카드 두번 클릭 (첫번째 카드 = 두번째 카드) ==> 무효
			if (m_cardIndex1 == cardIndexNow) {

				AfxMessageBox(L"동일한 카드를 두번 선택할 수 없습니다.\n이전 상태로 초기화합니다.", MB_OK);
				m_cardIndex1 = -1;
				Invalidate();
				m_bPicked1 = false;
				m_bPicked2 = false;

				CDialogEx::OnLButtonDown(nFlags, point);
				return;
			}

			// 두번째 카드 보여줌
			CClientDC dc(this);
			m_img[m_cardMap[cardIndexNow]].Draw(dc, m_imgW * x, m_imgH * y, m_imgW, m_imgH);
			Sleep(500);


			// match 성공
			if (m_cardMap[m_cardIndex1] == m_cardMap[cardIndexNow]) {
				m_cardMap[m_cardIndex1] = 0;		// 첫번째 선택된 카드 = 제거
				m_cardMap[cardIndexNow] = 0;		// 두번째 선택된 카드 = 제거
				Invalidate();

				m_cardIndex1 = -1;
				m_bPicked2 = false;
				m_bPicked1 = false;

				// 모든 카드쌍이 제거된 경우 ==> 승리
				m_pairLeft--;
				if (m_pairLeft == 0) {
					int response = MessageBox(L"승리하였습니다.\n다시하시겠습니까?", L"게임 종료", MB_OKCANCEL | MB_ICONQUESTION);
					if (response == IDOK) {
						InitGame();
						Invalidate();
					}
					else {
						PostQuitMessage(0);
					}
					
				}
			}
			// match 실패
			else {
				m_cardIndex1 = -1;
				Invalidate();

				m_bPicked2 = false;
				m_bPicked1 = false;
			}
		}

		// 위에서 m_bPicked == true인 경우는 모두 처리했으므로
		// 첫번째 선택된 카드라면 ==> 첫번째 카드 flag 올리고, 앞면 보여주고, 타이머2 5초
		else if (m_bPicked1 == false) {

			// 첫번째 카드 flag set
			m_bPicked1 = true;

			// 첫번째 카드의 인덱스
			m_cardIndex1 = cardIndexNow;

			// 선택된 카드 ==> 앞면 보여주기
			CClientDC dc(this);
			m_img[m_cardMap[cardIndexNow]].Draw(dc, m_imgW * x, m_imgH * y, m_imgW, m_imgH);

			// 타이머2
			SetTimer(2, 3000, NULL);
		}
		
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CM23ObjectRegionPairingCardsDlg::OnBnClickedButtonHint()
{
	if (m_hintLeft == 0) {
		return;
	}
	else {
		m_hintLeft--;

		// 모든 카드 앞면 보여주기
		m_bShow = true;
		Invalidate();
		SetTimer(1, 3000, NULL);

		// 버튼 텍스트 update
		CString strButton;
		strButton.Format(L"힌트보기 (remaining: %d)", m_hintLeft);
		SetDlgItemText(IDC_BUTTON_HINT, strButton);
	}
}


void CM23ObjectRegionPairingCardsDlg::InitGame()
{
	// 카드 보여주기 = true
	m_bShow = true;

	// 첫번째, 두번째 선택 = false
	m_bPicked1 = false;
	m_bPicked2 = false;

	// 첫번째 선택한 카드의 index 초기화 (어느 카드와도 같을 수 없다)
	m_cardIndex1 = -1;

	// 카드쌍 남은 수
	m_pairLeft = 18;

	// 힌트 남은 수
	m_hintLeft = 3;


	// 카드맵에 값 순서대로 채워넣기 : 0 ~ 36
	for (int j = 0; j < 18; j++) {
		m_cardMap[j] = j + 1;
		m_cardMap[j + 18] = j + 1;
	}


	// 카드 shuffle 섞기
	/*srand((unsigned int)time(NULL));*/
	for (int k = 0; k < 200; k++) {
		int pick1 = rand() % 36;
		int pick2 = rand() % 36;

		if (pick1 == pick2) {
			continue;
		}
		else {
			int temp = m_cardMap[pick1];
			m_cardMap[pick1] = m_cardMap[pick2];
			m_cardMap[pick2] = temp;
		}
	}

	// 프로그레스바 초기화
	m_progressTime.SetRange(0, 60);		// 0부터 60까지 (1분 기준)
	m_progressTime.SetPos(60);					// 가득찬 상태부터 시작
	SetTimer(10, 1000, NULL);	// 10번 타이머는 1초마다 발생


	// 최초 타이머
	SetTimer(1, 3000, NULL);
}