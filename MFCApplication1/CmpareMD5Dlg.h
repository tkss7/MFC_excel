#pragma once


// CCmpareMD5Dlg ��ȭ �����Դϴ�.

class CCmpareMD5Dlg : public CDialog
{
	DECLARE_DYNAMIC(CCmpareMD5Dlg)

public:
	CCmpareMD5Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	CCmpareMD5Dlg(CString& strMD5, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.

	virtual ~CCmpareMD5Dlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	CString m_strCmpMD5;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
};
