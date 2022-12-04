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
//------ StdAfx.cpp : source file that includes just the standard includes
//------  StdAfx.pch will be the pre-compiled header
//------  StdAfx.obj will contain the pre-compiled type information
//-----------------------------------------------------------------------------
#include "StdAfx.h"

using namespace ExcelFormat;

CMainDlg * main_dlg;

CString table_file;
CString arrows_file;
CString slice_file;
CString table_file_xls;
CString fasteners_file_xls;
CString menu_file;

std::map<int,ou_unit> ou_table;
std::map<int,ku_unit> ku_table;

CString main_path;

void calcData(AcDbObjectId oId, int l, int w, int tip, bool add_val)
{
	acDocManager->lockDocument(curDoc());
	int sign = 0;

	if(add_val) sign = 1;
	else sign = -1;

	switch(tip)
	{
	case OU:
		{
			DocVars.docData().a+=ou_table[l].a*w*sign;
			DocVars.docData().b+=ou_table[l].b*w*sign;
			DocVars.docData().c+=ou_table[l].c*w*sign;
			DocVars.docData().d+=ou_table[l].d*w*sign;
			DocVars.docData().dobor+=ou_table[l].dobor*w*sign;

			ou_data val;
			val.oId = oId;
			val.length = l;
			val.width = w*0.6;
			if(add_val)DocVars.docData().ou_list.push_back(val);

			resbuf * block_data = acutBuildList(RTSHORT,tip,RTSHORT,l,RTSHORT,w,RTNONE);
			addXdata(oId,UTYPE,block_data);
			acutRelRb(block_data);

			break;
		}
	case KU05:
		{
			DocVars.docData().ugol+=ku_table[l].ugol*sign;
			DocVars.docData().uklon+=ku_table[l].uklon*sign;
			DocVars.docData().dobor1+=ku_table[l].dobor1*sign;
			DocVars.docData().dobor2+=ku_table[l].dobor2*sign;

			ku_data val;
			val.oId = oId;
			val.length = l;
			val.cnt = /*ku_table[l].ugol+ku_table[l].uklon+ku_table[l].dobor1+ku_table[l].dobor2*/1;
			if(add_val)DocVars.docData().ku_list.push_back(val);

			resbuf * block_data = acutBuildList(RTSHORT,tip,RTSHORT,l,RTSHORT,0,RTNONE);
			addXdata(oId,UTYPE,block_data);
			acutRelRb(block_data);

			break;
		}
	case KU1:
		{
			DocVars.docData().ugol+=ku_table[l].ugol*2*sign;
			DocVars.docData().uklon+=ku_table[l].uklon*2*sign;
			DocVars.docData().dobor1+=ku_table[l].dobor1*2*sign;
			DocVars.docData().dobor2+=ku_table[l].dobor2*2*sign;

			ku_data val;
			val.oId = oId;
			val.length = l;
			val.cnt = /*(ku_table[l].ugol+ku_table[l].uklon+ku_table[l].dobor1+ku_table[l].dobor2)**/2;
			if(add_val)DocVars.docData().ku_list.push_back(val);

			resbuf * block_data = acutBuildList(RTSHORT,tip,RTSHORT,l,RTSHORT,0,RTNONE);
			addXdata(oId,UTYPE,block_data);
			acutRelRb(block_data);

			break;
		}
	case KU1PE:
		{
			DocVars.docData().ugol+=ku_table[l].ugol*2*sign;
			DocVars.docData().uklon+=ku_table[l].uklon*2*sign;
			DocVars.docData().dobor1+=ku_table[l].dobor1*2*sign;
			DocVars.docData().dobor2+=ku_table[l].dobor2*2*sign;

			ku_data val;
			val.oId = oId;
			val.length = l;
			val.cnt = /*(ku_table[l].ugol+ku_table[l].uklon+ku_table[l].dobor1+ku_table[l].dobor2)**/2;
			if(add_val)DocVars.docData().ku_list.push_back(val);

			resbuf * block_data = acutBuildList(RTSHORT,tip,RTSHORT,l,RTSHORT,0,RTNONE);
			addXdata(oId,UTYPE,block_data);
			acutRelRb(block_data);

			break;
		}
	case KU2:
		{
			DocVars.docData().ugol+=ku_table[l].ugol*4*sign;
			DocVars.docData().uklon+=ku_table[l].uklon*4*sign;
			DocVars.docData().dobor1+=ku_table[l].dobor1*4*sign;
			DocVars.docData().dobor2+=ku_table[l].dobor2*4*sign;

			ku_data val;
			val.oId = oId;
			val.length = l;
			val.cnt = /*(ku_table[l].ugol+ku_table[l].uklon+ku_table[l].dobor1+ku_table[l].dobor2)**/4;
			if(add_val)DocVars.docData().ku_list.push_back(val);

			resbuf * block_data = acutBuildList(RTSHORT,tip,RTSHORT,l,RTSHORT,0,RTNONE);
			addXdata(oId,UTYPE,block_data);
			acutRelRb(block_data);

			break;
		}
	}
	acDocManager->unlockDocument(curDoc());
}

void initTables()
{
	ou_table[1].a = 1;ou_table[1].b = 0;ou_table[1].c = 0;ou_table[1].d = 0;ou_table[1].dobor = 0;
	ou_table[2].a = 1;ou_table[2].b = 1;ou_table[2].c = 0;ou_table[2].d = 0;ou_table[2].dobor = 0; 
	ou_table[3].a = 1;ou_table[3].b = 1;ou_table[3].c = 1;ou_table[3].d = 0;ou_table[3].dobor = 0; 
	ou_table[4].a = 1;ou_table[4].b = 1;ou_table[4].c = 1;ou_table[4].d = 1;ou_table[4].dobor = 0; 
	ou_table[5].a = 2;ou_table[5].b = 1;ou_table[5].c = 1;ou_table[5].d = 1;ou_table[5].dobor = 1; 
	ou_table[6].a = 2;ou_table[6].b = 2;ou_table[6].c = 1;ou_table[6].d = 1;ou_table[6].dobor = 2; 
	ou_table[7].a = 2;ou_table[7].b = 2;ou_table[7].c = 2;ou_table[7].d = 1;ou_table[7].dobor = 3; 
	ou_table[8].a = 2;ou_table[8].b = 2;ou_table[8].c = 2;ou_table[8].d = 2;ou_table[8].dobor = 4; 
	ou_table[9].a = 3;ou_table[9].b = 2;ou_table[9].c = 2;ou_table[9].d = 2;ou_table[9].dobor = 6; 
	ou_table[10].a = 3;ou_table[10].b = 3;ou_table[10].c = 2;ou_table[10].d = 2;ou_table[10].dobor = 8; 
	ou_table[11].a = 3;ou_table[11].b = 3;ou_table[11].c = 3;ou_table[11].d = 2;ou_table[11].dobor = 10; 
	ou_table[12].a = 3;ou_table[12].b = 3;ou_table[12].c = 3;ou_table[12].d = 3;ou_table[12].dobor = 12; 
	ou_table[13].a = 4;ou_table[13].b = 3;ou_table[13].c = 3;ou_table[13].d = 3;ou_table[13].dobor = 15; 
	ou_table[14].a = 4;ou_table[14].b = 4;ou_table[14].c = 3;ou_table[14].d = 3;ou_table[14].dobor = 18; 
	ou_table[15].a = 4;ou_table[15].b = 4;ou_table[15].c = 4;ou_table[15].d = 3;ou_table[15].dobor = 21; 
	ou_table[16].a = 4;ou_table[16].b = 4;ou_table[16].c = 4;ou_table[16].d = 4;ou_table[16].dobor = 24;
	ou_table[17].a = 5;ou_table[17].b = 4;ou_table[17].c = 4;ou_table[17].d = 4;ou_table[17].dobor = 28; 
	ou_table[18].a = 5;ou_table[18].b = 5;ou_table[18].c = 4;ou_table[18].d = 4;ou_table[18].dobor = 32; 
	ou_table[19].a = 5;ou_table[19].b = 5;ou_table[19].c = 5;ou_table[19].d = 4;ou_table[19].dobor = 36; 
	ou_table[20].a = 5;ou_table[20].b = 5;ou_table[20].c = 5;ou_table[20].d = 5;ou_table[20].dobor = 40; 

	ku_table[1].ugol = 1; ku_table[1].uklon = 0; ku_table[1].dobor1 = 0; ku_table[1].dobor2 = 0;
	ku_table[2].ugol = 2; ku_table[2].uklon = 1; ku_table[2].dobor1 = 0; ku_table[2].dobor2 = 0;
	ku_table[3].ugol = 3; ku_table[3].uklon = 3; ku_table[3].dobor1 = 1; ku_table[3].dobor2 = 0;
	ku_table[4].ugol = 4; ku_table[4].uklon = 6; ku_table[4].dobor1 = 2; ku_table[4].dobor2 = 1;
	ku_table[5].ugol = 5; ku_table[5].uklon = 10; ku_table[5].dobor1 = 4; ku_table[5].dobor2 = 3;
	ku_table[6].ugol = 6; ku_table[6].uklon = 15; ku_table[6].dobor1 = 6; ku_table[6].dobor2 = 7;
	ku_table[7].ugol = 7; ku_table[7].uklon = 21; ku_table[7].dobor1 = 9; ku_table[7].dobor2 = 13;
	ku_table[8].ugol = 8; ku_table[8].uklon = 28; ku_table[8].dobor1 = 12; ku_table[8].dobor2 = 22;
	ku_table[9].ugol = 9; ku_table[9].uklon = 36; ku_table[9].dobor1 = 16; ku_table[9].dobor2 = 34;
	ku_table[10].ugol = 10; ku_table[10].uklon = 45; ku_table[10].dobor1 = 20; ku_table[10].dobor2 = 50;
	ku_table[11].ugol = 11; ku_table[11].uklon = 55; ku_table[11].dobor1 = 25; ku_table[11].dobor2 = 70;
	ku_table[12].ugol = 12; ku_table[12].uklon = 66; ku_table[12].dobor1 = 30; ku_table[12].dobor2 = 95;
	ku_table[13].ugol = 13; ku_table[13].uklon = 78; ku_table[13].dobor1 = 36; ku_table[13].dobor2 = 125;
	ku_table[14].ugol = 14; ku_table[14].uklon = 91; ku_table[14].dobor1 = 42; ku_table[14].dobor2 = 161;
	ku_table[15].ugol = 15; ku_table[15].uklon = 105; ku_table[15].dobor1 = 49; ku_table[15].dobor2 = 203;
	ku_table[16].ugol = 16; ku_table[16].uklon = 120; ku_table[16].dobor1 = 56; ku_table[16].dobor2 = 252;
	ku_table[17].ugol = 17; ku_table[17].uklon = 136; ku_table[17].dobor1 = 64; ku_table[17].dobor2 = 308;
	ku_table[18].ugol = 18; ku_table[18].uklon = 153; ku_table[18].dobor1 = 72; ku_table[18].dobor2 = 372;
	ku_table[19].ugol = 19; ku_table[19].uklon = 171; ku_table[19].dobor1 = 81; ku_table[19].dobor2 = 444;
	ku_table[20].ugol = 20; ku_table[20].uklon = 190; ku_table[20].dobor1 = 90; ku_table[20].dobor2 = 525;
}

