#include <utility>
//	
//template <class T> 
//T&& move(T&& a)
//{
//    return a;
//}

template <class T> void swap(T& a, T& b)
{
    T tmp(std::move(a)); // ?�Ha�Q��?��?�Htmp�Aa�Q�M��
    a = std::move(b);    // ?�Hb�Q��?��?�Ha�Ab�Q�M��
    b = std::move(tmp);  // ?�Htmp�Q��?��?�Hb
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
