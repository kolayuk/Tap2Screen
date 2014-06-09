/*
========================================================================
 Name        : Tap2ScreenAppUi.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
#include <Tap2Screen.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "Tap2ScreenAppUi.h"
#include "Tap2Screen.hrh"
#include "Main.hrh"
#include "MainView.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]


#include <const.h>
#include <bautils.h>
#include <aknglobalmsgquery.h>
#include <APGWGNAM.H>
#include <aknglobalnote.h>
#include <ImageConversion.h>
#include <Tap2Screen_aif.mbg>
#include <Button.h>
#include <aknquerydialog.h>
#include <uriutils.h>
#include <hwrmvibra.h>
#include <AudioPlayer.h>
#include <touchfeedback.h>
#include <logger.h>
enum TPlatform
	{
	ESymbian94=1,
	ESymbian3
	};

#include <sensrvchannel.h>
#include <sensrvproximitysensor.h>
#include <sensrvchannelfinder.h>
#include <sensrvchannelinfo.h>

/**
 * Construct the CTap2ScreenAppUi instance
 */ 
CTap2ScreenAppUi::CTap2ScreenAppUi(): MSensrvDataListener()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The appui's destructor removes the container from the control
 * stack and destroys it.
 */
CTap2ScreenAppUi::~CTap2ScreenAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	delete iObserver;
	iSession->Close();
	delete iButton;
	delete iSettings;
	}

// [[[ begin generated function: do not modify
void CTap2ScreenAppUi::InitializeContainersL()
	{
	iMainView = CMainView::NewL();
	AddViewL( iMainView );
	SetDefaultViewL( *iMainView );
	}
// ]]] end generated function

/**
 * Handle a command for this appui (override)
 * @param aCommand command id to be handled
 */
void CTap2ScreenAppUi::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{ // code to dispatch to the AppUi's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
		if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
			{
			Exit();
			}
		}
	// ]]] end generated region [Generated Code]
	}

/** 
 * Override of the HandleResourceChangeL virtual function
 */
void CTap2ScreenAppUi::HandleResourceChangeL( TInt aType )
	{
	CAknViewAppUi::HandleResourceChangeL( aType );
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}
				
/** 
 * Override of the HandleKeyEventL virtual function
 * @return EKeyWasConsumed if event was handled, EKeyWasNotConsumed if not
 * @param aKeyEvent 
 * @param aType 
 */
TKeyResponse CTap2ScreenAppUi::HandleKeyEventL(
		const TKeyEvent& aKeyEvent,
		TEventCode aType )
	{
	// The inherited HandleKeyEventL is private and cannot be called
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	return EKeyWasNotConsumed;
	}

/** 
 * Override of the HandleViewDeactivation virtual function
 *
 * @param aViewIdToBeDeactivated 
 * @param aNewlyActivatedViewId 
 */
void CTap2ScreenAppUi::HandleViewDeactivation( 
		const TVwsViewId& aViewIdToBeDeactivated, 
		const TVwsViewId& aNewlyActivatedViewId )
	{
	CAknViewAppUi::HandleViewDeactivation( 
			aViewIdToBeDeactivated, 
			aNewlyActivatedViewId );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here. 
 */ 
void CTap2ScreenAppUi::ConstructL()
	{
	iSettings=new (ELeave) CDesCArrayFlat(3);
 
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KFirstStartFile))
		{
		CEikonEnv::Static()->FsSession().Delete(KFirstStartFile);
		if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KSettingPath)){CEikonEnv::Static()->FsSession().Delete(KSettingPath);}
		}
	TBool ex=ReadSettings();
	CEikonEnv::Static()->FsSession().MkDirAll(iSettings->MdcaPoint(3));
#ifdef __S60_5X__
	// [[[ begin generated region: do not modify [Generated Contents]
	BaseConstructL( EAknEnableSkin ); 
	InitializeContainersL();
	// ]]] end generated region [Generated Contents]
#else
	BaseConstructL(EAknEnableSkin); 
	InitializeContainersL();
