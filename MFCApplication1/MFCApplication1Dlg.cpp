
// MFCApplication1Dlg.cpp : ���� ����
//

#include "stdafx.h"
//#include "DataLoad.h"

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
#include "CmpareMD5Dlg.h"




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
	, m_StrfilePath(_T("C:\\visual studio project\\MFCApplication1"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_ROGO/*IDR_MAINFRAME*/);
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
	//DDX_Control(pDX, IDC_BEFORE, m_ListFileName);
	DDX_Control(pDX, IDC_AFTER, m_lstView);
	DDX_Text(pDX, IDC_EDIT3, m_StrfilePath);
	DDX_Control(pDX, IDC_EDIT3, m_EditFilePath);
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
	ON_EN_UPDATE(IDC_EDIT3, &CMFCApplication1Dlg::OnEnUpdateEdit3)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication1Dlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
	ON_NOTIFY(NM_SETFOCUS, IDC_AFTER, &CMFCApplication1Dlg::OnNMSetfocusAfter)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_AFTER, OnCustomdrawList)
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

	//CDataLoad Dload;

	CRect rect;
	m_lstView.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER /*LVS_EX_CHECKBOXES*/); //������۸� ����

	CRect r;
	::GetClientRect(m_lstView.m_hWnd, r);

	int cx = r.right - r.left;
	//����Ʈ ��Ʈ�� �÷� �߰�


	m_lstView.InsertColumn(0, _T("���ϸ�"), LVCFMT_LEFT, int(cx * 0.5));

	m_lstView.InsertColumn(1, _T("Hash Code"), LVCFMT_LEFT, int(cx * 0.25));

	m_lstView.InsertColumn(2, _T("Compare Hash Code"), LVCFMT_LEFT, int(cx * 0.25));

	iFocus = 0;

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

//static BOOL CMFCApplication1Dlg::compare(const FILEDATA &a, const FILEDATA &b)
//static BOOL compare(const FILEDATA &a, const FILEDATA &b)
//{
//
//	if (a.strFolderName == b.strFolderName)
//	//if(a.strFolderName.Compare(b.strFolderName)!=0)
//	{
//		return a.strFileName < b.strFileName;
//	}
//	else
//		return a.strFolderName < b.strFolderName;
//
//}

static BOOL compare(const CString &a, const CString &b)
{

	if (a < b)
		//if(a.strFolderName.Compare(b.strFolderName)!=0)
	{
		return TRUE;
	}

}


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


	//app.put_SheetsInNewWorkbook(1); // Workbook ���� Worksheet #1�� ����
	wbs.AttachDispatch(l_lpDisp); // Workbooks�� ����


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
int GetFindCharCount(CString msg, char find_char)
{
	int msg_len = msg.GetLength();
	int find_cnt = 0;

	for (int i = 0; i<msg_len; i++)
	{
		if (msg[i] == find_char)
		{
			find_cnt++;
		}
	}
	return find_cnt;
}

