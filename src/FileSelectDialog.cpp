/*
 ============================================================================
 Name		: FileSelectDialog.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CFileSelectDialog implementation
 ============================================================================
 */

#include "FileSelectDialog.h"
#include <aknlists.h> //CAknSinglePopupMenuStyleListBox 
#include <aknpopup.h> //CAknPopupList

#include <akntitle.h> // title
#include <eikspane.h>
#include <eikaufty.h>

#include <aknappui.h>
#include <aknviewappui.h>
#include <aknview.h>
#include <eikenv.h>

#include <f32file.h>
#include <bautils.h>
#include <aknselectionlist.h>

#include <Tap2Screen.rsg>
#include <avkon.mbg>
#include <AknIconUtils.h>

CFileSelectDialog::CFileSelectDialog()
	{
	// No implementation required
	}

CFileSelectDialog::~CFileSelectDialog()
	{
	}

CFileSelectDialog* CFileSelectDialog::NewLC(TDes& aTitle,TTypeOfSelect aType, TDes& aStartFilePath,TDes& aMask)
	{
	CFileSelectDialog* self = new (ELeave) CFileSelectDialog();
	CleanupStack::PushL(self);
	self->ConstructL(aTitle,aType,aStartFilePath,aMask);
	return self;
	}

CFileSelectDialog* CFileSelectDialog::NewL(TDes& aTitle,TTypeOfSelect aType, TDes& aStartFilePath,TDes& aMask)
	{
	CFileSelectDialog* self = CFileSelectDialog::NewLC(aTitle,aType,aStartFilePath,aMask);
	CleanupStack::Pop(); // self;
	return self;
	}

void CFileSelectDialog::ConstructL(TDes& aTitle,TTypeOfSelect aType, TDes& aStartFilePath,TDes& aMask)
	{
	
	EViewId=999;
	iTitle.Copy(aTitle);
	iType=aType;
	iStartPath.Copy(aStartFilePath);
	iMask.Copy(aMask);
	
	iFs.Connect();
	iArray = new (ELeave) CDesCArrayFlat(3);
	
	iCurrentPath.Copy(iStartPath);
	/*
    CFbsBitmap* bitmapFile = NULL;
	CFbsBitmap* maskFile = NULL;
	AknIconUtils::CreateIconL(bitmapFile,maskFile, KIconsFileName,0,1);
	iFileIcon=CGulIcon::NewL(bitmapFile,maskFile);
	CFbsBitmap* bitmapFolder = NULL;
	CFbsBitmap* maskFolder = NULL;
	AknIconUtils::CreateIconL(bitmapFolder,maskFolder, KIconsFileName,0,1);
	iFolderIcon=CGulIcon::NewL(bitmapFolder,maskFolder);
	CFbsBitmap* bitmapDisk = NULL;
	CFbsBitmap* maskDisk = NULL;
	AknIconUtils::CreateIconL (bitmapFolder,maskFolder, KDiskIconFileName,EMbmAvkonQgn_note_empty);
	iFolderIcon=CGulIcon::NewL(bitmapFolder,maskFolder);
	*/
	}
TDes& CFileSelectDialog::Execute(TDes& aFileName)
	{
	iResult.Copy(aFileName);
	Update();
	return iResult;
	}
void CFileSelectDialog::Update()
	{
	iArray->Reset();
	if (iCurrentPath.Compare(_L(""))==0)
		{
		LoadDriveList();
		}
	else 
		{ScanDir();}
	TInt selected=Show();
	if (selected==-1){return;}
	else if (iCurrentPath.Compare(_L(""))==0)
		{
				iCurrentPath.Append(iArray->MdcaPoint(selected));
				iCurrentPath.Append(_L("\\"));
				if (BaflUtils::PathExists(iFs,iCurrentPath)){Update();}
				//Update();
		}
	else if ((selected>1)&&(iCurrentPath.Compare(_L(""))!=0))
		{
		TBuf<255> temp(iArray->MdcaPoint(selected));
		temp.Copy(temp.Left(temp.Length()-1));
		temp.Copy(temp.Right(temp.Length()-1));
		iCurrentPath.Append(temp);
		iCurrentPath.Append(_L("\\"));
		CEikonEnv::Static()->InfoMsg(iCurrentPath);
		User::After(500000);
		if (BaflUtils::PathExists(iFs,iCurrentPath)){Update();}
		else if (BaflUtils::FileExists(iFs,iCurrentPath.Left(iCurrentPath.Length()-1)))
			{
			iResult.Copy(iCurrentPath.Left(iCurrentPath.Length()-1));
			}
		}
	else if (selected==0&&(iCurrentPath.Compare(_L(""))!=0))
		{
		TParse p;
		iFs.Parse(iCurrentPath, p);
		TInt err=p.PopDir();
		if (err!=KErrNone||iCurrentPath.Compare(p.FullName())==0){iCurrentPath.Copy(_L(""));}
		if (iCurrentPath.Compare(_L(""))!=0){iCurrentPath.Copy(p.FullName());}
		Update();
		}
	else if (selected==1&&iType==EFolder&&(iCurrentPath.Compare(_L(""))!=0))
		{
		iResult.Copy(iCurrentPath);
		}
	}