#endif
		iWinGroup=new (ELeave) RWindowGroup(CEikonEnv::Static()->WsSession());
		iWinGroup->Construct((TUint32)&iWinGroup, EFalse);
		iWinGroup->EnableReceiptOfFocus(EFalse); // Don't capture any key events.
		iWinGroup->SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront+6);
		//iWindow=new (ELeave) RWindow(CEikonEnv::Static()->WsSession());
		//iWindow->Construct(*iWinGroup, (TUint32)&*iWindow);
		CApaWindowGroupName* wn=CApaWindowGroupName::NewL(CEikonEnv::Static()->WsSession());
		wn->SetHidden(ETrue);
		wn->SetSystem(ETrue);
		wn->SetWindowGroupName(*iWinGroup);
		delete wn;
		iTimeSensorPressed.HomeTime();
		iTimeSensorReleased.HomeTime();
		CSensrvChannelFinder* SensrvChannelFinder = CSensrvChannelFinder::NewL();
		RSensrvChannelInfoList ChannelInfoList;
		TSensrvChannelInfo mySearchConditions;
		mySearchConditions.iChannelDataTypeId = KSensrvChannelTypeIdProximityMonitor;
		SensrvChannelFinder->FindChannelsL(ChannelInfoList,mySearchConditions);
		iSensorInfo=ChannelInfoList[0];
		iSensorActive=EFalse;
		if (iSettings->MdcaPoint(16).Find(_L("1"))!=KErrNotFound)
			{
			iSensrvChannel = CSensrvChannel::NewL( iSensorInfo );
			iSensrvChannel->OpenChannelL();
			iSensrvChannel->StartDataListeningL( this, 1,1,0);
			iSensorActive=ETrue;
			}
		ChannelInfoList.Close();
		delete SensrvChannelFinder;
		iButton=CButton::NewL(iWinGroup,this,R_SCREEN_BUTTON);
		iButton->SetTransparentBackground(ETrue);
		UpdatePos();
		iButton->iButton->ActivateL();
		iSession= new (ELeave)RWsSession();
		iSession->Connect();
		iObserver=CFgrObserver::NewL(*iSession,*this);
		iVibra=CHWRMVibra::NewL();
		iIdle=CIdle::NewL(CActive::EPriorityIdle);
		if (ex)
			{
			if (iSettings->MdcaPoint(17).Find(_L("0"))!=KErrNotFound)
				{CEikonEnv::Static()->RootWin().SetOrdinalPosition(-4);}
			else 
				{
				TApaTaskList list(*iSession);
				TApaTask task=list.FindByPos(2);
				if (task.Exists()){task.BringToForeground();}
				}
			}	
	}




TBool CTap2ScreenAppUi::ReadSettings()
	{
	TInt err=KErrNone;
	iSettings->Reset();
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KSettingPath)) //!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
		TBuf<255> val;
		RFile filesave;
		TBuf<10> t;
		TFileText ft;
		filesave.Open(CEikonEnv::Static()->FsSession(), KSettingPath, EFileRead);
		ft.Set(filesave);
		while (ft.Read(val)==KErrNone)
			{
			iSettings->AppendL(val);
			}
		filesave.Close();
		TInt count;
		TLex conv;
		conv.Assign(iSettings->MdcaPoint(19));
		conv.Val(count);
		count=count+1;
		iSettings->Delete(19,1);
		TBuf<255> b; b.Num(count);
		iSettings->InsertL(19,b);
		
		return ETrue;
		}
	else
		{
		TParse parse;
		CEikonEnv::Static()->FsSession().Parse(KSettingPath,parse);
		if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),parse.DriveAndPath()))
			{
			CEikonEnv::Static()->FsSession().MkDirAll(parse.DriveAndPath());
			}
		iSettings->AppendL(KPosX);
		iSettings->AppendL(KPosY);
		iSettings->AppendL(KPosXLand);
		iSettings->AppendL(KPosYLand);
		iSettings->AppendL(KTransparency);
		iSettings->AppendL(KSize);
		iSettings->AppendL(KPath);
		iSettings->AppendL(KFormat);
		iSettings->AppendL(KBaseName);
		iSettings->AppendL(KQuality);
		iSettings->AppendL(KWaterMarkPath);
		iSettings->AppendL(KHideButtonOnScreen);
		iSettings->AppendL(KPlaySound);
		iSettings->AppendL(KVibrate);
		iSettings->AppendL(KDelayBeforeScreen);
		iSettings->AppendL(KAmountOfScreens);
		iSettings->AppendL(KProximitySensor);
		iSettings->AppendL(KSwitchToPrev);
		iSettings->AppendL(KHideInTasklist);
		
		TBuf<255> KMask;	
		KMask.Append(iSettings->MdcaPoint(8));
		KMask.Append(_L("*"));
		KMask.Append(iSettings->MdcaPoint(7)); //for select by extension
		CDir* results=NULL;
		TFindFile findFiles(CEikonEnv::Static()->FsSession());
		findFiles.FindWildByDir(KMask,iSettings->MdcaPoint(6),results);
		if (results!=NULL){
			TBuf<255> b;
			b.Num(results->Count());
			iSettings->AppendL(b);
		}
		else iSettings->AppendL(KScreensCaptured);
		
		//WriteSettings();
		return EFalse;
		}
	return EFalse;
	}
