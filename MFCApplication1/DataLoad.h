#pragma once
//#include <atlstr.h>





struct _CATEGORYCOUNT {    // 구조체 정의
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
	void FindSubDir(CString str, CProduct & product);  // 하위경로 모든파일 찾아 벡터에 저장
	int GetFindCharCount(CString &str, TCHAR find_char); // 폴더명, 파일명 나눌 때 사용 할 예정
	CString GetFoldNAame(CString str);
	CString ReverseSubPath(CString &strm, int nlocation);
	
};

