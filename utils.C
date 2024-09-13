#include <random>
#include <set>
#include <algorithm>
#include "utils.h"

void randomize(long* v, const std::size_t size, long maxval)
{
	std::set<long> s;
	std::random_device random_dev;
	std::mt19937 generator(random_dev());
	std::generate_n(&v[0], size, [&]() {
        	const long from(0);
	        const long to(maxval);
        	std::uniform_int_distribution<> distrib(from, to);
	        long r{ distrib(generator) };
        	while (s.find(r) != s.cend())
	        {	
        	    r = distrib(generator);
	        }
        	return r;
	 });
}

