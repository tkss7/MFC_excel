// CmpareMD5Dlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "CmpareMD5Dlg.h"
#include "afxdialogex.h"


// CCmpareMD5Dlg ��ȭ �����Դϴ�.

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


// CCmpareMD5Dlg �޽��� ó�����Դϴ�.


void CCmpareMD5Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


BOOL CCmpareMD5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CCmpareMD5Dlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//UpdateData(TRUE);
}


void CCmpareMD5Dlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	GetDlgItemText(IDC_EDIT1, m_strCmpMD5);


	CDialog::OnOK();
}
