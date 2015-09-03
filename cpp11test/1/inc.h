// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


// TODO: reference additional headers your program requires here
class	MyTimeMeasure
	{
		unsigned long	ulStartTime, ulEndTime;
		char	label_[250];
	public:
		
		explicit MyTimeMeasure(const	char *label = 0);
		
		~MyTimeMeasure();
		
		void Begin();
		
		void End(const	char *label);
	//private:
		
		static void MyTRACE(char *szFormat, ...);
};