#include <iostream>
#include <vector>

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
            difference += extractDifferenceFromMidElements(mid_elements, array[i]);
        }
        else
        {
            mid_elements.push_back(array[i]);
        }
    }

    return difference - targetCapacity;
}


int main()
{
    int elementsCount, targetCapacity;
    std::cin >> elementsCount >> targetCapacity;
    int* elements = new int[elementsCount];
    for (int i = 0; i < elementsCount; i++)
        std::cin >> elements[i];

    std::cout << getDifference(elements, elementsCount, targetCapacity);

    //printArray(elements, elementsCount);
}