void checkLayer(AcDbDatabase * pDwg)
{
	Acad::ErrorStatus es;
	AcDbLayerTable * pTable;
	AcDbLayerTableRecord * pRec;

	es = pDwg->getSymbolTable(pTable,AcDb::kForWrite);
	if(es!=Acad::eOk) return;

	if(!pTable->has(ROOFUklon_layer))
	{
		AcCmColor clr;
		clr.setColorIndex(7);

		pRec = new AcDbLayerTableRecord();
		pRec->setName(ROOFUklon_layer);
		pRec->setColor(clr);
		
		es = pTable->add(pRec);
		pRec->close();
	}
	pTable->close();
};

AcDbObjectId addToDataBase(AcDbDatabase * pDwg,AcDbEntity * pEnt)
{
	AcDbObjectId oId;
	Acad::ErrorStatus es;
	AcDbBlockTable * pTable;
	AcDbBlockTableRecord * pRec;
	es = pDwg->getBlockTable(pTable,AcDb::kForRead);
	if(es!=Acad::eOk) return NULL;

	es = pTable->getAt(ACDB_MODEL_SPACE,pRec,AcDb::kForWrite);
	if(es!=Acad::eOk) return NULL;
	pTable->close();

	es = pRec->appendAcDbEntity(oId,pEnt);
	pRec->close();

	return oId;
}

void getEndova()
{
	bool ortho_mode = curDoc()->database()->orthomode();
	curDoc()->database()->setOrthomode(TRUE);

	while(TRUE)
	{
		ads_point pt1,pt2;
		if(acedGetPoint(NULL,_T("\nУкажите 1 точку: \n"),pt1)!=RTNORM) return;
		if(acedGetPoint(pt1,_T("\nУкажите 2 точку: \n"),pt2)!=RTNORM) return;

		Acad::ErrorStatus es;
		AcDbObjectPointer<AcDbPolyline> pLine;
		pLine.create();
		pLine->addVertexAt(0,AcGePoint2d(pt1[X],pt1[Y]));
		pLine->addVertexAt(1,AcGePoint2d(pt2[X],pt2[Y]));

		double x1,x2;
		x1 = min(pt1[X],pt2[X])+2500;
		x2 = max(pt1[X],pt2[X]);

		while(x1<x2)
		{
			addArrows(AcGePoint3d(x1,pt1[Y],0.0));
			x1+=5000;
		}

		es = pLine->setColorIndex(5);
		es = pLine->setLayer(ROOFUklon_layer);
		es = pLine->setLineWeight(AcDb::LineWeight::kLnWt030);
		pLine->close();

		addToDataBase(curDoc()->database(),pLine);

		actrTransactionManager->flushGraphics();
		acedUpdateDisplay();
	}
	curDoc()->database()->setOrthomode(ortho_mode);
}

void getKonek()
{
	bool ortho_mode = curDoc()->database()->orthomode();
	curDoc()->database()->setOrthomode(TRUE);

	while(TRUE)
	{
		ads_point pt1,pt2;
		if(acedGetPoint(NULL,_T("\nУкажите 1 точку: \n"),pt1)!=RTNORM) return;
		if(acedGetPoint(pt1,_T("\nУкажите 2 точку: \n"),pt2)!=RTNORM) return;

		Acad::ErrorStatus es;
		AcDbObjectPointer<AcDbPolyline> pLine;
		pLine.create();
		pLine->addVertexAt(0,AcGePoint2d(pt1[X],pt1[Y]));
		pLine->addVertexAt(1,AcGePoint2d(pt2[X],pt2[Y]));

		es = pLine->setColorIndex(3);
		es = pLine->setLayer(ROOFUklon_layer);
		es = pLine->setLineWeight(AcDb::LineWeight::kLnWt030);
		pLine->close();

		addToDataBase(curDoc()->database(),pLine);

		actrTransactionManager->flushGraphics();
		acedUpdateDisplay();
	}
	curDoc()->database()->setOrthomode(ortho_mode);
}

