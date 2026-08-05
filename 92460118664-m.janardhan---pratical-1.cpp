#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

// Bubble Sort
void bubble(vector<int>& a)
{
    for (int i = 0; i < a.size() - 1; i++)
    {
        bool changed = false;

        for (int j = 0; j < a.size() - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                changed = true;
            }
        }

        if (!changed)
            break;
    }
}

// Selection Sort
void selection(vector<int>& a)
{
    for (int i = 0; i < a.size() - 1; i++)
    {
        int smallest = i;

        for (int j = i + 1; j < a.size(); j++)
        {
            if (a[j] < a[smallest])
                smallest = j;
        }

        if (smallest != i)
            swap(a[i], a[smallest]);
    }
}

// Insertion Sort
void insertion(vector<int>& a)
{
    for (int i = 1; i < a.size(); i++)
    {
        int value = a[i];
        int pos = i - 1;

        while (pos >= 0 && a[pos] > value)
        {
            a[pos + 1] = a[pos];
            pos--;
        }

        a[pos + 1] = value;
    }
}

// Merge function
void combine(vector<int>& a, int left, int middle, int right)
{
    vector<int> first(a.begin() + left, a.begin() + middle + 1);
    vector<int> second(a.begin() + middle + 1, a.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < first.size() && j < second.size())
    {
        if (first[i] <= second[j])
            a[k++] = first[i++];
        else
            a[k++] = second[j++];
    }

    while (i < first.size())
        a[k++] = first[i++];

    while (j < second.size())
        a[k++] = second[j++];
}

// Merge Sort
void mergeSorting(vector<int>& a, int left, int right)
{
    if (left >= right)
        return;

    int middle = left + (right - left) / 2;

    mergeSorting(a, left, middle);
    mergeSorting(a, middle + 1, right);

    combine(a, left, middle, right);
}

// Partition for Quick Sort
int divide(vector<int>& a, int low, int high)
{
    int pivot = a[low];
    int i = low + 1;
    int j = high;

    while (i <= j)
    {
        while (i <= high && a[i] <= pivot)
            i++;

        while (j >= low && a[j] > pivot)
            j--;

        if (i < j)
            swap(a[i], a[j]);
    }

    swap(a[low], a[j]);

    return j;
}

// Quick Sort
void quick(vector<int>& a, int low, int high)
{
    if (low < high)
    {
        int position = divide(a, low, high);

        quick(a, low, position - 1);
        quick(a, position + 1, high);
    }
}

int main()
{
    const int SIZE = 100;

    vector<int> original(SIZE);

    // Random number generator
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> range(1, 999);

    for (int& x : original)
        x = range(generator);

    cout << "Sorting Algorithm Time Analysis\n";
    cout << "-------------------------------\n";
    cout << "Number of Elements : " << SIZE << "\n\n";

    vector<int> data;

    // Bubble Sort
    data = original;
    auto begin = chrono::steady_clock::now();

    bubble(data);

    auto finish = chrono::steady_clock::now();

    cout << "Bubble Sort    : "
         << chrono::duration_cast<chrono::microseconds>
            (finish - begin).count()
         << " microseconds\n";

    // Selection Sort
    data = original;
    begin = chrono::steady_clock::now();

    selection(data);

    finish = chrono::steady_clock::now();

    cout << "Selection Sort : "
         << chrono::duration_cast<chrono::microseconds>
            (finish - begin).count()
         << " microseconds\n";

    // Insertion Sort
    data = original;
    begin = chrono::steady_clock::now();

    insertion(data);

    finish = chrono::steady_clock::now();

    cout << "Insertion Sort : "
         << chrono::duration_cast<chrono::microseconds>
            (finish - begin).count()
         << " microseconds\n";

    // Merge Sort
    data = original;
    begin = chrono::steady_clock::now();

    mergeSorting(data, 0, SIZE - 1);

    finish = chrono::steady_clock::now();

    cout << "Merge Sort     : "
         << chrono::duration_cast<chrono::microseconds>
            (finish - begin).count()
         << " microseconds\n";

    // Quick Sort
    data = original;
    begin = chrono::steady_clock::now();

    quick(data, 0, SIZE - 1);

    finish = chrono::steady_clock::now();

    cout << "Quick Sort     : "
         << chrono::duration_cast<chrono::microseconds>
            (finish - begin).count()
         << " microseconds\n";

    return 0;
}