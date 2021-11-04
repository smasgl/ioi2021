#include <iostream>
#include <limits>

void printArray(int* array, int count)
{
    for (int i = 0; i < count; i++)
        std::cout << array[i] << " ";
}

int getDifference(int* array, int count, int targetCapacity)
{
    int t1 = array[0];
    int t2 = std::numeric_limits<int>::max();
    int lDistance = 0;
    int cDistance = 1;
    int result = 0;
    int difference = 0;
    
    for (int i = 1; i < count - 1; i++)
    {
        cDistance++;

        if (t2 > array[i])
        {
            t2 = array[i];
            result += t1 - t2;
        }
        else
        {

            // Calculate
            t1 = array[i];
            t2 = array[i + 1];
            i++;
            lDistance = cDistance;
            cDistance = 1;
        }
    }
    return difference;
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