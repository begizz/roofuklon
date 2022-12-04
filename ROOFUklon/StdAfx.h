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
//- StdAfx.h : include file for standard system include files,
//-      or project specific include files that are used frequently,
//-      but are changed infrequently
//-----------------------------------------------------------------------------
#pragma once

#pragma pack (push, 8)
#pragma warning(disable: 4786 4996)
//#pragma warning(disable: 4098)

//-----------------------------------------------------------------------------
#define STRICT

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN			//- Exclude rarely-used stuff from Windows headers
#endif

//- Modify the following defines if you have to target a platform prior to the ones specified below.
//- Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER					//- Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0400			//- Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT			//- Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0400		//- Change this to the appropriate value to target Windows 2000 or later.
#endif						

#ifndef _WIN32_WINDOWS			//- Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410	//- Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE				//- Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0400		//- Change this to the appropriate value to target IE 5.0 or later.
#endif


//- ObjectARX and OMF headers needs this
#include <map>

//-----------------------------------------------------------------------------
#include <afxwin.h>				//- MFC core and standard components
#include <afxext.h>				//- MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>				//- MFC OLE classes
#include <afxodlgs.h>			//- MFC OLE dialog classes
#include <afxdisp.h>			//- MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>				//- MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>				//- MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>			//- MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>				//- MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//-----------------------------------------------------------------------------
#using <mscorlib.dll>
#using <System.dll>

#using <acdbmgd.dll>
#using <acmgd.dll>
#using <AcCui.dll>

#include <vcclr.h>

//-----------------------------------------------------------------------------
//- Include ObjectDBX/ObjectARX headers
//- Uncomment one of the following lines to bring a given library in your project.
//#define _BREP_SUPPORT_			//- Support for the BRep API
//#define _HLR_SUPPORT_				//- Support for the Hidden Line Removal API
//#define _AMODELER_SUPPORT_		//- Support for the AModeler API
//#define _ASE_SUPPORT_				//- Support for the ASI/ASE API
//#define _RENDER_SUPPORT_			//- Support for the AutoCAD Render API
//#define _ARX_CUSTOM_DRAG_N_DROP_	//- Support for the ObjectARX Drag'n Drop API
//#define _INC_LEAGACY_HEADERS_		//- Include legacy headers in this project
#include "arxHeaders.h"
#include <map>
#include <list>
#include <afxbutton.h>

#define OU_MAX	20000
#define KU_MAX	20000

#define ROOFUklon_layer _T("ROOFUklon")

#define TEXT_NR _T("TEXT_NR")
#define UTYPE   _T("UTYPE")
#define SET_TW_TB _T("SET_TW_TB")

#define KU_MIN	1000

#define KU05	0
#define KU1		1
#define KU1PE	2
#define KU2		3
#define OU		4

#define SCALE_SLICE 20

#define EXPORT_RAZUKLONKA 1
#define EXPORT_KREPEZ 2

#define RAD 0.0174532925
#define pi 3.14159265


//-----------------------------------------------------------------------------
#include "DataTypes.h"
#include "DocData.h" //- Your document specific data class holder
#include "ExcelFormat.h"
#include "resource.h"
#include "CMenuReactor.h"
#include "CDBReactor.h"
#include "CDocReactor.h"

#include "MainDlg.h"
#include "SpecDlg.h"

//- Declare it as an extern here so that it becomes available in all modules
extern AcApDataManager<CDocData> DocVars ;
extern CMainDlg * main_dlg;
extern CString table_file;
extern CString arrows_file;
extern CString slice_file;
extern CString main_path;
extern CString table_file_xls;
extern CString fasteners_file_xls;
extern CString menu_file;

extern std::map<int,ou_unit> ou_table;
extern std::map<int,ku_unit> ku_table;

void checkLayer(AcDbDatabase * pDwg);
AcDbObjectId addToDataBase(AcDbDatabase * pDwg = curDoc()->database(),AcDbEntity * pEnt = NULL);

void initTables();
void getEndova();
void getKonek();
void getOU();
void getKU(int tip);
void getSpecs();
void addSpecs();
void resetDrw();
void addSlise();
void updateTable();
void calcData(AcDbObjectId oId, int l, int w, int tip, bool add_val);
void resetDocVars();
void initArrows();
void initSlice();
void addArrows(AcGePoint3d pt);
void exportExcel(int ext_type);
void getTable();
void initBlocks();

Acad::ErrorStatus getXdata(AcDbObjectId oId, CString key, resbuf *& data);
Acad::ErrorStatus addXdata(AcDbObjectId oId, CString key, resbuf * data);

void addText(AcDbObjectId parent_id, AcGePoint3d base_point, int clr, int tip);

void razuklonka();
void krepez();

void removeData(AcDbObjectId oId);

table_data * getTableData();

#pragma pack (pop)

