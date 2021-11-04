#include <iostream>
#include <vector>

void printArray(long* array, long count)
{
    for (long i = 0; i < count; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
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

long getDifference(long* elements, long count, long targetCapacity, long max_index)
{
    //number of elements in first array
    long n_f_elements = max_index + 1;


    long difference = 0;
    //iterate first array
    long left_element = elements[0];
    std::vector<long> mid_elements;

    for (long i = 1; i < n_f_elements; i++)
    {
        if (elements[i] > left_element)
        {
            if (mid_elements.size() > 0)
                difference += extractDifferenceFromMidElements(mid_elements, left_element);
            left_element = elements[i];
            mid_elements.clear();
        }
        else
        {
            mid_elements.push_back(elements[i]);
        }
    }

    //iterate second array
    left_element = elements[count - 1];
    mid_elements.clear();

    for (long i = count - 2; i >= n_f_elements - 1; i--)
    {
        if (elements[i] > left_element)
        {
            if (mid_elements.size() > 0)
                difference += extractDifferenceFromMidElements(mid_elements, left_element);
            left_element = elements[i];
            mid_elements.clear();
        }
        else
        {
            mid_elements.push_back(elements[i]);
        }
    }

    long returnValueResult = targetCapacity - difference;
    if (returnValueResult < 0)
    {
        return returnValueResult * -1;
    }

    return returnValueResult;
}


int main()
{
    long elementsCount, targetCapacity;
    std::cin >> elementsCount >> targetCapacity;
    long* elements = new long[elementsCount];
    long max_index = 0;
    for (long i = 0; i < elementsCount; i++)
    {
        std::cin >> elements[i];

        if (elements[i] == elementsCount)
            max_index = i;
    }
    // Start measuring time
    //auto begin = std::chrono::high_resolution_clock::now();

    std::cout << getDifference(elements, elementsCount, targetCapacity, max_index) << "\n";

    // Stop measuring time and calculate the elapsed time
    //auto end = std::chrono::high_resolution_clock::now();
    //auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    //std::cout << "\n" << elapsed.count() * 1e-9 << "s";

    printArray(elements, elementsCount);
}