#include <utility>
//	
//template <class T> 
//T&& move(T&& a)
//{
//    return a;
//}

template <class T> void swap(T& a, T& b)
{
    T tmp(std::move(a)); // ?象a被移?到?象tmp，a被清空
    a = std::move(b);    // ?象b被移?到?象a，b被清空
    b = std::move(tmp);  // ?象tmp被移?到?象b
}

struct	A
{
	char x[123];
};

void test_move()
{
    A a;
    A b;

	memset(a.x,0, sizeof(a.x));
	memset(b.x,0, sizeof(b.x));

    swap(a, b);

   
}
