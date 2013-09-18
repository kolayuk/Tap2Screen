/*
 * FgrObserver.cpp
 *
 *  Created on: 24.10.2009
 *      Author: Avis
 */

#include "FgrObserver.h"
#include <apgtask.h>
#include <apgwgnam.h> //CApaWindowGroupName
#ifdef _DEBUG
#include <e32debug.h>
#endif

CFgrObserver* CFgrObserver::NewL(RWsSession& aWsSession,MFgrCallBack& aCallBack)
	{
	CFgrObserver* self = CFgrObserver::NewLC(aWsSession,aCallBack);
	CleanupStack::Pop(self);
	return self;
	}
 
 
CFgrObserver* CFgrObserver::NewLC(RWsSession& aWsSession,MFgrCallBack& aCallBack)
	{
	CFgrObserver* self = new (ELeave) CFgrObserver(aWsSession,aCallBack);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
 
 
CFgrObserver::CFgrObserver(RWsSession& aWsSession,MFgrCallBack& aCallBack)
:CActive(EPriorityHigh),iCallBack(aCallBack), iWsSession(aWsSession), iWg(aWsSession)
{
}
 
CFgrObserver::~CFgrObserver()
{
	Cancel();
	iWg.Close();
}
 
void CFgrObserver::ConstructL()
{
	CActiveScheduler::Add(this);
 
	User::LeaveIfError(iWg.Construct((TUint32)&iWg, EFalse));
	iWg.SetOrdinalPosition(-1);
	iWg.EnableReceiptOfFocus(EFalse);
 
	CApaWindowGroupName* wn=CApaWindowGroupName::NewLC(iWsSession);
	wn->SetHidden(ETrue);
	wn->SetWindowGroupName(iWg);
	CleanupStack::PopAndDestroy();
 
//	User::LeaveIfError(iWg.EnableGroupChangeEvents());
	User::LeaveIfError(iWg.EnableFocusChangeEvents());
	User::LeaveIfError(iWg.EnableScreenChangeEvents());
//	User::LeaveIfError(iWg.EnableVisibilityChangeEvents());
//	iTaskList = new (ELeave) TApaTaskList(iWsSession);
 
	Listen();
}
 
void CFgrObserver::RunL()
	{
		TWsEvent wsEvent;
		iWsSession.GetEvent(wsEvent); 
		switch (wsEvent.Type())
			{
			case EEventScreenDeviceChanged:
				{
					//you will get notification here, do whatever you want to do here.
				iCallBack.ScreenChangeEventL();	
				break;
				}
			default:
				iCallBack.ForegroundEventL();
				break;
			}	 

		if (iStatus != KErrCancel) 
		{
			Listen();
		}
	}
 
void CFgrObserver::DoCancel()
{
	iWsSession.EventReadyCancel();
}
 
void CFgrObserver::Listen()
{
	iWsSession.EventReady(&iStatus);
	SetActive();
}
