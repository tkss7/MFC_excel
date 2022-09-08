
// MFCApplication1Dlg.cpp : 구현 파일
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
#include "CmpareMD5Dlg.h"

#include <Wincrypt.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	CApplication oExcel;
	CWorkbook oBook;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFCApplication1Dlg 대화 상자


IMPLEMENT_DYNAMIC(CMFCApplication1Dlg, CDialogEx);

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_StrfilePath(_T("C:\\visual studio project\\MFCApplication1"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMFCApplication1Dlg::~CMFCApplication1Dlg()
{
	// 이 대화 상자에 대한 자동화 프록시가 있을 경우 이 대화 상자에 대한
	//  후방 포인터를 NULL로 설정하여
	//  대화 상자가 삭제되었음을 알 수 있게 합니다.
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
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	CRect rect;
	m_lstView.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES /*LVS_EX_CHECKBOXES*/);

	CRect r;
	::GetClientRect(m_lstView.m_hWnd, r);

	int cx = r.right - r.left;
	//리스트 컨트롤 컬럼 추가


	m_lstView.InsertColumn(0, _T("파일명"), LVCFMT_LEFT, int(cx * 0.5));

	m_lstView.InsertColumn(1, _T("Hash Code"), LVCFMT_LEFT, int(cx * 0.25));

	m_lstView.InsertColumn(2, _T("Compare Hash Code"), LVCFMT_LEFT, int(cx * 0.25));

	iFocus = 0;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 컨트롤러에서 해당 개체 중 하나를 계속 사용하고 있을 경우
//  사용자가 UI를 닫을 때 자동화 서버를 종료하면 안 됩니다.  이들
//  메시지 처리기는 프록시가 아직 사용 중인 경우 UI는 숨기지만,
//  UI가 표시되지 않아도 대화 상자는
//  남겨 둡니다.

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
	// 프록시 개체가 계속 남아 있으면 자동화 컨트롤러에서는
	//  이 응용 프로그램을 계속 사용합니다.  대화 상자는 남겨 두지만
	//  해당 UI는 숨깁니다.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

//static BOOL CMFCApplication1Dlg::compare(const FILEDATA &a, const FILEDATA &b)
static BOOL compare(const FILEDATA &a, const FILEDATA &b)
{

	if (a.strFolderName == b.strFolderName)
	//if(a.strFolderName.Compare(b.strFolderName)!=0)
	{
		return a.strFileName < b.strFileName;
	}
	else
		return a.strFolderName < b.strFolderName;

}

CString md5gen(CString input) 
{ BYTE rgbHash[16];
	BYTE *data;	int data_len;
	DWORD cbHash;	CString ret;
	CStringA str;	HCRYPTPROV hCryptProv;
	HCRYPTHASH hHash;
	str = input;
	data = (BYTE *)str.GetString();
	data_len = str.GetLength();
	CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0);
	CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash);
	CryptHashData(hHash, (const BYTE *)data, data_len, 0);
	CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0);
	for (DWORD i = 0; i < cbHash; i++)			ret.AppendFormat(_T("%02x"), rgbHash[i]);	CryptDestroyHash(hHash);
	CryptReleaseContext(hCryptProv, 0);
	return ret;
}

void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CApplication app; // Declare a variable for Excel applicaton
					  // Start Excel
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		AfxMessageBox(_T("Couldn’t start Excel."));
	}
	else
	{
		app.put_Visible(true); // To show user operation during Excel automation
	}

	CWorkbooks wbs; // Workbooks 변수 선언
	CWorkbook wb; // Workbooks 내의 Workbook 변수 선언

	LPDISPATCH l_lpDisp = app.get_Workbooks(); //Get an IDispatch pointer
	COleVariant covTrue((short)TRUE);
	COleVariant covFalse((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);


	//app.put_SheetsInNewWorkbook(1); // Workbook 내의 Worksheet #1을 생성
	wbs.AttachDispatch(l_lpDisp); // Workbooks를 연결


	l_lpDisp = wbs.Open(exFilePath, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);



	wb.AttachDispatch(l_lpDisp); // Workbook을 연결


	CWorksheets wss; // Worksheets의 변수를 선언
	wss = wb.get_Sheets(); // Worksheets Workbook을 연결

						   //Excel sheet을 하나 만든 후, WorkSheet #1에 연결할 것임.
	CWorksheet ws; // Worksheet을 선엄함.
	ws = wss.get_Item(COleVariant((short)1)); // 이 Worksheets을 Worksheet과 연결함.

	ws.put_Name(_T("BOM")); // Worksheet의 이름을 변경함. (엑셀 문서 아래의 Sheet 이름을 지정함.


}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

