#pragma once
//#include <atlstr.h>

class CDataLoad
{
public:
	CDataLoad();

	~CDataLoad();

private:
	CString m_StrfilePath;

public:
	void SetPath(CString& str);
	CString GetPath();

	void FindSubDir(vector<CString> &FileArray);  // ������� ������� ã�� ���Ϳ� ����
	int GetFindCharCount(char find_char); // ������, ���ϸ� ���� �� ��� �� ����

};

