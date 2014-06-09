/*
========================================================================
 Name        : MainView.cpp
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
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <Tap2Screen.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "Tap2Screen.hrh"
#include "MainView.h"
#include "Main.hrh"
#include "Main.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

#include <Tap2ScreenAppUi.h>
#include <FileSelectDialog.h>
#include <aknquerydialog.h>
#include <apgcli.h>
#include <apparc.h>

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CMainView::CMainView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iMain = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CMainView::~CMainView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iMain;
	iMain = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CMainView
 */
CMainView* CMainView::NewL()
	{
	CMainView* self = CMainView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CMainView
 */
CMainView* CMainView::NewLC()
	{
	CMainView* self = new ( ELeave ) CMainView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CMainView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_MAIN_MAIN_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	}

/**
 * @return The UID for this view
 */
TUid CMainView::Id() const
	{
	return TUid::Uid( EMainViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CMainView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
	
		case EAknSoftkeyExit:
			commandHandled = HandleControlPaneRightSoftKeyPressedL( aCommand );
			break;
		case EMainView_MenuItemCommand:
			commandHandled = Handle_MenuItemSelectedL( aCommand );
			break;
		case EMainView_MenuItem1Command:
			commandHandled = Handle_MenuItem1SelectedL( aCommand );
			break;
		case EMainView_MenuItem3Command:
			commandHandled = Handle_MenuItem3SelectedL( aCommand );
			break;
		case EMainView_MenuItem4Command:
			commandHandled = OtherApps( aCommand );
			break;
		case EMainView_MenuItem2Command:
			commandHandled = Handle_MenuItem2SelectedL( aCommand );
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		if ( aCommand == EAknSoftkeyExit )
			{
			AppUi()->HandleCommandL( EEikCmdExit );
			}
	
		}
	// ]]] end generated region [Generated Code]
	
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CMainView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iMain == NULL )
		{
		iMain = CreateContainerL();
		iMain->SetMopParent( this );
		AppUi()->AddToStackL( *this, iMain );
		} 
	// ]]] end generated region [Generated Contents]
	InitValues();
	}

/**
 */
void CMainView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iMain != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iMain );
		delete iMain;
		iMain = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CMainView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange();
	
	// this may fail, but we're not able to propagate exceptions here
	TVwsViewId view;
	AppUi()->GetActiveViewId( view );
	if ( view.iViewUid == Id() )
		{
		TInt result;
		TRAP( result, SetupStatusPaneL() );
		}
	
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}

