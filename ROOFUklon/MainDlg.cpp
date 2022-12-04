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
//----- MainDlg.cpp : Implementation of CMainDlg
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "MainDlg.h"

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CMainDlg, CAcUiDialog)

BEGIN_MESSAGE_MAP(CMainDlg, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	//ON_BN_CLICKED(IDC_UE_BUT, &CMainDlg::OnBnClickedUeBut)
	//ON_BN_CLICKED(IDC_UK_BUT, &CMainDlg::OnBnClickedUkBut)
	ON_BN_CLICKED(IDC_OU_BUT, &CMainDlg::OnBnClickedOuBut)
	ON_BN_CLICKED(IDC_OU_CHECK, &CMainDlg::OnBnClickedOuCheck)
	ON_BN_CLICKED(IDC_KU05_BUT, &CMainDlg::OnBnClickedKu05But)
	ON_BN_CLICKED(IDC_KU1_BUT, &CMainDlg::OnBnClickedKu1But)
	ON_BN_CLICKED(IDC_KU1PE_BUT, &CMainDlg::OnBnClickedKu1peBut)
	ON_BN_CLICKED(IDC_KU2_BUT, &CMainDlg::OnBnClickedKu2But)
	ON_BN_CLICKED(IDC_RESET_BUT, &CMainDlg::OnBnClickedResetBut)
	ON_BN_CLICKED(IDC_EDIT_SPEC_BUT, &CMainDlg::OnBnClickedEditSpecBut)
	ON_BN_CLICKED(IDC_ADD_SPEC_BUT, &CMainDlg::OnBnClickedAddSpecBut)
	ON_BN_CLICKED(IDC_ADD_SLICE_BUT, &CMainDlg::OnBnClickedAddSliceBut)
	ON_BN_CLICKED(IDC_KU6_CHECK, &CMainDlg::OnBnClickedKu6Check)
	ON_BN_CLICKED(IDC_KU3_CHECK, &CMainDlg::OnBnClickedKu3Check)
	ON_BN_CLICKED(IDC_KU2_CHECK, &CMainDlg::OnBnClickedKu2Check)
	ON_BN_CLICKED(IDC_EXPORT_SPEC_BUT, &CMainDlg::OnBnClickedExportSpecBut)
	ON_EN_CHANGE(IDC_TW, &CMainDlg::OnEnChangeTw)
	ON_CBN_SELCHANGE(IDC_TB, &CMainDlg::OnCbnSelchangeTb)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CMainDlg::CMainDlg (CWnd *pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CMainDlg::IDD, pParent, hInstance) {
}

//-----------------------------------------------------------------------------
void CMainDlg::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	DDX_Control(pDX, IDC_OU_CHECK, m_ou_check);
	DDX_Control(pDX, IDC_KU6_CHECK, m_ku6_check);
	DDX_Control(pDX, IDC_KU2_CHECK, m_ku2_check);
	DDX_Control(pDX, IDC_KU3_CHECK, m_ku3_check);
	DDX_Control(pDX, IDC_TW, m_tw);
	DDX_Control(pDX, IDC_TB, m_tb);
	DDX_Control(pDX, IDC_EXPORT_SPEC_BUT, m_export_spec_but);
	DDX_Control(pDX, IDC_KU05_BUT, m_ku05_but);
	DDX_Control(pDX, IDC_KU1_BUT, m_ku1_but);
	DDX_Control(pDX, IDC_KU1PE_BUT, m_ku1pe_but);
	DDX_Control(pDX, IDC_KU2_BUT, m_ku2_but);
}

//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CMainDlg::OnAcadKeepFocus (WPARAM, LPARAM) {
	return (TRUE) ;
}

BOOL CMainDlg::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	HBITMAP hBitmap; 

	//hBitmap = (HBITMAP)LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PNG1));
	m_ku1_but.SetImage(IDB_BITMAP1);

	//hBitmap = (HBITMAP)LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PNG2));
	m_ku1pe_but.SetImage(IDB_BITMAP2);

	//hBitmap = (HBITMAP)LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PNG3));
	m_ku2_but.SetImage(IDB_BITMAP3);

	//hBitmap = (HBITMAP)LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PNG4));
	m_ku05_but.SetImage(IDB_BITMAP4);

	initControls();

	return true;
}

