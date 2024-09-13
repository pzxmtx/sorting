/**
 * Implementation of some popular sorting algorithms in C.
 */
#ifndef __SORTING_H
#define __SORTING_H
#endif /* __SORTING_H */

/*
* Bubble sort
*
* Run several iterations, comparing values of current and 
* previous elements on each of them. If current value is less than
* the previous one, swap them. On each iteration number of elements
* to compare reduced by 1. 
*
* Algorithm finishes when the number of elements becomes equal 1.
* 
* @param values    Array to sort
* @param size      Number of elements to sort
* @param ascending <code>true</code> if sort needs to be done in 
*                  ascending order; <code>false</code> otherwise
*/
template<class T> size_t bubble(T* values, size_t size, bool ascending = true)
{
	size_t counter = 0;		  

	for(size_t end = size;  end > 1 ; --end, ++counter)
	{
		for (size_t i = 0, j = 1; j < end; ++i, ++j, ++counter)
		{
			if (ascending ? values[j] < values[i] : values[j] > values[i])
			{
				T t = values[i];
				values[i] = values[j];
				values[j] = t;
			}
		}
	}

	return counter;
}

/*
* Selection sort algorithm.
*
* Look for a smallest value among the others and swap it with
* the next element from the start of array. Shift to the next
* element and repeat. 
*
* Algorithm finishes when there are no more elements left 
* to look over.
*
* @param values    Array to sort
* @param size      Number of elements to sort
* @param ascending <code>true</code> if ascending order needed, 
*                  <code>false</code> otherwise. 
*/
template<class T> size_t selection(T* values, size_t size, bool ascending = true)
{
	size_t counter = 0;		 

	for (size_t i = 0; i < size; ++i, ++counter)
	{
		T v{ values[i] };
		size_t p{ i };	
		for (size_t j = i; j < size; ++j, ++counter)
		{
			if (ascending ? values[j] < v : values[j] > v)
			{
				v = values[j];
				p = j;
			}
		}
		T t = values[i];
		values[i] = v;
		values[p] = t;
	}

	return counter;
}

/*
* Insertion sort.
*
* @param values    Array to sort
* @param size      Number of elements to sort
* @param ascneding <code>true</code> sort in ascending order, 
*                  <code>false</code> otherwise.
*/
template<typename T> size_t insertion(T* values, size_t size, bool ascending = true)
{
	size_t counter = 0;	
	for (size_t i = 0; i < size; ++i, ++counter)
	{
		auto j = i;
		T v = values[j];
		for ( ; j != 0 && (ascending ? values[j - 1] > v : values[j - 1] < v); j--, ++counter)
		{
			values[j] = values[j-1];
		}
		values[j] = v;
	}

	return counter;
}


/*
* Shell sort.
*
* It is another interpretation of insertion sort, but uses different step
* sizes.  
*
* @param values    Array to sort
* @param size      Number of elements to sort
* @param ascending <code>true</code> to sort in ascending order,
*                  <code>false</code> otherwise.
*/
template<class T> size_t shell(T* values, size_t size, bool ascending = true)
{
	size_t steps[] = { 9, 7, 2, 1 }; 
	size_t counter = 0;		  

	for (size_t n = 0; n < sizeof(steps) / sizeof(steps[0]); ++n, ++counter)
	{
		size_t stepSize = steps[n];

		for (size_t start = stepSize; start < size; ++start, ++counter)
		{
			T v = values[start];
			size_t j = start - stepSize;
			for ( ; j >= 0 && values[j] > v; j -= stepSize, ++counter)
			{
				values[j + stepSize] = values[j];
			}
			values[j + stepSize] = v;
		}
	}

	return counter;
}

/*
* Partition function for quick sort algorithm.
*
* @param values   Array to partition
* @param left     Left index 
* @param right    Right index
* @param counter  [output, optional] Number of loops ran
*/
template<class T> size_t partition(T* values, const size_t left, const size_t right, size_t& counter)
{
	T p{ values[right - 1] };
	size_t i{ left };
	size_t j{ right };
	
	while (true)
	{
		while (values[i] < p)
		{
			++i;
			++counter;
		}
		while(values[j] > p)
		{
			--j;
			++counter;
		}
		if (i >= j)
		{
			break;
		}
		std::swap(values[i++], values[j--]);
		++counter;
	}

	return j;
}

/*
 * Quick sort, non-recursive version of algorithm.
 *
 * This version uses STL's stack to hold ranges on array to partition.
 *
 * @param values    Array to sort
 * @param size      Number of elements to sort
 * @param ascending <code>true</code> to sort in ascending order,
 *                  <code>false</code> otherwise.
 */