void CMFCApplication1Dlg::OnBnClickedButton2()
{
// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

//static TCHAR BASED_CODE szFilter[] = _T("���� ����(*.xls, *.xlsx) | *.xls;*.xlsx;|�������(*.*)|*.*||");
// 
//CFileDialog dlg(TRUE, _T("*.xlsx"), _T("excel"), OFN_HIDEREADONLY, szFilter);
//
//if (IDOK == dlg.DoModal())
//
//{
//	exFilePath = dlg.GetPathName();
//	//MessageBox(exFilePath);
//}
	
	m_lstView.DeleteItem(iFocus);
	
	//////////////////////////////////////////////// �� ���͸� CProduct �� ���� ���̶�� ��� erase �޼��� ����?
	if(!FileArray.empty())
		FileArray.erase(FileArray.begin() + iFocus);

	if(!vstrMD5.empty())
		vstrMD5.erase(vstrMD5.begin() + iFocus);
	////////////////////////////////////////////////

	//CString strtmp2, strtmp3;

	//for (int i = 0; i < FileArray.size(); i++)
	//{
	//	int sepCount = GetFindCharCount(FileArray[i], _T('\\'));   // " , " �� ������ ����´�. //�����ͺκ� �޼ҵ�?

	//	AfxExtractSubString(strtmp2, FileArray[i], sepCount - 1, _T('\\'));
	//	AfxExtractSubString(strtmp3, FileArray[i], sepCount, _T('\\'));

	//AfxMessageBox(strtmp2);
	//AfxMessageBox(strtmp3);
	//}





}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//char *pszInput = "test";
	//CString pszInput2 = _T("Test");

	

	//CString strCheckSum;

	for (int i = 0; i < FileArray.size(); i++)
	{
		vstrMD5.emplace_back(CMD5Checksum::GetMD5(FileArray[i]));
		//strMD5.emplace_back(md5gen(FileArray[i].strFileName));
		m_lstView.SetItemText(i, 1, vstrMD5[i]);

	}

	//strCheckSum.MakeUpper();

}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	//// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.


	CString strInitPath = _T("C:\\");

	// ���� ���� ���̾�α�
	CFolderPickerDialog Picker(strInitPath, OFN_FILEMUSTEXIST , NULL, 0);

	if (Picker.DoModal() == IDOK)
	{
		// ���õ� ���� ��ξ���
		if (Dload.GetPath() == Picker.GetPathName())
			return;

		Dload.SetPath(Picker.GetPathName());
		m_EditFilePath.SetWindowTextW(Dload.GetPath());
		OnEnUpdateEdit3();
		Dload.FindSubDir(FileArray);
		m_lstView.DeleteAllItems();

		sort(FileArray.begin(), FileArray.end(), compare);



		for (int i = 0; i < FileArray.size(); i++)
		{
			m_lstView.InsertItem(i, FileArray[i]);
		}
		if (!vstrMD5.empty())
		{
			for (int i = 0; i < vstrMD5.size(); i++)
			{
				m_lstView.SetItemText(i, 1, vstrMD5[i]);

			}
		}

	}





}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMFCApplication1Dlg::FindSubDir(CString strDir, vector<CString> &FileArray)
{
	strDir += _T("\\*.*");

	CFileFind ff;
	BOOL bFound = ff.FindFile(strDir);
	CString strtmp;

	//FILEDATA tmpfile;

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
			//if (((ff.GetFileName()).Find(_T(".exe")) > -1) || ((ff.GetFileName()).Find(_T(".dll")) > -1)) // Find�Լ� = ��ã���� -1 ��ȯ
			//{

				////FileArray.push_back(ff.GetFileName());
				//strtmp = ff.GetRoot();
				//strtmp.Delete(strtmp.GetLength() - 1);
				////FileArray.push_back(strtmp);
				//strtmp = strtmp.Right(strtmp.GetLength() - strtmp.ReverseFind('\\') - 1);

				//tmpfile.strFileName = ff.GetFileName();
				//tmpfile.strFolderName = strtmp;
				FileArray.push_back(ff.GetFilePath());
			//}

		}
	}
}



void CMFCApplication1Dlg::OnEnUpdateEdit3()
{


	//UpdateData(FALSE);  // ������ ���� ���� ��Ʈ�ѿ� ǥ���ϵ��� �������ش�.

	//UpdateData(TRUE); // ���� ��Ʈ�ѿ� ���� ���� ������ �־� �������ش�.

	UpdateData(TRUE);

}


void CMFCApplication1Dlg::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(FALSE);
	//UpdateData(TRUE);

}



void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	strCmpMD5;
	CCmpareMD5Dlg dlg(strCmpMD5);
	if (dlg.DoModal() == IDOK)  
	{
		iFocus = m_lstView.GetSelectionMark();
		//dlg.m_strCmpMD5;
		//SetDlgItemText(IDC_EDIT1, strCmpMD5);
		m_lstView.SetItemText(iFocus, 2, dlg.m_strCmpMD5);
		//m_lstView.SetItemText(3, 2, CMD5Checksum::GetMD5(xx));
		Invalidate(FALSE);
	}
}