void CMainDlg::initControls()
{
	m_ou_check.SetCheck(DocVars.docData().ou_active);

	switch(DocVars.docData().ku_tip)
	{
	case 2: m_ku6_check.SetCheck(TRUE);
			m_ku3_check.SetCheck(FALSE);
			m_ku2_check.SetCheck(FALSE); 
		break;
	case 3: m_ku6_check.SetCheck(FALSE);
			m_ku3_check.SetCheck(TRUE);
			m_ku2_check.SetCheck(FALSE);
		break;
	case 4: m_ku6_check.SetCheck(FALSE);
			m_ku3_check.SetCheck(FALSE);
			m_ku2_check.SetCheck(TRUE); 
		break;
	}

	if(DocVars.docData().ku_fixed)
	{
		m_ku6_check.EnableWindow(FALSE);
		m_ku3_check.EnableWindow(FALSE);
		m_ku2_check.EnableWindow(FALSE);
	}
	else 
	{
		m_ku6_check.EnableWindow(TRUE);
		m_ku3_check.EnableWindow(TRUE);
		m_ku2_check.EnableWindow(TRUE);
	}

	m_tb.SelectString(-1,DocVars.docData().tb);
	CString tw; tw.Format(_T("%d"),DocVars.docData().tw);
	m_tw.SetWindowText(tw);

	if(DocVars.docData().ou_active)	GetDlgItem(IDC_OU_BUT)->EnableWindow(TRUE);
	else GetDlgItem(IDC_OU_BUT)->EnableWindow(FALSE);
}

void CMainDlg::OnBnClickedUeBut()
{
	BeginEditorCommand();
	acDocManager->lockDocument(curDoc());
	getEndova();
	acDocManager->unlockDocument(curDoc());
	CompleteEditorCommand();
}

void CMainDlg::OnBnClickedUkBut()
{
	BeginEditorCommand();
	acDocManager->lockDocument(curDoc());
	getKonek();
	acDocManager->unlockDocument(curDoc());
	CompleteEditorCommand();
}

void CMainDlg::OnBnClickedOuBut()
{
	BeginEditorCommand();
	acDocManager->lockDocument(curDoc());
	getOU();
	acDocManager->unlockDocument(curDoc());
	CompleteEditorCommand();
}

void CMainDlg::OnBnClickedOuCheck()
{
	if(!m_ou_check.GetCheck()) 
	{
		GetDlgItem(IDC_OU_BUT)->EnableWindow(FALSE);
		DocVars.docData().ou_active = 0;

	}
	else 
	{
		GetDlgItem(IDC_OU_BUT)->EnableWindow(TRUE);
		DocVars.docData().ou_active = 1;
	}

	resbuf * tip = acutBuildList(RTSHORT,DocVars.docData().ou_active,RTNONE);
	acDocManager->lockDocument(curDoc());
	addXdata(curDoc()->database()->namedObjectsDictionaryId(),_T("OU_ACTIVE"),tip);
	acDocManager->unlockDocument(curDoc());
	acutRelRb(tip);
}

void CMainDlg::OnBnClickedKu05But()
{
	BeginEditorCommand();
	acDocManager->lockDocument(curDoc());
	getKU(KU05);
	acDocManager->unlockDocument(curDoc());
	CompleteEditorCommand();
}

void CMainDlg::OnBnClickedKu1But()
{
	BeginEditorCommand();
	acDocManager->lockDocument(curDoc());
	getKU(KU1);
	acDocManager->unlockDocument(curDoc());
	CompleteEditorCommand();
}

void CMainDlg::OnBnClickedKu1peBut()
{
	BeginEditorCommand();
	acDocManager->lockDocument(curDoc());
	getKU(KU1PE);
	acDocManager->unlockDocument(curDoc());
	CompleteEditorCommand();
}

void CMainDlg::OnBnClickedKu2But()
{
	BeginEditorCommand();
	acDocManager->lockDocument(curDoc());
	getKU(KU2);
	acDocManager->unlockDocument(curDoc());
	CompleteEditorCommand();
}

void CMainDlg::OnBnClickedResetBut()
{
	acDocManager->lockDocument(curDoc());
	resetDrw();
	initControls();
	acDocManager->unlockDocument(curDoc());
}

void CMainDlg::OnBnClickedEditSpecBut()
{
	acDocManager->lockDocument(curDoc());
	getSpecs();
	acDocManager->unlockDocument(curDoc());
}