//void getOU()
//{
//	if (!DocVars.docData().ou_active)
//	{
//		acutPrintf(_T("\nЕлемент ОУ откючен\n"));
//		return;
//	}
//
//	bool ortho_mode = curDoc()->database()->orthomode();
//	curDoc()->database()->setOrthomode(TRUE);
//
//	while(TRUE)
//	{
//		ads_name ename;
//		ads_point pt1,pt2,pt3;
//		AcDbObjectId oId;
//		AcGePoint2dArray pArray;
//		AcGeDoubleArray  bArray;
//
//		int len;
//		int wid;
//
//		double len_div;
//		double wid_div;
//
//		Acad::ErrorStatus es;
//		
//		if(acedGetPoint(NULL,_T("\nУкажите 1 точку: \n"),pt1)!=RTNORM) return;
//		if(acedGetPoint(pt1,_T("\nУкажите 2 точку: \n"),pt2)!=RTNORM) return;
//		if(acedGetPoint(pt2,_T("\nУкажите 3 точку: \n"),pt3)!=RTNORM) return;
//
//		int clr = 4;
//
//		int w = 0;
//		int h = 0;
//
//		if(pt1[Y]==pt2[Y])
//		{
//			len = abs(max(pt1[Y],pt3[Y])-min(pt1[Y],pt3[Y]));
//			wid = ceil(abs(pt1[X]-pt2[X])/600);
//
//			if(pt3[X]<pt1[X]) w = -1;
//			else w = 1;
//
//			if(pt3[Y]<pt1[Y]) h = -1;
//			else h = 1;
//
//			if(pt3[Y]==pt1[Y])
//			{
//				AfxMessageBox(_T("Точки лежат на одной линии!\nПроверьте настойки OSNAP"));
//				continue;
//			}
//
//		}
//
//		if(pt1[X]==pt2[X])
//		{
//			len = abs(max(pt1[X],pt3[X])-min(pt1[X],pt3[X]));
//			wid = ceil(abs(pt1[Y]-pt2[Y])/600);
//
//			if(pt3[Y]<pt1[Y]) w = -1;
//			else w = 1;
//
//			if(pt3[X]<pt1[X]) h = -1;
//			else h = 1;
//
//			if(pt3[X]==pt1[X])
//			{
//				AfxMessageBox(_T("Точки лежат на одной линии!\nПроверьте настойки OSNAP"));
//				continue;
//			}
//		}
//		
//		AcGePoint3d p1,p2;
//		p1.x=pt1[X];
//		p1.y=pt1[Y];
//
//		p2.x=pt2[X];
//		p2.y=pt2[Y];
//
//		if(p1.distanceTo(p2)>OU_MAX)
//		{
//			AfxMessageBox(_T("\nДлина Контруклона превышает допустимое значение.\nВнесите необходимые коррективы\n"));
//			acutPrintf(_T("\nДлина Основного Уклона превышает допустимое значение в 20м. Внесите необходимые коррективы\n"));
//			clr = 8;
//		}
//
//		if(pt1[Y]==pt2[Y])
//		{
//			wid_div = (ceil(abs(pt1[X]-pt2[X])/600)-abs(pt1[X]-pt2[X])/600)*600;
//			len_div = (ceil((double)len/1000)-(double)len/1000)*1000;
//		}
//
//		if(pt1[X]==pt2[X])
//		{
//			wid_div = (ceil(abs(pt1[Y]-pt2[Y])/600)-abs(pt1[Y]-pt2[Y])/600)*600;
//			len_div = (ceil((double)len/1000)-(double)len/1000)*1000;
//		}
//
//
//		
//
//		len = ceil((double)len/1000);
//
//		AcDbObjectPointer<AcDbPolyline> pLine;
//		pLine.create();
//
//		if(pt1[Y]==pt2[Y])
//		{
//			pLine->addVertexAt(0,AcGePoint2d(pt1[X],pt1[Y])); 
//			pLine->addVertexAt(1,AcGePoint2d(pt1[X],pt3[Y]+h*len_div)); 
//			pLine->addVertexAt(2,AcGePoint2d(pt3[X]+w*wid_div,pt3[Y]+h*len_div)); 
//			pLine->addVertexAt(3,AcGePoint2d(pt3[X]+w*wid_div,pt1[Y])); 
//
//			pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);
//			pArray.append(AcGePoint2d(pt1[X],pt3[Y]+h*len_div)); bArray.append(0.0);
//			pArray.append(AcGePoint2d(pt3[X]+w*wid_div,pt3[Y]+h*len_div)); bArray.append(0.0);
//			pArray.append(AcGePoint2d(pt3[X]+w*wid_div,pt1[Y])); bArray.append(0.0);
//			pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);
//		}
//
//		if(pt1[X]==pt2[X])
//		{
//			pLine->addVertexAt(0,AcGePoint2d(pt1[X],pt1[Y])); 
//			pLine->addVertexAt(1,AcGePoint2d(pt1[X],pt3[Y]+w*wid_div)); 
//			pLine->addVertexAt(2,AcGePoint2d(pt3[X]+h*len_div,pt3[Y]+w*wid_div)); 
//			pLine->addVertexAt(3,AcGePoint2d(pt3[X]+h*len_div,pt1[Y])); 
//
//			pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);
//			pArray.append(AcGePoint2d(pt1[X],pt3[Y]+w*wid_div)); bArray.append(0.0);
//			pArray.append(AcGePoint2d(pt3[X]+h*len_div,pt3[Y]+w*wid_div)); bArray.append(0.0);
//			pArray.append(AcGePoint2d(pt3[X]+h*len_div,pt1[Y])); bArray.append(0.0);
//			pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);
//		}
//		
//		
//
//		pLine->setClosed(TRUE);
//		pLine->setLayer(ROOFUklon_layer);
//		pLine->setColorIndex(clr);
//		pLine->close();
//
//		oId = addToDataBase(curDoc()->database(),pLine);
//
//		AcDbObjectPointer<AcDbHatch> pHatch;
//		pHatch.create();
//		pHatch->setOriginPoint(AcGePoint2d(pt1[X],pt1[Y]));
//		if(pt1[X]==pt2[X]) es = pHatch->setPatternAngle(90*RAD);
//		pHatch->setLayer(ROOFUklon_layer);
//		pHatch->setColorIndex(clr);
//
//		oId = addToDataBase(curDoc()->database(),pHatch);
//
//		es = pHatch->setPattern(AcDbHatch::HatchPatternType::kPreDefined,_T("ROCKWOOL_OU6"));
//		es = pHatch->setAssociative(TRUE);
//		es = pHatch->appendLoop(AcDbHatch::kExternal,pArray,bArray);
//		es = pHatch->evaluateHatch();
//				
//		pHatch->close();
//
//		actrTransactionManager->flushGraphics();
//		acedUpdateDisplay();
//		if(len!=0 && wid!=0) 
//		{
//			calcData(pHatch->objectId(),len,wid,OU,TRUE);
//			AcDbExtents ext;
//			pHatch->getGeomExtents(ext);
//			AcGePoint3d base_point((ext.minPoint().x+ext.maxPoint().x)/2,(ext.minPoint().y+ext.maxPoint().y)/2,0);
//			addText(pHatch->objectId(),base_point,clr,OU);
//		}
//	}
//
//	curDoc()->database()->setOrthomode(ortho_mode);
//
//}

void getOU()
{
	if (!DocVars.docData().ou_active)
	{
		acutPrintf(_T("\nЕлемент ОУ откючен\n"));
		return;
	}

	bool ortho_mode = curDoc()->database()->orthomode();
	curDoc()->database()->setOrthomode(TRUE);

	while(TRUE)
	{
		ads_name ename;
		ads_point pt1,pt2,pt3;
		AcDbObjectId oId;
		AcGePoint2dArray pArray;
		AcGeDoubleArray  bArray;

		double len;
		double wid;

		double len_div;
		double wid_div;

		Acad::ErrorStatus es;

		if(acedGetPoint(NULL,_T("\nУкажите 1 точку: \n"),pt1)!=RTNORM) break;
		if(acedGetPoint(pt1,_T("\nУкажите 2 точку: \n"),pt2)!=RTNORM) break;
		if(acedGetPoint(pt2,_T("\nУкажите 3 точку: \n"),pt3)!=RTNORM) break;

		int clr = 4;

		AcGePoint2d p1(pt1[X],pt1[Y]);
		AcGePoint2d p2(pt2[X],pt2[Y]);
		AcGePoint2d p3(pt3[X],pt3[Y]);

		//len = abs(pt1[Y]-pt2[Y]); 
		len = p2.distanceTo(p3);
		//wid = ceil(abs(pt1[X]-pt2[X])/600);
		wid = p1.distanceTo(p2);

		if(len>OU_MAX)
		{
			AfxMessageBox(_T("\nДлина Основного Уклона превышает допустимое значение в 20м.\nВнесите необходимые коррективы\n"));
			acutPrintf(_T("\nДлина Основного Уклона превышает допустимое значение в 20м. Внесите необходимые коррективы\n"));
			clr = 8;
		}

		double ang = 0;

		wid_div = (ceil(wid/600)-wid/600)*600;
		len_div = (ceil(len/1000)-len/1000)*1000;

		if(p1.x==p2.x)
		{
			double tmp = wid_div;
			wid_div = len_div;
			len_div = tmp;

			if(p1.y > p2.y) len_div*=-1;

			ang = 90 * (pi/180);

			if(p3.y==p2.y)
			{
				if(p3.x < p2.x) wid_div*=-1;
			}

			if(p3.x==p1.x)
			{
				AfxMessageBox(_T("Точки лежат на одной линии!\nПроверьте настойки OSNAP"));
				continue;
			}
		}
		else
		{
			if(p1.x > p2.x) wid_div*=-1;

			if(p3.x==p2.x)
			{
				if(p3.y < p2.y) len_div*=-1;
			}

			if(p3.y==p1.y)
			{
				AfxMessageBox(_T("Точки лежат на одной линии!\nПроверьте настойки OSNAP"));
				continue;
			}
		}

		len = ceil(len/1000);
		wid = ceil(wid/600);

		AcDbObjectPointer<AcDbPolyline> pLine;
		pLine.create();
		pLine->addVertexAt(0,AcGePoint2d(pt1[X],pt1[Y])); 
		pLine->addVertexAt(1,AcGePoint2d(pt1[X],pt3[Y]+len_div)); 
		pLine->addVertexAt(2,AcGePoint2d(pt3[X]+wid_div,pt3[Y]+len_div)); 
		pLine->addVertexAt(3,AcGePoint2d(pt3[X]+wid_div,pt1[Y])); 

		pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);
		pArray.append(AcGePoint2d(pt1[X],pt3[Y]+len_div)); bArray.append(0.0);
		pArray.append(AcGePoint2d(pt3[X]+wid_div,pt3[Y]+len_div)); bArray.append(0.0);
		pArray.append(AcGePoint2d(pt3[X]+wid_div,pt1[Y])); bArray.append(0.0);
		pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);

		pLine->setClosed(TRUE);
		pLine->setLayer(ROOFUklon_layer);
		pLine->setColorIndex(clr);
		pLine->close();

		oId = addToDataBase(curDoc()->database(),pLine);

		AcDbObjectPointer<AcDbHatch> pHatch;
		pHatch.create();
		pHatch->setOriginPoint(AcGePoint2d(pt1[X],pt1[Y]));
		pHatch->setPatternAngle(ang);
		pHatch->setLayer(ROOFUklon_layer);
		pHatch->setColorIndex(clr);

		oId = addToDataBase(curDoc()->database(),pHatch);

		es = pHatch->setPattern(AcDbHatch::HatchPatternType::kPreDefined,_T("ROCKWOOL_OU6"));
		es = pHatch->setAssociative(TRUE);
		es = pHatch->appendLoop(AcDbHatch::kExternal,pArray,bArray);
		es = pHatch->evaluateHatch();
		pHatch->close();

		AcDbObjectPointer<AcDbText> pText;
		pText.create();
		pText->setPosition(AcGePoint3d((pt1[X]+pt3[X])/2,(pt1[Y]+pt3[Y])/2,0));
		pText->setColorIndex(clr);
		pText->setLayer(ROOFUklon_layer);
		pText->setRotation(ang);
		pText->setHeight(300);
		pText->setTextString(_T("ROCKWOOL_OU6"));
		pText->close();

		//oId = addToDataBase(curDoc()->database(),pText);

		actrTransactionManager->flushGraphics();
		acedUpdateDisplay();

		if(len!=0 && wid!=0) 
		{
			calcData(pHatch->objectId(),len,wid,OU,TRUE);
			AcDbExtents ext;
			pHatch->getGeomExtents(ext);
			AcGePoint3d base_point((ext.minPoint().x+ext.maxPoint().x)/2,(ext.minPoint().y+ext.maxPoint().y)/2,0);
			addText(pHatch->objectId(),base_point,clr,OU);
		}
	}

	curDoc()->database()->setOrthomode(ortho_mode);
}

