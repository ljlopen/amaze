#include "stdafx.h"
#include "CGridReg.h"
#include <Shlwapi.h> 

CGridReg::CGridReg()
{
}


CGridReg::~CGridReg()
{
}


//尝试创建一个报表对象，判断是否已经自注册
bool CGridReg::TestGridReportDLLRegister(void) //这个函数适用于VC
{
	bool Success = true;
	try
	{
		IGridppReportPtr pGridppReport;
		pGridppReport.CreateInstance(__uuidof(GridppReport));
		Success = (pGridppReport != NULL);
	}
	catch (...)
	{
		Success = false;
	}
	return Success;
}

//---------------------------------------------------------------------------
//调用COM DLL的DllRegisterServer函数进行自注册
bool CGridReg::RegisterComDLL(CString DLLFileName)
{
	HINSTANCE hLib = LoadLibrary(DLLFileName);
	if (hLib == (HINSTANCE)HINSTANCE_ERROR)
		return false; //获取注册函数DllRegisterServer地址
	FARPROC lpDllEntryPoint = GetProcAddress(hLib, "DllRegisterServer");
	//调用注册函数DllRegisterServer
	if (lpDllEntryPoint != NULL)
	{
		if (FAILED((*lpDllEntryPoint)()))
		{
			FreeLibrary(hLib);
			return false;
		};
		FreeLibrary(hLib);
	}
	return true;
}

//---------------------------------------------------------------------------
//调用COM DLL的DllRegisterServer函数进行自注册
bool CGridReg::UnRegisterComDLL(CString DLLFileName)
{
	HINSTANCE hLib = LoadLibrary(DLLFileName);
	if (hLib == (HINSTANCE)HINSTANCE_ERROR)
		return false; //获取注册函数DllRegisterServer地址
	FARPROC lpDllEntryPoint = GetProcAddress(hLib, "DllUnregisterServer");
	//调用注册函数DllRegisterServer
	if (lpDllEntryPoint != NULL)
	{
		if (FAILED((*lpDllEntryPoint)()))
		{
			FreeLibrary(hLib);
			return false;
		};
		FreeLibrary(hLib);
	}
	return true;
}

//---------------------------------------------------------------------------
//按需进行Grid++Report的自注册
bool CGridReg::RegisterGridReportDLL(void)
{
	bool Success = true;
	if (!TestGridReportDLLRegister())
	{

		//AnsiString AppPath = ExtractFilePath(Application->ExeName);
		//AnsiString EgnDLLFile = AppPath + "gregn6.dll";
		//AnsiString DesDLLFile = AppPath + "grdes6.dll";
		//TBD.. 这里应该根据实际改为绝对路径，并保持文件路径的正确性

		CString path = GetExePath();

		TCHAR EgnDLLFile[] = _T("gregn6x64.dll");
		TCHAR DesDLLFile[] = _T("grdes6x64.dll");
		Success = RegisterComDLL(path + EgnDLLFile);
		if (!Success)
		{
			MessageBox(NULL, _T("注册gregn6x64.dll失败"), _T(""), MB_OK);
		}
		else
		{
			Success = RegisterComDLL(path + DesDLLFile);
			if (!Success)
			{
				MessageBox(NULL, _T("注册grdes6x64.dll失败"), _T(""), MB_OK);

			}

		}
	}
	return Success;
}
//---------------------------------------------------------------------------
//按需进行Grid++Report的自注册
bool CGridReg::UnRegisterGridReportDLL(void)
{
	bool Success = true;
	if (TestGridReportDLLRegister())
	{

		//AnsiString AppPath = ExtractFilePath(Application->ExeName);
		//AnsiString EgnDLLFile = AppPath + "gregn6.dll";
		//AnsiString DesDLLFile = AppPath + "grdes6.dll";
		//TBD.. 这里应该根据实际改为绝对路径，并保持文件路径的正确性

		CString path = GetExePath();

		TCHAR EgnDLLFile[] = _T("gregn6x64.dll");
		TCHAR DesDLLFile[] = _T("grdes6x64.dll");
		Success = UnRegisterComDLL(path + EgnDLLFile);
		if (!Success)
		{
			MessageBox(NULL, _T("注册gregn6x64.dll失败"), _T(""), MB_OK);
		}
		else
		{
			Success = UnRegisterComDLL(path + DesDLLFile);
			if (!Success)
			{
				MessageBox(NULL, _T("注册grdes6x64.dll失败"), _T(""), MB_OK);

			}

		}
	}
	return Success;
}


CString CGridReg::GetExePath(void)
{

	TCHAR FileName[MAX_PATH];
	GetModuleFileName(NULL, FileName, MAX_PATH);
	(_tcsrchr(FileName, _T('\\')))[1] = 0;//删除文件名，只获得路径 字串
	return FileName;
}