void CMFCApplication1Dlg::OnNMSetfocusAfter(NMHDR *pNMHDR, LRESULT *pResult)   // ��� ����
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//iFocus = m_lstView.GetSelectionMark();


	*pResult = 0;
}

void CMFCApplication1Dlg::OnCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pNMCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	// TODO: Add your control notification handler code here


	if (pNMCD->nmcd.dwDrawStage == CDDS_PREPAINT) {
		*pResult = (LRESULT)CDRF_NOTIFYITEMDRAW;
		return; // ���⼭ �Լ��� ���� ������ *pResult ���� �����ȴ�.
	}

	//RGB(219, 239, 252); �ϴû�
	if (pNMCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT) {

		// �� �� (row) �� �׷��� ��. ���⼭�� �����ϸ� �� ���� ��� �����ϰ� ������ �ȴ�.
		int nRow = pNMCD->nmcd.dwItemSpec;

		if (m_lstView.GetItemText(nRow, 2).IsEmpty())
			return;
		CString text = m_lstView.GetItemText(nRow, 1);
		if (text.CompareNoCase(m_lstView.GetItemText(nRow, 2))){
			pNMCD->clrText = RGB(255, 255, 255);
			pNMCD->clrTextBk = RGB(219, 68, 85);
			*pResult = (LRESULT)CDRF_NEWFONT;//���⼭ ������ sub-item �� ������� �ʴ´�.
			//*pResult = (LRESULT)CDRF_NOTIFYSUBITEMDRAW;//sub-item �� �����ϱ� ���ؼ�. 
			return;//���⼭ �ߴ��ؾ� *pResult ���� �����ȴ�.
		}
		else { // When all matrices are already made. 

			pNMCD->clrText = RGB(0, 0, 0);

			pNMCD->clrTextBk = RGB(219, 239, 100);
			*pResult = (LRESULT)CDRF_NEWFONT;
			return;
		}

	}
	

	//else if (pNMCD->nmcd.dwDrawStage == (CDDS_SUBITEM | CDDS_ITEMPREPAINT)) {
	//	// sub-item �� �׷����� ����. ������ *pResult �� CDRF_NOTIFYSUBITEMDRAW �� �ؼ� �����

	//	// �� �� �־��� ���̴�.
	//	// �� �� (row) �� �׷��� ��. ���⼭�� �����ϸ� �� ���� ��� �����ϰ� ������ �ȴ�.
	//	//if (m_lstView.GetItemData(pNMCD->dwItemSpec) == 0) {//dwItemSpec �� ���� �׷����� row index
	//	if (m_lstView.GetItemText(pNMCD->nmcd.dwItemSpec, 2).IsEmpty())
	//		return;
	//	CString text = m_lstView.GetItemText(pNMCD->nmcd.dwItemSpec, 1);
	//	if (text == m_lstView.GetItemText(pNMCD->nmcd.dwItemSpec, 2)&& nSub==0) {

	//		pNMCD->clrText = RGB(0, 0, 0);

	//		pNMCD->clrTextBk = RGB(219, 239, 252);
	//		*pResult = (LRESULT)CDRF_NEWFONT;//���⼭ ������ sub-item �� ������� �ʴ´�.
	//										 //*pResult = (LRESULT)CDRF_NOTIFYSUBITEMDRAW;//sub-item �� �����ϱ� ���ؼ�. 
	//		return;//���⼭ �ߴ��ؾ� *pResult ���� �����ȴ�.
	//	}
	//	else { // When all matrices are already made. 
	//		pNMCD->clrText = 0x0;
	//		pNMCD->clrTextBk = RGB(219, 239, 100);
	//		*pResult = (LRESULT)CDRF_NEWFONT;
	//		//*pResult = (LRESULT)CDRF_NOTIFYSUBITEMDRAW;
	//		return;
	//	}
	
	//}

	
}