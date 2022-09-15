
// MFCApplication1Dlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DataLoad.h"
//
//struct _FILEDATA {    // ����ü ����
//	CString strFolderName;
//	CString strFileName;
//}typedef FILEDATA;


class CMFCApplication1DlgAutoProxy;


// CMFCApplication1Dlg ��ȭ ����
class CMFCApplication1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCApplication1Dlg);
	friend class CMFCApplication1DlgAutoProxy;

// �����Դϴ�.
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	virtual ~CMFCApplication1Dlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	CMFCApplication1DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	CString exFilePath; // ���� �ڵ�ȭ�� ���


	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:

	CDataLoad Dload;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	//CListCtrl m_ListFileName;
	CListCtrl m_lstView; // ����Ʈ��Ʈ��
	//void FindSubDir(CString strDir, CStringArray &FileArray);
	void FindSubDir(CString strDir, vector<CString> &FileArray); //
	afx_msg void OnBnClickedButton4();
	CString m_StrfilePath; // �⺻ ���ϰ�ΰ� ( �ʼ��� X)
	CEdit m_EditFilePath; // ���ϰ�� ��Ÿ���� edit
	vector<CString> FileArray; // ������ü��� ��� ����
	vector<CString> vstrMD5; //MD5�ڵ� ��� ����
	INT iFocus; // ����Ʈ��Ʈ�� ���� ���� ��Ŀ�� �����ִ� �ε��� ��� ����
	CString strCmpMD5; //  ���� MD5 ���� ����
	CString strFolderPath; // ����Ʈ ��Ʈ�ѿ� ǥ���� ���ϰ�� ��� ����


	afx_msg void OnEnUpdateEdit3();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnNMSetfocusAfter(NMHDR *pNMHDR, LRESULT *pResult); // �ʿ� X
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult); // ��������� �Լ�
};

