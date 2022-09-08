#pragma once


// CCmpareMD5Dlg 대화 상자입니다.

class CCmpareMD5Dlg : public CDialog
{
	DECLARE_DYNAMIC(CCmpareMD5Dlg)

public:
	CCmpareMD5Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	CCmpareMD5Dlg(CString& strMD5, CWnd* pParent = NULL);   // 표준 생성자입니다.

	virtual ~CCmpareMD5Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	CString m_strCmpMD5;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
};
