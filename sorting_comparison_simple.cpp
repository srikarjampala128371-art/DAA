#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*
    This program compares 5 sorting algorithms:
    1. Bubble Sort
    2. Selection Sort
    3. Insertion Sort
    4. Merge Sort
    5. Quick Sort

    Each algorithm sorts its own copy of the same list of
    random numbers, so the time comparison is fair.
*/

// Bubble Sort: repeatedly swap neighboring numbers if they are in the wrong order
void bubbleSort(vector<int>& numbers)
{
    int size = numbers.size();

    for (int pass = 0; pass < size - 1; pass++)
    {
        for (int i = 0; i < size - pass - 1; i++)
        {
            if (numbers[i] > numbers[i + 1])
                swap(numbers[i], numbers[i + 1]);
        }
    }
}

// Selection Sort: repeatedly find the smallest number and move it to the front
void selectionSort(vector<int>& numbers)
{
    int size = numbers.size();

    for (int current = 0; current < size - 1; current++)
    {
        int smallestIndex = current;

        for (int i = current + 1; i < size; i++)
        {
            if (numbers[i] < numbers[smallestIndex])
                smallestIndex = i;
        }

        swap(numbers[current], numbers[smallestIndex]);
    }
}

// Insertion Sort: build the sorted list one number at a time
void insertionSort(vector<int>& numbers)
{
    int size = numbers.size();

    for (int i = 1; i < size; i++)
    {
        int currentValue = numbers[i];
        int j = i - 1;

        while (j >= 0 && numbers[j] > currentValue)
        {
            numbers[j + 1] = numbers[j];
            j--;
        }

        numbers[j + 1] = currentValue;
    }
}

// Merges two sorted halves of the list back together in order
void mergeTwoHalves(vector<int>& numbers, int start, int mid, int end)
{
    vector<int> leftHalf(numbers.begin() + start, numbers.begin() + mid + 1);
    vector<int> rightHalf(numbers.begin() + mid + 1, numbers.begin() + end + 1);

    int i = 0, j = 0, k = start;

    while (i < leftHalf.size() && j < rightHalf.size())
    {
        if (leftHalf[i] <= rightHalf[j])
            numbers[k++] = leftHalf[i++];
        else
            numbers[k++] = rightHalf[j++];
    }

    while (i < leftHalf.size())
        numbers[k++] = leftHalf[i++];

    while (j < rightHalf.size())
        numbers[k++] = rightHalf[j++];
}

// Merge Sort: split the list in half repeatedly, then merge the sorted halves
void mergeSort(vector<int>& numbers, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(numbers, start, mid);
        mergeSort(numbers, mid + 1, end);
        mergeTwoHalves(numbers, start, mid, end);
    }
}

// Places the pivot number in its correct position, smaller numbers to the left
int partition(vector<int>& numbers, int low, int high)
{
    int pivot = numbers[high];
    int boundary = low - 1;

    for (int i = low; i < high; i++)
    {
        if (numbers[i] < pivot)
        {
            boundary++;
            swap(numbers[boundary], numbers[i]);
        }
    }

    swap(numbers[boundary + 1], numbers[high]);
    return boundary + 1;
}

// Quick Sort: pick a pivot, sort numbers around it, repeat on each side
void quickSort(vector<int>& numbers, int low, int high)
{
    if (low < high)
    {
        int pivotPosition = partition(numbers, low, high);
        quickSort(numbers, low, pivotPosition - 1);
        quickSort(numbers, pivotPosition + 1, high);
    }
}

int main()
{
    const int totalNumbers = 100;
    vector<int> originalList(totalNumbers);

    // Fill the list with random numbers between 0 and 999
    srand(time(0));
    for (int i = 0; i < totalNumbers; i++)
        originalList[i] = rand() % 1000;

    cout << "Number of Elements = " << totalNumbers << "\n\n";

    // --- Bubble Sort ---
    vector<int> list1 = originalList;
    auto start1 = high_resolution_clock::now();
    bubbleSort(list1);
    auto end1 = high_resolution_clock::now();
    cout << "Bubble Sort Time    : " << duration_cast<microseconds>(end1 - start1).count() << " microseconds\n";

    // --- Selection Sort ---
    vector<int> list2 = originalList;
    auto start2 = high_resolution_clock::now();
    selectionSort(list2);
    auto end2 = high_resolution_clock::now();
    cout << "Selection Sort Time : " << duration_cast<microseconds>(end2 - start2).count() << " microseconds\n";

    // --- Insertion Sort ---
    vector<int> list3 = originalList;
    auto start3 = high_resolution_clock::now();
    insertionSort(list3);
    auto end3 = high_resolution_clock::now();
    cout << "Insertion Sort Time : " << duration_cast<microseconds>(end3 - start3).count() << " microseconds\n";

    // --- Merge Sort ---
    vector<int> list4 = originalList;
    auto start4 = high_resolution_clock::now();
    mergeSort(list4, 0, list4.size() - 1);
    auto end4 = high_resolution_clock::now();
    cout << "Merge Sort Time     : " << duration_cast<microseconds>(end4 - start4).count() << " microseconds\n";

    // --- Quick Sort ---
    vector<int> list5 = originalList;
    auto start5 = high_resolution_clock::now();
    quickSort(list5, 0, list5.size() - 1);
    auto end5 = high_resolution_clock::now();
    cout << "Quick Sort Time     : " << duration_cast<microseconds>(end5 - start5).count() << " microseconds\n";

    return 0;
}
