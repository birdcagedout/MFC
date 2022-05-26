
// M25SnakeGameDlg.h: 헤더 파일
//

#pragma once

#define SCREEN_WIDTH		1600
#define SCREEN_HEIGHT		1200
#define CELL_SIZE			10
#define CELL_COUNT_X		(SCREEN_WIDTH / CELL_SIZE)
#define CELL_COUNT_Y		(SCREEN_HEIGHT / CELL_SIZE)
#define BAIT_COUNT			300


#define LEFT				0		// VK_LEFT	= 0x25
#define UP					1		// VK_UP	= 0x26
#define RIGHT				2		// VK_RIGHT	= 0x27
#define DOWN				3		// VK_DOWN	= 0x28

#define BLACK				RGB(0, 0, 0)
#define RED					RGB(255, 50, 50)
#define GREEN				RGB(50, 255, 50)

#define WIN					1
#define LOSE				0


// CM25SnakeGameDlg 대화 상자
class CM25SnakeGameDlg : public CDialogEx
{
// 생성입니다.
public:
	CM25SnakeGameDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M25SNAKEGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	
	
	CImage m_img;												// 배경 비트맵 이미지
	CDC m_dc;													// 이미지의 DC (메모리DC)

	COLORREF m_map[CELL_COUNT_Y][CELL_COUNT_X] = { 0, };		// 맵의 셀 정보 (BLACK=배경, RED=먹이, GREEN=뱀)
	int m_snakeMap[CELL_COUNT_Y][CELL_COUNT_X] = { 0, };		// 각 셀이 뱀(GREEN)이 될지 배경(BLACK)이 될지는 먹이를 먹은 개수에 따라 다름

	POINT m_pos = { CELL_COUNT_X / 2, CELL_COUNT_Y / 2 };		// 뱀의 위치 (초기: 화면 중앙)

	int m_direction = LEFT;										// 뱀의 방향 (기본값 = 왼쪽)
	int m_eaten = 1;											// 먹이 1개 먹은 걸로 시작




	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);


	void DrawMap();												// 맵, 먹이, 뱀 그리는 루틴
	void EndGame(int code=LOSE);								// 게임 끝내기
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
