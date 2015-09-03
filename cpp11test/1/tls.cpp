#include <boost/thread.hpp>
#include <boost/circular_buffer.hpp>
#include <windows.h>
//http://stackoverflow.com/questions/22785024/thread-specific-ptr-multithread-confusion

struct StreamX
{
    StreamX() { printf("con %p\n", this);; }
   ~StreamX() { printf("des %p\n", this);; }
};

static boost::thread_specific_ptr<StreamX> StreamThreadSpecificPtr;
void thread_proc() {
    StreamX * stream = NULL;
    stream = StreamThreadSpecificPtr.get();
    if (NULL == stream) {

        stream = new StreamX();
        StreamThreadSpecificPtr.reset(stream);
    }
    printf("%p\n", stream);
}

DWORD WINAPI PrepTrigThread( void * )
{
	thread_proc();
	return 0;
}

void run_tls() {
	boost::thread_group threads;
	for(int i = 0; i < 5; i ++) {
	    threads.create_thread(&thread_proc);
	}
	threads.join_all();
}

void run_tls2() {
	HANDLE h[5];
	for(int i = 0; i < 5; i ++) {
		h[i] =::CreateThread(NULL, NULL, PrepTrigThread, NULL, NULL, NULL);
	}
	for(int i = 0; i < 5; i ++) {
		WaitForSingleObject(h[i], INFINITE);
	}
}

//struct Item{
//	DWORD 		thread;
//	unsigned long 	ulTime;
//	char		acMsg[100];
//};
//	
//static boost::thread_specific_ptr<boost::circular_buffer<Item> > g_StreamThreadSpecificPtr;
//#define M	1000
//static char g_ThreadSts[M] ={0};	// 0: Init, 1: To be clear
//#define	N	10000
//
//void AddMsg(const char*fmt, ...)	// Log a message If full
//{
//	if(!g_StreamThreadSpecificPtr.get())
//		g_StreamThreadSpecificPtr.reset(new boost::circular_buffer<Item>(N));
//	
//	
//	Item i;
//	i.thread =GetCurrentThreadId();
//
//	if( g_ThreadSts[i.thread%M]==1 )
//	{
//		g_StreamThreadSpecificPtr->clear();
//		g_ThreadSts[i.thread%M] =0;
//	}
//	
//	//SYS_GetTimeInUS(&i.ulTime);
//	va_list l;
//	va_start(l, fmt);
//	vsnprintf(i.acMsg, 100, fmt, l);
//	va_end(l);
//	g_StreamThreadSpecificPtr->push_back(i);
//}
//	
//void DumpAndReset()
//{
//	if(g_StreamThreadSpecificPtr.get())
//	{	
//		for( boost::circular_buffer<Item>::iterator it = mData.begin(), end=mData.end(); it!=end; ++it)
//		{
//			Item &i =*it;
//			xx
//		}
//	}
//}
//	
//
//
