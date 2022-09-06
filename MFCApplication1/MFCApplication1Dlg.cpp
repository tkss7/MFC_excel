
// MFCApplication1Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"

#include "MD5ChecksumDefines.h"
#include "MD5Checksum.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	CApplication oExcel;
	CWorkbook oBook;
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��ȭ ����


IMPLEMENT_DYNAMIC(CMFCApplication1Dlg, CDialogEx);

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMFCApplication1Dlg::~CMFCApplication1Dlg()
{
	// �� ��ȭ ���ڿ� ���� �ڵ�ȭ ���Ͻð� ���� ��� �� ��ȭ ���ڿ� ����
	//  �Ĺ� �����͸� NULL�� �����Ͽ�
	//  ��ȭ ���ڰ� �����Ǿ����� �� �� �ְ� �մϴ�.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BEFORE, m_ListFileName);
	DDX_Control(pDX, IDC_AFTER, m_ListMD5);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCApplication1Dlg �޽��� ó����

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	CRect rect;

	m_ListFileName.GetClientRect(&rect);

	//����Ʈ ��Ʈ�� �÷� �߰�

	m_ListFileName.InsertColumn(0, _T("���ϸ�"), LVCFMT_LEFT, rect.Width());

	m_ListMD5.GetClientRect(&rect);

	//����Ʈ ��Ʈ�� �÷� �߰�

	m_ListMD5.InsertColumn(0, _T("���ϸ�"), LVCFMT_LEFT, rect.Width()/2);

	m_ListMD5.InsertColumn(1, _T("��ȣȭ �ڵ�"), LVCFMT_LEFT, rect.Width() / 2);


	//for (int i = 0; i < 2; i++)

	//{

	//	//�̸� �߰��ϱ�

	//	m_List.InsertItem(i, sampleName[i], i % 5);



	//	//���� �߰��ϱ�

	//	m_List.SetItemText(i, 1, sampleAge[i]);

	//}

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ��Ʈ�ѷ����� �ش� ��ü �� �ϳ��� ��� ����ϰ� ���� ���
//  ����ڰ� UI�� ���� �� �ڵ�ȭ ������ �����ϸ� �� �˴ϴ�.  �̵�
//  �޽��� ó����� ���Ͻð� ���� ��� ���� ��� UI�� ��������,
//  UI�� ǥ�õ��� �ʾƵ� ��ȭ ���ڴ�
//  ���� �Ӵϴ�.

void CMFCApplication1Dlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CMFCApplication1Dlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CMFCApplication1Dlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CMFCApplication1Dlg::CanExit()
{
	// ���Ͻ� ��ü�� ��� ���� ������ �ڵ�ȭ ��Ʈ�ѷ�������
	//  �� ���� ���α׷��� ��� ����մϴ�.  ��ȭ ���ڴ� ���� ������
	//  �ش� UI�� ����ϴ�.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


//#include "CRange.h"
//#include "CWorkbook.h"
//#include "CWorkbooks.h"
//#include "CWorksheet.h"
//#include "CWorksheets.h"

void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CApplication app; // Declare a variable for Excel applicaton
					  // Start Excel
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		AfxMessageBox(_T("Couldn��t start Excel."));
	}
	else
	{
		app.put_Visible(true); // To show user operation during Excel automation
	}

	CWorkbooks wbs; // Workbooks ���� ����
	CWorkbook wb; // Workbooks ���� Workbook ���� ����

	LPDISPATCH l_lpDisp = app.get_Workbooks(); //Get an IDispatch pointer
	COleVariant covTrue((short)TRUE);
	COleVariant covFalse((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	//app.get_Workbooks();
	//app.get_Sheets();
	//app.put_SheetsInNewWorkbook(1); // Workbook ���� Worksheet #1�� ����
	wbs.AttachDispatch(l_lpDisp); // Workbooks�� ����

	//l_lpDisp = wbs.Open(_T("C:\\Users\\user\\Desktop\\1.xlsx"), covOptional, covOptional, covOptional,
	//	covOptional, covOptional, covOptional, covOptional, covOptional,
	//	covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);

	l_lpDisp = wbs.Open(exFilePath, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);



	wb.AttachDispatch(l_lpDisp); // Workbook�� ����


	CWorksheets wss; // Worksheets�� ������ ����
	wss = wb.get_Sheets(); // Worksheets Workbook�� ����

						   //Excel sheet�� �ϳ� ���� ��, WorkSheet #1�� ������ ����.
	CWorksheet ws; // Worksheet�� ������.
	ws = wss.get_Item(COleVariant((short)1)); // �� Worksheets�� Worksheet�� ������.

	ws.put_Name(_T("BOM")); // Worksheet�� �̸��� ������. (���� ���� �Ʒ��� Sheet �̸��� ������.


}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

static TCHAR BASED_CODE szFilter[] = _T("���� ����(*.xls, *.xlsx) | *.xls;*.xlsx;|�������(*.*)|*.*||");

CFileDialog dlg(TRUE, _T("*.xlsx"), _T("excel"), OFN_HIDEREADONLY, szFilter);

if (IDOK == dlg.DoModal())

{
	exFilePath = dlg.GetPathName();

	MessageBox(exFilePath);

}

}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char *pszInput = "test";

	CString strCheckSum;
	strCheckSum = CMD5Checksum::GetMD5((BYTE *)pszInput, strlen(pszInput));

	AfxMessageBox(strCheckSum);

}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	//// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//static TCHAR BASED_CODE szFilter[] = _T("���� ����(*.exe) | *.exe;|�������(*.*)|*.*||");

	//CFileDialog dlg(TRUE, _T("*.xlsx"), _T("exe"), OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT, szFilter);

	//if (IDOK == dlg.DoModal())

	//{
	//	for (auto pos = dlg.GetStartPosition(); pos != NULL;)
	//	{
	//		
	//		CString str = dlg.GetNextPathName(pos);
	//		CString str1 = dlg.GetFolderPath();

	//		str.Delete(0, str1.GetLength()+1);
	//		exFilePath += str;
	//		//exFilePath.Remove(dlg.GetFolderPath);
	//		
	//	}

	//	//exFilePath = dlg.GetFileName();

	//	MessageBox(exFilePath);

	//}
	CStringArray FileArray;
	CString strInitPath = _T("C:\\");

	// ���� ���� ���̾�α�
	CFolderPickerDialog Picker(strInitPath, OFN_FILEMUSTEXIST, NULL, 0);
	if (Picker.DoModal() == IDOK)
	{
		// ���õ� ���� ��ξ���
		CString strFolderPath = Picker.GetPathName();

		FindSubDir(strFolderPath, FileArray);

	}
	for (int i = 0; i < FileArray.GetSize(); i++)
	{
		AfxMessageBox(FileArray.GetAt(i));
	}

}

void CMFCApplication1Dlg::FindSubDir(CString strDir, CStringArray &FileArray)
{
	strDir += _T("\\*.*");

	CFileFind ff;
	BOOL bFound = ff.FindFile(strDir);
	CString strtmp;

	while (bFound)
	{
		bFound = ff.FindNextFile();

		if (ff.IsDots()) continue; //ã�� ������ �̸��� ������ ���͸����� ��Ÿ���� "." �Ǵ� ".."��� �̸��� �ִ��� Ȯ���մϴ�.
		if (ff.IsDirectory()) // ã�� ������ ���͸����� Ȯ���մϴ�.
		{
			FindSubDir(ff.GetFilePath(), FileArray);

		}
		else
		{
			if (((ff.GetFileName()).Find(_T(".exe")) > -1)|| ((ff.GetFileName()).Find(_T(".dll")) > -1)) // Find�Լ� = ��ã���� -1 ��ȯ
			{
				FileArray.Add(ff.GetFileName());
			}

		}
	}
}