void CTap2ScreenAppUi::WriteSettings()
	{
		RFs iFS=CEikonEnv::Static()->FsSession();
		RFile filesave;
		TInt err1=filesave.Replace(iFS, KSettingPath, EFileWrite);
		TFileText ft;
		ft.Set(filesave);
		TInt i;
		for (i=0;i<iSettings->Count();i++)
			{
			ft.Write(iSettings->MdcaPoint(i));
			}
		filesave.Close();
	}

TBool CTap2ScreenAppUi::GlobalMsgQuery(TPtrC aText,TPtrC aHeader)
	{
	
	    TInt queryAnswer = 1;
	    char* querystr = NULL;
	    int querystr_l = 0;
	    char* headerstr = NULL;
	    int headerstr_l = 0;
	    TRequestStatus msgQueryStatus = KRequestPending;
	    TRequestStatus timerStatus = KRequestPending;
	    int delayInSeconds = 0;
	    TInt timeout = 0;
	    
	    TTimeIntervalMicroSeconds32 timeoutValue = TTimeIntervalMicroSeconds32(timeout);

	    CAknGlobalMsgQuery *msgQueryDialog = NULL;
	    
	    TRAPD(err,
	        {
	            msgQueryDialog = CAknGlobalMsgQuery::NewL();
	        });
	    CleanupStack::PushL(msgQueryDialog);
	    TRAPD(err1,
	        {
	            msgQueryDialog->ShowMsgQueryL(msgQueryStatus,aText,R_AVKON_SOFTKEYS_OK_CANCEL,aHeader, KNullDesC);
	        });
	    if(err1 != KErrNone||err!=KErrNone){
	       CleanupStack::PopAndDestroy(msgQueryDialog);
	    } 
		User::WaitForRequest(msgQueryStatus);
	    
	    CleanupStack::PopAndDestroy(msgQueryDialog);
	    return msgQueryStatus.Int() == EAknSoftkeyOk ? 1 : 0;		
	}


void CTap2ScreenAppUi::Tap()
	{
	if (iIdle->IsActive()){iIdle->Cancel();}
	iIdle->Start(TCallBack(stDoScreens,this));
	WriteSettings();
	}
TInt CTap2ScreenAppUi::stDoScreens(TAny* aObj)
	{
	if (((CTap2ScreenAppUi*)aObj)->iIdle->IsActive()){((CTap2ScreenAppUi*)aObj)->iIdle->Cancel();}
	((CTap2ScreenAppUi*)aObj)->DoScreens();
	return 0;
	}
void CTap2ScreenAppUi::DoScreens()
	{
	TInt delay; TLex conv(iSettings->MdcaPoint(14)); conv.Val(delay);
	TInt count; TLex conv2(iSettings->MdcaPoint(15)); conv2.Val(count);
	TBool hide=EFalse,sound=EFalse,vibrate=EFalse;
	if (iSettings->MdcaPoint(11).Compare(_L("1"))==0&&iSettings->MdcaPoint(16).Compare(_L("0"))==0){hide=ETrue;}
	if (iSettings->MdcaPoint(12).Compare(_L("1"))==0){sound=ETrue;}
	if (iSettings->MdcaPoint(13).Compare(_L("1"))==0){vibrate=ETrue;}
	if (hide){iButton->iButton->MakeVisible(EFalse);}
	iButton->UpdateScreen();
	TBuf<255> fn(_L(" "));
	for (TInt i=0;i<count;i++)
		{
		if (delay>0){User::After(delay*1000+1);}
		User::After(100000);
		fn.Copy(Screen());
		User::After(100000);
		}
	if (hide){iButton->iButton->MakeVisible(ETrue);}
	iButton->UpdateScreen();
	if (sound) 
			{TRAPD(err,{CPlayerUtility* player=CPlayerUtility::NewL(KSoundPath);});}
	if (vibrate)
			{
			TRAPD(err,{iVibra->StartVibraL(KVibraDuration,KVibraIntensivity);})
			TBuf<25> a; a.Num(err); CEikonEnv::Static()->InfoMsg(a); 
			}
	if (count==1&&iSettings->MdcaPoint(16).Find(_L("0"))!=KErrNotFound)
		{iButton->Message(fn,1000);}
	if (count==1&&iSettings->MdcaPoint(16).Find(_L("1"))!=KErrNotFound)
			{
			CAknGlobalNote* Note=CAknGlobalNote::NewL();
			TRequestStatus status=KRequestPending;
			Note->ShowNoteL(status,EAknGlobalInformationNote,fn);
			User::WaitForRequest(status);
			delete Note;
			}
	}
