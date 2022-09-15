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

	void FindSubDir(vector<CString> &FileArray);  // 하위경로 모든파일 찾아 벡터에 저장
	int GetFindCharCount(char find_char); // 폴더명, 파일명 나눌 때 사용 할 예정

};

