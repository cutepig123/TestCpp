#include <boost/optional.hpp>

struct A;




struct A
{
	int t[1000];
};
boost::optional<A> opt;
void test_opt()
{
	
	A a;

	opt.reset(a);
}
