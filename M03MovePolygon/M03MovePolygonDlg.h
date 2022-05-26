
// M03MovePolygonDlg.h : header file
//

#pragma once


#define		OBJ_COUNT		4

#define		OBJ_NONE_INDEX	-1
#define		OBJ_NONE		0
#define		OBJ_SQUARE		1
#define		OBJ_STAR		2
#define		OBJ_CIRCLE		3
#define		OBJ_RECTANGLE	4



// 개체의 Z-order를 따로 관리할 수 있는 class 선언
class CMyZOrder {
protected:
	int m_count;						// object의 총 개수
	int m_order[3];						// Z-order 순서대로(index=0이면 최상위 개체)

public:
	CMyZOrder()
	{
		m_count = OBJ_COUNT;					// object의 총개수
		m_order[0] = OBJ_RECTANGLE;
		m_order[1] = OBJ_CIRCLE;
		m_order[2] = OBJ_STAR;
		m_order[3] = OBJ_SQUARE;
	}
	~CMyZOrder()
	{
		//delete[] m_order;
	}


	// 최상위에 특정 개체 올리기
	void SetOnTop(int a_objID)
	{
		// 특정 개체의 index 찾기(index=k)
		for (int index = 0; index < m_count; index++) {
			if (m_order[index] == a_objID) {
				int temp = m_order[index];

				// index 0 ~ k-1까지 한칸씩 뒤로 미룬다.
				for (int j = index; j > 0; j--) {
					m_order[j] = m_order[j - 1];			// j 자리에 index를 적어놨다가 못 찾아서 디버깅 고생함(2022.4.22.)
				}

				// 첫번째(=최상위)에 특정 개체
				m_order[0] = temp;

				// 탈출
				return;
			}
		}
	}

	// 특정 index로 개체 얻어오기
	int GetItem(int a_index)
	{
		if (a_index >= m_count) {
			return -1;
		}
		else {
			return m_order[a_index];
		}
	}
};



// CM03MovePolygonDlg dialog
class CM03MovePolygonDlg : public CDialogEx
{
// Construction
public:
	CM03MovePolygonDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M03MOVEPOLYGON_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	int m_objCount;			// 총 개체 개수
	
	CRect m_square;			// 정사각형
	CRect m_rect;			// 직사각형

	CRgn m_starRegion;		// 별모양 내부영역
	CRgn m_circleRegion;	// 원모양 내부영역
	
	CBrush m_starBrush;		// 별모양 테두리선 브러시
	CBrush m_circleBrush;	// 원모양 테두리선 브러시

	int m_isClicked;
	CPoint m_prevPoint;
	CMyZOrder *m_pZ;		// Z-order 관리 객체

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	void PaintObject(CPaintDC *a_hDC, int a_objID);			// 개체 순서대로 그리기
	int GetClickedObjectIndex(CPoint a_point);				// (최상위 개체부터 순서대로) 클릭된 개체의 index 반환(없으면 OBJ_NONE=-1 반환)
};
