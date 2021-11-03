#include <iostream>
#include <chrono>

void printArray(int* array, int count)
{
    for (int i = 0; i < count; i++)
        std::cout << array[i] << " ";
}

int main()
{
    int elementSum = 0;
    int elementsCount, targetCapacity;
    std::cin >> elementsCount >> targetCapacity;
    int fieldSum = elementsCount * elementsCount;
    int* elements = new int[elementsCount];
    for (int i = 0; i < elementsCount; i++)
    {
        std::cin >> elements[i];
        elementSum += elements[i];
    }

    int possibleWater = fieldSum - elementSum;
    // Start measuring time
    //auto begin = std::chrono::high_resolution_clock::now();

    int maxElementIndex = 0;
    int travelDistance = 0;
    int maxElementInRangeIndex = -1;

    for (int i = 0; i < elementsCount; i++)
    {
        if (elements[i] > elements[maxElementIndex])
        {
            maxElementIndex = i;
            possibleWater -= (elements[maxElementIndex] - elements[maxElementInRangeIndex]) * travelDistance;
            travelDistance = 0;
            maxElementInRangeIndex = -1;
        }
        else if (i == elementsCount - 1)
        {
            if (maxElementInRangeIndex == -1 || elements[i] > elements[maxElementInRangeIndex])
            {
                maxElementInRangeIndex = i;
            }

            possibleWater -= (elements[maxElementIndex] - elements[i]) * travelDistance;
            maxElementIndex = i;
            travelDistance = 0;

            if (maxElementInRangeIndex == elementsCount - 1)
                break;
            i = maxElementInRangeIndex;
            maxElementInRangeIndex = -1;
        }
        else if (maxElementInRangeIndex == -1 || elements[i] > elements[maxElementInRangeIndex])
        {
            maxElementInRangeIndex = i;
        }

        travelDistance++;
    }


    std::cout << abs(possibleWater - targetCapacity) << "\n";


    // Stop measuring time and calculate the elapsed time
    //auto end = std::chrono::high_resolution_clock::now();
    //auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    //std::cout << "\n" << elapsed.count() * 1e-9 << "s";

    printArray(elements, elementsCount);
}