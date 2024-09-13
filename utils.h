#ifndef __UTILS_H
#define __UTILS_H
#include <iostream>
#include <iomanip>

/**
* Test array generator
*
* Generates an array of a given size and fills it with
* with the random numbers
*
* @param v    Array to fill
* @param size Size of array
*/
void randomize(long* v, const std::size_t size, long maxval = 1000000);

/**
 * Print out array to console
 *
 * @param prefix Prefix output with specified string (may be empty)
 * @param values Array to print
 * @param size   Size of array
 * @param head   Print some kind of table header
 */
template<class T> void print(std::string prefix, T* values, size_t size, bool header = true)
{
        if (!prefix.empty())
        {
                for (size_t i = 0; i < prefix.length(); ++i)
                {
                        std::cout << " ";
                }
        }
        if (header)
        {

                for (size_t i = 0; i < size; ++i)
                {
                        std::cout << std::setw(4) << i << " ";
                }
        }
        std::cout << std::endl;
        std::cout << prefix;
        for (size_t i = 0; i < size; ++i)
        {
                std::cout << std::setw(4) << values[i] << " ";
        }
        std::cout << std::endl;
}

#endif /* __UTILS_H */
