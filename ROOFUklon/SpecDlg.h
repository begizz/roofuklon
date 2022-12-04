#pragma once
#include "afxwin.h"


// CSpecDlg dialog

class CSpecDlg : public CDialog
{
	DECLARE_DYNAMIC(CSpecDlg)

public:
	CSpecDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSpecDlg();

// Dialog Data
	enum { IDD = IDD_SPECS };

	BOOL OnInitDialog();
	void initControls();
	void writeControls();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit edit1;
	CEdit edit2;
	CEdit edit3;
	CEdit edit4;
	CEdit edit5;
	CEdit edit6;
	CEdit edit7;
	CEdit edit8;
	CEdit edit9;
	CEdit edit10;
	CEdit edit11;
	CEdit edit12;
	CEdit edit13;
	CEdit edit14;
	CEdit edit15;
	CEdit edit16;
	CEdit edit17;
	CEdit edit18;
	CEdit edit19;
	CEdit edit20;
	CEdit edit21;
	CEdit edit22;
	CEdit edit23;
	CEdit edit24;
	CEdit edit25;
	CEdit edit26;
	CEdit edit27;
	CEdit edit28;
	CEdit edit29;
	CEdit edit30;
	CEdit edit31;
	CEdit edit32;
	CEdit edit33;
	CEdit edit34;
	CEdit edit35;
	CEdit edit36;
	CEdit edit37;
	CEdit edit38;
	CEdit edit39;
	CEdit edit40;
	CEdit edit41;
	CEdit edit42;
	CEdit edit43;
	CEdit edit44;
	CEdit edit45;
	CEdit edit46;
	CEdit edit47;
	CEdit edit48;
	CEdit edit49;
	CEdit edit50;
	CEdit edit51;
};
