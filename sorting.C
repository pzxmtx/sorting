/**
* Test for different sorting algorithms. The goals are:
*  - to ensure that an algorithm works as expected
*  - to measure performance of a given algorithm 
*    regardless the data set specifics
*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <chrono>
#include <iomanip>
#include <functional>
#include <vector>
#include <random>
#include <map>
#include <set>
#include "sorting.h"
#include "utils.h"

/*
 * Descriptor of the tests to be ran
 */
template<typename T>
struct sorting_test
{
    typedef size_t(*sortptr)(T*, size_t, bool);	

    sorting_test(const std::string name, sortptr ptr, bool skip=false) : 
        algo_name{ name },
        algoptr{ ptr },
        skip{ skip }
    {
    }

    const std::string algo_name;	// Name of the algorithm
    sortptr algoptr;			// Pointer to the implementation 
    bool skip;				// Set to <code>true</code> to skip this test
};

struct sorting_test<long> testSuite[] =
{
    {
        "bubble",
        bubble
    },
    {
        "selection",
        selection
    },
    {
	"selection in assembler",
	selection_asm
    },
    {
        "shell",
        shell
    },
    {
        "shell in assembler",
        shell_asm
    },
    {
        "insert",
        insertion
    },
    {
        "insertion in assembler",
        insertion_asm
    },
    {
        "merge",
        merge
    },
    {
        "quicksort with stack",
        qs
    },
    {
        "quicksort with recursion",
        qs_recursive
    },
    {
        "pyramid",
        pyramid
    },
    {
        "std::sort",
        standard_sort
    }
};

/*
 * Make the data sets. Each algorithm will run with the same 
 * data as other ones, so that the timings would be measured on the 
 * same data set.
 *
 * @param numberOfTests How many times each data set needs to be measured
 */
void run_tests(const size_t numberOfTests)
{
    // total time for each algorithm
    std::map<std::string, std::chrono::duration<double> > totals;
    std::map<std::string, size_t > complexity; // number of circles an algorithm made for a given data set

    for (size_t testSet = 0; testSet < numberOfTests; ++testSet)
    {
        const size_t maxnum{ 100 }; // data set size
        long v[maxnum];              // data set
        randomize(v, maxnum);       // fill the data set
        
        for (auto i = std::begin(testSuite); i != std::end(testSuite); ++i)
        {
            if ((*i).skip)
            {
                continue;
            }

            bool failed{ false };
            size_t n = maxnum;

            long original[maxnum];

	    // fill a data set copy with test data to prove algorithm's correctness
            long* sample = new long[n];
            for (size_t s = 0; s < n; ++s)
            {
                sample[s] = v[s];
                original[s] = v[s];
            }

            // perform sample sort using an algorithm provided by standard library
            std::sort(&sample[0], &sample[n]);

            // start timer and do sort using our implementation 
            auto start = std::chrono::steady_clock::now();
            size_t steps = (*i).algoptr(v, n, true);
            auto end = std::chrono::steady_clock::now();
                        
            // verify that the sort was done correctly 
            for (size_t s = 0; s < n; ++s)
            {
                if (sample[s] != v[s])
                {
                    failed = true;
                    break;
                }
            }

            if (failed)
            {
                std::cerr << (*i).algo_name << " failed to sort correctly" << std::endl;
                print<long>("Unsorted array     : ", original, n);
                print<long>("Correctly sorted   : ", sample, n);
                print<long>("Sorted by algorithm: ", v, n);
            }
            else
            {
                totals[(*i).algo_name] += (end - start);
                complexity[(*i).algo_name] = steps;
            }

            delete[] sample;
        }
    }
    
    for (auto i = std::begin(testSuite); i != std::end(testSuite); ++i)
    {
        if (totals[(*i).algo_name] == std::chrono::duration<double>::zero())
        {
            std::cout << (*i).algo_name << std::setw(15) << " -- " << std::endl;
            
        }
        else
        {
            std::cout << (*i).algo_name << " sort took " << std::setw(15) << (totals[(*i).algo_name] / 10) * 1000000 << " ms to complete" << std::endl;
            std::cout << (*i).algo_name << " sort took " << (complexity[(*i).algo_name]) << " steps to complete" << std::endl;
        }
        std::cout << std::endl;
    }
}

const int number_of_tests = 10;

int main()
{
    run_tests(number_of_tests);

    return 0;

}