void getKU(int tip)
{
	bool ortho_mode = curDoc()->database()->orthomode();
	curDoc()->database()->setOrthomode(TRUE);

	while(TRUE)
	{
		ads_name ename;
		ads_point pt1,pt2,pt3;
		AcDbObjectId oId;
		AcGePoint2dArray pArray;
		AcGeDoubleArray  bArray;

		double len;

		Acad::ErrorStatus es;

		if(acedGetPoint(NULL,_T("\nУкажите 1 точку: \n"),pt1)!=RTNORM) break;
		if(acedGetPoint(pt1,_T("\nУкажите 2 точку: \n"),pt2)!=RTNORM) break;
		if(tip==KU05 || tip==KU1PE)
		{
			if(acedGetPoint(pt2,_T("\nУкажите направление: \n"),pt3)!=RTNORM) break;

			if(pt1[X]==pt3[X] || pt1[Y]==pt3[Y])
			{
				AfxMessageBox(_T("Точки лежат на одной линии!\nПроверьте настойки OSNAP"));
				continue;
			}
		}

		if(pt1[X]==pt2[X])
		{
			double ll = max(pt1[Y],pt2[Y]) - min(pt1[Y],pt2[Y]);
			if(tip == KU1PE || tip == KU2)
			{
				double ll1 = fmod(ll,2000);
				if(pt1[Y]>pt2[Y]) 
				{
					pt2[Y]+=ll1/2;
					pt1[Y]-=ll1/2;
				}
				else 
				{
					pt2[Y]-=ll1/2;
					pt1[Y]+=ll1/2;
				}
			}
			else
			{
				double ll1 = fmod(ll,1000);
				if(pt1[Y]>pt2[Y]) pt2[Y]+=ll1;
				else pt2[Y]-=ll1;
			}
		}

		if(pt1[Y]==pt2[Y])
		{
			double ll = max(pt1[X],pt2[X]) - min(pt1[X],pt2[X]);
			if(tip == KU1PE || tip == KU2)
			{
				double ll1 = fmod(ll,2000);
				if(pt1[X]>pt2[X]) 
				{
					pt2[X]+=ll1/2;
					pt1[X]-=ll1/2;
				}
				else 
				{
					pt2[X]-=ll1/2;
					pt1[X]+=ll1/2;
				}
			}
			else
			{
				double ll1 = fmod(ll,1000);
				if(pt1[X]>pt2[X]) pt2[X]+=ll1;
				else pt2[X]-=ll1;
			}
		}

		int clr = 10;

		CString pat;
		double mult = 0;

		CString txt;

		switch(DocVars.docData().ku_tip)
		{
		case 2: pat = _T("ROCKWOOL_KU6"); mult = asin(0.6); break;
		case 3: pat = _T("ROCKWOOL_KU3"); mult = asin(0.3); break;
		case 4: pat = _T("ROCKWOOL_KU2"); mult = asin(0.2); break;
		}

		txt.Append(pat);

		int w = 0;
		int h = 0;

		double ang = 0;

		if(pt1[X]==pt2[X])
		{
			if(pt3[X]<pt1[X]) h = -1;
			else h = 1;

			len = abs(pt1[Y]-pt2[Y]);
		}

		if(pt1[Y]==pt2[Y])
		{
			if(pt3[Y]<pt1[Y]) w = -1;
			else w = 1;

			len = abs(pt1[X]-pt2[X]);

			ang = 90 * (pi/180);
		}

		len = floor(len+0.5);

		if(tip == KU1PE || tip == KU2) len = len / 2;

		if(len < KU_MIN)
		{
			AfxMessageBox(_T("Длинна меньше 1000"));
			curDoc()->database()->setOrthomode(ortho_mode);
			return;
		}

		if(len>KU_MAX)
		{
			CString msg;
			int m;
			if(tip == KU1PE || tip == KU2) m = 40;
			else m = 20;
			msg.Format(_T("Длина Контруклона превышает допустимое значение в %dм.\nВнесите необходимые коррективы\n"),m);
			AfxMessageBox(msg);
			acutPrintf(msg);
			clr = 8;
		}

		AcDbObjectPointer<AcDbPolyline> pLine;
		pLine.create();

		switch(tip)
		{
		case KU05:
			{	
				pLine->addVertexAt(0,AcGePoint2d(pt1[X],pt1[Y])); 
				pLine->addVertexAt(1,AcGePoint2d(pt2[X],pt2[Y])); 
				pLine->addVertexAt(2,AcGePoint2d(pt1[X]+h*(abs((pt2[Y]-pt1[Y]))*mult), 
					pt1[Y]+w*(abs((pt2[X]-pt1[X]))*mult))); 

				pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);
				pArray.append(AcGePoint2d(pt2[X],pt2[Y])); bArray.append(0.0);
				pArray.append(AcGePoint2d(pt1[X]+h*(abs((pt2[Y]-pt1[Y]))*mult),
					pt1[Y]+w*(abs((pt2[X]-pt1[X]))*mult))); bArray.append(0.0);
				pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);
				len = (int)floor(len/1000);
				txt.Append(_T(" KU05"));
				break;
			}
		case KU1:
			{	
				pLine->addVertexAt(0,AcGePoint2d(pt1[X]-h*(abs((pt2[Y]-pt1[Y]))*mult),
					pt1[Y]-w*(abs((pt2[X]-pt1[X]))*mult))); 
				pLine->addVertexAt(1,AcGePoint2d(pt2[X],pt2[Y])); 
				pLine->addVertexAt(2,AcGePoint2d(pt1[X]+h*(abs((pt2[Y]-pt1[Y]))*mult),
					pt1[Y]+w*(abs((pt2[X]-pt1[X]))*mult))); 

				pArray.append(AcGePoint2d(pt1[X]-h*(abs((pt2[Y]-pt1[Y]))*mult),
					pt1[Y]-w*(abs((pt2[X]-pt1[X]))*mult))); bArray.append(0.0);
				pArray.append(AcGePoint2d(pt2[X],pt2[Y])); bArray.append(0.0);
				pArray.append(AcGePoint2d(pt1[X]+h*(abs((pt2[Y]-pt1[Y]))*mult),
					pt1[Y]+w*(abs((pt2[X]-pt1[X]))*mult))); bArray.append(0.0);
				pArray.append(AcGePoint2d(pt1[X]-h*(abs((pt2[Y]-pt1[Y]))*mult),
					pt1[Y]-w*(abs((pt2[X]-pt1[X]))*mult))); bArray.append(0.0);
				len = (int)floor(len/1000);
				txt.Append(_T(" KU1"));
				break;
			}
		case KU1PE:
			{	
				pLine->addVertexAt(0,AcGePoint2d(pt1[X],pt1[Y]));
				if(w!=0) pLine->addVertexAt(1,AcGePoint2d((pt2[X]+pt1[X])/2,pt2[Y]+w*(abs((pt2[X]-pt1[X]))*mult/2))); 
				if(h!=0) pLine->addVertexAt(1,AcGePoint2d(pt2[X]+h*(abs((pt2[Y]-pt1[Y]))*mult/2),(pt2[Y]+pt1[Y])/2)); 
				pLine->addVertexAt(2,AcGePoint2d(pt2[X],pt2[Y])); 

				pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);
				if(w!=0) pArray.append(AcGePoint2d((pt2[X]+pt1[X])/2,pt2[Y]+w*(abs((pt2[X]-pt1[X]))*mult/2))); 
				if(h!=0) pArray.append(AcGePoint2d(pt2[X]+h*(abs((pt2[Y]-pt1[Y]))*mult/2),(pt2[Y]+pt1[Y])/2)); 

				bArray.append(0.0);

				pArray.append(AcGePoint2d(pt2[X],pt2[Y])); bArray.append(0.0);
				pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);

				len = (int)floor(len/1000);
				txt.Append(_T(" KU1PE"));
				break;
			}
		case KU2:
			{	
				pLine->addVertexAt(0,AcGePoint2d(pt1[X],pt1[Y])); 
				pLine->addVertexAt(1,AcGePoint2d( h*h*pt2[X]+w*w*(pt2[X]+pt1[X])/2-h*(abs((pt2[Y]-pt1[Y]))*mult/2),
					w*w*pt2[Y]+h*h*(pt2[Y]+pt1[Y])/2-w*(abs((pt2[X]-pt1[X]))*mult/2))); 
				pLine->addVertexAt(2,AcGePoint2d(pt2[X],pt2[Y])); 
				pLine->addVertexAt(3,AcGePoint2d( h*h*pt2[X]+w*w*(pt2[X]+pt1[X])/2+h*(abs((pt2[Y]-pt1[Y]))*mult/2),
					w*w*pt2[Y]+h*h*(pt2[Y]+pt1[Y])/2+w*(abs((pt2[X]-pt1[X]))*mult/2))); 

				pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);
				pArray.append(AcGePoint2d( h*h*pt2[X]+w*w*(pt2[X]+pt1[X])/2-h*(abs((pt2[Y]-pt1[Y]))*mult/2),
					w*w*pt2[Y]+h*h*(pt2[Y]+pt1[Y])/2-w*(abs((pt2[X]-pt1[X]))*mult/2))); 
				bArray.append(0.0);
				pArray.append(AcGePoint2d(pt2[X],pt2[Y])); bArray.append(0.0);
				pArray.append(AcGePoint2d( h*h*pt2[X]+w*w*(pt2[X]+pt1[X])/2+h*(abs((pt2[Y]-pt1[Y]))*mult/2),
					w*w*pt2[Y]+h*h*(pt2[Y]+pt1[Y])/2+w*(abs((pt2[X]-pt1[X]))*mult/2))); 
				bArray.append(0.0);
				pArray.append(AcGePoint2d(pt1[X],pt1[Y])); bArray.append(0.0);

				len = (int)floor(len/1000);
				txt.Append(_T(" KU2"));
				break;
			}
		}	

		pLine->setClosed(TRUE);
		pLine->setLayer(ROOFUklon_layer);
		pLine->setColorIndex(clr);
		pLine->close();

		oId = addToDataBase(curDoc()->database(),pLine);

		AcDbObjectPointer<AcDbHatch> pHatch;
		pHatch.create();
		pHatch->setDatabaseDefaults();
		pHatch->setLayer(ROOFUklon_layer);
		pHatch->setColorIndex(clr);

		oId = addToDataBase(curDoc()->database(),pHatch);

		es = pHatch->setPatternAngle(ang);
		if(tip==KU2 || tip==KU1PE) es = pHatch->setOriginPoint(AcGePoint2d((pt1[X]+pt2[X])/2,(pt1[Y]+pt2[Y])/2));
		else es = pHatch->setOriginPoint(AcGePoint2d(pt1[X],pt1[Y]));
		es = pHatch->setPattern(AcDbHatch::HatchPatternType::kPreDefined,pat);
		es = pHatch->setAssociative(TRUE);
		es = pHatch->appendLoop(AcDbHatch::kExternal,pArray,bArray);
		es = pHatch->evaluateHatch();
		pHatch->close();

		double t_ang;
		if(ang == 0) t_ang = 90 * (pi/180);
		else t_ang = 0;

		AcDbObjectPointer<AcDbText> pText;
		pText.create();
		pText->setPosition(AcGePoint3d(pt1[X],pt1[Y],0));
		pText->setColorIndex(clr);
		pText->setLayer(ROOFUklon_layer);
		pText->setTextString(txt);
		pText->setHeight(300);
		pText->setRotation(t_ang);
		pText->close();

		//oId = addToDataBase(curDoc()->database(),pText);

		actrTransactionManager->flushGraphics();
		acedUpdateDisplay();
		
		if(len!=0) 
		{
			calcData(pHatch->objectId(),len,0,tip,TRUE);
			AcDbExtents ext;
			pHatch->getGeomExtents(ext);
			AcGePoint3d base_point((ext.minPoint().x+ext.maxPoint().x)/2,(ext.minPoint().y+ext.maxPoint().y)/2,0);
			addText(pHatch->objectId(),base_point,clr,tip);
		}

		if(!DocVars.docData().ku_fixed) 
		{
			DocVars.docData().ku_fixed = true;
			resbuf * ku_fixed = acutBuildList(RTSHORT,1,RTNONE);
			addXdata(curDoc()->database()->namedObjectsDictionaryId(),_T("KU_FIXED"),ku_fixed);
			acutRelRb(ku_fixed);
			main_dlg->initControls(); 
		}
	}

	curDoc()->database()->setOrthomode(ortho_mode);
}


