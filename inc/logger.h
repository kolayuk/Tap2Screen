/*
 * logger1.h
 *
 *  Created on: 28.02.2010
 *      Author: SQR
 */

#ifndef __FILELOGGER_H__
#define __FILELOGGER_H__
#include <e32std.h>
#include <flogger.h>
#include <e32debug.h>
_LIT(KLogsDir,"Tap2Screen");
_LIT(KLogsFileName,"log.txt");
#define _LOG(KTmpStr){RFileLogger::WriteFormat(KLogsDir(),KLogsFileName(),EFileLoggingModeAppend,KTmpStr);RDebug::Print(KTmpStr);}
//#define _LOGSTR(S){RFileLogger::WriteFormat(KLogsDir(),KLogsFileName(),EFileLoggingModeAppend,KTmpStr);RDebug::Print(KTmpStr);}
#define _LOGDATA(KTmpStr,P0){RFileLogger::WriteFormat(KLogsDir(),KLogsFileName(),EFileLoggingModeAppend,TRefByValue<const TDesC>(KTmpStr),P0);RDebug::Print(KTmpStr,P0);}
#define _LOGDATA2(KTmpStr,P0,P1){RFileLogger::WriteFormat(KLogsDir(),KLogsFileName(),EFileLoggingModeAppend,TRefByValue<const TDesC>(KTmpStr),P0,P1);RDebug::Print(KTmpStr,P0,P1);}
#define __LOGSTR3(S,P0,P1,P2){_LIT(KTmpStr,S);RFileLogger::WriteFormat(KLogsDir(),KLogsFileName,EFileLoggingModeAppend,TRefByValue<const TDesC>(KTmpStr()),P0,P1,P2);}

#endif
