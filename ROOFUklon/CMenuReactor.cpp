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
//----- Reactor\CMenuReactor.cpp : Implementation of CMenuReactor
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "CMenuReactor.h"

//-----------------------------------------------------------------------------
ACRX_CONS_DEFINE_MEMBERS(CMenuReactor, AcApDocManagerReactor, 1)

//-----------------------------------------------------------------------------
CMenuReactor::CMenuReactor (const bool autoInitAndRelease) : AcApDocManagerReactor(), mbAutoInitAndRelease(autoInitAndRelease) {
	if ( autoInitAndRelease ) {
		if ( acDocManager )
			acDocManager->addReactor (this) ;
		else
			mbAutoInitAndRelease =false ;
	}
}

//-----------------------------------------------------------------------------
CMenuReactor::~CMenuReactor () {
	Detach () ;
}

//-----------------------------------------------------------------------------
void CMenuReactor::Attach () {
	Detach () ;
	if ( !mbAutoInitAndRelease ) {
		if ( acDocManager ) {
			acDocManager->addReactor (this) ;
			mbAutoInitAndRelease =true ;
		}
	}
}

void CMenuReactor::Detach () {
	if ( mbAutoInitAndRelease ) {
		if ( acDocManager ) {
			acDocManager->removeReactor (this) ;
			mbAutoInitAndRelease =false ;
		}
	}
}

AcApDocManager *CMenuReactor::Subject () const {
	return (acDocManager) ;
}

bool CMenuReactor::IsAttached () const {
	return (mbAutoInitAndRelease) ;
}

static boolean partialCuiUnloaded;

// -----------------------------------------------------------------------------
void CMenuReactor::documentLockModeChanged(AcApDocument * param2, AcAp::DocLockMode myPreviousMode, AcAp::DocLockMode myCurrentMode, AcAp::DocLockMode currentMode, const ACHAR * pGlobalCmdName)
{
	if( partialCuiUnloaded == false )
	{
		if((NULL != _tcsstr(pGlobalCmdName,_T("QUIT"))) || (NULL != _tcsstr(pGlobalCmdName,_T("EXIT"))))
		{
			veto();
			acDocManagerPtr()->sendStringToExecute(curDoc(),_T("(command \"_.cuiunload\" \"roofuklon\") "));
			partialCuiUnloaded = true;
			acDocManagerPtr()->sendStringToExecute(curDoc(),_T("_.QUIT "));
			return;
		}
	}

	AcApDocManagerReactor::documentLockModeChanged (param2, myPreviousMode, myCurrentMode, currentMode, pGlobalCmdName) ;
}
