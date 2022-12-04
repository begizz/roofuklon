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
//----- MainDlg.h : Declaration of the CMainDlg
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "acui.h"
#include "afxwin.h"

//-----------------------------------------------------------------------------
class CMainDlg : public CAcUiDialog {
	DECLARE_DYNAMIC (CMainDlg)

public:
	CMainDlg (CWnd *pParent =NULL, HINSTANCE hInstance =NULL) ;

	enum { IDD = IDD_MAINDLG} ;

protected:
	virtual void DoDataExchange (CDataExchange *pDX) ;
	afx_msg LRESULT OnAcadKeepFocus (WPARAM, LPARAM) ;

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ou_check;
	CButton m_ku6_check;
	CButton m_ku2_check;

	BOOL OnInitDialog();
	void initControls();
	CButton m_ku3_check;
	afx_msg void OnBnClickedUeBut();
	afx_msg void OnBnClickedUkBut();
	afx_msg void OnBnClickedOuBut();
	afx_msg void OnBnClickedOuCheck();
	afx_msg void OnBnClickedKu05But();
	afx_msg void OnBnClickedKu1But();
	afx_msg void OnBnClickedKu1peBut();
	afx_msg void OnBnClickedKu2But();
	afx_msg void OnBnClickedResetBut();
	afx_msg void OnBnClickedEditSpecBut();
	afx_msg void OnBnClickedAddSpecBut();
	afx_msg void OnBnClickedAddSliceBut();
	afx_msg void OnBnClickedKu6Check();
	afx_msg void OnBnClickedKu3Check();
	afx_msg void OnBnClickedKu2Check();
	afx_msg void OnBnClickedExportSpecBut();
	CEdit m_tw;
	CComboBox m_tb;
	afx_msg void OnEnChangeTw();
	afx_msg void OnCbnSelchangeTb();
	CButton m_export_spec_but;
	void OnShowWindow(BOOL show_window,UINT nStatus);

	CMFCButton  m_ku05_but;
	CMFCButton  m_ku1_but;
	CMFCButton  m_ku1pe_but;
	CMFCButton  m_ku2_but;
} ;
