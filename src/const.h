/*
 * const.h
 *
 *  Created on: 12.09.2010
 *      Author: mvideo
 */

#ifndef CONST_H_
#define CONST_H_


_LIT(KSettingPath,"C:\\System\\Apps\\Tap2Screen\\config.ini");

_LIT(KPosX,"240");
_LIT(KPosY,"480");
_LIT(KPosXLand,"520");
_LIT(KPosYLand,"80");
_LIT(KSize,"100");
_LIT(KPath,"C:\\Data\\Images\\Screens\\");
_LIT(KFormat,".jpg");
_LIT(KBaseName,"Screen");
_LIT(KQuality,"100");
_LIT(KTransparency,"255");
_LIT(KWaterMarkPath,"C:\\System\\Apps\\Tap2Screen\\watermark.mbm");
_LIT(KHideButtonOnScreen,"1");
_LIT(KVibrate,"0");
_LIT(KPlaySound,"1");
_LIT(KDelayBeforeScreen,"0");
_LIT(KAmountOfScreens,"1");
_LIT(KProximitySensor,"0");
_LIT(KSwitchToPrev,"0");
_LIT(KHideInTasklist,"0");
_LIT(KScreensCaptured,"0");

const TInt KProximityMin=400;
const TInt KProximityMax=2000;
const TInt KProximityExit=4000;
_LIT(KSoundPath,"C:\\System\\Apps\\Tap2Screen\\camera.wav");
const TInt KVibraDuration=50;
const TInt KVibraIntensivity=50;
_LIT(KFirstStartFile,"C:\\system\\apps\\Tap2Screen\\firststart");

_LIT(KSymbian3CheckFile,"Z:\\system\\install\\Series60v5.2.sis");
_LIT(KSymbian94CheckFile,"Z:\\system\\install\\Series60v5.0.sis");

#ifdef _DEBUG
_LIT(KCallBackUrl,"http://kolaysoft.ru/comments/add.php?project=Tap2Screen_DEBUG&message=");
#else
_LIT(KCallBackUrl,"http://kolaysoft.ru/comments/add.php?project=Tap2Screen&message=");
#endif

#endif /* CONST_H_ */
