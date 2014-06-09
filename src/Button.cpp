/*
 ============================================================================
 Name		: Button.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CButton implementation
 ============================================================================
 */

#include "Button.h"
#include <eiklabel.h>
#include <aknsutils.h>
#include <gulcolor.h>
#include <GDI.H>
#include <aknutils.h>
#include <const.h>
#include <bautils.h>
#include <coecntrl.h>
CButton::CButton(): MCoeControlObserver()
	{
	}

CButton::~CButton()
	{
	delete iButton;
	delete iLabel;
	delete iTimer;
	delete iMsgTimer;
	}

CButton* CButton::NewLC(RWindowGroup* aWg,MButtonCallBack* aCB,TInt aResourceId)
	{
	CButton* self = new (ELeave) CButton();
	CleanupStack::PushL(self);
	self->ConstructL(aWg,aCB,aResourceId);
	return self;
	}

CButton* CButton::NewL(RWindowGroup* aWg,MButtonCallBack* aCB,TInt aResourceId)
	{
	CButton* self = CButton::NewLC(aWg,aCB,aResourceId);
	CleanupStack::Pop(); // self;
	return self;
	}

void CButton::ConstructL(RWindowGroup* aWinGroup,MButtonCallBack* aCallBack,TInt aResourceId)
	{
	iWinGroup=aWinGroup;
	iCallBack=aCallBack;
	iButton = CAknButton::NewL();
	iButton->ConstructFromResourceL(aResourceId);
	iButton->CreateWindowL(iWinGroup);
	iButton->SetObserver(this);
	iButton->MakeVisible(ETrue);
	iButton->Window().SetPointerGrab(ETrue);
	iMoving=EFalse;
	iLabel = new (ELeave) CEikLabel;
	iLabel->CreateWindowL(iWinGroup);
	iLabel->MakeVisible(EFalse);
	iLabel->ActivateL();
	iTimer=CPeriodic::NewL(CActive::EPriorityStandard);
	iMsgTimer=CPeriodic::NewL(CActive::EPriorityStandard);
	}
void CButton::HandleControlEventL(CCoeControl* aControl, enum TCoeEvent aEventType)
	{	
		if (aControl==iButton)
			{
			if (aEventType==iButton->ELongPressEvent)
				{
				if (!iMoving){iCallBack->LongTap();}
				}
			else if (aEventType==EEventStateChanged)
				{
				iTime1.HomeTime();
				if ((Abs((TInt)iTime1.MicroSecondsFrom(iTime2).Int64())>KDoubleDelay*1000))
					{
					iTimer->Start(KDoubleDelay*1000,KDoubleDelay*1000,TCallBack(Tick,this));
					}
				else {iCount++;}
				iTime2.HomeTime();
				}
			}
		}

TInt CButton::Tick(TAny* aObj)
	{
	((CButton*)aObj)->iTimer->Cancel();
	if (((CButton*)aObj)->iCount==0)
		{if (!(((CButton*)aObj)->iMoving)){((CButton*)aObj)->iCallBack->Tap();}}
	else {((CButton*)aObj)->iCallBack->DoubleTap();}
	((CButton*)aObj)->iCount=0;
	return 0;
	}

void CButton::Message(TDes& aText,TInt aInterval)
	{
	const TInt KBetween=10;
	const TInt KFontSize = 120;
	_LIT(KFontName, "Nokia Hindi S60");
	
	CFont* font;
	TTypefaceSupport iTypefaceSupport;
	TBuf<KMaxTypefaceNameLength> fontName;
	fontName.FillZ(KMaxTypefaceNameLength);
	CEikonEnv::Static()->ScreenDevice()->TypefaceSupport(iTypefaceSupport, 0);
	fontName = iTypefaceSupport.iTypeface.iName;
		
	TFontSpec fontSpec(fontName, KFontSize);
	CEikonEnv::Static()->ScreenDevice()->GetNearestFontInTwips(font, fontSpec);
	TInt maxW;
	TInt scrX=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
	TInt scrY=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;
	
	iLabel->SetFont(font);
	
	TInt w=iLabel->Font()->TextWidthInPixels(aText);
	TInt h=iLabel->Font()->HeightInPixels();
	TInt posX=iButton->Position().iX+(iButton->Size().iWidth/2)-(w/2);
	TInt posY=0;
	if (iButton->Position().iY>scrY/2)
		{posY=iButton->Position().iY-h-KBetween;} //bottom
	else {posY=iButton->Position().iY+iButton->Size().iHeight+KBetween;} //top 
	if (iButton->Position().iX<scrX/2)
			{maxW=2*(iButton->Position().iX+(iButton->Size().iWidth/2));} //left
		else {maxW=2*((scrX-(iButton->Position().iX+iButton->Size().iWidth))-(iButton->Size().iWidth/2));} //right
	TRgb themecolor;
	MAknsSkinInstance* skin=AknsUtils::SkinInstance();
	AknsUtils::GetCachedColor(skin,themecolor,KAknsIIDQsnTextColors,EAknsCIQsnTextColorsCG6 );
	iLabel->SetBrushStyle(CGraphicsContext::ESolidBrush);
	TRgb col=KRgbBlack;
	themecolor=KRgbWhite;
	iLabel->OverrideColorL(EColorControlBackground,col);
	iLabel->OverrideColorL(EColorLabelText,themecolor);
	iLabel->SetPosition(TPoint(posX,posY));
	iLabel->SetSize(TSize(w,h));
	iLabel->SetFont(font);
	iLabel->MakeVisible(ETrue);
	iLabel->SetTextL(aText);
	iLabel->DrawNow();
	iMsgTimer->Start(aInterval*1000,aInterval*1000,TCallBack(MsgTick,this));
	}

void CButton::SetTransparentBackground(TBool aState)
	{
	TInt alpha;
	if (aState){alpha=0;}
	else {alpha=255;}
	TRgb backgroundColour = KRgbWhite; // for example
	if(KErrNone == iButton->Window().SetTransparencyAlphaChannel())
		{backgroundColour.SetAlpha(alpha);}
	iButton->Window().SetBackgroundColor(backgroundColour);
	}
void CButton::SetTransparency(TInt val)
	{
	TRgb c=TRgb(val,val,val);
	c.SetAlpha(val);
	iButton->Window().SetTransparencyAlphaChannel();
	TInt err=iButton->Window().SetTransparencyFactor(c);
	TBuf<255> a;
	a.Num(err);
	CEikonEnv::Static()->InfoMsg(a);
	}
TInt CButton::MsgTick(TAny* aObj)
	{
	((CButton*)aObj)->iMsgTimer->Cancel();
	((CButton*)aObj)->iLabel->MakeVisible(EFalse);
	return 0;
	}
void CButton::UpdateScreen()
	{
	 RWindow wnd(CEikonEnv::Static()->WsSession());
	 User::LeaveIfError(wnd.Construct(*iWinGroup,TUint32(&wnd)));
	 wnd.SetExtent(TPoint(0,0),TSize(1,1));
	 wnd.SetVisible(ETrue);
	 wnd.Activate();
	 User::After(5000);
	 wnd.SetVisible(EFalse);
	 wnd.Close();
	}
