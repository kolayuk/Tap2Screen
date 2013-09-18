/*
========================================================================
 Name        : Tap2ScreenAppUi.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef TAP2SCREENAPPUI_H
#define TAP2SCREENAPPUI_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknviewappui.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CMainView;
// ]]] end generated region [Generated Forward Declarations]

#include <w32std.h>
#include <button.h>
#include <FgrObserver.h>
#include <AudioPlayer.h>
#include <hwrmvibra.h>

#include <sensrvchannel.h>
#include <sensrvproximitysensor.h>
#include <sensrvdatalistener.h>

/**
 * 
 * @class	CTap2ScreenAppUi Tap2ScreenAppUi.h
 * @brief The AppUi class handles application-wide aspects of the user interface, including
 *        view management and the default menu, control pane, and status pane.
 */
class CTap2ScreenAppUi : public CAknViewAppUi, public MButtonCallBack, public MFgrCallBack, public MSensrvDataListener
	{
public: 
	// constructor and destructor
	CTap2ScreenAppUi();
	virtual ~CTap2ScreenAppUi();
	void ConstructL();
	TBool ReadSettings();
	void WriteSettings();
	CDesCArray* iSettings;
	TBool GlobalMsgQuery(TPtrC aText,TPtrC aHeader);
	RWindowGroup* iWinGroup;
	CButton* iButton;
	TBuf<255> iScreenName;
	CIdle* iIdle;
	void DoScreens();
	static TInt stDoScreens(TAny* aObj);
	void UpdatePos();
	TBuf<255> Screen();
	void Tap();
	void LongTap();
	void DoubleTap();
	void MoveModeChanged(TBool aMode);
	CFbsBitmap* AddWaterMark(CFbsBitmap* aBitmap);
	TTime iTime1;
	TTime iTime2;
	void ScreenChangeEventL();
	void ForegroundEventL();
	CFgrObserver* iObserver;
	RWsSession* iSession;
	void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDest);
	TPoint iMovePoint1;
	TPoint iMovePoint2;
	CPlayerUtility* iPlayer;
	CHWRMVibra* iVibra;
	
	TSensrvChannelInfo iSensorInfo;
	void DataReceived( CSensrvChannel& aChannel, TInt aCount, TInt aDataLost );
	void DataError( CSensrvChannel& aChannel, TSensrvErrorSeverity aError );
	void GetDataListenerInterfaceL( TUid aInterfaceUid, TAny*& aInterface );
	CSensrvChannel* iSensrvChannel;
	TInt iCount;
	CPeriodic* iTimer;
	static TInt Tick(TAny* aObj);
	void SensorPressed(TBool aDown);
	TSensrvProximityData::TProximityState iLastState;
	TTime iTimeSensorPressed;
	TTime iTimeSensorReleased;
	TBool iSensorActive;
	
	
public:
	// from CCoeAppUi
	TKeyResponse HandleKeyEventL(
				const TKeyEvent& aKeyEvent,
				TEventCode aType );

	// from CEikAppUi
	void HandleCommandL( TInt aCommand );
	void HandleResourceChangeL( TInt aType );

	// from CAknAppUi
	void HandleViewDeactivation( 
			const TVwsViewId& aViewIdToBeDeactivated, 
			const TVwsViewId& aNewlyActivatedViewId );

private:
	void InitializeContainersL();
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CMainView* iMainView;
	// ]]] end generated region [Generated Instance Variables]
	
	
	// [[[ begin [User Handlers]
protected: 
	// ]]] end [User Handlers]
	
	};

#endif // TAP2SCREENAPPUI_H			
