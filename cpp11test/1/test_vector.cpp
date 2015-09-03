#include <vector>

struct A
{
	int x[10];

	A()
	{
	}

	A(A&& r)
	{
		int i=0;
	}
};

void test_vector()
{
	std::vector<A> vA;

	vA.push_back(A());
}
