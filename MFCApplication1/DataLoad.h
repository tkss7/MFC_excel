#pragma once
//#include <atlstr.h>





struct _CATEGORYCOUNT {    // ����ü ����
	CString strCategoryName;
	int iCategoryNum;
}typedef CATEGORYCOUNT;

class CProduct
{
public:
	CProduct();

	~CProduct();

public:
	vector<CATEGORYCOUNT> m_vCategory;
	vector<CString> m_vstrFilePath;
	vector<CString> m_vstrMD5;

};



class CDataLoad
{
public:
	CDataLoad();

	~CDataLoad();

private:
	CString m_strFilePath;
	
public:
	void SetPath(CString& str);
	CString GetPath();
	void FindSubDir(CString str, CProduct & product);  // ������� ������� ã�� ���Ϳ� ����
	int GetFindCharCount(CString &str, TCHAR find_char); // ������, ���ϸ� ���� �� ��� �� ����
	CString GetFoldNAame(CString str);
	CString ReverseSubPath(CString &strm, int nlocation);
	
};

