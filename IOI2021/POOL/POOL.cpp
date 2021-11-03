#include <iostream>
#include <vector>
#include <chrono>

void printArray(long* array, long count)
{
    for (long i = 0; i < count; i++)
        std::cout << array[i] << " ";
}

long extractDifferenceFromMidElements(std::vector<long> mid_elements, long comparer)
{
    long difference = 0;
    for (long i : mid_elements)
    {
        difference += comparer - i;
    }
    return difference;
}

long getDifference(long* array, long count, long targetCapacity)
{
    long difference = 0;
    long left_element = array[0];
    std::vector<long> mid_elements;

    for (long i = 1; i < count; i++)
    {
        if (array[i] > left_element)
        {
            difference += extractDifferenceFromMidElements(mid_elements ,left_element);
            left_element = array[i];
            mid_elements.clear();
        }
        else if (i == count - 1)
        {
            mid_elements.push_back(array[i]);
            mid_elements.insert(mid_elements.begin(), left_element);
            left_element = mid_elements[mid_elements.size() - 1];
            std::vector<long> extra_mid_elements;

            for (long i = mid_elements.size() - 2; i >= 0; i--)
            {
                if (mid_elements[i] > left_element)
                {
                    difference += extractDifferenceFromMidElements(extra_mid_elements, left_element);
                    left_element = mid_elements[i];
                    extra_mid_elements.clear();
                }
                else if (i == 0)
                {
                    difference += extractDifferenceFromMidElements(extra_mid_elements, left_element);
                }
                else
                {
                    extra_mid_elements.push_back(mid_elements[i]);
                }
            }
            //difference += extractDifferenceFromMidElements(mid_elements, left_element);
        }
        else
        {
            mid_elements.push_back(array[i]);
        }
    }

    return abs(difference - targetCapacity);
}


int main()
{
    long elementsCount, targetCapacity;
    std::cin >> elementsCount >> targetCapacity;
    long* elements = new long[elementsCount];
    for (long i = 0; i < elementsCount; i++)
        std::cin >> elements[i];
    // Start measuring time
    //auto begin = std::chrono::high_resolution_clock::now();

    std::cout << abs(getDifference(elements, elementsCount, targetCapacity)) << "\n";

    // Stop measuring time and calculate the elapsed time
    //auto end = std::chrono::high_resolution_clock::now();
    //auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    //std::cout << "\n" << elapsed.count() * 1e-9 << "s";

    printArray(elements, elementsCount);
}