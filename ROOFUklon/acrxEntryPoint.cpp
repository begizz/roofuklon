// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("")
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
AC_DECLARE_EXTENSION_MODULE(ROOFUklonDLL) ;

CDBReactor * pDBReactor;
CMenuReactor * pMReactor;
CDocReactor * pDocReactor;

void getMainPath()
{
	LPTSTR  strDLLPath1 = new TCHAR[_MAX_PATH];
	::GetModuleFileName((HINSTANCE)&__ImageBase, strDLLPath1, _MAX_PATH);

	main_path = strDLLPath1; main_path.MakeLower();
	main_path.Replace(_T("\\roofuklon.dll"),_T(""));

	//main_path = _T("C:\\Users\\Begiz\\Documents\\Visual Studio 2008\\Projects\\ROOFUklon");

	return;
}

void initSupportFiles()
{
	getMainPath();

	table_file=main_path+_T("\\data\\table.dwg"); 
	arrows_file=main_path+_T("\\data\\arrows.dwg"); 
	slice_file=main_path+("\\data\\srez.dwg"); 
	table_file_xls=main_path+_T("\\data\\table.xls");
	fasteners_file_xls=main_path+_T("\\data\\fasteners.xls");
	menu_file=main_path+_T("\\data\\roofuklon.cuix"); 
	menu_file.Replace(_T("\\"),_T("\\\\"));
	
};