void CMainDlg::OnBnClickedAddSpecBut()
{
	exportExcel(EXPORT_RAZUKLONKA);
	//BeginEditorCommand();
	//acDocManager->lockDocument(curDoc());
	//if(DocVars.docData().specs_table_id!=NULL) updateTable();
	//else 
	//{
	//	addSpecs();
	//	if(DocVars.docData().specs_table_id!=NULL)
	//	{
	//		GetDlgItem(IDC_ADD_SPEC_BUT)->SetWindowText(_T("Обновить спецификацию"));
	//	}
	//}
	//acDocManager->unlockDocument(curDoc());
	//CompleteEditorCommand();
}

void CMainDlg::OnBnClickedAddSliceBut()
{
	BeginEditorCommand();
	acDocManager->lockDocument(curDoc());
	addSlise();
	acDocManager->unlockDocument(curDoc());
	CompleteEditorCommand();
}

void CMainDlg::OnBnClickedKu6Check()
{
	DocVars.docData().ku_tip = 2;
	resbuf * tip = acutBuildList(RTSHORT,2,RTNONE);
	acDocManager->lockDocument(curDoc());
	addXdata(curDoc()->database()->namedObjectsDictionaryId(),_T("KU_TIP"),tip);
	acDocManager->unlockDocument(curDoc());
	acutRelRb(tip);
}

void CMainDlg::OnBnClickedKu3Check()
{
	DocVars.docData().ku_tip = 3;
	resbuf * tip = acutBuildList(RTSHORT,3,RTNONE);
	acDocManager->lockDocument(curDoc());
	addXdata(curDoc()->database()->namedObjectsDictionaryId(),_T("KU_TIP"),tip);
	acDocManager->unlockDocument(curDoc());
	acutRelRb(tip);
}

void CMainDlg::OnBnClickedKu2Check()
{
	DocVars.docData().ku_tip = 4;
	resbuf * tip = acutBuildList(RTSHORT,4,RTNONE);
	acDocManager->lockDocument(curDoc());
	addXdata(curDoc()->database()->namedObjectsDictionaryId(),_T("KU_TIP"),tip);
	acDocManager->unlockDocument(curDoc());
	acutRelRb(tip);
}

void CMainDlg::OnBnClickedExportSpecBut()
{
	exportExcel(EXPORT_KREPEZ);
}

void CMainDlg::OnEnChangeTw()
{
	CString val;
	m_tw.GetWindowText(val);

	if(val.GetLength()==0 || m_tb.GetCurSel()==-1 || _ttoi(val)<40) m_export_spec_but.EnableWindow(FALSE);
	else 
	{
		CString mat;
		m_tb.GetLBText(m_tb.GetCurSel(),mat);

		DocVars.docData().tw = _ttoi(val);
		DocVars.docData().tb = mat;

		m_export_spec_but.EnableWindow(TRUE);

		acDocManager->lockDocument(curDoc());

		resbuf * set_tw_tb = acutBuildList(RTSTR,val,RTSTR,mat,RTNONE);
		addXdata(curDoc()->database()->namedObjectsDictionaryId(),SET_TW_TB,set_tw_tb);
		acutRelRb(set_tw_tb);

		acDocManager->unlockDocument(curDoc());
	}
}

void CMainDlg::OnCbnSelchangeTb()
{
	CString val;
	m_tw.GetWindowText(val);

	if(val.GetLength()==0 || m_tb.GetCurSel()==-1 || _ttoi(val)<40) m_export_spec_but.EnableWindow(FALSE);
	else 
	{
		CString mat;
		m_tb.GetLBText(m_tb.GetCurSel(),mat);

		DocVars.docData().tw = _ttoi(val);
		DocVars.docData().tb = mat;

		m_export_spec_but.EnableWindow(TRUE);

		acDocManager->lockDocument(curDoc());

		resbuf * set_tw_tb = acutBuildList(RTSTR,val,RTSTR,mat,RTNONE);
		addXdata(curDoc()->database()->namedObjectsDictionaryId(),SET_TW_TB,set_tw_tb);
		acutRelRb(set_tw_tb);

		acDocManager->unlockDocument(curDoc());
	}
}

void CMainDlg::OnShowWindow(BOOL show_window,UINT nStatus)
{
	CAcUiDialog::OnShowWindow(show_window,nStatus);
	if(show_window)
	{
		initControls();
	}
}
