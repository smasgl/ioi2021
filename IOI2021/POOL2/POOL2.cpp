#include <iostream>
#include <chrono>

void printArray(int* array, int count)
{
    for (int i = 0; i < count; i++)
        std::cout << array[i] << " ";
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
    int globalWaterCount = 0;
    for (int i = elementsCount-1; i > 0; i--)
    {
        int localWaterCount = 0;
        int wallSpotted = 0;
        for (int j = 0; j < elementsCount; j++)
        {
            if ((i - elements[j]) > 0) // = 0
                localWaterCount += wallSpotted;
            else // = 1
            {
                globalWaterCount += localWaterCount;
                localWaterCount = 0;
                wallSpotted = 1;
            }
        }
    }
    std::cout << abs(globalWaterCount - targetCapacity) << "\n";


    // Stop measuring time and calculate the elapsed time
    //auto end = std::chrono::high_resolution_clock::now();
    //auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    //std::cout << "\n" << elapsed.count() * 1e-9 << "s";

    printArray(elements, elementsCount);
}