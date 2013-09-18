
#ifndef TAP2SCREEN_PAN_H
#define TAP2SCREEN_PAN_H

/** Tap2Screen application panic codes */
enum TTap2ScreenPanics
	{
	ETap2ScreenUi = 1
	// add further panics here
	};

inline void Panic(TTap2ScreenPanics aReason)
	{
	_LIT(applicationName,"Tap2Screen");
	User::Panic(applicationName, aReason);
	}

#endif // TAP2SCREEN_PAN_H
