/*
========================================================================
 Name        : Tap2ScreenDocument.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated User Includes]
#include "Tap2ScreenDocument.h"
#include "Tap2ScreenAppUi.h"
// ]]] end generated region [Generated User Includes]

#include <apgwgnam.h>
/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CTap2ScreenDocument::CTap2ScreenDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CTap2ScreenDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CTap2ScreenDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CTap2ScreenDocument
 */
CTap2ScreenDocument* CTap2ScreenDocument::NewL( CEikApplication& aApp )
	{
	CTap2ScreenDocument* self = new ( ELeave ) CTap2ScreenDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CTap2ScreenDocument::CreateAppUiL()
	{
	return new ( ELeave ) CTap2ScreenAppUi;
	}
void CTap2ScreenDocument::UpdateTaskNameL(CApaWindowGroupName* aWg)
	{
	//TLex conv;
	//TInt hide;
	//conv.Assign(((CTap2ScreenAppUi*)iAppUi)->iSettings->MdcaPoint(18));
	//conv.Val(hide);
	CAknDocument::UpdateTaskNameL(aWg);
	aWg->SetSystem(ETrue);
	//aWg->SetHidden(hide==1?ETrue:EFalse);
	}
				