void CTap2ScreenAppUi::LongTap()
	{
	
	Exit();
	}
void CTap2ScreenAppUi::DoubleTap()
	{
	TInt Resource;
	TBuf<255> txt;
	iButton->iMoving=!iButton->iMoving;
	if (iButton->iMoving)
		{Resource=R_MOVE_BUTTON;}
	else {Resource=R_NOT_MOVE_BUTTON;}
	CEikonEnv::Static()->ReadResource(txt,Resource);
	iButton->Message(txt,1000);
	MoveModeChanged(iButton->iMoving);
	}
void CTap2ScreenAppUi::UpdatePos()
	{
	TInt X; TInt Y;
	TInt size;
	TInt transp;
	TLex conv;
	TInt proximity;
	TInt hide;
	
	TInt scrX=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
	TInt scrY=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;
	if (scrY>scrX)
		{ //portrait
		conv.Assign(iSettings->MdcaPoint(0));
		conv.Val(X);
		conv.Assign(iSettings->MdcaPoint(1));
		conv.Val(Y);
		}
	else
		{
		conv.Assign(iSettings->MdcaPoint(2));
		conv.Val(X);
		conv.Assign(iSettings->MdcaPoint(3));
		conv.Val(Y);
		}
	
	conv.Assign(iSettings->MdcaPoint(5));
	conv.Val(size);
	conv.Assign(iSettings->MdcaPoint(4));
	conv.Val(transp);	
	conv.Assign(iSettings->MdcaPoint(16));
	conv.Val(proximity);
	conv.Assign(iSettings->MdcaPoint(18));
	conv.Val(hide);
	
	iButton->SetTransparency(transp);
	iButton->iButton->SetPosition(TPoint(X,Y));
	iButton->iButton->SetSize(TSize(size,size));
	iButton->iButton->DrawNow();
	
	if (proximity)
		{
		iButton->iButton->MakeVisible(EFalse);
		if (!iSensorActive)
			{
			iSensrvChannel=CSensrvChannel::NewL(iSensorInfo);
			iSensrvChannel->OpenChannelL();
			iSensrvChannel->StartDataListeningL( this, 1,1,0);
			iSensorActive=ETrue;
			}
		}
	else 
		{
		iButton->iButton->MakeVisible(ETrue);
		if (iSensorActive)
			{
			_LOG(_L("Disable sensor by block"));
			iSensrvChannel->StopDataListening();
			iSensrvChannel->CloseChannel();
			if (iSensrvChannel) {delete iSensrvChannel;}
			iSensorActive=EFalse;
			}
		}
	
		CCoeEnv *env = CCoeEnv::Static();
		TInt wgId = env->RootWin().Identifier();
		RWsSession session = env->WsSession();
		CApaWindowGroupName *wgName = CApaWindowGroupName::NewL(session, wgId);
		wgName->SetHidden(hide==1?ETrue:EFalse);
		wgName->SetWindowGroupName(env->RootWin());
		CEikonEnv::Static()->iWgName=wgName;
	CEikonEnv::Static()->WsSession().Flush();
	}

