/*
========================================================================
 Name        : Tap2ScreenDocument.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef TAP2SCREENDOCUMENT_H
#define TAP2SCREENDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CTap2ScreenDocument Tap2ScreenDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CTap2ScreenDocument : public CAknDocument
	{
public: 
	// constructor
	static CTap2ScreenDocument* NewL( CEikApplication& aApp );

private: 
	// constructors
	CTap2ScreenDocument( CEikApplication& aApp );
	void ConstructL();
	void UpdateTaskNameL(CApaWindowGroupName* aWg);
	
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // TAP2SCREENDOCUMENT_H
