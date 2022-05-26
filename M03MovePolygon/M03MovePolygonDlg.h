
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



// ��ü�� Z-order�� ���� ������ �� �ִ� class ����
class CMyZOrder {
protected:
	int m_count;						// object�� �� ����
	int m_order[3];						// Z-order �������(index=0�̸� �ֻ��� ��ü)

public:
	CMyZOrder()
	{
		m_count = OBJ_COUNT;					// object�� �Ѱ���
		m_order[0] = OBJ_RECTANGLE;
		m_order[1] = OBJ_CIRCLE;
		m_order[2] = OBJ_STAR;
		m_order[3] = OBJ_SQUARE;
	}
	~CMyZOrder()
	{
		//delete[] m_order;
	}


	// �ֻ����� Ư�� ��ü �ø���
	void SetOnTop(int a_objID)
	{
		// Ư�� ��ü�� index ã��(index=k)
		for (int index = 0; index < m_count; index++) {
			if (m_order[index] == a_objID) {
				int temp = m_order[index];

				// index 0 ~ k-1���� ��ĭ�� �ڷ� �̷��.
				for (int j = index; j > 0; j--) {
					m_order[j] = m_order[j - 1];			// j �ڸ��� index�� ������ٰ� �� ã�Ƽ� ����� �����(2022.4.22.)
				}

				// ù��°(=�ֻ���)�� Ư�� ��ü
				m_order[0] = temp;

				// Ż��
				return;
			}
		}
	}

	// Ư�� index�� ��ü ������
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

	int m_objCount;			// �� ��ü ����
	
	CRect m_square;			// ���簢��
	CRect m_rect;			// ���簢��

	CRgn m_starRegion;		// ����� ���ο���
	CRgn m_circleRegion;	// ����� ���ο���
	
	CBrush m_starBrush;		// ����� �׵θ��� �귯��
	CBrush m_circleBrush;	// ����� �׵θ��� �귯��

	int m_isClicked;
	CPoint m_prevPoint;
	CMyZOrder *m_pZ;		// Z-order ���� ��ü

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	void PaintObject(CPaintDC *a_hDC, int a_objID);			// ��ü ������� �׸���
	int GetClickedObjectIndex(CPoint a_point);				// (�ֻ��� ��ü���� �������) Ŭ���� ��ü�� index ��ȯ(������ OBJ_NONE=-1 ��ȯ)
};
