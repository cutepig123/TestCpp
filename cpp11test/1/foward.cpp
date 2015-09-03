#include  <utility>

template <typename T> void f(T&& p1) {
	g(std::forward<T>(p1));
}


//void g(int &a)
//{
//	printf(__FUNCSIG__ "\n");
//}

void g(int a)
{
	printf(__FUNCSIG__ "\n");
}


void test_forward()
{
	f(int());

	int a=1;
	f(a);

	
}