// [[[ begin generated function: do not modify
void CMainView::SetupStatusPaneL()
	{
	// reset the context pane
	TUid contextPaneUid = TUid::Uid( EEikStatusPaneUidContext );
	CEikStatusPaneBase::TPaneCapabilities subPaneContext = 
		StatusPane()->PaneCapabilities( contextPaneUid );
	if ( subPaneContext.IsPresent() && subPaneContext.IsAppOwned() )
		{
		CAknContextPane* context = static_cast< CAknContextPane* > ( 
			StatusPane()->ControlL( contextPaneUid ) );
		context->SetPictureToDefaultL();
		}
	
	// setup the title pane
	TUid titlePaneUid = TUid::Uid( EEikStatusPaneUidTitle );
	CEikStatusPaneBase::TPaneCapabilities subPaneTitle = 
		StatusPane()->PaneCapabilities( titlePaneUid );
	if ( subPaneTitle.IsPresent() && subPaneTitle.IsAppOwned() )
		{
		CAknTitlePane* title = static_cast< CAknTitlePane* >( 
			StatusPane()->ControlL( titlePaneUid ) );
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_MAIN_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CMainView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CMain::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CMain
 */
CMain* CMainView::CreateContainerL()
	{
	return CMain::NewL( ClientRect(), NULL, this );
	}

/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::Handle_MenuItemSelectedL( TInt aCommand )
	{
	TInt index=iMain->ListBox()->CurrentItemIndex();
	HandleLBSelect(index);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::Handle_MenuItem1SelectedL( TInt aCommand )
	{
	//about
	TBuf<1024> header;
	CEikonEnv::Static()->ReadResource(header,R_ABOUT_HEADER);
	TBuf<1024> txt;
	CEikonEnv::Static()->ReadResource(txt,R_ABOUT_TEXT);
	txt.Append(_L("WMR R321502538916\nWMZ Z208634876649\nWMU U221598315212\nWME E234802202031\nYandex-Money: 41001686491180"));
	((CTap2ScreenAppUi*)AppUi())->GlobalMsgQuery(txt,header);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::Handle_MenuItem2SelectedL( TInt aCommand )
	{
	//exit
	AppUi()->Exit();
	return ETrue;
	}
				
void CMainView::HandleLBSelect(TInt aIndex)
	{
	CEikonEnv::Static()->InfoMsg(_L("ListBox select"));
	TBuf<255> newVal;
	TBuf<255> currVal;
	TBuf<255> text;
	currVal.Copy(((CTap2ScreenAppUi*)AppUi())->iSettings->MdcaPoint(aIndex));

	if (aIndex==0||aIndex==1||aIndex==2||aIndex==3||aIndex==4||aIndex==5||aIndex==9||aIndex==14||aIndex==15)
		{
		TBuf<255> title;
		TInt val;
		TLex conv(currVal);
		conv.Val(val);
		if (aIndex==0){CEikonEnv::Static()->ReadResource(title,R_POS_X_TXT);}
		else if (aIndex==1){CEikonEnv::Static()->ReadResource(title,R_POS_Y_TXT);}
		else if (aIndex==2){CEikonEnv::Static()->ReadResource(title,R_POS_X_LAND_TXT);}
		else if (aIndex==3){CEikonEnv::Static()->ReadResource(title,R_POS_Y_LAND_TXT);}
		else if (aIndex==4){CEikonEnv::Static()->ReadResource(title,R_TRANSPARENCY);}
		else if (aIndex==5){CEikonEnv::Static()->ReadResource(title,R_SIZE_TXT);}
		else if (aIndex==9){CEikonEnv::Static()->ReadResource(title,R_QUALITY_TXT);}
		else if (aIndex==14){CEikonEnv::Static()->ReadResource(title,R_DELAY_TXT);}
		else if (aIndex==15){CEikonEnv::Static()->ReadResource(title,R_AMOUNT_DIALOG);}
		if (!NumberQuery(title,val)){return;}
		newVal.Num(val);
		text.Copy(newVal);
		}
	if (aIndex==6||aIndex==10)
		{
		TBuf<255> title;
		TTypeOfSelect sel;
		if (aIndex==6){CEikonEnv::Static()->ReadResource(title,R_PATH_TXT);sel=EFolder;}
		else if (aIndex==10){CEikonEnv::Static()->ReadResource(title,R_WATERMARK_TXT);sel=EFile;}
		TBuf<255> KMask(_L("*"));
		TParse p;
		CEikonEnv::Static()->FsSession().Parse(currVal,p);
		TBuf<255> root(p.DriveAndPath());
		CFileSelectDialog* d=CFileSelectDialog::NewL(title,sel,root,KMask);
		newVal.Copy(d->Execute(currVal));
		text.Copy(newVal);
		}
	if (aIndex==7||aIndex==11||aIndex==12||aIndex==13||aIndex==16||aIndex==17||aIndex==18)
		{
		TBuf<255> title;
		
		if (aIndex==7)
			{
			CDesCArray* arr=CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_FORMAT_POPUP);
			CEikonEnv::Static()->ReadResource(title,R_FORMAT_TXT);
			TInt a=PopupMenu(title,0,arr);
			if (a==-1){delete arr;return;}
			newVal.Copy(arr->MdcaPoint(a));
			text.Copy(newVal);
			delete arr;
			}
		else if (aIndex==11)
			{
			TInt newValInt;
			TInt val; TLex conv(currVal); conv.Val(val);
			if (val==1){newValInt=0;}
			else {newValInt=1;}
			CDesCArray* arr=CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_HIDE_POPUP);
			text.Copy(arr->MdcaPoint(newValInt));
			newVal.Num(newValInt);
			delete arr;
			}
		else if (aIndex==12)
			{
			TInt newValInt;
			TInt val; TLex conv(currVal); conv.Val(val);
			if (val==1){newValInt=0;}
			else {newValInt=1;}
			CDesCArray* arr=CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_HIDE_POPUP);
			text.Copy(arr->MdcaPoint(newValInt));
			newVal.Num(newValInt);
			delete arr;
			}
		else if (aIndex==13)
			{
			TInt newValInt;
			TInt val; TLex conv(currVal); conv.Val(val);
			if (val==1){newValInt=0;}
			else {newValInt=1;}
			CDesCArray* arr=CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_HIDE_POPUP);
			text.Copy(arr->MdcaPoint(newValInt));
			newVal.Num(newValInt);
			delete arr;
			}
		else if (aIndex==16)
			{
			TInt newValInt;
			TInt val; TLex conv(currVal); conv.Val(val);
			if (val==1){newValInt=0;}
			else {newValInt=1;}
			CDesCArray* arr=CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_HIDE_POPUP);
			text.Copy(arr->MdcaPoint(newValInt));
			newVal.Num(newValInt);
			delete arr;
			}
		else if (aIndex==17)
			{
			TInt newValInt;
			TInt val; TLex conv(currVal); conv.Val(val);
			if (val==1){newValInt=0;}
			else {newValInt=1;}
			CDesCArray* arr=CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_HIDE_POPUP);
			text.Copy(arr->MdcaPoint(newValInt));
			newVal.Num(newValInt);
			delete arr;
			}
	else if (aIndex==18)
		{
		TInt newValInt;
		TInt val; TLex conv(currVal); conv.Val(val);
		if (val==1){newValInt=0;}
		else {newValInt=1;}
		CDesCArray* arr=CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_HIDE_POPUP);
		text.Copy(arr->MdcaPoint(newValInt));
		newVal.Num(newValInt);
		delete arr;
		}
	}
	if (aIndex==8)
		{
		TBuf<255> title;
		CEikonEnv::Static()->ReadResource(title,R_BASE_TXT);
		if(!TextQuery(title,currVal)){return;}
		newVal.Copy(currVal);
		text.Copy(newVal);
		}
	
	
	((CTap2ScreenAppUi*)AppUi())->iSettings->Delete(aIndex);
	((CTap2ScreenAppUi*)AppUi())->iSettings->InsertL(aIndex,newVal);
	ChangeItemSubtitle(aIndex,text);
	((CTap2ScreenAppUi*)AppUi())->WriteSettings();
	((CTap2ScreenAppUi*)AppUi())->UpdatePos();
	}