void initMenu()
{
	ACHAR* MENUGROUP = _T("ROOUklon");
	if(acedIsMenuGroupLoaded(MENUGROUP)==Adesk::kTrue) return; 

	ACHAR szMencmd [512] ;  
	swprintf (szMencmd, _T("(command \"_.CUILOAD\" \"%s\")"), menu_file);   
	ads_queueexpr (szMencmd) ;

	CString full_version_english;
	CString full_version_russian;
	CString version;

	resbuf *rv;
	rv = acutNewRb(RTSTR);
	rv->resval.rstring = NULL;
	acedGetVar(_T("_VERNUM"),rv);

	CString sv(rv->resval.rstring);
	if(sv.Find(_T("D."))!=-1) 
	{
		version = _T("2010");
		full_version_english = _T("R18.0\\ACAD-8001:409");
		full_version_russian = _T("R18.0\\ACAD-8001:419");
	}
	if(sv.Find(_T("E."))!=-1) 
	{
		version = _T("2011");
		full_version_english = _T("R18.1\\ACAD-9001:409");
		full_version_russian = _T("R18.1\\ACAD-9001:419");
	}
	if(sv.Find(_T("F."))!=-1) 
	{
		version = _T("2012");
		full_version_english = _T("R18.2\\ACAD-A001:409");
		full_version_russian = _T("R18.2\\ACAD-A001:419");
	}
	if(sv.Find(_T("G."))!=-1) 
	{
		version = _T("2013");
		full_version_english = _T("R19.0\\ACAD-B001:409");
		full_version_russian = _T("R19.0\\ACAD-B001:419");
	}

	CString val1 = _T("show left 0 0");

	HKEY keyHandle;

	if (RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Autodesk\\AutoCAD\\")+full_version_english+_T("\\Profiles\\<<Unnamed Profile>>\\Toolbars"),0,KEY_SET_VALUE, &keyHandle) == ERROR_SUCCESS)
	{
		if(RegSetValueEx(keyHandle,_T("ROOFUKLON.Toolbar1"),NULL,REG_SZ,(LPBYTE)val1.GetBuffer(),val1.GetLength()*2+1)!=ERROR_SUCCESS)
		{
			acutPrintf(_T("Error accessing registry"));
		}
		RegCloseKey(keyHandle);
	}

	if (RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Autodesk\\AutoCAD\\")+full_version_russian+_T("\\Profiles\\<<Unnamed Profile>>\\Toolbars"),0,KEY_SET_VALUE, &keyHandle) == ERROR_SUCCESS)
	{
		if(RegSetValueEx(keyHandle,_T("ROOFUKLON.Toolbar1"),NULL,REG_SZ,(LPBYTE)val1.GetBuffer(),val1.GetLength()*2+1)!=ERROR_SUCCESS)
		{
			acutPrintf(_T("Error accessing registry"));
		}
		RegCloseKey(keyHandle);
	}
}

void initPattern()
{
	const TCHAR* loc;
	acdbHostApplicationServices()->getLocalRootFolder(loc);

	CString loc_path(loc);loc_path.Append(_T("support\\acadiso.pat"));

	if(loc_path.Find(_T("Local Settings"))>0) loc_path.Replace(_T("Local Settings\\"),_T(""));
	else loc_path.Replace(_T("Local"),_T("Roaming"));

	CFile fl;
	fl.Open(loc_path,CFile::OpenFlags::modeReadWrite | CFile::typeText);

	UINT nBytes = (UINT)fl.GetLength()+1; 
	int nChars = nBytes / sizeof(char);

	char p[50000];

	nBytes = fl.Read(p, nBytes); 

	if (strstr(p,"ROCKWOOL")==NULL)
	{
		char out_patt[74];
		strcpy(out_patt,"*ROCKWOOL_OU6, ROCKWOOL ROOFUklon\r\n0, 0, 0, 0, 1000 \r\n90, 0, 0, 0, 600 \r\n");
		fl.Write(out_patt,strlen(out_patt));

		strcpy(out_patt,"*ROCKWOOL_KU6, ROCKWOOL ROOFUklon\r\n0, 0, 0, 0, 1000 \r\n90, 0, 0, 0, 600 \r\n");
		fl.Write(out_patt,strlen(out_patt));

		strcpy(out_patt,"*ROCKWOOL_KU3, ROCKWOOL ROOFUklon\r\n0, 0, 0, 0, 1000 \r\n90, 0, 0, 0, 300 \r\n");
		fl.Write(out_patt,strlen(out_patt));

		strcpy(out_patt,"*ROCKWOOL_KU2, ROCKWOOL ROOFUklon\r\n0, 0, 0, 0, 1000 \r\n90, 0, 0, 0, 200 \r\n");
		fl.Write(out_patt,strlen(out_patt));
	}

	fl.Close();
}

void deInitPattern()
{
	const TCHAR* loc;
	acdbHostApplicationServices()->getLocalRootFolder(loc);

	CString loc_path(loc);loc_path.Append(_T("support\\acadiso.pat"));

	if(loc_path.Find(_T("Local Settings"))>0) loc_path.Replace(_T("Local Settings\\"),_T(""));
	else loc_path.Replace(_T("Local"),_T("Roaming"));

	CFile fl;
	fl.Open(loc_path,CFile::OpenFlags::modeReadWrite | CFile::typeText);

	UINT nBytes = (UINT)fl.GetLength()+1; 
	int nChars = nBytes / sizeof(char);

	char p[50000];

	nBytes = fl.Read(p, nBytes); 

	fl.Close();

	if (strstr(p,"ROCKWOOL")!=NULL)
	{
		std::string val = p;

		val = val.substr(0,val.find("*ROCKWOOL"));

		fl.Open(loc_path,CFile::modeCreate | CFile::modeWrite);

		fl.Write(val.c_str(), strlen(val.c_str()));

		fl.Close();
	}

}

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CROOFUklonApp : public AcRxArxApp {

public:
	CROOFUklonApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here
		// Save critical data pointers before running the constructors (see afxdllx.h for details)
		AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
		pModuleState->m_pClassInit = pModuleState->m_classList;
		pModuleState->m_pFactoryInit = pModuleState->m_factoryList;
		pModuleState->m_classList.m_pHead = NULL;
		pModuleState->m_factoryList.m_pHead = NULL;

		ROOFUklonDLL.AttachInstance (_hdllInstance) ;
		InitAcUiDLL () ;

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;

		pMReactor = new CMenuReactor();
		pDBReactor = new CDBReactor();
		pDocReactor = new CDocReactor();

		initSupportFiles();

		initPattern();
		initMenu();
		
		initTables();

		acutPrintf(_T("\nROCKWOOL ROOFUklon загружен...\n"));
		acutPrintf(_T("\nНаберите 'r_help' для полного списка доступных команд...\n"));

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here
		ROOFUklonDLL.DetachInstance () ;

		delete main_dlg;

		delete pMReactor;

		delete pDBReactor;

		delete pDocReactor;

		deInitPattern();

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kLoadDwgMsg(void *pkt) {

		AcRx::AppRetCode retCode = AcRxArxApp::On_kLoadDwgMsg (pkt);

		curDoc()->database()->addReactor(pDBReactor);

		curDoc()->database()->setLineWeightDisplay(TRUE);

		checkLayer(curDoc()->database());

		//initArrows();

		initBlocks();

		resbuf * get_tw_tb = NULL;
		getXdata(curDoc()->database()->namedObjectsDictionaryId(),SET_TW_TB,get_tw_tb);
		if(get_tw_tb!=NULL)
		{
			CString tw = get_tw_tb->resval.rstring; get_tw_tb= get_tw_tb->rbnext;
			CString tb = get_tw_tb->resval.rstring;

			acutRelRb(get_tw_tb);

			DocVars.docData().tb = tb;
			DocVars.docData().tw = _ttoi(tw);
		}

		resbuf * get_ku_tip = NULL;
		getXdata(curDoc()->database()->namedObjectsDictionaryId(),_T("KU_TIP"),get_ku_tip);
		if(get_ku_tip!=NULL)
		{
			int ku_tip = get_ku_tip->resval.rint; 

			acutRelRb(get_ku_tip);

			DocVars.docData().ku_tip = ku_tip;
		}

		resbuf * get_ku_fixed = NULL;
		getXdata(curDoc()->database()->namedObjectsDictionaryId(),_T("KU_FIXED"),get_ku_fixed);
		if(get_ku_fixed!=NULL)
		{
			int ku_fixed = get_ku_fixed->resval.rint; 

			acutRelRb(get_ku_fixed);

			DocVars.docData().ku_fixed = (bool)ku_fixed;
		}

		resbuf * get_ou_active = NULL;
		getXdata(curDoc()->database()->namedObjectsDictionaryId(),_T("OU_ACTIVE"),get_ou_active);
		if(get_ou_active!=NULL)
		{
			int ou_active = get_ou_active->resval.rint; 

			acutRelRb(get_ou_active);

			DocVars.docData().ou_active = (bool)ou_active;
		}

		return (retCode);
	}

	virtual void RegisterServerComponents () {
	}


	// ----- ROOFUklon._ru command
	static void ROOFUklon_ru(void)
	{
		if(main_dlg==NULL)
		{
			main_dlg = new CMainDlg();
			main_dlg->Create(IDD_MAINDLG);
		}
		main_dlg->ShowWindow(SW_SHOW);
	}

	static void ROOFUklon_endv(void)
	{
		acDocManager->lockDocument(curDoc());
		getEndova();
		acDocManager->unlockDocument(curDoc());
	}

	static void ROOFUklon_kon(void)
	{
		acDocManager->lockDocument(curDoc());
		getKonek();
		acDocManager->unlockDocument(curDoc());
	}

	static void ROOFUklon_ou(void)
	{
		acDocManager->lockDocument(curDoc());
		getOU();
		acDocManager->unlockDocument(curDoc());
	}

	static void ROOFUklon_ku5(void)
	{
		acDocManager->lockDocument(curDoc());
		getKU(KU05);
		acDocManager->unlockDocument(curDoc());
	}
	static void ROOFUklon_ku1(void)
	{
		acDocManager->lockDocument(curDoc());
		getKU(KU1);
		acDocManager->unlockDocument(curDoc());
	}

	static void ROOFUklon_ku1pe(void)
	{
		acDocManager->lockDocument(curDoc());
		getKU(KU1PE);
		acDocManager->unlockDocument(curDoc());
	}

	static void ROOFUklon_ku2(void)
	{
		acDocManager->lockDocument(curDoc());
		getKU(KU2);
		acDocManager->unlockDocument(curDoc());
	}

	static void ROOFUklon_spec(void)
	{
		acDocManager->lockDocument(curDoc());
		addSpecs();
		acDocManager->unlockDocument(curDoc());
	}

	static void ROOFUklon_pspec(void)
	{
		acDocManager->lockDocument(curDoc());
		getSpecs();
		acDocManager->unlockDocument(curDoc());
	}

	static void ROOFUklon_sbros(void)
	{
		acDocManager->lockDocument(curDoc());
		resetDrw();
		acDocManager->unlockDocument(curDoc());
	}

	static void ROOFUklon_vraz(void)
	{
		acDocManager->lockDocument(curDoc());
		addSlise();
		acDocManager->unlockDocument(curDoc());
	}

	static void ROOFUklon_r_export(void)
	{
		//exportExcel();
	}

	static void ROOFUklon_r_help(void)
	{
		acutPrintf(_T("\nКоманда : ру(ru) - ROCKWOOL ROOFUklon\n"));
		acutPrintf(_T("\nКоманда : оу(ou) - Основной уклон\n"));
		acutPrintf(_T("\nКоманда : ку5(ku5) - Контруклон 0,5\n"));
		acutPrintf(_T("\nКоманда : ку1(ku1) - Контруклон 1\n"));
		acutPrintf(_T("\nКоманда : ку1пе(ku1pe) - Контруклон 1 (п.е.)\n"));
		acutPrintf(_T("\nКоманда : ку2(ku2) - Контруклон 2\n"));
		acutPrintf(_T("\nКоманда : спец(spec) - Добавить спецификацию\n"));
		acutPrintf(_T("\nКоманда : сброс(sbros) - Сбросить все\n"));
		acutPrintf(_T("\nКоманда : враз(vraz) - Вставить Разрезы\n"));
		acutPrintf(_T("\nКоманда : r_help - Помощь\n"));
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CROOFUklonApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _ru, _ру, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _endv, _ендв, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _kon, _кон, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _ou, _оу, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _ku5, _ку5, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _ku1, _ку1, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _ku1pe, _ку1пе, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _ku2, _ку2, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _spec, _спец, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _pspec, _пспец, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _sbros, _сброс, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _vraz, _враз, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _r_help, _r_help, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CROOFUklonApp, ROOFUklon, _r_export, _р_експорт, ACRX_CMD_TRANSPARENT, NULL)

