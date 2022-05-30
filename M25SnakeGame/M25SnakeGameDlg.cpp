﻿
// M25SnakeGameDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M25SnakeGame.h"
#include "M25SnakeGameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM25SnakeGameDlg 대화 상자



CM25SnakeGameDlg::CM25SnakeGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M25SNAKEGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM25SnakeGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM25SnakeGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CM25SnakeGameDlg 메시지 처리기

BOOL CM25SnakeGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	
	// 화면 배경
	m_img.Create(SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1, 32);
	m_dc.Attach(m_img.GetDC());


	// 먹이 맵에 채우기
	srand((unsigned int)time(NULL));
	for (int i = 0; i < BAIT_COUNT; i++) {
		int x = rand() % CELL_COUNT_X;
		int y = rand() % CELL_COUNT_Y;

		if (m_map[y][x] == BLACK) {
			m_map[y][x] = RED;
		}
		else {
			i--;
		}
	}

	// 뱀의 위치 정보
	m_map[m_pos.y][m_pos.x] = GREEN;

	// 뱀길이 정보
	m_snakeMap[m_pos.y][m_pos.x] = -1;			// 최초 실행임을 표시
	
	// 맵 전체 그리기
	DrawMap();
	
	// 타이머
	SetTimer(1, 50, NULL);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


// 맵 전체 그리기
void CM25SnakeGameDlg::DrawMap()
{
	// 펜과 브러시
	m_dc.SelectStockObject(DC_PEN);
	m_dc.SelectStockObject(DC_BRUSH);
	m_dc.SetDCPenColor(RGB(48, 48, 12));	// 살짝 노란색 선
	m_dc.SetDCBrushColor(RGB(0, 0, 0));		// 검은색 배경


	// 전체 맵 (배경, 먹이, 뱀) 그리기
	for (int y = 0; y < CELL_COUNT_Y; y++) {
		for (int x = 0; x < CELL_COUNT_X; x++) {

			// 뱀이 지나간 셀: 1빼고 그리기
			if (m_snakeMap[y][x] >= 1) {
				m_snakeMap[y][x]--;

				// 1뺀 값이 0이면 배경(BLACK)
				if (m_snakeMap[y][x] == 0) {
					m_map[y][x] = BLACK;
				}
				// 1뺀 값이 1이상이면 뱀(GREEN)
				else {
					m_map[y][x] = GREEN;
				}
			}
			// 최초 실행시 ==> 별도 처리
			else if (m_snakeMap[y][x] == -1) {
				m_snakeMap[y][x] = m_eaten + 1;		// 값이 2여야 길이=1이 된다.
				m_map[y][x] = GREEN;
			}

			m_dc.SetDCBrushColor(m_map[y][x]);
			m_dc.Rectangle(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE + 1, (y + 1) * CELL_SIZE + 1);		// 겹쳐지도록 끝좌표 +1
		}
	}
}


// 게임 종료
void CM25SnakeGameDlg::EndGame(int a_code)
{
	if (a_code == LOSE) {
		KillTimer(1);
		MessageBox(L"미션에 실패하였습니다.", L"Game Over", MB_OK | MB_ICONSTOP);
	}
	else {
		KillTimer(1);
		MessageBox(L"미션에 성공하였습니다.", L"Game Over", MB_OK | MB_ICONSTOP);
	}
	PostQuitMessage(0);
}




// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM25SnakeGameDlg::OnPaint()
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
		m_img.Draw(dc, 0, 0);

		//CDialogEx::OnPaint();
	}
}



void CM25SnakeGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {

		// 원래 있던 위치 지우기
		//m_map[m_pos.y][m_pos.x] = BLACK;


		// 새로운 위치
		if (m_direction == LEFT) {
			m_pos.x--;
		}
		else if (m_direction == UP) {
			m_pos.y--;
		}
		else if (m_direction == RIGHT) {
			m_pos.x++;
		}
		else if (m_direction == DOWN) {
			m_pos.y++;
		}

		// 새로운 위치가 유효할 때만 위치 update + 그리기
		if (m_pos.x >= 0 && m_pos.x < CELL_COUNT_X && m_pos.y >= 0 && m_pos.y < CELL_COUNT_Y) {

			// 새로운 위치가 먹이(RED)
			if (m_map[m_pos.y][m_pos.x] == RED) {
				m_eaten++;
			}
			// 새로운 위치가 먹이(RED)도 아니고 배경(BLACK)도 아닌 경우 ==> 자기 몸
			else if (m_map[m_pos.y][m_pos.x] != BLACK) {
				EndGame(LOSE);
				return;
			}

			// 뱀 위치 update
			m_map[m_pos.y][m_pos.x] = GREEN;

			// 뱀 길이 update
			m_snakeMap[m_pos.y][m_pos.x] = m_eaten + 1;		// 값이 2여야 길이=1이 된다.

			// 맵 전체 그리기
			DrawMap();
			Invalidate(FALSE);
		}
		// 새로운 위치가 유효하지 않으면 Game Over
		else {
			EndGame(LOSE);
		}
		
	}

	CDialogEx::OnTimer(nIDEvent);
}


// 종결시 타이머 제거 + dc분리 + dc해제
void CM25SnakeGameDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);

	m_dc.Detach();
	m_img.ReleaseDC();
}


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM25SnakeGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 방향키 눌렸을 때 처리
void CM25SnakeGameDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar >= VK_LEFT && nChar <= VK_DOWN) {
		if (nChar == VK_LEFT) {
			// 뒤돌면 무효화
			if (m_direction == RIGHT) {
				return;
			}
			m_direction = LEFT;
		}
		else if (nChar == VK_UP) {
			// 뒤돌면 무효화
			if (m_direction == DOWN) {
				return;
			}
			m_direction = UP;
		}
		else if (nChar == VK_RIGHT) {
			// 뒤돌면 무효화
			if (m_direction == LEFT) {
				return;
			}
			m_direction = RIGHT;
		}
		else if (nChar == VK_DOWN) {
			// 뒤돌면 무효화
			if (m_direction == UP) {
				return;
			}
			m_direction = DOWN;
		}
		DrawMap();
		Invalidate(FALSE);
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


// 대화상자로 오는 방향키는 확인/취소 버튼에서 받아서 써버리기 때문에 
// Translate되기 전에 낚아채서 처리해야 한다.
BOOL CM25SnakeGameDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	}
	

	return CDialogEx::PreTranslateMessage(pMsg);			// 처리 후 ==> 반드시 이 부분을 살려둬야 TranslateMessage가 처리된다.
}