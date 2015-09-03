#include "inc.h"
#include <DSP_SYS.h>


inline
	IMG_VVOID SYS_GetTime_int(IMG_LREAL *plrClick, IMG_REAL rFactor)
	{
#ifdef  WIN32
		LARGE_INTEGER	liTime, liFreq;
		
		QueryPerformanceCounter(&liTime);
		QueryPerformanceFrequency(&liFreq);

		*plrClick = (IMG_LREAL)((IMG_LREAL)liTime.QuadPart / liFreq.QuadPart * rFactor);
#else
#ifdef	__unix__
		IMG_LREAL				lrRealFactor = 1000.0 / rFactor;
		struct ntptimeval       stInfo;

		ntp_gettime(&stInfo);
		*plrClick = (IMG_LREAL)(stInfo.time.tv_sec * 1000 * 1000 +
								(stInfo.time.tv_usec)) / lrRealFactor;
#else
		__int64	click;
		if (sys_ulFreqPerMS)
		{
			click = SYS_GetCycleCount();
			*plrClick = (IMG_LREAL)((IMG_LREAL)click * (rFactor / 1000.0) / (IMG_LREAL)sys_ulFreqPerMS);
		}
		else
		{
			*plrClick = 0;
		}
#endif	//	UNIX
#endif  //  WIN32
	}
/*lint -restore */

// Measure time in ms
	inline
	IMG_VVOID SYS_GetTime(IMG_ULWORD *pulClick)
	{
		IMG_LREAL		lrTemp = 0;
		SYS_GetTime_int(&lrTemp, 1000.0);
		*pulClick = (IMG_ULWORD)floor(lrTemp + 0.5);
	}

// Measure time in us
	inline
	IMG_VVOID SYS_GetTimeInUS(IMG_ULWORD *pulClick)
	{
		IMG_LREAL		lrTemp = 0;
		SYS_GetTime_int(&lrTemp, 1000000.0);
		*pulClick = (IMG_ULWORD)floor(lrTemp + 0.5);
	}

MyTimeMeasure::MyTimeMeasure(const	char *label)
{
	if (label)
	{
		strcpy(label_, label);
	}
	else
	{
		label_[0] = 0;
	}
				
	Begin();
}
		
MyTimeMeasure::~MyTimeMeasure()
{
	if (label_[0])
	{
		End(label_);
	}
}
		
void MyTimeMeasure::Begin()
{
	SYS_GetTimeInUS(&ulStartTime);
	//MyTRACE("%s Begin:%lu\n", label_, ulStartTime);
}
		
void MyTimeMeasure::End(const	char *label)
{
	SYS_GetTimeInUS(&ulEndTime);
			
	//MyTRACE("%s End:%lu\n", label, ulEndTime);
	MyTRACE("%s Time:%d\n", label, ulEndTime - ulStartTime);
	//Begin();
}

void MyTimeMeasure::MyTRACE(char *szFormat, ...)
{
	va_list l;
	static char s[1000];
	va_start(l, szFormat);
	vsprintf(s, szFormat, l);
	OutputDebugStringA(s);
	printf("%s\n",s);
}
