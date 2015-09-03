#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <stdarg.h>
#include <stdio.h>

struct Item{
	size_t 		thread;
	unsigned long 	ulTimeBegin, ulTimeEnd;
	char		acMsg[100];

	Item()
	{
		memset(this, 0, sizeof(*this));
	}
};

#define	N	10000
boost::circular_buffer<Item> g_Items(N);

class TimeLog
{
	boost::circular_buffer<Item> &mItems;
	Item mi;
	char mIsEnd;

public:
	TimeLog(boost::circular_buffer<Item> &items, const char* s)
		:mItems(items), mIsEnd(0)
	{
		memset(&mi, 0, sizeof(mi));
		mi.thread =boost::lexical_cast<size_t>(boost::this_thread::get_id());
		strcpy( mi.acMsg, s );

		begin();
	}

	~TimeLog()
	{
		end();
	}
	
	void begin()
	{
		
	}
	
	void end()
	{
		if(!mIsEnd)
		{
			mIsEnd =1;
			mItems.push_back(mi);
		}
	}

	void DumpAndReset(const char *file)
	{
		FILE *fp =fopen(file, "a");
		if(!fp)return;

		for( boost::circular_buffer<Item>::iterator it = mItems.begin(), end=mItems.end(); it!=end; ++it)
		{
			Item &i =*it;
			fprintf(fp, "%lu\t%lu\t%lu\t%s\n", i.thread,i.ulTimeBegin, i.ulTimeEnd, i.acMsg);
		}
		mItems.clear();
		fclose(fp);
	}
};
