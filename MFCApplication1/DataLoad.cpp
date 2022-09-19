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

		if (ff.IsDots()) continue; //ã�� ������ �̸��� ������ ���͸����� ��Ÿ���� "." �Ǵ� ".."��� �̸��� �ִ��� Ȯ���մϴ�.
		if (ff.IsDirectory()) // ã�� ������ ���͸����� Ȯ���մϴ�.
		{
			str = ff.GetFilePath();
			FindSubDir(str, FileArray);

		}
		else
		{
			//if (((ff.GetFileName()).Find(_T(".exe")) > -1) || ((ff.GetFileName()).Find(_T(".dll")) > -1)) // Find�Լ� = ��ã���� -1 ��ȯ
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

	//	int sepCount = GetFindCharCount(FileArray[i], _T('\\'));   // " , " �� ������ ����´�. //�����ͺκ� �޼ҵ�?

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