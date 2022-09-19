#pragma once
//#include <atlstr.h>

struct _CATEGORYCOUNT {    // ����ü ����
	CString strCategoryName;
	int iCategoryNum;
}typedef CATEGORYCOUNT;

class CDataLoad
{
public:
	CDataLoad();

	~CDataLoad();

private:
	CString m_StrfilePath;
	vector<CATEGORYCOUNT> Category;
public:
	void SetPath(CString& str);
	CString GetPath();
	vector<CATEGORYCOUNT> GetCategoryVec();
	void FindSubDir(CString str, vector<CString> &FileArray);  // ������� ������� ã�� ���Ϳ� ����
	int GetFindCharCount(TCHAR find_char); // ������, ���ϸ� ���� �� ��� �� ����
	CString GetFoldNAame(CString str);
	
};


