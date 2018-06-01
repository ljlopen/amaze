#pragma once
class CGridReg
{
public:
	CGridReg();
	~CGridReg();

	//尝试创建一个报表对象，判断是否已经自注册
	static bool TestGridReportDLLRegister(void);


	//---------------------------------------------------------------------------
	//调用COM DLL的DllRegisterServer函数进行自注册
	static bool RegisterComDLL(CString DLLFileName);


	bool UnRegisterComDLL(CString DLLFileName);
	bool UnRegisterGridReportDLL(void);

	//---------------------------------------------------------------------------
	//按需进行Grid++Report的自注册
	static bool RegisterGridReportDLL(void);



	static CString GetExePath(void);

};

