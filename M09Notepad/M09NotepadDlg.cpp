
// M09NotepadDlg.cpp : implementation file
// ���Ͽ���/���������ϴ� �޸��� ����(�c�氢��)

#include "pch.h"
#include "framework.h"
#include "M09Notepad.h"
#include "M09NotepadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM09NotepadDlg dialog



CM09NotepadDlg::CM09NotepadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M09NOTEPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM09NotepadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM09NotepadDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CM09NotepadDlg::OnBnClickedButtonOpenfile)
	ON_BN_CLICKED(IDC_BUTTON_SAVEFILE, &CM09NotepadDlg::OnBnClickedButtonSavefile)
	ON_BN_CLICKED(IDOK, &CM09NotepadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CM09NotepadDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CM09NotepadDlg message handlers

BOOL CM09NotepadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CM09NotepadDlg::OnPaint()
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
HCURSOR CM09NotepadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ���� ��ȭ���� ����
// CFileDialog : https://docs.microsoft.com/en-us/cpp/mfc/reference/cfiledialog-class?f1url=%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(AFXDLGS%252FCFileDialog)%3Bk(CFileDialog)%3Bk(DevLang-C%252B%252B)%3Bk(TargetOS-Windows)%26rd%3Dtrue&view=msvc-170#cfiledialog

void CM09NotepadDlg::OnBnClickedButtonOpenfile()
{
	wchar_t fileExtFilter[] = L"��� ����(*.*)|*.*|C++�ҽ�����(*.cpp)|*.cpp|C++�������(*.h)|*.h|�ؽ�Ʈ����(*.txt)|*.txt||";	// Ȯ���� ���� = L"�������κ�|����Ȯ��������|......||"
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, fileExtFilter);
	//			fileDlg(TRUE=���Ͽ��� FALSE=��������, �⺻Ȯ����(�����Ҷ� Ȯ���� �������� ������ �ڿ� �ڵ� ����), �⺻�����̸�, �Ӽ�Flags, Ȯ����filter���ڿ�);
	fileDlg.m_ofn.nFilterIndex = 4;		// ���� ��ȭ���ڰ� ������ �� �⺻ filter ����(0=���þ���, 1=fileExtFilter�迭�� 1��°, 2=fileExtFilter�迭�� 2��°, ...)


	// ���� ��ȭ���ڿ��� OK��ư ���� ��츸 ó��
	if (fileDlg.DoModal() == IDOK) {
		SetDlgItemText(IDC_EDIT_PATH, fileDlg.GetPathName());		// ��ü ��� + �����̸�


		// File ó��
		FILE* pFile = NULL;
		CString strContent;

		// File Encoding : 3���� (2�� 3���� Unicode)
		// 1) ANSI(EUC-KR, CP949 ��) : ���� 1byte, �ѱ�/���� 2byte									==> �������� �ۼ��� ����(The system default Windows ANSI code page)
		// 2) �����ڵ� : ��� 2byte, ������ ��� ���� ǥ�� ����, Web���� �ۼ� �Ұ�
		// 3) UTF-8 : ���� 1byte, �ѱ�/���� �� 3byte, ������ ��� ���� ǥ�� ����, Web���� ǥ��		==> ������/���¼ҽ�/�� �⺻��
		// ==> �����ڵ�� UTF-8�� ���� : https://jeongdowon.medium.com/unicode%EC%99%80-utf-8-%EA%B0%84%EB%8B%A8%ED%9E%88-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0-b6aa3f7edf96
		// Big-Endian vs Little-Endian : https://jhnyang.tistory.com/172


		// ���� �̸�=UNICODE�� �� ���Ͽ���(���� ������ 0)
		if (_wfopen_s(&pFile, fileDlg.GetPathName(), L"rt") == 0) {

			// ���� ���� 1�� �޾ƿ� buffer
			char buff[1024];
			int len;
			wchar_t strConverted[1024];

			while (fgets(buff, 1024, pFile) != NULL) {							// fgets(): ���پ� �о����, ���̻� ���� ���� ������ NULL ��ȯ


				// 1. ANSI ���ڵ�: MultiByteToWideChar�Լ��� CP_ACP ��� ==> ���� CPP���� ������ �� �ѱ� �ȱ���(=���� ������ ANSI�� ���ڵ���)
				//len = MultiByteToWideChar(CP_ACP, 0, buff, -1, NULL, 0);		// ANSI�� ��ȯ�� �� ����� �� ���ڿ� ����(����) ���	(���� 6�� �� �ǳ� 2��)
				//MultiByteToWideChar(CP_ACP, 0, buff, -1, strConverted, len);	// ��ȯ �� ���� ���ڿ�(����)�� strConverted�� �ֱ�		(���� 6�� �� �ǳ� 2��)
				//strContent += strConverted;


				// 2. UTF-8 ���ڵ�: MultiByteToWideChar�Լ��� CP_UTF8 ��� ==> ���� CPP���� ������ �� �ѱ� ����(=���� ������ UTF-8�� ���ڵ����� �ʾ���)
				len = MultiByteToWideChar(CP_UTF8, 0, buff, -1, NULL, 0);		// UTF-8�� ��ȯ�� �� ����� �� ���ڿ� ����(����) ���	(���� 6�� �� �ǳ� 2��)
				MultiByteToWideChar(CP_UTF8, 0, buff, -1, strConverted, len);	// ��ȯ �� ���� ���ڿ�(����)�� strConverted�� �ֱ�		(���� 6�� �� �ǳ� 2��)
				strContent += strConverted;



				//strContent += buff;												// buff=ASCII, CString�� +�����ڴ� buff�� ASCII�� �����ڵ�� ��ȯ
			}
			strContent.Replace(L"\n", L"\r\n");									// �ٹٲ� ����
			SetDlgItemText(IDC_EDIT_MAIN, strContent);

			fclose(pFile);
		}
	}
}