void getSpecs()
{
	CAcModuleResourceOverride res;

	CSpecDlg dlg;
	dlg.DoModal();
}

void addSpecs()
{
	ads_point pt1;
	if(acedGetPoint(NULL,_T("\nУкажите точку: \n"),pt1)!=RTNORM) return;

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
		pIter->getEntity(pEnt,AcDb::kForRead);

		if(!pEnt->isKindOf(AcDbTable::desc())) 
		{
			pEnt->close();
			continue;
		}

		AcDbTable * pOldTable = (AcDbTable*)pEnt;
		AcDbTable * pNewTable;

		AcDbObjectIdArray idArray; idArray.append(pEnt->objectId()); pEnt->close();
		AcDbIdMapping idMap;

		AcDbObjectId oId;
		AcDbBlockTable * pTable;
		AcDbBlockTableRecord * pRec;
		es = curDoc()->database()->getBlockTable(pTable,AcDb::kForRead);
		if(es!=Acad::eOk) return;

		es = pTable->getAt(ACDB_MODEL_SPACE,oId);
		if(es!=Acad::eOk) return;
		pTable->close();

		es = pDwg->wblockCloneObjects(idArray,oId,idMap,AcDb::DuplicateRecordCloning::kDrcIgnore,false);

		AcDbIdMappingIter Iter(idMap); 
		AcDbIdPair idPair;

		for (Iter.start(); !Iter.done(); Iter.next())
		{
			Iter.getMap(idPair);
			oId = idPair.value();

			AcDbObject * pObj;

			es = acdbOpenAcDbObject(pObj,oId,AcDb::kForWrite);

			if(pObj->isKindOf(AcDbTable::desc()))
			{
				DocVars.docData().specs_table_id = oId;

				pNewTable = (AcDbTable *) pObj;
				es = pNewTable->setLayer(ROOFUklon_layer);
				es = pNewTable->setPosition(AcGePoint3d(pt1[X],pt1[Y],0));

				CString val;
				val.Format(_T("%d"),DocVars.docData().a);
				pNewTable->setTextString(4,3,0,val);
				val.Format(_T("%d"),DocVars.docData().b);
				pNewTable->setTextString(5,3,0,val);
				val.Format(_T("%d"),DocVars.docData().c);
				pNewTable->setTextString(6,3,0,val);
				val.Format(_T("%d"),DocVars.docData().d);
				pNewTable->setTextString(7,3,0,val);
				val.Format(_T("%d"),DocVars.docData().dobor);
				pNewTable->setTextString(8,3,0,val);

				switch(DocVars.docData().ku_tip)
				{
				case 1:
					{
						val.Format(_T("%d"),DocVars.docData().ugol);
						pNewTable->setTextString(10,3,0,val);
						val.Format(_T("%d"),DocVars.docData().uklon);
						pNewTable->setTextString(11,3,0,val);
						val.Format(_T("%d"),DocVars.docData().dobor1);
						pNewTable->setTextString(12,3,0,val);
						val.Format(_T("%d"),DocVars.docData().dobor2);
						pNewTable->setTextString(13,3,0,val);
						break;
					}
				case 2:
					{
						val.Format(_T("%d"),DocVars.docData().ugol);
						pNewTable->setTextString(15,3,0,val);
						val.Format(_T("%d"),DocVars.docData().uklon);
						pNewTable->setTextString(16,3,0,val);
						val.Format(_T("%d"),DocVars.docData().dobor1);
						pNewTable->setTextString(17,3,0,val);
						val.Format(_T("%d"),DocVars.docData().dobor2);
						pNewTable->setTextString(18,3,0,val);
						break;
					}
				case 3:
					{
						val.Format(_T("%d"),DocVars.docData().ugol);
						pNewTable->setTextString(20,3,0,val);
						val.Format(_T("%d"),DocVars.docData().uklon);
						pNewTable->setTextString(21,3,0,val);
						val.Format(_T("%d"),DocVars.docData().dobor1);
						pNewTable->setTextString(22,3,0,val);
						val.Format(_T("%d"),DocVars.docData().dobor2);
						pNewTable->setTextString(23,3,0,val);
						break;
					}
				}

				es = pNewTable->close();
				break;
			}

			pObj->close();
		}
		
		acDocManager->sendStringToExecute(curDoc(),_T("regen\n"));

		actrTransactionManager->flushGraphics();
		acedUpdateDisplay();

		pIter->step();
	}

	delete pIter;
	delete pDwg;
}

void resetDrw()
{
	if(AfxMessageBox(_T("Сбросить все?"),MB_YESNO)==IDNO) return;

	struct resbuf eb2;
	TCHAR sbuf2[10];
	ads_name ssname2; 
	eb2.restype = 8; 
	_tcscpy(sbuf2, ROOFUklon_layer);
	eb2.resval.rstring = sbuf2;
	eb2.rbnext = NULL;
	acedSSGet(_T("X"), NULL, NULL, &eb2, ssname2);

	long length = 0;
	acedSSLength(ssname2, &length);
	for(long l = 0; l < length; l++)
	{
		ads_name ename;
		if(RTNORM != acedSSName(ssname2, l, ename))
			continue;
		AcDbObjectId objId;
		if(Acad::eOk != acdbGetObjectId(objId, ename))
			continue;

		AcDbObjectPointer<AcDbEntity> pR(objId,AcDb::kForWrite);
		if(Acad::eOk != pR.openStatus())
			continue;
		pR->erase();
		pR->close();
	}

	resetDocVars();

	resbuf * tip = acutBuildList(RTSHORT,0,RTNONE);
	acDocManager->lockDocument(curDoc());
	addXdata(curDoc()->database()->namedObjectsDictionaryId(),_T("KU_FIXED"),tip);
	acDocManager->unlockDocument(curDoc());
	acutRelRb(tip);

	actrTransactionManager->flushGraphics();
	acedUpdateDisplay();
}

