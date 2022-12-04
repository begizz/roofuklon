// SpecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpecDlg.h"


// CSpecDlg dialog

IMPLEMENT_DYNAMIC(CSpecDlg, CDialog)

CSpecDlg::CSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpecDlg::IDD, pParent)
{
	
}

CSpecDlg::~CSpecDlg()
{
}

void CSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_EDIT2, edit2);
	DDX_Control(pDX, IDC_EDIT3, edit3);
	DDX_Control(pDX, IDC_EDIT4, edit4);
	DDX_Control(pDX, IDC_EDIT5, edit5);
	DDX_Control(pDX, IDC_EDIT6, edit6);
	DDX_Control(pDX, IDC_EDIT7, edit7);
	DDX_Control(pDX, IDC_EDIT8, edit8);
	DDX_Control(pDX, IDC_EDIT9, edit9);
	DDX_Control(pDX, IDC_EDIT10, edit10);
	DDX_Control(pDX, IDC_EDIT11, edit11);
	DDX_Control(pDX, IDC_EDIT12, edit12);
	DDX_Control(pDX, IDC_EDIT13, edit13);
	DDX_Control(pDX, IDC_EDIT14, edit14);
	DDX_Control(pDX, IDC_EDIT15, edit15);
	DDX_Control(pDX, IDC_EDIT16, edit16);
	DDX_Control(pDX, IDC_EDIT17, edit17);
	DDX_Control(pDX, IDC_EDIT18, edit18);
	DDX_Control(pDX, IDC_EDIT19, edit19);
	DDX_Control(pDX, IDC_EDIT20, edit20);
	DDX_Control(pDX, IDC_EDIT21, edit21);
	DDX_Control(pDX, IDC_EDIT22, edit22);
	DDX_Control(pDX, IDC_EDIT23, edit23);
	DDX_Control(pDX, IDC_EDIT24, edit24);
	DDX_Control(pDX, IDC_EDIT25, edit25);
	DDX_Control(pDX, IDC_EDIT26, edit26);
	DDX_Control(pDX, IDC_EDIT27, edit27);
	DDX_Control(pDX, IDC_EDIT28, edit28);
	DDX_Control(pDX, IDC_EDIT29, edit29);
	DDX_Control(pDX, IDC_EDIT30, edit30);
	DDX_Control(pDX, IDC_EDIT31, edit31);
	DDX_Control(pDX, IDC_EDIT32, edit32);
	DDX_Control(pDX, IDC_EDIT33, edit33);
	DDX_Control(pDX, IDC_EDIT34, edit34);
	DDX_Control(pDX, IDC_EDIT35, edit35);
	DDX_Control(pDX, IDC_EDIT36, edit36);
	DDX_Control(pDX, IDC_EDIT37, edit37);
	DDX_Control(pDX, IDC_EDIT38, edit38);
	DDX_Control(pDX, IDC_EDIT39, edit39);
	DDX_Control(pDX, IDC_EDIT40, edit40);
	DDX_Control(pDX, IDC_EDIT41, edit41);
	DDX_Control(pDX, IDC_EDIT42, edit42);
	DDX_Control(pDX, IDC_EDIT43, edit43);
	DDX_Control(pDX, IDC_EDIT44, edit44);
	DDX_Control(pDX, IDC_EDIT45, edit45);
	DDX_Control(pDX, IDC_EDIT46, edit46);
	DDX_Control(pDX, IDC_EDIT47, edit47);
	DDX_Control(pDX, IDC_EDIT48, edit48);
	DDX_Control(pDX, IDC_EDIT49, edit49);
	DDX_Control(pDX, IDC_EDIT50, edit50);
	DDX_Control(pDX, IDC_EDIT51, edit51);
}


