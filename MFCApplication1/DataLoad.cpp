#include "stdafx.h"
#include "DataLoad.h"
//#include "afx.h"
CDataLoad::CDataLoad()
{
	m_strFilePath = _T("");
}


CDataLoad::~CDataLoad()
{
}

VOID  CDataLoad::SetPath(CString& str) { m_strFilePath = str; }

CString CDataLoad::GetPath() { return m_strFilePath; }


void CDataLoad::FindSubDir(CString str, CProduct & product)  // 하위경로 모든파일 찾아 벡터에 저장
{
	//if (str.GetBuffer() == NULL)
	//	str = m_StrfilePath;

	int icount = 0;
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
			FindSubDir(str, product);

		}
		else
		{
			//if (((ff.GetFileName()).Find(_T(".exe")) > -1) || ((ff.GetFileName()).Find(_T(".dll")) > -1)) // Find함수 = 못찾으면 -1 반환
			//{
			product.m_vstrFilePath.push_back(ff.GetFilePath());
			icount++;
			//}
		}
	}

	if (icount)
	{
		CATEGORYCOUNT cate;
		cate.strCategoryName = GetFoldNAame(ff.GetRoot());
		cate.iCategoryNum = icount;

		product.m_vCategory.push_back(cate);
	}

	ff.Close();
}

int CDataLoad::GetFindCharCount(CString &str, TCHAR find_char)
{
	int imsg_len = str.GetLength();
	int ifind_cnt = 0;

	for (int i = 0; i<imsg_len; i++)
	{
		if (str[i] == find_char)
		{
			ifind_cnt++;
		}
	}
	return ifind_cnt;
}

CString CDataLoad::ReverseSubPath(CString &str, int ilocation)
{
	CString strtmp;
	int sepCount = GetFindCharCount(str, _T('\\'));   // " , " 의 갯수를 세어온다. //데이터부분 메소드?

	AfxExtractSubString(strtmp, str, sepCount - ilocation, _T('\\'));

	return strtmp;
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



CString CDataLoad::GetFoldNAame(CString str)
{
	
	str.Delete(str.GetLength() - 1);
	str = str.Right(str.GetLength() - str.ReverseFind(_T('\\')) - 1);
	return str;
}

CProduct::CProduct()
{

}

CProduct::~CProduct()
{

}