TBuf<255> CTap2ScreenAppUi::Screen()
	{
	_LIT(KMaskEnd,"*");
	TBuf<255> KMask;
	KMask.Append(iSettings->MdcaPoint(8));
	KMask.Append(_L("*"));
	KMask.Append(iSettings->MdcaPoint(7)); //for select by extension
	
	
	_LIT8(KMimeType,"image/jpeg");
	if (iSettings->MdcaPoint(7).Find(_L("jpg"))!=KErrNotFound)
		{_LIT8(KMimeType,"image/jpeg");}
	else if (iSettings->MdcaPoint(7).Find(_L("png"))!=KErrNotFound)
		{_LIT8(KMimeType,"image/png");}
	else 
		{_LIT8(KMimeType,"image/jpeg");}

	if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),iSettings->MdcaPoint(6))){CEikonEnv::Static()->FsSession().MkDirAll(iSettings->MdcaPoint(6));}
	TInt count=0;
	CDir* results=NULL;
	TBuf<255> filename;
	/*
	while (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),filename))
		{
		count+=1;
		filename.Copy(iSettings->MdcaPoint(6));
		filename.Append(iSettings->MdcaPoint(8));
		filename.AppendNum(count);
		filename.Append(iSettings->MdcaPoint(7));
		}
	*/
	TLex conv;
	conv.Assign(iSettings->MdcaPoint(19));
	conv.Val(count);
	count=count+1;
	filename.Copy(iSettings->MdcaPoint(6));
	filename.Append(iSettings->MdcaPoint(8));
	filename.AppendNum(count);
	filename.Append(iSettings->MdcaPoint(7));
	iSettings->Delete(19,1);
	TBuf<255> b; b.Num(count);
	iSettings->InsertL(19,b);
	//User::After(100000);
	
	CFbsBitmap* Bitmap= new (ELeave) CFbsBitmap();
	Bitmap->Create(CEikonEnv::Static()->ScreenDevice()->SizeInPixels(),CEikonEnv::Static()->ScreenDevice()->DisplayMode());
	CEikonEnv::Static()->ScreenDevice()->CopyScreenToBitmap(Bitmap);
	
	//delete Bitmap;
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),iSettings->MdcaPoint(10)))
		{Bitmap=AddWaterMark(Bitmap);}
	
	TInt q;
	TLex conv1(iSettings->MdcaPoint(9));
	conv1.Val(q);
	
	TJpegImageData *imageData=new (ELeave) TJpegImageData;
	imageData->iSampleScheme=TJpegImageData::EColor444;
	imageData->iQualityFactor=q;
	CFrameImageData* iFrameImageData=CFrameImageData::NewL();
	iFrameImageData->AppendImageData(imageData); // assumes ownership of imageData
	
	CImageEncoder* coder=CImageEncoder::FileNewL(CEikonEnv::Static()->FsSession(),filename,KMimeType,CImageEncoder::EOptionAlwaysThread);
	TRequestStatus status=KRequestPending;
	coder->Convert(&status,*Bitmap,iFrameImageData);
	User::WaitForRequest(status);

	TBuf<255> t;
	t.Copy(iSettings->MdcaPoint(8));
	t.AppendNum(count);
	t.Append(iSettings->MdcaPoint(7));
	delete Bitmap; delete coder; delete iFrameImageData;
	return t;
	}
CFbsBitmap* CTap2ScreenAppUi::AddWaterMark(CFbsBitmap* aBitmap)
	{
	CGulIcon* Icon=CEikonEnv::Static()->CreateIconL(iSettings->MdcaPoint(10),0,1);
	CFbsBitmap* Bitmap=new(ELeave) CFbsBitmap();
	Bitmap->Create(aBitmap->SizeInPixels(),EColor16M);
		
	CFbsBitmapDevice* BitDevice=CFbsBitmapDevice::NewL(Bitmap);
	CFbsBitGc* BitGc;
	BitDevice->CreateContext(BitGc);
	BitGc->BitBlt(TPoint(0,0),aBitmap);
	BitGc->BitBltMasked(TPoint(0,0),Icon->Bitmap(),TRect(Icon->Bitmap()->SizeInPixels()),Icon->Mask(),ETrue);
	delete Icon;
	delete aBitmap;
	delete BitDevice;
	delete BitGc;
	return Bitmap;
	}
void CTap2ScreenAppUi::ScreenChangeEventL()
	{
	UpdatePos();
	}
