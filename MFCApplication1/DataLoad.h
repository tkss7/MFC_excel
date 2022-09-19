#pragma once
//#include <atlstr.h>

struct _CATEGORYCOUNT {    // 구조체 정의
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
	void FindSubDir(CString str, vector<CString> &FileArray);  // 하위경로 모든파일 찾아 벡터에 저장
	int GetFindCharCount(TCHAR find_char); // 폴더명, 파일명 나눌 때 사용 할 예정
	CString GetFoldNAame(CString str);
	
};


