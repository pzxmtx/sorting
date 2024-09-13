#include <iostream>
#include "utils.h"

extern "C" void _insertion(long* v, size_t n);

int main(int argc, char** argv)
{
	for (size_t i = 0 ; i < 10; ++i)
	{
		const int n{ 100 };
		long* v{ new long[n] };
		randomize(v, n);
		_insertion(v, n);
		delete [] v;
	}
	return 0;
}