void CFileSelectDialog::ScanDir()
	{
	TInt i=0;
	CDir* results=NULL;
	TFindFile findFiles(iFs);
	findFiles.FindWildByDir(iMask,iCurrentPath,results);
	if (results==NULL){return;}
	for (i=0;i<results->Count();i++)
		{
		if (((TEntry)(*results)[i]).IsDir())
		{
		TBuf<255> buf;
		buf.Copy(_L("["));
		buf.Append(((TEntry)(*results)[i]).iName);
		buf.Append(_L("]"));
		iArray->AppendL(buf);}
		}
	if (iType!=EFolder)
	{
	for (i=0;i<results->Count();i++)
		{
		if (!((TEntry)(*results)[i]).IsDir())
			{iArray->AppendL(((TEntry)(*results)[i]).iName);}
		}
	}
}
TInt CFileSelectDialog::Show()
	{
	_LIT(KListItemFormat, "%S");
	CAknSinglePopupMenuStyleListBox* list = new(ELeave) CAknSinglePopupMenuStyleListBox;
	CleanupStack::PushL(list);
		
	CAknPopupList* popupList = CAknPopupList::NewL(list, R_AVKON_SOFTKEYS_OK_BACK, AknPopupLayouts::EMenuWindow);
	CleanupStack::PushL(popupList);    
	list->ConstructL(popupList, CEikListBox::ELeftDownInViewRect);
	list->CreateScrollBarFrameL(ETrue);
	list->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOn, CEikScrollBarFrame::EAuto);
	TBuf<255> t; CEikonEnv::Static()->ReadResource(t,R_FILE_SELECTER_FOLDER_SELECT);
	if (iCurrentPath.Compare(_L(""))!=0){if (iType==EFolder){iArray->InsertL(0,t);}iArray->InsertL(0,_L("..."));}
	list->Model()->SetItemTextArray(iArray);
	list->Model()->SetOwnershipType(ELbmOwnsItemArray);
	list->ItemDrawer()->FormattedCellData()->EnableMarqueeL( ETrue );
	popupList->SetTitleL(iTitle); 
	popupList->EnableFind(ETrue);
	CleanupStack::Pop();            // popuplist
	TBool popupOk = popupList->ExecuteLD();
	if (!popupOk)
	{
		CleanupStack::Pop(); //list
		return -1;
	}
	else 
		{
		CleanupStack::Pop(); //list
		TInt current=list->CurrentItemIndex();
		return current;
		}
	}
void CFileSelectDialog::LoadDriveList()
	{
	TInt i=0;
	BaflUtils::GetDiskListL(iFs,*iArray);
	for (i=0; i<iArray->Count();i++)
		{
		TBuf<255> a(iArray->MdcaPoint(i));
		a.Append(_L(":"));
		iArray->Delete(i);
		iArray->InsertL(i,a); 
		}
	}

void CFileSelectDialog::SetTitle()
	{
	
		TUid titlePaneUid;
		titlePaneUid.iUid = EEikStatusPaneUidTitle;
		TVwsViewId ViewID;CEikonEnv::Static()->AppUi()->GetActiveViewId(ViewID);
		CEikStatusPane* statusPane =((CAknAppUi*)CEikonEnv::Static()->AppUi())->StatusPane();		CEikStatusPaneBase::TPaneCapabilities subPane = statusPane->PaneCapabilities(titlePaneUid);
		if ( subPane.IsPresent() && subPane.IsAppOwned() )
			{
			CAknTitlePane* titlePane =(CAknTitlePane*) statusPane->ControlL(titlePaneUid);
			iOldTitle = *titlePane->Text();
			titlePane->SetTextL(iTitle);
			}
		
	}
/*
CGulIcon* CFileSelectDialog::LoadIconL()
    {
    _LIT(KIconsFile, "C:\\resource\\apps\\FileManIcons.mif");
    // Create icon from SVG
    AknIconUtils::CreateIconL(aBitmap, aMask, KIconsFile, aIndex, aIndex + 1);
    // Give size
    AknIconUtils::SetSize(aBitmap, aSize);
    AknIconUtils::SetSize(aMask, aSize);
    }
    */