// ���� �����ϱ� ��ư
void CM09NotepadDlg::OnBnClickedButtonSavefile()
{
	wchar_t fileExtFilter[] = L"��� ����(*.*)|*.*|C++�ҽ�����(*.cpp)|*.cpp|C++�������(*.h)|*.h|�ؽ�Ʈ����(*.txt)|*.txt||";	// Ȯ���� ���� = L"�������κ�|����Ȯ��������|......||"
	CFileDialog fileDlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT, fileExtFilter);				// OFN_OVERWRITEPROMPT = ����� ���
	//			fileDlg(TRUE=���Ͽ��� FALSE=��������, �⺻Ȯ����(�����Ҷ� Ȯ���� �������� ������ �ڿ� �ڵ� ����), �⺻�����̸�, �Ӽ�Flags, Ȯ����filter���ڿ�);
	//fileDlg.m_ofn.nFilterIndex = 4;		// ���� ��ȭ���ڰ� ������ �� �⺻ filter ����(0=���þ���, 1=fileExtFilter�迭�� 1��°, 2=fileExtFilter�迭�� 2��°, ...)


	// ���� ��ȭ���ڿ��� OK��ư ���� ��츸 ó��
	if (fileDlg.DoModal() == IDOK) {
		SetDlgItemText(IDC_EDIT_PATH, fileDlg.GetPathName());


		// ���� ó��
		FILE* pFile = NULL;
		CString strContent;

		// ���� �̸�=UNICODE�� �� ���Ͽ���(���� ������ 0)
		if (_wfopen_s(&pFile, fileDlg.GetPathName(), L"wt") == 0) {
			GetDlgItemText(IDC_EDIT_MAIN, strContent);
			strContent.Replace(L"\r\n", L"\n");

			// ANSI�� ���� (����� UTF-8�� �����ִٰ� ����)
			int len = WideCharToMultiByte(CP_ACP, 0, strContent, -1, NULL, 0, NULL, NULL);		// ANSI�� ��ȯ�� �� ����� �� ���ڿ� ����(��ü) ���
			char* p = new char[len];															// ���� ��ü�� ���� char �迭 (Ŀ�� �ϹǷ� ���� ����)
			WideCharToMultiByte(CP_ACP, 0, strContent, -1, p, len, NULL, NULL);

			// ���Ͽ� ����
			fwrite(p, len, 1, pFile);
			delete[] p;

			fclose(pFile);
		}
	}
}


void CM09NotepadDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	//CDialogEx::OnOK();
}


void CM09NotepadDlg::OnBnClickedCancel()
{
	// �����Ͻðڽ��ϱ� ���
	if (MessageBox(L"���α׷��� �����Ͻðڽ��ϱ�?", L"Ȯ��", MB_OKCANCEL | MB_ICONINFORMATION) == IDOK) {
		CDialogEx::OnCancel();
	}
	
}