void addSlise()
{
	initSlice();

	ads_point pt1;
	if(acedGetPoint(NULL,_T("\nУкажите точку: \n"),pt1)!=RTNORM) return;

	ads_real sc;
	acedInitGet(6,_T(""));
	if(acedGetReal(_T("Маштаб (1): \n"),&sc)!=RTNORM) sc = 1;

	sc*=20;

	AcGePoint3d pt(pt1[X],pt1[Y],0.0);

	Acad::ErrorStatus es;
	AcDbObjectId oId;
	AcDbBlockTable * pTable;
	AcDbBlockReference * pRef;

	CString nm;

	double mv_scl = 50;

	/*if(DocVars.docData().ku_fixed)
	{
		nm = _T("1");
		es = curDoc()->database()->getBlockTable(pTable,AcDb::kForRead);
		es = pTable->getAt(nm,oId);
		pTable->close();

		if(es!=Acad::eOk) return;

		pRef = new AcDbBlockReference(pt,oId);

		pRef->setLayer(ROOFUklon_layer);
		pRef->setPosition(pt);
		pRef->setScaleFactors(AcGeScale3d(sc));

		addToDataBase(curDoc()->database(),pRef);

		pRef->close();

		nm.Format(_T("%d"),DocVars.docData().ku_tip);
		es = curDoc()->database()->getBlockTable(pTable,AcDb::kForRead);
		es = pTable->getAt(nm,oId);
		pTable->close();

		if(es!=Acad::eOk) return;

		pt.y-=mv_scl*sc;

		pRef = new AcDbBlockReference(pt,oId);

		pRef->setLayer(ROOFUklon_layer);
		pRef->setPosition(pt);
		pRef->setScaleFactors(AcGeScale3d(sc));

		addToDataBase(curDoc()->database(),pRef);

		pRef->close();
	}*/

	//if(DocVars.docData().ou_active)
	{
		nm = _T("slice");
		es = curDoc()->database()->getBlockTable(pTable,AcDb::kForRead);
		es = pTable->getAt(nm,oId);
		pTable->close();

		if(es!=Acad::eOk) return;

		pt.y-=mv_scl*sc;

		pRef = new AcDbBlockReference(pt,oId);

		pRef->setLayer(ROOFUklon_layer);
		pRef->setPosition(pt);
		pRef->setScaleFactors(AcGeScale3d(sc));

		addToDataBase(curDoc()->database(),pRef);

		pRef->close();
	}

}

void updateTable()
{
	if(DocVars.docData().specs_table_id==NULL) return;
	Acad::ErrorStatus es;
	AcDbTable *pNewTable;
	es = acdbOpenAcDbObject((AcDbObject*&)pNewTable,DocVars.docData().specs_table_id,AcDb::kForWrite);

	CString val;
	val.Format(_T("%d"),DocVars.docData().a);
	pNewTable->setTextString(4,3,0,val);
	val.Format(_T("%d"),DocVars.docData().b);
	pNewTable->setTextString(5,3,0,val);
	val.Format(_T("%d"),DocVars.docData().c);
	pNewTable->setTextString(6,3,0,val);
	val.Format(_T("%d"),DocVars.docData().d);
	pNewTable->setTextString(7,3,0,val);
	val.Format(_T("%d"),DocVars.docData().dobor);
	pNewTable->setTextString(8,3,0,val);

	switch(DocVars.docData().ku_tip)
	{
	case 1:
		{
			val.Format(_T("%d"),DocVars.docData().ugol);
			pNewTable->setTextString(10,3,0,val);
			val.Format(_T("%d"),DocVars.docData().uklon);
			pNewTable->setTextString(11,3,0,val);
			val.Format(_T("%d"),DocVars.docData().dobor1);
			pNewTable->setTextString(12,3,0,val);
			val.Format(_T("%d"),DocVars.docData().dobor2);
			pNewTable->setTextString(13,3,0,val);
			break;
		}
	case 2:
		{
			val.Format(_T("%d"),DocVars.docData().ugol);
			pNewTable->setTextString(15,3,0,val);
			val.Format(_T("%d"),DocVars.docData().uklon);
			pNewTable->setTextString(16,3,0,val);
			val.Format(_T("%d"),DocVars.docData().dobor1);
			pNewTable->setTextString(17,3,0,val);
			val.Format(_T("%d"),DocVars.docData().dobor2);
			pNewTable->setTextString(18,3,0,val);
			break;
		}
	case 3:
		{
			val.Format(_T("%d"),DocVars.docData().ugol);
			pNewTable->setTextString(20,3,0,val);
			val.Format(_T("%d"),DocVars.docData().uklon);
			pNewTable->setTextString(21,3,0,val);
			val.Format(_T("%d"),DocVars.docData().dobor1);
			pNewTable->setTextString(22,3,0,val);
			val.Format(_T("%d"),DocVars.docData().dobor2);
			pNewTable->setTextString(23,3,0,val);
			break;
		}
	}

	es = pNewTable->close();

	actrTransactionManager->flushGraphics();
	acedUpdateDisplay();
}


void resetDocVars()
{
	DocVars.docData().a = 0;
	DocVars.docData().b = 0;
	DocVars.docData().c = 0;
	DocVars.docData().d = 0;
	DocVars.docData().dobor = 0;

	DocVars.docData().ugol = 0;
	DocVars.docData().uklon = 0;
	DocVars.docData().dobor1 = 0;
	DocVars.docData().dobor2 = 0;

	DocVars.docData().specs_table_id = NULL;

	DocVars.docData().ku_tip = 3;
	DocVars.docData().ou_active = 1;

	DocVars.docData().tb = _T("");
	DocVars.docData().tw = 40;

	DocVars.docData().ku_fixed = false;
}

void initArrows()
{
	Acad::ErrorStatus es;
	AcDbBlockTable * pTable;
	AcDbBlockTableRecord * pRec;
	AcDbObjectId oId1,oId2;

	curDoc()->database()->getBlockTable(pTable,AcDb::kForWrite);
	es = pTable->getAt(_T("arrows1"),oId1,AcDb::kForRead);
	es = pTable->getAt(_T("arrows2"),oId2,AcDb::kForRead);
	pTable->close();
	if(es==Acad::eOk) return;

	AcDbDatabase * pDwg = new AcDbDatabase(false,true);
	es = pDwg->readDwgFile(arrows_file);
	if(es!=Acad::eOk) return;

	es = curDoc()->database()->insert(oId1,_T("arrows"),pDwg,true);

	delete pDwg;
}

void initSlice()
{
	Acad::ErrorStatus es;
	AcDbBlockTable * pTable;
	AcDbBlockTableRecord * pRec;
	AcDbObjectId oId1;

	curDoc()->database()->getBlockTable(pTable,AcDb::kForWrite);
	es = pTable->getAt(_T("slice"),oId1,AcDb::kForRead);
	pTable->close();
	if(es==Acad::eOk) return;

	AcDbDatabase * pDwg = new AcDbDatabase(false,true);
	es = pDwg->readDwgFile(slice_file);
	if(es!=Acad::eOk) return;

	es = curDoc()->database()->insert(oId1,_T("slice"),pDwg,true);

	delete pDwg;
}

void addArrows(AcGePoint3d pt)
{
	Acad::ErrorStatus es;
	AcDbObjectId oId;
	AcDbBlockTable * pTable;
	AcDbBlockReference * pRef;

	CString nm;
	if(!DocVars.docData().ou_active) nm = _T("arrows1");
	else nm = _T("arrows2");

	es = curDoc()->database()->getBlockTable(pTable,AcDb::kForRead);
	es = pTable->getAt(nm,oId);
	pTable->close();

	if(es!=Acad::eOk) return;
		
	pRef = new AcDbBlockReference(pt,oId);

	pRef->setLayer(ROOFUklon_layer);
	pRef->setPosition(pt);

	addToDataBase(curDoc()->database(),pRef);

	pRef->close();
}

void exportExcel(int ext_type)
{
	switch(ext_type) 
	{
	case EXPORT_RAZUKLONKA : razuklonka(); break;
	case EXPORT_KREPEZ: krepez(); break;
	}
}

void getTable()
{
	struct resbuf eb2;
	TCHAR sbuf2[10];
	ads_name ssname2; 
	eb2.restype = 8; 
	_tcscpy(sbuf2, ROOFUklon_layer);
	eb2.resval.rstring = sbuf2;
	eb2.rbnext = NULL;
	acedSSGet(_T("X"), NULL, NULL, &eb2, ssname2);

	long length = 0;
	acedSSLength(ssname2, &length);
	for(long l = 0; l < length; l++)
	{
		ads_name ename;
		if(RTNORM != acedSSName(ssname2, l, ename))
			continue;
		AcDbObjectId objId;
		if(Acad::eOk != acdbGetObjectId(objId, ename))
			continue;

		AcDbObjectPointer<AcDbEntity> pR(objId,AcDb::kForWrite);
		if(Acad::eOk != pR.openStatus())
			continue;
		if(pR.object()->isKindOf(AcDbTable::desc()))
		{
			DocVars.docData().specs_table_id = pR->objectId();
			pR->close();
			return;
		}
		pR->close();
	}
}

