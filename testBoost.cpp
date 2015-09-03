// testBoost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include  <iostream>
#include  "boost\variant.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	system("pause");
	boost::variant< int, std::string > v;
	v = "hello";
	//std::cout << v << std::endl;
	new int;

	return 0;
}

