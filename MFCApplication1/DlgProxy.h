
// DlgProxy.h: ��� ����
//

#pragma once

class CMFCApplication1Dlg;


// CMFCApplication1DlgAutoProxy ��� ���

class CMFCApplication1DlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMFCApplication1DlgAutoProxy)

	CMFCApplication1DlgAutoProxy();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.

// Ư���Դϴ�.
public:
	CMFCApplication1Dlg* m_pDialog;

// �۾��Դϴ�.
public:

// �������Դϴ�.
	public:
	virtual void OnFinalRelease();

// �����Դϴ�.
protected:
	virtual ~CMFCApplication1DlgAutoProxy();

	// ������ �޽��� �� �Լ�

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMFCApplication1DlgAutoProxy)

	// ������ OLE ����ġ �� �Լ�

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