table_data * getTableData()
{
	Acad::ErrorStatus es;

	table_data * dt = NULL;

	AcDbDatabase * pDwg = new AcDbDatabase(false,true);

	es = pDwg->readDwgFile(table_file);
	if(es!=Acad::eOk) return dt;

	AcDbBlockTable * pTable;
	es = pDwg->getBlockTable(pTable,AcDb::kForRead);
	if(es!=Acad::eOk) return dt;

	AcDbBlockTableRecord * pRec;
	es = pTable->getAt(ACDB_MODEL_SPACE,pRec,AcDb::kForRead);
	pTable->close();
	if(es!=Acad::eOk) return dt;

	AcDbBlockTableRecordIterator * pIter;
	es = pRec->newIterator(pIter);
	pRec->close();

	while (!pIter->done())
	{
		AcDbEntity * pEnt;
		pIter->getEntity(pEnt,AcDb::kForRead);

		if(!pEnt->isKindOf(AcDbTable::desc())) 
		{
			pEnt->close();
			continue;
		}

		dt = new table_data();

		AcDbTable * pATable = (AcDbTable*)pEnt;

		//1blok
		dt->a[0] = pATable->textString(4,1,0).kwszPtr();
		dt->a[1] = pATable->textString(4,2,0).kwszPtr();
		dt->a[2] = pATable->textString(4,4,0).kwszPtr();

		dt->b[0] = pATable->textString(5,1,0).kwszPtr();
		dt->b[1] = pATable->textString(5,2,0).kwszPtr();
		dt->b[2] = pATable->textString(5,4,0).kwszPtr();

		dt->c[0] = pATable->textString(6,1,0).kwszPtr();
		dt->c[1] = pATable->textString(6,2,0).kwszPtr();
		dt->c[2] = pATable->textString(6,4,0).kwszPtr();

		dt->d[0] = pATable->textString(7,1,0).kwszPtr();
		dt->d[1] = pATable->textString(7,2,0).kwszPtr();
		dt->d[2] = pATable->textString(7,4,0).kwszPtr();

		dt->dobor[0] = pATable->textString(8,1,0).kwszPtr();
		dt->dobor[1] = pATable->textString(8,2,0).kwszPtr();
		dt->dobor[2] = pATable->textString(8,4,0).kwszPtr();

		//2blok
		dt->ugol600[0] = pATable->textString(10,1,0).kwszPtr();
		dt->ugol600[1] = pATable->textString(10,2,0).kwszPtr();
		dt->ugol600[2] = pATable->textString(10,4,0).kwszPtr();

		dt->uklon600[0] = pATable->textString(11,1,0).kwszPtr();
		dt->uklon600[1] = pATable->textString(11,2,0).kwszPtr();
		dt->uklon600[2] = pATable->textString(11,4,0).kwszPtr();

		dt->dobor1600[0] = pATable->textString(12,1,0).kwszPtr();
		dt->dobor1600[1] = pATable->textString(12,2,0).kwszPtr();
		dt->dobor1600[2] = pATable->textString(12,4,0).kwszPtr();

		dt->dobor1600[0] = pATable->textString(13,1,0).kwszPtr();
		dt->dobor1600[1] = pATable->textString(13,2,0).kwszPtr();
		dt->dobor1600[2] = pATable->textString(13,4,0).kwszPtr();

		//3blok
		dt->ugol300[0] = pATable->textString(15,1,0).kwszPtr();
		dt->ugol300[1] = pATable->textString(15,2,0).kwszPtr();
		dt->ugol300[2] = pATable->textString(15,4,0).kwszPtr();

		dt->uklon300[0] = pATable->textString(16,1,0).kwszPtr();
		dt->uklon300[1] = pATable->textString(16,2,0).kwszPtr();
		dt->uklon300[2] = pATable->textString(16,4,0).kwszPtr();

		dt->dobor1300[0] = pATable->textString(17,1,0).kwszPtr();
		dt->dobor1300[1] = pATable->textString(17,2,0).kwszPtr();
		dt->dobor1300[2] = pATable->textString(17,4,0).kwszPtr();

		dt->dobor1300[0] = pATable->textString(18,1,0).kwszPtr();
		dt->dobor1300[1] = pATable->textString(18,2,0).kwszPtr();
		dt->dobor1300[2] = pATable->textString(18,4,0).kwszPtr();

		//4blok
		dt->ugol200[0] = pATable->textString(20,1,0).kwszPtr();
		dt->ugol200[1] = pATable->textString(20,2,0).kwszPtr();
		dt->ugol200[2] = pATable->textString(20,4,0).kwszPtr();

		dt->uklon200[0] = pATable->textString(21,1,0).kwszPtr();
		dt->uklon200[1] = pATable->textString(21,2,0).kwszPtr();
		dt->uklon200[2] = pATable->textString(21,4,0).kwszPtr();

		dt->dobor1200[0] = pATable->textString(22,1,0).kwszPtr();
		dt->dobor1200[1] = pATable->textString(22,2,0).kwszPtr();
		dt->dobor1200[2] = pATable->textString(22,4,0).kwszPtr();

		dt->dobor1200[0] = pATable->textString(23,1,0).kwszPtr();
		dt->dobor1200[1] = pATable->textString(23,2,0).kwszPtr();
		dt->dobor1200[2] = pATable->textString(23,4,0).kwszPtr();

		pATable->close();
		pIter->step();
	}
	delete pIter;

	delete pDwg;

	return dt;
}


void razuklonka()
{
	struct resbuf res;
	if(acedGetFileD(_T(""),_T("spec"),_T("xls"),33,&res)!=RTNORM) return;

	CString file_name = res.resval.rstring;

	BasicExcel xls;
	if(!xls.Load(table_file_xls)) 
	{
		AfxMessageBox(_T("Ошибка загрузки шаблона таблицы (table.xls)"));
		return;
	}

	BasicExcelWorksheet * w = xls.GetWorksheet(1);
	BasicExcelCell * cell;

	cell = w->Cell(6,4);
	cell->SetInteger(DocVars.docData().a);
	cell = w->Cell(7,4);
	cell->SetInteger(DocVars.docData().b);
	cell = w->Cell(8,4);
	cell->SetInteger(DocVars.docData().c);
	cell = w->Cell(9,4);
	cell->SetInteger(DocVars.docData().d);
	cell = w->Cell(10,4);
	cell->SetInteger(DocVars.docData().dobor);

	switch(DocVars.docData().ku_tip)
	{
	case 2:
		{
			cell = w->Cell(18,4);
			cell->SetInteger(DocVars.docData().ugol);
			cell = w->Cell(19,4);
			cell->SetInteger(DocVars.docData().uklon);
			cell = w->Cell(20,4);
			cell->SetInteger(DocVars.docData().dobor1);
			cell = w->Cell(21,4);
			cell->SetInteger(DocVars.docData().dobor2);
			break;
		}
	case 3:
		{
			cell = w->Cell(29,4);
			cell->SetInteger(DocVars.docData().ugol);
			cell = w->Cell(30,4);
			cell->SetInteger(DocVars.docData().uklon);
			cell = w->Cell(31,4);
			cell->SetInteger(DocVars.docData().dobor1);
			cell = w->Cell(32,4);
			cell->SetInteger(DocVars.docData().dobor2);
			break;
		}
	case 4:
		{
			cell = w->Cell(39,4);
			cell->SetInteger(DocVars.docData().ugol);
			cell = w->Cell(40,4);
			cell->SetInteger(DocVars.docData().uklon);
			cell = w->Cell(41,4);
			cell->SetInteger(DocVars.docData().dobor1);
			cell = w->Cell(42,4);
			cell->SetInteger(DocVars.docData().dobor2);
			break;
		}
	}

	w = xls.GetWorksheet(0);

	int cnt = 2;
	for (std::list<ou_data>::iterator it = DocVars.docData().ou_list.begin(); it!=DocVars.docData().ou_list.end(); it++)
	{
		cell = w->Cell(cnt,1);
		cell->SetInteger(it->length);
		cell = w->Cell(cnt,2);
		cell->SetDouble(it->width);
		cnt++;
	}

	cnt = 2;
	for (std::list<ku_data>::iterator it = DocVars.docData().ku_list.begin(); it!=DocVars.docData().ku_list.end(); it++)
	{
		cell = w->Cell(cnt,5);
		cell->SetInteger(it->length);
		cell = w->Cell(cnt,6);
		cell->SetInteger(it->cnt);
		cnt++;
	}

	xls.SaveAs(file_name);
	xls.Close();

	if(::MessageBox(NULL,_T("Таблица експортирована в:\n")+file_name+_T("\nОткрыть?"),_T(""),MB_YESNO)==IDYES)
	{
		ShellExecute(NULL,_T("open"),file_name,NULL,NULL,SW_NORMAL);
	}
}


