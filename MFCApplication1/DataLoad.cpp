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

void  CDataLoad::SetPath(CString& str) { m_StrfilePath = str; }

CString CDataLoad::GetPath() { return m_StrfilePath; }

void CDataLoad::FindSubDir(vector<CString> &FileArray)
{

	CFileFind ff;
	m_StrfilePath += _T("\\*.*");

	BOOL bFound = ff.FindFile(m_StrfilePath);
	CString strtmp;

	//FILEDATA tmpfile;

	while (bFound)
	{
		bFound = ff.FindNextFile();

		if (ff.IsDots()) continue; //찾은 파일의 이름에 실제로 디렉터리임을 나타내는 "." 또는 ".."라는 이름이 있는지 확인합니다.
		if (ff.IsDirectory()) // 찾은 파일이 디렉터리인지 확인합니다.
		{
			m_StrfilePath = ff.GetFilePath();
			FindSubDir(FileArray);

		}
		else
		{
			//if (((ff.GetFileName()).Find(_T(".exe")) > -1) || ((ff.GetFileName()).Find(_T(".dll")) > -1)) // Find함수 = 못찾으면 -1 반환
			//{

			FileArray.push_back(ff.GetFilePath());
			//}

		}
	}
}

int CDataLoad::GetFindCharCount(char find_char)
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
}