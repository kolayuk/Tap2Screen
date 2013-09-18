/*
 * FgrObserver.h
 *
 *  Created on: 24.10.2009
 *      Author: Avis
 */

#ifndef FGROBSERVER_H_
#define FGROBSERVER_H_

#include <apgtask.h>
#include <w32std.h>
class MFgrCallBack 
{
public:
	virtual void ForegroundEventL() = 0;
	virtual void ScreenChangeEventL() = 0;	
};
 
class CFgrObserver : public CActive 
{
public:
	static CFgrObserver* NewL(RWsSession& aWsSession,MFgrCallBack& aCallBack);
	static CFgrObserver* NewLC(RWsSession& aWsSession,MFgrCallBack& aCallBack);
	virtual ~CFgrObserver();
private:
	CFgrObserver(RWsSession& aWsSession,MFgrCallBack& aCallBack);
	void ConstructL();
	void RunL();
	void DoCancel();
	void Listen();
private:
	MFgrCallBack& 	iCallBack;
	RWsSession&     iWsSession;
	RWindowGroup    iWg; 
//	TApaTaskList*	iTaskList;
};
#endif /* FGROBSERVER_H_ */
