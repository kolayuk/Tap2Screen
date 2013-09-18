/*
 ============================================================================
 Name		: Button.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CButton declaration
 ============================================================================
 */

#ifndef BUTTON_H
#define BUTTON_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknbutton.h>
#include <w32std.h>
#include <eiklabel.h>
//CONSTANTS
const TInt KDoubleDelay=1000; 

//CALLBACK M-Class
class MButtonCallBack
	{
public:
	virtual void LongTap()=0;
	virtual void Tap()=0;
	virtual void DoubleTap()=0;
	};

// CLASS DECLARATION
class CButton : public CBase, public MCoeControlObserver
	{
public:
	~CButton();
	static CButton* NewL(RWindowGroup* aWg,MButtonCallBack* aCB,TInt aResourceId);
	static CButton* NewLC(RWindowGroup* aWg,MButtonCallBack* aCB,TInt aResourceId);
	CAknButton* iButton;
	virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
	void Message(TDes& aTxt,TInt aInterval);
	void SetTransparentBackground(TBool aState);
	void SetTransparency(TInt aVal);
	static TInt Tick(TAny*);
	TBool iMoving;
	static TInt MsgTick(TAny* aObj);
	void UpdateScreen();
private:
	CButton();
	void ConstructL(RWindowGroup* aWg,MButtonCallBack* aCB,TInt aResourceId);
	MButtonCallBack* iCallBack;
	RWindowGroup* iWinGroup;
	TTime iTime1;
	TTime iTime2;
	CEikLabel* iLabel;
	CPeriodic* iMsgTimer;
	CPeriodic* iTimer;
	TInt iCount;
	};

#endif // BUTTON_H
