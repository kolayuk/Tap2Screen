/*
========================================================================
 Name        : MainView.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef MAINVIEW_H
#define MAINVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CMain;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for MainView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CMainView MainView.h
 */						
			
class CMainView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CMainView();
	static CMainView* NewL();
	static CMainView* NewLC();        
	void ConstructL();
	virtual ~CMainView();
	void OpenBrowser(const TDesC& aUrl);
	void HandleLBSelect(TInt aIndex);	
	TInt NumberQuery(TDes& aText,TInt& aNumber);
	void ChangeItemSubtitle(TInt aIndex,TDes16& aText);
	TInt PopupMenu(TDes& aTxt,TInt aDef,CDesCArray* aArray);
	TInt TextQuery(TDes& aTxt, TDes& aBuffer);
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	void InitValues();
	void PosChanged(TPoint aPos);
	// [[[ begin generated region: do not modify [Generated Methods]
	CMain* CreateContainerL();
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Public Section]
	
	
	// [[[ begin [Protected Section]
protected:
	// from base class CAknView
	void DoActivateL(
		const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId,
		const TDesC8& aCustomMessage );
	void DoDeactivate();
	void HandleStatusPaneSizeChange();
	
	// [[[ begin generated region: do not modify [Overridden Methods]
	// ]]] end generated region [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
	TBool Handle_MenuItemSelectedL( TInt aCommand );
	TBool Handle_MenuItem1SelectedL( TInt aCommand );
	TBool Handle_MenuItem2SelectedL( TInt aCommand );
	TBool HandleControlPaneRightSoftKeyPressedL( TInt aCommand );
	TBool Handle_MenuItem3SelectedL( TInt aCommand );
	TBool OtherApps( TInt aCommand );
	// ]]] end [User Handlers]
	
	// ]]] end [Protected Section]
	
	
	// [[[ begin [Private Section]
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CMain* iMain;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	enum TListQuery1Images
		{
		// [[[ begin generated region: do not modify [Generated Enums]
		// ]]] end generated region [Generated Enums]
		
		};
	};

#endif // MAINVIEW_H