void krepez()
{
	struct resbuf res;
	if(acedGetFileD(_T(""),_T("spec"),_T("xls"),33,&res)!=RTNORM) return;

	CString file_name = res.resval.rstring;

	BasicExcel xls;
	if(!xls.Load(fasteners_file_xls)) 
	{
		AfxMessageBox(_T("Ошибка загрузки шаблона таблицы (fasteners.xls)"));
		return;
	}

	BasicExcelWorksheet * w = xls.GetWorksheet(0);
	BasicExcelCell * cell;

	int cnt = 2;
	for (std::list<ou_data>::iterator it = DocVars.docData().ou_list.begin(); it!=DocVars.docData().ou_list.end(); it++)
	{
		cell = w->Cell(cnt,1);
		cell->SetInteger(it->length);
		cell = w->Cell(cnt,2);
		cell->SetDouble(it->width);
		cnt++;
	}

	cnt = 2;
	for (std::list<ku_data>::iterator it = DocVars.docData().ku_list.begin(); it!=DocVars.docData().ku_list.end(); it++)
	{
		cell = w->Cell(cnt,5);
		cell->SetInteger(it->length);
		cell = w->Cell(cnt,6);
		cell->SetInteger(it->cnt);
		cnt++;
	}

	cell = w->Cell(1,8);
	cell->SetWString(DocVars.docData().tb);
	

	cell = w->Cell(4,8);
	cell->SetInteger(DocVars.docData().tw);

	xls.SaveAs(file_name);
	xls.Close();

	if(::MessageBox(NULL,_T("Таблица експортирована в:\n")+file_name+_T("\nОткрыть?"),_T(""),MB_YESNO)==IDYES)
	{
		ShellExecute(NULL,_T("open"),file_name,NULL,NULL,SW_NORMAL);
	}
}

void addText(AcDbObjectId parent_id, AcGePoint3d base_point, int clr, int tip)
{
	CString txt;

	if(tip==OU) txt.Format(_T("%d"),DocVars.docData().ou_list.size());
	else txt.Format(_T("%d"),DocVars.docData().ku_list.size());

	AcDbObjectPointer<AcDbText> pText;
	pText.create();
	pText->setPosition(base_point);
	pText->setHeight(250);
	pText->setTextString(txt);
	pText->setColorIndex(clr);

	ads_name ename;
	AcDbObjectId mTextId = addToDataBase(curDoc()->database(),pText);

	pText->close();

	acdbGetAdsName(ename,mTextId);

	acDocManager->lockDocument(curDoc());

	resbuf * txt_data = acutBuildList(AcDb::kDxfHardPointerId, ename, RTNONE);
	addXdata(parent_id,TEXT_NR,txt_data);
	acutRelRb(txt_data);

	acDocManager->unlockDocument(curDoc());
}



Acad::ErrorStatus addXdata(AcDbObjectId oId, CString key, resbuf * data)
{
	Acad::ErrorStatus es;
	AcDbObject *pObj;
	AcDbObjectId dictId;
	AcDbDictionary *pDict;
	AcDbXrecord *pRec;// = new AcDbXrecord();

	if(oId!=curDoc()->database()->namedObjectsDictionaryId())
	{
		es = acdbOpenObject(pObj,oId,AcDb::kForWrite);
		if(es!=Acad::eOk) return es;

		es = pObj->createExtensionDictionary();
		dictId = pObj->extensionDictionary();
		es = pObj->close();
	}
	else dictId = oId;

	es = acdbOpenObject((AcDbObject*&)pDict,dictId,AcDb::kForWrite);
	if(es!=Acad::eOk) return es;
	//es = pDict->remove(key);
	es = pDict->getAt(key,(AcDbObject*&)pRec,AcDb::kForWrite);
	if(es!=Acad::eOk) 
	{
		pRec = new AcDbXrecord();
		es = pDict->setAt(key,(AcDbObject*&)pRec,oId);
	}
	pDict->close();

	if(es!=Acad::eOk) return es;

	es = pRec->setFromRbChain(*data);
	pRec->close();

	return es;
}

Acad::ErrorStatus getXdata(AcDbObjectId oId, CString key, resbuf *& data)
{
	Acad::ErrorStatus es;
	AcDbObject *pObj;
	AcDbObjectId dictId;
	AcDbDictionary *pDict;
	AcDbXrecord *pRec;

	if(oId!=curDoc()->database()->namedObjectsDictionaryId())
	{
		es = acdbOpenObject(pObj,oId,AcDb::kForRead,TRUE);
		if(es!=Acad::eOk) return es;

		dictId = pObj->extensionDictionary();
		pObj->close();
	}
	else dictId = oId;

	es = acdbOpenObject((AcDbObject*&)pDict,dictId,AcDb::kForRead);
	if(es!=Acad::eOk) return Acad::eKeyNotFound;
	es = pDict->getAt(key,(AcDbObject*&)pRec,AcDb::kForRead);
	pDict->close();

	if(es!=Acad::eOk) return es;

	es = pRec->rbChain(&data);
	pRec->close();

	return es;
}

void removeData(AcDbObjectId oId)
{
	resbuf * tmp_data = NULL;
	getXdata(oId,TEXT_NR,tmp_data);

	if(tmp_data==NULL) return;

	ads_name ename;
	ads_name_set(tmp_data->resval.rlname,ename);
	acutRelRb(tmp_data);
	AcDbObjectId oid;
	acdbGetObjectId(oid,ename);

	AcDbEntity * pEnt;

	Acad::ErrorStatus es = acdbOpenObject(pEnt,oid,AcDb::kForWrite);
	if(es==Acad::eOk)
	{
		pEnt->erase();
		pEnt->close();
	}
	
	resbuf * tmp_data2 = NULL;
	getXdata(oId,UTYPE,tmp_data2);

	if(tmp_data2==NULL) return;

	int utype = tmp_data2->resval.rint; tmp_data2 = tmp_data2->rbnext;
	int l	  = tmp_data2->resval.rint; tmp_data2 = tmp_data2->rbnext;
	int w	  = tmp_data2->resval.rint;
	acutRelRb(tmp_data2);

	if(utype==OU)
	{
		for (std::list<ou_data>::iterator it = DocVars.docData().ou_list.begin(); it!=DocVars.docData().ou_list.end(); it++)
		{
			ou_data tmp = *it;
			if(tmp.oId==oId) 
			{
				DocVars.docData().ou_list.erase(it);
				break;
			}
		}

		int nr = 1;

		for (std::list<ou_data>::iterator it = DocVars.docData().ou_list.begin(); it!=DocVars.docData().ou_list.end(); it++)
		{
			CString nr_str; nr_str.Format(_T("%d"),nr++);
			ou_data tmp = *it;
			AcDbText * pText;

			resbuf * txt_data = NULL;
			getXdata(tmp.oId,TEXT_NR,txt_data);

			if(txt_data==NULL) return;

			ads_name ename;
			ads_name_set(txt_data->resval.rlname,ename);
			acutRelRb(txt_data);
			AcDbObjectId oid;
			acdbGetObjectId(oid,ename);

			es = acdbOpenObject(pText,oid,AcDb::kForWrite);
			if(es!=Acad::eOk) continue;
			
			es = pText->setTextString(nr_str);
			es = pText->close();
		}
	}
	else 
	{
		for (std::list<ku_data>::iterator it = DocVars.docData().ku_list.begin(); it!=DocVars.docData().ku_list.end(); it++)
		{
			ku_data tmp = *it;
			if(tmp.oId==oId) 
			{
				DocVars.docData().ku_list.erase(it);
				break;
			}
		}

		int nr = 1;

		for (std::list<ku_data>::iterator it = DocVars.docData().ku_list.begin(); it!=DocVars.docData().ku_list.end(); it++)
		{
			CString nr_str; nr_str.Format(_T("%d"),nr++);
			ku_data tmp = *it;
			AcDbText * pText;

			resbuf * txt_data = NULL;
			getXdata(tmp.oId,TEXT_NR,txt_data);

			if(txt_data==NULL) return;

			ads_name ename;
			ads_name_set(txt_data->resval.rlname,ename);
			acutRelRb(txt_data);
			AcDbObjectId oid;
			acdbGetObjectId(oid,ename);

			es = acdbOpenObject(pText,oid,AcDb::kForWrite);
			if(es!=Acad::eOk) continue;
			es = pText->setTextString(nr_str);
			es = pText->close();
		}
	}

	calcData(oId,l,w,utype,FALSE);
}

void initBlocks()
{
	resetDocVars();
	ads_name ss;
	resbuf * filtr = acutBuildList(RTDXF0,_T("HATCH"),RTNONE);
	acedSSGet(_T("_X"),NULL,NULL,filtr,ss);

	long len = 0;
	acedSSLength(ss,&len);

	for (int i = 0 ; i < len; i++)
	{
		ads_name ename;
		if (acedSSName (ss, i, ename) != RTNORM)
			continue;
		AcDbObjectId objId;
		acdbGetObjectId (objId, ename);

		resbuf * block_data = NULL;
		getXdata(objId,UTYPE,block_data);

		int utype = block_data->resval.rint; block_data = block_data->rbnext;
		int l	  = block_data->resval.rint; block_data = block_data->rbnext;
		int w     = block_data->resval.rint; 

		acutRelRb(block_data);

		calcData(objId,l,w,utype,TRUE);
	}

	acedSSFree(ss);
	acutRelRb(filtr);
}