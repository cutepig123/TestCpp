#include <string>
#include <vector>

void split(const char *s, const char *splitter, std::vector<std::string> *d)
{
	const char *p1=s;
	const char *p2=s;
	for(p2 =strstr(p1, splitter); p2; p1=p2+strlen(splitter),p2 =strstr(p1, splitter))
	{
		d->push_back(std::string(p1,p2));
	}
	d->push_back(std::string(p1));
}

bool isSpace(char c)
{
	return c==' '||c=='\t'||c=='\n'||c=='\r';
}

void strip(const char *s, std::string *d)
{
	const char *p=s;
	while(isSpace(*p)) p++;
	
	const char *p2=p+strlen(p)-1;
	
	while(p<p2)
	{
		if(!isSpace(*p2)) break;
		p2--;
	}
	
	*d =std::string(p, p2+1);
}

void print(std::vector<std::string> const &s)
{
	for(size_t i=0, n=s.size(); i<n; i++)
		printf("%d %s\n", i, s[i].c_str());
}

struct Arg
{
	bool isConst;
	bool isPointerOrRef;
	std::string sName;
	
	Arg():isConst(false),isPointerOrRef(false)
	{}

};

void getArgs(const char *s, std::vector<Arg> *args)
{
	//splitbycomma
	std::vector<std::string> splitbycomma;
	split(s, ",",&splitbycomma);
	for(size_t i=0, n=splitbycomma.size(); i<n; i++)
	{
		const std::string &s =splitbycomma[i];
		
		std::string sstriped;
		strip(s.c_str(), &sstriped);
		if(sstriped.empty())continue;
		
		//rfind =
		//if exist = then the left part is arg name
		std::string sRmvEqu;
		auto it=sstriped.rfind("=");
		if(it!=std::string::npos)
			sRmvEqu =sstriped.substr(0, it);
		else sRmvEqu =sstriped;
		
		//
		std::string sstriped2;
		strip(sRmvEqu.c_str(), &sstriped2);
		
		//find the " \t*&" the right part is arg name
		std::string sArg, sLeft;
		auto it2=sstriped2.find_last_of(" \t*&");
		if(it2!=std::string::npos) 
		{
			sArg=sstriped2.substr(it2+1);
			sLeft=sstriped2.substr(0,it2+1);
		}
		else sArg=sstriped2;

		std::string sLeft2;
		strip(sLeft.c_str(), &sLeft2);

		Arg arg;
		if(sLeft2.find("const")!=std::string::npos)
			arg.isConst =true;
		if(!sLeft2.empty() && (sLeft2.back()=='*'||sLeft2.back()=='&'))
			arg.isPointerOrRef =true;
		if(sArg.find("[")!=std::string::npos && sArg.find("]")!=std::string::npos)
			arg.isPointerOrRef =true;
		
		arg.sName =sArg;

		args->push_back(arg);
	}
}

void teststrfcn()
{
	std::vector<std::string> res;
	split("const CGrabsetWrapper&gs, const char*file, std::vectorxx x *d=0", ",",&res);
	print(res);
	
	std::string s;
	strip("",&s);
	strip(" \tajska ss = \t === \t ",&s);
	printf("%s\n",s.c_str());

	std::vector<Arg> args;   ///< hello
	getArgs("const CGrabsetWrapper&gs, int a[], const char*file, std::vectorxx x *d=0",  &args);
}