TInt CMainView::NumberQuery(TDes& aText,TInt& aNumber)
{
	CAknNumberQueryDialog* Dialog = CAknNumberQueryDialog::NewL(aNumber,CAknQueryDialog::ENoTone);
	Dialog->PrepareLC(R_NUMBER_QUERY);
	Dialog->SetPromptL(aText);
	return Dialog->RunLD();	
}
void CMainView::ChangeItemSubtitle(TInt aIndex,TDes16& aText)
	{
	TBuf<255> prev = iMain->ListBox()->Model()->ItemText(aIndex);
	TChar a = '\t'; 
	TInt pos = prev.LocateReverse(a); 
	if (pos != KErrNotFound) 
		{	 
    TInt replace_length = prev.Length() - pos;
    prev.Delete(pos+1, replace_length); 
    prev.Insert(pos+1, aText); 
		}
	CDesCArray* itemArray = static_cast<CDesCArray*> (iMain->ListBox()->Model()->ItemTextArray());
	itemArray->Delete(aIndex);
	itemArray->InsertL(aIndex,prev);
	iMain->ListBox()->DrawNow();
	}
TInt CMainView::PopupMenu(TDes& aTxt,TInt aDef,CDesCArray* itemList)
	{
	_LIT(KListItemFormat, "%S");
	CAknSinglePopupMenuStyleListBox* list = new(ELeave) CAknSinglePopupMenuStyleListBox;
	CleanupStack::PushL(list);
	CAknPopupList* popupList = CAknPopupList::NewL(list, R_AVKON_SOFTKEYS_OK_BACK, AknPopupLayouts::EMenuWindow);
	CleanupStack::PushL(popupList);    
	list->ConstructL(popupList, CEikListBox::ELeftDownInViewRect);
	list->CreateScrollBarFrameL(ETrue);
	list->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
		
	list->Model()->SetItemTextArray(itemList);
	list->Model()->SetOwnershipType(ELbmOwnsItemArray);
	list->ItemDrawer()->FormattedCellData()->EnableMarqueeL( ETrue );
	popupList->SetTitleL(aTxt);    
	CleanupStack::Pop();            // popuplist
	CleanupStack::Pop();	//list
	TBool popupOk = popupList->ExecuteLD();
	if (!popupOk)
		{
		return -1;
		}
	else 
		{
		TInt current=list->CurrentItemIndex();
		return current;
		}
	}
