#include <MdaAudioTonePlayer.h>
#include <eikmenup.h>
#include <AudioPlayer.h>
 
 
CPlayerUtility* CPlayerUtility::NewL(const TDesC& aFileName)
{
    CPlayerUtility* self = NewLC(aFileName);
    CleanupStack::Pop(self);  
    return self;
}
 
CPlayerUtility* CPlayerUtility::NewLC(const TDesC& aFileName)
{
    CPlayerUtility* self = new (ELeave) CPlayerUtility();
    CleanupStack::PushL(self);
    self->ConstructL(aFileName);
    return self;
}
 
CPlayerUtility::~CPlayerUtility()
{
	if(iPlayUtility)
	{
		iPlayUtility->Stop();
		iPlayUtility->Close();
	}
 
    delete iPlayUtility;
}
 
CPlayerUtility::CPlayerUtility()
{
}
 
void CPlayerUtility::ConstructL(const TDesC& aFileName)
{
    iPlayUtility = CMdaAudioPlayerUtility::NewFilePlayerL(aFileName, *this);
	iPlaying = iPrepared = EFalse;
}
 
void CPlayerUtility::Play()
{
	iPlayUtility->Play();
	iPlaying = ETrue;
}
 
void CPlayerUtility::Stop()
{
	iPlayUtility->Stop();
	iPlaying = EFalse;
}
 
 
void CPlayerUtility::MapcPlayComplete(TInt /*aError*/)
{
	iPlaying = EFalse;
	delete this;
}
 
void CPlayerUtility::MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& /*aDuration*/)	
{
	if(aError == KErrNone)
	{
		iPrepared = ETrue;
		iPlayUtility->SetVolume(iPlayUtility->MaxVolume());
		iPlayUtility->Play();
	}
}
