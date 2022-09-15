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

		if (ff.IsDots()) continue; //ã�� ������ �̸��� ������ ���͸����� ��Ÿ���� "." �Ǵ� ".."��� �̸��� �ִ��� Ȯ���մϴ�.
		if (ff.IsDirectory()) // ã�� ������ ���͸����� Ȯ���մϴ�.
		{
			m_StrfilePath = ff.GetFilePath();
			FindSubDir(FileArray);

		}
		else
		{
			//if (((ff.GetFileName()).Find(_T(".exe")) > -1) || ((ff.GetFileName()).Find(_T(".dll")) > -1)) // Find�Լ� = ��ã���� -1 ��ȯ
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