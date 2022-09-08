// CmpareMD5Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "CmpareMD5Dlg.h"
#include "afxdialogex.h"


// CCmpareMD5Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCmpareMD5Dlg, CDialog)

CCmpareMD5Dlg::CCmpareMD5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CMP_DIALOG, pParent)
	, m_strCmpMD5(_T(""))
{

}
CCmpareMD5Dlg::CCmpareMD5Dlg(CString& strMD5, CWnd* pParent /*= NULL*/)
	: CDialog(IDD_CMP_DIALOG, pParent)
	, m_strCmpMD5(_T(""))
{
	strMD5 = m_strCmpMD5;
}
CCmpareMD5Dlg::~CCmpareMD5Dlg()
{
}

void CCmpareMD5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strCmpMD5);
}


BEGIN_MESSAGE_MAP(CCmpareMD5Dlg, CDialog)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT1, &CCmpareMD5Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CCmpareMD5Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCmpareMD5Dlg 메시지 처리기입니다.


void CCmpareMD5Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}


BOOL CCmpareMD5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCmpareMD5Dlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//UpdateData(TRUE);
}


void CCmpareMD5Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	GetDlgItemText(IDC_EDIT1, m_strCmpMD5);


	CDialog::OnOK();
}
