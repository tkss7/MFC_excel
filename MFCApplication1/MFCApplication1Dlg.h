
// MFCApplication1Dlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


struct _FILEDATA {    // 구조체 정의
	CString strFolderName;
	CString strFileName;
}typedef FILEDATA;


class CMFCApplication1DlgAutoProxy;


// CMFCApplication1Dlg 대화 상자
class CMFCApplication1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCApplication1Dlg);
	friend class CMFCApplication1DlgAutoProxy;

// 생성입니다.
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	virtual ~CMFCApplication1Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	CMFCApplication1DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	CString exFilePath;


	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	//CListCtrl m_ListFileName;
	CListCtrl m_lstView;
	//void FindSubDir(CString strDir, CStringArray &FileArray);
	void FindSubDir(CString strDir, vector<CString> &FileArray); //
	afx_msg void OnBnClickedButton4();
	CString m_StrfilePath;
	CEdit m_EditFilePath;
	vector<CString> FileArray; //
	vector<CString> vstrMD5;
	INT iFocus; //
	CString xx;
	CString strFolderPath;
	afx_msg void OnEnUpdateEdit3();
	afx_msg void OnEnChangeEdit3();
	//static BOOL compare(const FILEDATA &a, const FILEDATA &b);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnNMSetfocusAfter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
};

