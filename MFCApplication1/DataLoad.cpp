#include "stdafx.h"
#include "DataLoad.h"
//#include "afx.h"
CDataLoad::CDataLoad()
{
	m_StrfilePath = _T("");
}


CDataLoad::~CDataLoad()
{
}

VOID  CDataLoad::SetPath(CString& str) { m_StrfilePath = str; }

CString CDataLoad::GetPath() { return m_StrfilePath; }

VOID CDataLoad::FindSubDir(CString str, vector<CString> &FileArray)
{
	if (str.GetBuffer() == NULL)
		str = m_StrfilePath;

	int count = 0;
	CFileFind ff;
	//m_StrfilePath += _T("\\*.*");
	str += _T("\\*.*");

	BOOL bFound = ff.FindFile(str);

	//FILEDATA tmpfile;

	while (bFound)
	{
		bFound = ff.FindNextFile();

		if (ff.IsDots()) continue; //찾은 파일의 이름에 실제로 디렉터리임을 나타내는 "." 또는 ".."라는 이름이 있는지 확인합니다.
		if (ff.IsDirectory()) // 찾은 파일이 디렉터리인지 확인합니다.
		{
			str = ff.GetFilePath();
			FindSubDir(str, FileArray);

		}
		else
		{
			//if (((ff.GetFileName()).Find(_T(".exe")) > -1) || ((ff.GetFileName()).Find(_T(".dll")) > -1)) // Find함수 = 못찾으면 -1 반환
			//{
			FileArray.push_back(ff.GetFilePath());
			count++;
			//}
		}
	}

	if (count)
	{
		CATEGORYCOUNT cate;
		cate.strCategoryName = GetFoldNAame(ff.GetRoot());
		cate.iCategoryNum = count;

		Category.push_back(cate);
	}

	ff.Close();
}
  
int CDataLoad::GetFindCharCount(TCHAR find_char)
{
	int msg_len = m_StrfilePath.GetLength();
	int find_cnt = 0;

	for (int i = 0; i<msg_len; i++)
	{
		if (m_StrfilePath[i] == find_char)
		{
			find_cnt++;
		}
	}
	return find_cnt;

	//	int sepCount = GetFindCharCount(FileArray[i], _T('\\'));   // " , " 의 갯수를 세어온다. //데이터부분 메소드?

	//	AfxExtractSubString(strtmp2, FileArray[i], sepCount - 1, _T('\\'));
	//	AfxExtractSubString(strtmp3, FileArray[i], sepCount, _T('\\'));

}

//void CDataLoad::GetDirFilesNum()
//{
//
//	CString str = m_StrfilePath;
//
//	int count = 0;
//	CFileFind finder;
//	str += _T("/*.*");
//	BOOL bWorking = TRUE;
//	
//	while (bWorking)
//	{
//		bWorking = finder.FindFile(str);
//
//		while (bWorking)
//		{
//			bWorking = finder.FindNextFile();
//			if (finder.IsDots())
//			{
//				continue;
//			}
//			if (!finder.IsDirectory())
//			{
//				count++;
//			}
//			
//
//		}
//		Category.emplace_back(count);
//		str = finder.GetFilePath();
//		count = 0;
//	}
//	
//
//	finder.Close();
//
//	return count;
//}

vector<CATEGORYCOUNT> CDataLoad::GetCategoryVec()
{

	//GetDirFilesNum();
	return Category;
}

CString CDataLoad::GetFoldNAame(CString str)
{
	
	str.Delete(str.GetLength() - 1);
	str = str.Right(str.GetLength() - str.ReverseFind(_T('\\')) - 1);
	return str;
}