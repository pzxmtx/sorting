#include <iostream>
#include "utils.h"

extern "C" void _selection(long* v, size_t n);

int main(int argc, char** argv)
{
	for (size_t i = 0 ; i < 1; ++i)
	{
		const int n{ 10 };
		long* v{ new long[n] };
		randomize(v, n, 100);
		print("unsorted: ", v, n, false);
		_selection(v, n);
		print("sorted: ", v, n, false);
		delete [] v;
	}
//	long v[] = { 100, 43, 51, 79, 13, 21, 5, 1, 37 };
//	_selection(v, sizeof(v)/sizeof(v[0]));
	return 0;
}
