/**
* Definition
*/
void* timelog_create(int MaxSize);
void timelog_log(void const *timelog, const char *fmt,...);
void timelog_dump(void const *timelog, const char *file);
void timelog_free(void **timelog);
/**
* Testing
*/

#include <windows.h>

DWORD WINAPI ThreadProc(
   LPVOID lpParameter
){
	void *timelog =(void*)lpParameter;

	for(int i=0; i<5;i++)
	{
		timelog_log(timelog, "%d_%d",GetCurrentThreadId(), i);
		Sleep(100);
	}

	/*for(int i=0; i<50000;i++)
		Sleep(10000);*/
	return 0;
}

void test_mytimelog()
{
	int MaxSize=4;
	void* timelog =timelog_create(MaxSize);
	timelog_log(timelog, "Start!");
	
	HANDLE h[10];
	for(int i=0; i<10; i++)
	{
		h[i] =CreateThread( 0, 0, ThreadProc, timelog, 0,0);
	}

	//Sleep(1000);
	

	for(int i=0; i<10; i++)
		WaitForSingleObject(h[i], INFINITE);

	timelog_dump(timelog, "file");
	timelog_free(&timelog);
	
}

/**
* Implementation
*/
#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <set>
#include <stdarg.h>
#include <stdio.h>
#include <windows.h>

struct Item{
	unsigned long 	ulTime;
	char			acMsg[100];

	Item()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct Threadpara{
	boost::shared_ptr<boost::circular_buffer<Item> > queue;
	int thread;

	explicit Threadpara(int n):queue(new boost::circular_buffer<Item>( n)), thread(GetCurrentThreadId())
	{
	}

	bool operator<(Threadpara const &r) const
	{
		if( queue.get()<r.queue.get() )return true;
		if( queue.get()==r.queue.get() )assert(thread==r.thread );
		return false;
	}
};

static boost::thread_specific_ptr<Threadpara> StreamThreadSpecificPtr;

struct MyTimeLog{
	int maxSz;

	std::set<Threadpara> para;
	boost::mutex mtxPara;

	explicit MyTimeLog(int n):maxSz(n)
	{
	}
};

void* timelog_create(int maxsz)
{
	MyTimeLog *tm=new MyTimeLog(maxsz);
	tm->maxSz=maxsz;
	return tm;
}

void timelog_free(void **timelog)
{
	MyTimeLog *tm=(MyTimeLog*)*timelog;
	delete tm;
	*timelog =NULL;
}

void timelog_log(void const *timelog, const char *fmt,...)
{
	MyTimeLog *tm=(MyTimeLog*)timelog;

	Threadpara * stream = NULL;
    stream = StreamThreadSpecificPtr.get();
    if (NULL == stream) {
        stream = new Threadpara(tm->maxSz);
        StreamThreadSpecificPtr.reset(stream);
		
		tm->mtxPara.lock();
		tm->para.insert(*stream);
		tm->mtxPara.unlock();
    }
	else
	{
		assert(GetCurrentThreadId()==stream->thread);
	}

	Item item;
	item.ulTime =GetTickCount();
	va_list l;
	va_start(l, fmt);
	_vsnprintf(item.acMsg, sizeof(item.acMsg), fmt,l);
	va_end(l);

	stream->queue->push_back(item);
}

void timelog_dump(void const *timelog, const char *file)
{
	FILE *fp =fopen(file, "a");
	if(!fp)return;

	MyTimeLog *tm=(MyTimeLog*)timelog;

	tm->mtxPara.lock();
	for(auto i=tm->para.begin();i!=tm->para.end();++i)
	{
		auto &mItems =(*i).queue;
		assert(mItems);
		{
			int thread=(*i).thread;
			for( boost::circular_buffer<Item>::iterator it = mItems->begin(), end=mItems->end(); it!=end; ++it)
			{
				Item &i =*it;
				fprintf(fp, "%lu\t%lu\t%s\n", thread,i.ulTime, i.acMsg);
			}
			mItems->clear();
		}
	}
		
	tm->mtxPara.unlock();
	
	fclose(fp);
}
