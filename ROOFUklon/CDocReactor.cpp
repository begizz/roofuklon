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
//----- CDocReactor.cpp : Implementation of CDocReactor
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "CDocReactor.h"

//-----------------------------------------------------------------------------
ACRX_CONS_DEFINE_MEMBERS(CDocReactor, AcApDocManagerReactor, 1)

//-----------------------------------------------------------------------------
CDocReactor::CDocReactor (const bool autoInitAndRelease) : AcApDocManagerReactor(), mbAutoInitAndRelease(autoInitAndRelease) {
	if ( autoInitAndRelease ) {
		if ( acDocManager )
			acDocManager->addReactor (this) ;
		else
			mbAutoInitAndRelease =false ;
	}
}

//-----------------------------------------------------------------------------
CDocReactor::~CDocReactor () {
	Detach () ;
}

//-----------------------------------------------------------------------------
void CDocReactor::Attach () {
	Detach () ;
	if ( !mbAutoInitAndRelease ) {
		if ( acDocManager ) {
			acDocManager->addReactor (this) ;
			mbAutoInitAndRelease =true ;
		}
	}
}

void CDocReactor::Detach () {
	if ( mbAutoInitAndRelease ) {
		if ( acDocManager ) {
			acDocManager->removeReactor (this) ;
			mbAutoInitAndRelease =false ;
		}
	}
}

AcApDocManager *CDocReactor::Subject () const {
	return (acDocManager) ;
}

bool CDocReactor::IsAttached () const {
	return (mbAutoInitAndRelease) ;
}


// -----------------------------------------------------------------------------
void CDocReactor::documentBecameCurrent(AcApDocument * param2)
{
	if(main_dlg!=NULL)
	{
		main_dlg->initControls();
		//main_dlg->m_tb.SelectString(-1,DocVars.docData().tb);
		//CString tw; tw.Format(_T("%d"),DocVars.docData().tw);
		//main_dlg->m_tw.SetWindowText(tw);
	}
	AcApDocManagerReactor::documentBecameCurrent (param2) ;
}
