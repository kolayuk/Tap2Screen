#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <e32std.h>
#include <MdaAudioSamplePlayer.h>

class CPlayerUtility : public CBase, public MMdaAudioPlayerCallback
    {
public:
    static CPlayerUtility* NewL(const TDesC& aFileName);
    static CPlayerUtility* NewLC(const TDesC& aFileName);
    ~CPlayerUtility();
    CMdaAudioPlayerUtility* iPlayUtility;
private:
    CPlayerUtility();
    void ConstructL(const TDesC& aFileName);
public:
    void Play();
    void Stop();
public: // from MMdaAudioToneObserver
	void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration);
	void MapcPlayComplete(TInt aError);
private:
    TBool					iPlaying,iPrepared;
};
#endif