TInt CMainView::TextQuery(TDes& aTxt, TDes& aBuffer)
{
	CAknTextQueryDialog* Dialog =CAknTextQueryDialog::NewL(aBuffer,CAknQueryDialog::ENoTone);
	Dialog->PrepareLC(R_TEXT_QUERY);
	Dialog->SetPromptL(aTxt);
	return Dialog->RunLD();
}
/** 
 * Handle the rightSoftKeyPressed event.
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::HandleControlPaneRightSoftKeyPressedL( TInt aCommand )
	{
	CEikonEnv::Static()->RootWin().SetOrdinalPosition(-1);
	return ETrue;
	}
				
void CMainView::InitValues()
	{
	TInt i=0;
	TBuf<255> val;
	for (i=0; i<((CTap2ScreenAppUi*)AppUi())->iSettings->Count();i++)
		{
		if (i==19) continue; // screen number
		val.Copy(((CTap2ScreenAppUi*)AppUi())->iSettings->MdcaPoint(i));
		ChangeItemSubtitle(i,val);
		if (i==11||i==12||i==13||i==16||i==17||i==18)
			{
			TInt intval; 
			TLex conv(val);
			conv.Val(intval);
			CDesCArray* arr=CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_HIDE_POPUP);
			val.Copy(arr->MdcaPoint(intval));
			ChangeItemSubtitle(i,val);
			delete arr;
			}
		}
	}
void CMainView::PosChanged(TPoint aPos)
	{
	TInt scrX=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
	TInt scrY=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;
	TInt ind1; TInt ind2;
	if (scrY>scrX){ind1=0;ind2=1;}
	else {ind1=2;ind2=3;}
	TBuf<255> d;
	d.Num(aPos.iX);
	ChangeItemSubtitle(ind1,d);
	d.Num(aPos.iY);
	ChangeItemSubtitle(ind2,d);
	}
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::Handle_MenuItem3SelectedL( TInt aCommand )
	{
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::OtherApps( TInt aCommand )
	{
	TBuf<255> url(_L("http://store.ovi.com/publisher/Alexander+Fokin/"));
	OpenBrowser(url);
	return ETrue;
	}

#ifndef __WINS__
	const TInt KBrowserUid = 0x10008D39;
#else
	const TInt KBrowserUid = 0x1020724D;
#endif

	void CMainView::OpenBrowser(const TDesC& aUrl)
	{
		TUid id(TUid::Uid(KBrowserUid));
		TApaTaskList taskList(CEikonEnv::Static()->WsSession());
		TApaTask task = taskList.FindApp(id);

		if (task.Exists())
		{
			HBufC8* param8 = HBufC8::NewLC(100);
			param8->Des().Append(aUrl);
			// Uid is not used
			task.SendMessage(TUid::Uid(0), *param8);
			CleanupStack::PopAndDestroy();
		}
		else
		{
			RApaLsSession appArcSession;
			// connect to AppArc server
			User::LeaveIfError(appArcSession.Connect());
			TThreadId id;
			TInt ret = appArcSession.StartDocument(aUrl, TUid::Uid(KBrowserUid), id);
			appArcSession.Close();
		}
	}