void CTap2ScreenAppUi::HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDest)
	{
	if (aEvent.Type()==EEventPointer)
		{
		TPointerEvent p=*aEvent.Pointer();
		if (aDest==iButton->iButton&&iButton->iMoving)
			{
			if (p.iType==p.EButton1Down)
				{
				iMovePoint1=p.iPosition;
				}
			else if (p.iType==p.EDrag)
				{
				TBuf<255> X; TBuf<255> Y;
				TInt npX; TInt npY;
				TInt scrX=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
				TInt scrY=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;
				
				npX=iButton->iButton->Position().iX+(p.iPosition.iX-iMovePoint1.iX);
				npY=iButton->iButton->Position().iY+(p.iPosition.iY-iMovePoint1.iY);
				X.Num(npX);
				Y.Num(npY);
				if (scrY>scrX)
					{ //portrait
					iSettings->Delete(0);
					iSettings->InsertL(0,X);
					iSettings->Delete(1);
					iSettings->InsertL(1,Y);					
					}
				else
					{
					iSettings->Delete(2);
					iSettings->InsertL(2,X);
					iSettings->Delete(3);
					iSettings->InsertL(3,Y);
					}
				UpdatePos();
				}
			}
		}
	CAknAppUi::HandleWsEventL(aEvent,aDest);
	}
void CTap2ScreenAppUi::MoveModeChanged(TBool aMode)
	{
	if (!aMode){iMainView->PosChanged(iButton->iButton->Position());}
	}

void CTap2ScreenAppUi::DataReceived( CSensrvChannel& aChannel, TInt aCount, TInt aDataLost )
    {
	_LOG(_L("DataReceived"));
    if ( aChannel.GetChannelInfo().iChannelType ==  KSensrvChannelTypeIdProximityMonitor )
        {
        TSensrvProximityData data;
        for( TInt i = 0; i < aCount; i++ )
            {
            TPckgBuf<TSensrvProximityData> dataBuf;
            aChannel.GetData( dataBuf );
            data = dataBuf();
            TSensrvProximityData::TProximityState state = data.iProximityState;
            if ( iLastState != state )
                {
                if( state == TSensrvProximityData::EProximityIndiscernible )
                    {
                    //button up
                    SensorPressed( EFalse );
                }
                if( state == TSensrvProximityData::EProximityDiscernible )
                    {
                    //button down
                    SensorPressed( ETrue );
                    }
                }
            iLastState = state;
            }
        }
    //dataRequested = EFalse;
    }
void CTap2ScreenAppUi::SensorPressed(TBool aDown)
	{
	_LOGDATA(_L("CTap2ScreenAppUi::SensorPressed(%d)"),aDown);
	/* old solution
	if (aDown)
		{
		iCount=0;
		if (iTimer->IsActive()){iTimer->Cancel();}
		iTimer->Start(1000000,1000000,TCallBack(Tick,this));
		}
	iCount++;
	*/
	if (aDown){iTimeSensorPressed.HomeTime();}
	else {iTimeSensorReleased.HomeTime();}
	if (!aDown)
		{
		if ((Abs((TInt)iTimeSensorPressed.MicroSecondsFrom(iTimeSensorReleased).Int64())>KProximityMin*1000)&&((Abs((TInt)iTimeSensorPressed.MicroSecondsFrom(iTimeSensorReleased).Int64())<KProximityMax*1000)))
			{
			DoScreens();
			}
		//else if (Abs((TInt)iTimeSensorPressed.MicroSecondsFrom(iTimeSensorReleased).Int64())>KProximityExit*1000)
		//	{
		//	Exit();
		//	}
		}
	}
void CTap2ScreenAppUi::DataError(CSensrvChannel& aChannel, enum TSensrvErrorSeverity aErr)
	{
	
	}
void CTap2ScreenAppUi::GetDataListenerInterfaceL( TUid aInterfaceUid, TAny*& aInterface )
	{
	
	}
void CTap2ScreenAppUi::ForegroundEventL()
	{
	TInt id=iSession->GetFocusWindowGroup();
	CApaWindowGroupName* gn = CApaWindowGroupName::NewL(*iSession, id);
	TBuf<255> uid;
	uid.Num((TUint32)gn->AppUid().iUid,EHex);
	_LOGDATA(_L("FgrEvent %S"),&uid);
	delete gn;
	iWinGroup->SetOrdinalPosition(-1,ECoeWinPriorityNeverAtFront-6);
	iWinGroup->SetOrdinalPosition(0,ECoeWinPriorityAlwaysAtFront+6);
	iButton->iButton->DrawNow();
	CEikonEnv::Static()->WsSession().Flush();
	}
