
// M05SliderCtrlDlg.cpp : implementation file
// �����̴��� ����� ���� ������
// 1. NM_THUMBPOSCHANGING�� ����� ���������ϱ� ��ƴ� ==> ��������
// 2. �����̴� �̵����� �ǽð� ó�� ��ƴ�.
// 3. Ű����� �����̴� �̵���Ű�� ��� �̺�Ʈ �߻� �� ��.
// ==> ���� 2,3���� ó���ϰ� �ʹٸ� ��ũ�ѹ� �޽����� ó���� ��



#include "pch.h"
#include "framework.h"
#include "M05SliderCtrl.h"
#include "M05SliderCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM05SliderCtrlDlg dialog



CM05SliderCtrlDlg::CM05SliderCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M05SLIDERCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM05SliderCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_1, m_mySlider);
	DDX_Control(pDX, IDC_LIST_SHOW, m_listShow);
}

BEGIN_MESSAGE_MAP(CM05SliderCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_1, &CM05SliderCtrlDlg::OnNMReleasedcaptureSlider1)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CM05SliderCtrlDlg message handlers

BOOL CM05SliderCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	// �����̴� ���� �ʱ�ȭ(���� 0~100)
	m_mySlider.SetRange(0, 200);

	m_mySlider.SetTicFreq(10);




	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CM05SliderCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CM05SliderCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM05SliderCtrlDlg::OnNMReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	/*int pos = m_mySlider.GetPos();

	CString str;
	str.Format(L"%d", pos);
	int index = m_listShow.InsertString(-1, str);
	m_listShow.SetCurSel(index);*/
	

	*pResult = 0;
}


void CM05SliderCtrlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// nSBCode : ���� �޽����� ���� �������� ���� ����
	// nPos : nSBCode�� ������ ���� ���� �ǹ̰� �޶����ų�, �ǹ̰� ���� ���� �ִ�.(������ ���� ����)
	// pScrollBar : ���� ��ũ�ѹ��� �ּ�(������). ���� ==> ���� �⺻ ��ũ���� ��� NULL�� ����

	if (pScrollBar != NULL && pScrollBar->GetDlgCtrlID() == IDC_SLIDER_1) {

		// ���콺�� �����̴� ���� ***�巡��***�ϸ鼭 ��� �� �˻�
		// ==> ���� : 1. ���콺�� �����̴� �߰��� Ŭ��, Ŭ���ϸ� �� �޽��� �߻����� ����. 2. Ű����� �������� �޽��� �߻� �� ��
		if (nSBCode == SB_THUMBTRACK) {
			// �� ��쿡�� nPos�� ��ȿ
			CString str;
			str.Format(L"%d", nPos);
			int index = m_listShow.InsertString(-1, str);
			m_listShow.SetCurSel(index);
		}
		// �� ��ġ�� ��ũ���� ������ �� �߻��ϴ� �޽���
		// 1) ���콺�� �����̴� �߰��� 1ȸ�� Ŭ������ ���� �߻� 
		// 2) Ű����� �������� �޽��� �߻� (��, Ű�� ������ ���� ���������� ��� �߻��ϴ� ���� �ƴ϶� ���� �� 1���� �߻�)
		// ==> ���� : �̶��� nPos���� ��ȿ���� ���� (���� �����̴� ���������  GetPos() �ʿ�)
		else if (nSBCode == SB_ENDSCROLL) {
			// nPos ��� �����̴� ������ GetPos() ���
			int pos = m_mySlider.GetPos();
			CString str;
			str.Format(L"%d", pos);
			int index = m_listShow.InsertString(-1, str);
			m_listShow.SetCurSel(index);
		}
	}


	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