static TCHAR BASED_CODE szFilter[] = _T("엑셀 파일(*.xls, *.xlsx) | *.xls;*.xlsx;|모든파일(*.*)|*.*||");
 
CFileDialog dlg(TRUE, _T("*.xlsx"), _T("excel"), OFN_HIDEREADONLY, szFilter);

if (IDOK == dlg.DoModal())

{
	exFilePath = dlg.GetPathName();
	MessageBox(exFilePath);
}

}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//char *pszInput = "test";
	//CString pszInput2 = _T("Test");

	vector<CString> strMD5;

	CString strCheckSum;

	for (int i = 0; i < FileArray.size(); i++)
	{
		strMD5.emplace_back(md5gen(FileArray[i].strFileName));
		m_lstView.SetItemText(i, 1, strMD5[i]);

	}

	//strCheckSum.MakeUpper();

}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	CString strInitPath = _T("C:\\");

	// 폴더 선택 다이얼로그
	CFolderPickerDialog Picker(strInitPath, OFN_FILEMUSTEXIST, NULL, 0);
	if (Picker.DoModal() == IDOK)
	{
		// 선택된 폴더 경로얻음
		CString strFolderPath = Picker.GetPathName();
		m_EditFilePath.SetWindowTextW(strFolderPath);
		OnEnUpdateEdit3();
		FindSubDir(strFolderPath, FileArray);
		m_lstView.DeleteAllItems();

	}

	sort(FileArray.begin(), FileArray.end(), compare);



	for (int i = 0; i < FileArray.size(); i++)
	{
		m_lstView.InsertItem(i, FileArray[i].strFileName);
		//m_lstView.SetItemText(i, 1, FileArray[i].strFolderName);

		//AfxMessageBox(FileArray[i].strFileName + FileArray[i].strFolderName);
	}   
	for (auto i : FileArray)
	{
		AfxMessageBox((i.strFileName));
	}


}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMFCApplication1Dlg::FindSubDir(CString strDir, vector<FILEDATA> &FileArray)
{
	strDir += _T("\\*.*");

	CFileFind ff;
	BOOL bFound = ff.FindFile(strDir);
	CString strtmp;

	FILEDATA tmpfile;

	while (bFound)
	{
		bFound = ff.FindNextFile();

		if (ff.IsDots()) continue; //찾은 파일의 이름에 실제로 디렉터리임을 나타내는 "." 또는 ".."라는 이름이 있는지 확인합니다.
		if (ff.IsDirectory()) // 찾은 파일이 디렉터리인지 확인합니다.
		{
			FindSubDir(ff.GetFilePath(), FileArray);

		}
		else
		{
			if (((ff.GetFileName()).Find(_T(".exe")) > -1) || ((ff.GetFileName()).Find(_T(".dll")) > -1)) // Find함수 = 못찾으면 -1 반환
			{

				//FileArray.push_back(ff.GetFileName());
				strtmp = ff.GetRoot();
				strtmp.Delete(strtmp.GetLength() - 1);
				//FileArray.push_back(strtmp);
				strtmp = strtmp.Right(strtmp.GetLength() - strtmp.ReverseFind('\\') - 1);

				tmpfile.strFileName = ff.GetFileName();
				tmpfile.strFolderName = strtmp;
				FileArray.push_back(tmpfile);
			}

		}
	}
}



void CMFCApplication1Dlg::OnEnUpdateEdit3()
{


	//UpdateData(FALSE);  // 변수에 적힌 값을 컨트롤에 표시하도록 갱신해준다.

	//UpdateData(TRUE); // 현재 컨트롤에 적힌 값을 변수로 넣어 갱신해준다.

	UpdateData(TRUE);

}


void CMFCApplication1Dlg::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(FALSE);
	//UpdateData(TRUE);

}



void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strCmpMD5;
	CCmpareMD5Dlg dlg(strCmpMD5);
	if (dlg.DoModal() == IDOK)
	{
		//dlg.m_strCmpMD5;
		//SetDlgItemText(IDC_EDIT1, strCmpMD5);
		m_lstView.SetItemText(iFocus, 2, dlg.m_strCmpMD5);

	}
}


void CMFCApplication1Dlg::OnNMSetfocusAfter(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	iFocus = m_lstView.GetSelectionMark();


	*pResult = 0;
}
