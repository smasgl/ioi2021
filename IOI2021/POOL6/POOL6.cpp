#include <iostream>
#include <vector>

void printArray(long* array, long count)
{
    for (long i = 0; i < count; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}

void printVector(std::vector<long> vect)
{
    for (long i : vect)
    {
        std::cout << i << " ";
    }
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
    long elementsCount, targetCapacity, currentCapacity, comparer;
    currentCapacity = comparer = 0;
    std::cin >> elementsCount >> targetCapacity;
    long* elements = new long[elementsCount];
    long max_index = 0;
    long factorial = 0;
    comparer = elementsCount - 1;
    std::vector<long> result_elements;
    result_elements.push_back(comparer);
    long left_counter = 0;
    for (long i = 0; i < elementsCount; i++)
    {
        std::cin >> elements[i];

        if (elements[i] == elementsCount)
        {
            max_index = i;
        }

        if (i >= elementsCount - 2)
            continue;

        if ((comparer - (i + 1) + currentCapacity <= targetCapacity))
        {
            currentCapacity += comparer - (i + 1);
            result_elements.push_back(i + 1);
        }
        else
        {
            result_elements.insert(result_elements.begin() + left_counter, i + 1);
            left_counter++;
        }
    }
    result_elements.push_back(elementsCount);

    std::cout << getDifference(elements, elementsCount, targetCapacity, max_index) << std::endl;

    if (currentCapacity != targetCapacity)
        std::cout << -1;
    else
        printVector(result_elements);
}