template<class T> size_t qs(T* values, size_t size, bool acending = true)
{
	std::stack<std::pair<size_t, size_t>> s;
	size_t left = 0;
	size_t right = size - 1;
	size_t counter = 0;		  

	s.push({ left, right });

	while (!s.empty())
	{
		std::pair<size_t, size_t> p{ s.top() };
		s.pop();
		size_t n = partition(values, p.first, p.second, counter);
		if (p.first < n)
		{
			s.push({ p.first, n });
			s.push({ n + 1, p.second });
		}
		++counter;
	}
	return counter;
}

/*
 * Quick sort, recursive version of algorithm.
 *
 * @param values    Array to sort
 * @param size      Number of elements to sort
 * @param ascending <code>true</code> to sort in ascending order,
 *                  <code>false</code> otherwise.
 */
template<class T> size_t qs_recursive(T* values, size_t size, bool ascending = true)
{
	size_t counter = 0;
	std::function<void(long*, size_t, size_t)> sort;
	sort = [&sort, &counter](long* v, size_t left, size_t right)
	{
		++counter;
		if (left < right)
		{
			size_t n = partition(v, left, right, counter);
			sort(v, left, n);
			sort(v, n + 1, right);
		}
	};
	++counter;
	sort(values, 0, size - 1);
	return counter;
}

/*
 * Just a wrapper for standard library's sort
 *
 * It is used here as a sample for verification purposes.
 */
template<class T> size_t standard_sort(T* values, size_t size, bool ascending = true)
{
	std::sort(&values[0], &values[size]);
	return 0;
}

/*
* Merge sort
*
* @param values     Array to sort
* @param size       Number of elements to sort
* @param ascending  <code>true</code> to sort in ascending order, 
*                   <code>false</code> otherwise.
*/
template<class T> size_t merge(T* values, size_t size, bool ascending = true)
{
	T* sorted{ new T[size] }; // array to store intermediately sorted values
	size_t counter = 0;       // loop counter for algorithm analysis purpose

	for (size_t blockSize = 1; blockSize < size; blockSize *= 2, ++counter)
	{
		size_t sortedIndex = 0;

		for (size_t currentBlock = 0; currentBlock <= size / blockSize; currentBlock += 2, ++counter)
		{
			size_t left = currentBlock * blockSize;
			size_t left_stop = left + blockSize;
			size_t right = left_stop;
			size_t right_stop = right + blockSize > size ? size : right + blockSize;

			if (right > size || right_stop > size)
			{
				break;
			}

			while (left < left_stop && right < right_stop)
			{
				if (values[left] <= values[right])
				{
					sorted[sortedIndex++] = values[left++];
				}
				else if (values[left] > values[right])
				{
					sorted[sortedIndex++] = values[right++];
				}
				++counter;
			}

			while (left < left_stop)
			{
				sorted[sortedIndex++] = values[left++];
				++counter;
			}
			while (right < right_stop)
			{
				sorted[sortedIndex++] = values[right++];
				++counter;
			}
		}

		for (size_t t = 0; t < size; ++t, ++counter)
		{
			values[t] = sorted[t];
		}
	}

	delete[] sorted;

	return counter;
}

/*
* Pyramid sort
*
* @param values    Array to sort
* @param size      Number of elements to sort
* @param ascending <code>true</code> to sort in ascending order,
*                  <code>false</code> otherwise.
*/
template<class T=long> size_t pyramid(T* values, size_t size, bool ascending = true)
{
	auto heapify = [&values](const size_t to, bool asc) -> size_t 
	{
		size_t counter = 0;

		for (int i = (static_cast<int>(to) / 2) - 1; i >= 0; --i, ++counter)
		{
			size_t left  = (2 * i) + 1;
			size_t right = (2 * i) + 2;

			T* p = &values[left];

			++counter;
			if (right < to && *p < values[right])
			{
				p = &values[right];
			}

			++counter;
			if (values[i] < *p)
			{
				T t = *p;
				*p = values[i];
				values[i] = t;
			}

			++counter;
			if (i == 0)
			{
				break;
			}
		}
		return counter;
	};
	
	size_t counter = 0;

	for (size_t i = size, j = i - 1; i > 1; --i, --j, ++counter)
	{
		counter += heapify(i, ascending);
		T t = values[0];
		values[0] = values[j];
		values[j] = t;
	}

	return counter;
}

extern "C" void _shell(long* v, size_t n);
template<typename T> size_t shell_asm(T* v, size_t n, bool ascending = true)
{
         _shell(v, n);
         return 0;
}

extern "C" void _insertion(long* v, size_t n);
template<typename T> size_t insertion_asm(T* v, size_t n, bool ascending = true)
{
        _insertion(v, n);
        return 0;
}

extern "C" void _selection(long* v, size_t n);
template<typename T> size_t selection_asm(T* v, size_t n, bool ascending = true)
{
	_selection(v, n);
	return 0;
}
