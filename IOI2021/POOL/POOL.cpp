#include <iostream>
#include <vector>
#include <chrono>

void printArray(int* array, int count)
{
    for (int i = 0; i < count; i++)
        std::cout << array[i] << " ";
}

int extractDifferenceFromMidElements(std::vector<int> mid_elements, int comparer)
{
    int difference = 0;
    for (int i : mid_elements)
    {
        difference += comparer - i;
    }
    return difference;
}

int getDifference(int* array, int count, int targetCapacity)
{
    int difference = 0;
    int left_element = array[0];
    std::vector<int> mid_elements;

    for (int i = 1; i < count; i++)
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
            std::vector<int> extra_mid_elements;

            for (int i = mid_elements.size() - 2; i >= 0; i--)
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
    int elementsCount, targetCapacity;
    std::cin >> elementsCount >> targetCapacity;
    int* elements = new int[elementsCount];
    for (int i = 0; i < elementsCount; i++)
        std::cin >> elements[i];
    // Start measuring time
    //auto begin = std::chrono::high_resolution_clock::now();

    std::cout << getDifference(elements, elementsCount, targetCapacity) << "\n";

    // Stop measuring time and calculate the elapsed time
    //auto end = std::chrono::high_resolution_clock::now();
    //auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    //std::cout << "\n" << elapsed.count() * 1e-9 << "s";

    printArray(elements, elementsCount);
}