BEGIN_MESSAGE_MAP(CSpecDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSpecDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CSpecDlg::initControls()
{
	table_data * dt = getTableData();
	if(dt==NULL) return;

	//1blok
	edit1.SetWindowText(dt->a[0]);
	edit6.SetWindowText(dt->a[1]);
	edit11.SetWindowText(dt->a[2]);

	edit2.SetWindowText(dt->b[0]);
	edit7.SetWindowText(dt->b[1]);
	edit12.SetWindowText(dt->b[2]);

	edit3.SetWindowText(dt->c[0]);
	edit8.SetWindowText(dt->c[1]);
	edit13.SetWindowText(dt->c[2]);

	edit4.SetWindowText(dt->d[0]);
	edit9.SetWindowText(dt->d[1]);
	edit14.SetWindowText(dt->d[2]);

	edit5.SetWindowText(dt->dobor[0]);
	edit10.SetWindowText(dt->dobor[1]);
	edit15.SetWindowText(dt->dobor[2]);

	//2blok
	edit16.SetWindowText(dt->ugol600[0]);
	edit21.SetWindowText(dt->ugol600[1]);
	edit26.SetWindowText(dt->ugol600[2]);

	edit17.SetWindowText(dt->uklon600[0]);
	edit22.SetWindowText(dt->uklon600[1]);
	edit27.SetWindowText(dt->uklon600[2]);

	edit18.SetWindowText(dt->dobor1600[0]);
	edit23.SetWindowText(dt->dobor1600[1]);
	edit28.SetWindowText(dt->dobor1600[2]);

	edit19.SetWindowText(dt->dobor2600[0]);
	edit24.SetWindowText(dt->dobor2600[1]);
	edit29.SetWindowText(dt->dobor2600[2]);

	//3blok
	edit20.SetWindowText(dt->ugol300[0]);
	edit32.SetWindowText(dt->ugol300[1]);
	edit36.SetWindowText(dt->ugol300[2]);

	edit21.SetWindowText(dt->uklon300[0]);
	edit33.SetWindowText(dt->uklon300[1]);
	edit37.SetWindowText(dt->uklon300[2]);

	edit22.SetWindowText(dt->dobor1300[0]);
	edit34.SetWindowText(dt->dobor1300[1]);
	edit38.SetWindowText(dt->dobor1300[2]);

	edit23.SetWindowText(dt->dobor2300[0]);
	edit35.SetWindowText(dt->dobor2300[1]);
	edit39.SetWindowText(dt->dobor2300[2]);

	//4blok
	edit40.SetWindowText(dt->ugol200[0]);
	edit44.SetWindowText(dt->ugol200[1]);
	edit48.SetWindowText(dt->ugol200[2]);

	edit41.SetWindowText(dt->uklon200[0]);
	edit45.SetWindowText(dt->uklon200[1]);
	edit49.SetWindowText(dt->uklon200[2]);

	edit42.SetWindowText(dt->dobor1200[0]);
	edit46.SetWindowText(dt->dobor1200[1]);
	edit50.SetWindowText(dt->dobor1200[2]);

	edit43.SetWindowText(dt->dobor1200[0]);
	edit47.SetWindowText(dt->dobor1200[1]);
	edit51.SetWindowText(dt->dobor1200[2]);

	delete dt;
}

void CSpecDlg::writeControls()
{
	Acad::ErrorStatus es;

	AcDbDatabase * pDwg = new AcDbDatabase(false,true);

	es = pDwg->readDwgFile(table_file);
	if(es!=Acad::eOk) return;

	AcDbBlockTable * pTable;
	es = pDwg->getBlockTable(pTable,AcDb::kForRead);
	if(es!=Acad::eOk) return;

	AcDbBlockTableRecord * pRec;
	es = pTable->getAt(ACDB_MODEL_SPACE,pRec,AcDb::kForRead);
	pTable->close();
	if(es!=Acad::eOk) return;

	AcDbBlockTableRecordIterator * pIter;
	es = pRec->newIterator(pIter);
	pRec->close();

	while (!pIter->done())
	{
		AcDbEntity * pEnt;
		pIter->getEntity(pEnt,AcDb::kForWrite);

		if(!pEnt->isKindOf(AcDbTable::desc())) 
		{
			pEnt->close();
			continue;
		}

		AcDbTable * pATable = (AcDbTable*)pEnt;

		CString val;

		//1blok
		GetDlgItem(IDC_EDIT1)->GetWindowText(val);pATable->setTextString(4,1,0,val);
		GetDlgItem(IDC_EDIT6)->GetWindowText(val);pATable->setTextString(4,2,0,val);
		GetDlgItem(IDC_EDIT11)->GetWindowText(val);pATable->setTextString(4,4,0,val);

		GetDlgItem(IDC_EDIT2)->GetWindowText(val);pATable->setTextString(5,1,0,val);
		GetDlgItem(IDC_EDIT7)->GetWindowText(val);pATable->setTextString(5,2,0,val);
		GetDlgItem(IDC_EDIT12)->GetWindowText(val);pATable->setTextString(5,4,0,val);

		GetDlgItem(IDC_EDIT3)->GetWindowText(val);pATable->setTextString(6,1,0,val);
		GetDlgItem(IDC_EDIT8)->GetWindowText(val);pATable->setTextString(6,2,0,val);
		GetDlgItem(IDC_EDIT13)->GetWindowText(val);pATable->setTextString(6,4,0,val);

		GetDlgItem(IDC_EDIT4)->GetWindowText(val);pATable->setTextString(7,1,0,val);
		GetDlgItem(IDC_EDIT9)->GetWindowText(val);pATable->setTextString(7,2,0,val);
		GetDlgItem(IDC_EDIT14)->GetWindowText(val);pATable->setTextString(7,4,0,val);

		GetDlgItem(IDC_EDIT5)->GetWindowText(val);pATable->setTextString(8,1,0,val);
		GetDlgItem(IDC_EDIT10)->GetWindowText(val);pATable->setTextString(8,2,0,val);
		GetDlgItem(IDC_EDIT15)->GetWindowText(val);pATable->setTextString(8,4,0,val);

		//2blok
		GetDlgItem(IDC_EDIT16)->GetWindowText(val);pATable->setTextString(10,1,0,val);
		GetDlgItem(IDC_EDIT21)->GetWindowText(val);pATable->setTextString(10,2,0,val);
		GetDlgItem(IDC_EDIT26)->GetWindowText(val);pATable->setTextString(10,4,0,val);

		GetDlgItem(IDC_EDIT17)->GetWindowText(val);pATable->setTextString(11,1,0,val);
		GetDlgItem(IDC_EDIT22)->GetWindowText(val);pATable->setTextString(11,2,0,val);
		GetDlgItem(IDC_EDIT27)->GetWindowText(val);pATable->setTextString(11,4,0,val);

		GetDlgItem(IDC_EDIT18)->GetWindowText(val);pATable->setTextString(12,1,0,val);
		GetDlgItem(IDC_EDIT23)->GetWindowText(val);pATable->setTextString(12,2,0,val);
		GetDlgItem(IDC_EDIT28)->GetWindowText(val);pATable->setTextString(12,4,0,val);

		GetDlgItem(IDC_EDIT19)->GetWindowText(val);pATable->setTextString(13,1,0,val);
		GetDlgItem(IDC_EDIT24)->GetWindowText(val);pATable->setTextString(13,2,0,val);
		GetDlgItem(IDC_EDIT29)->GetWindowText(val);pATable->setTextString(13,4,0,val);

		//3blok
		GetDlgItem(IDC_EDIT20)->GetWindowText(val);pATable->setTextString(15,1,0,val);
		GetDlgItem(IDC_EDIT32)->GetWindowText(val);pATable->setTextString(15,2,0,val);
		GetDlgItem(IDC_EDIT36)->GetWindowText(val);pATable->setTextString(15,4,0,val);

		GetDlgItem(IDC_EDIT21)->GetWindowText(val);pATable->setTextString(16,1,0,val);
		GetDlgItem(IDC_EDIT33)->GetWindowText(val);pATable->setTextString(16,2,0,val);
		GetDlgItem(IDC_EDIT37)->GetWindowText(val);pATable->setTextString(16,4,0,val);

		GetDlgItem(IDC_EDIT22)->GetWindowText(val);pATable->setTextString(17,1,0,val);
		GetDlgItem(IDC_EDIT34)->GetWindowText(val);pATable->setTextString(17,2,0,val);
		GetDlgItem(IDC_EDIT38)->GetWindowText(val);pATable->setTextString(17,4,0,val);

		GetDlgItem(IDC_EDIT23)->GetWindowText(val);pATable->setTextString(18,1,0,val);
		GetDlgItem(IDC_EDIT35)->GetWindowText(val);pATable->setTextString(18,2,0,val);
		GetDlgItem(IDC_EDIT39)->GetWindowText(val);pATable->setTextString(18,4,0,val);

		//4blok
		GetDlgItem(IDC_EDIT40)->GetWindowText(val);pATable->setTextString(20,1,0,val);
		GetDlgItem(IDC_EDIT44)->GetWindowText(val);pATable->setTextString(20,2,0,val);
		GetDlgItem(IDC_EDIT48)->GetWindowText(val);pATable->setTextString(20,4,0,val);

		GetDlgItem(IDC_EDIT41)->GetWindowText(val);pATable->setTextString(21,1,0,val);
		GetDlgItem(IDC_EDIT45)->GetWindowText(val);pATable->setTextString(21,2,0,val);
		GetDlgItem(IDC_EDIT49)->GetWindowText(val);pATable->setTextString(21,4,0,val);

		GetDlgItem(IDC_EDIT42)->GetWindowText(val);pATable->setTextString(22,1,0,val);
		GetDlgItem(IDC_EDIT46)->GetWindowText(val);pATable->setTextString(22,2,0,val);
		GetDlgItem(IDC_EDIT50)->GetWindowText(val);pATable->setTextString(22,4,0,val);

		GetDlgItem(IDC_EDIT43)->GetWindowText(val);pATable->setTextString(23,1,0,val);
		GetDlgItem(IDC_EDIT47)->GetWindowText(val);pATable->setTextString(23,2,0,val);
		GetDlgItem(IDC_EDIT51)->GetWindowText(val);pATable->setTextString(23,4,0,val);

		pATable->close();
		pIter->step();
	}
	delete pIter;

	pDwg->saveAs(table_file);
	delete pDwg;
}

BOOL CSpecDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	initControls();

	return TRUE;
}

// CSpecDlg message handlers

void CSpecDlg::OnBnClickedOk()
{
	writeControls();

	OnOK();
}
