#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void swap (int *p1, int *p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// inclusive bounds
void slowsort(int A[], int start, int end) {
    if (start >= end) 
        return;
    
    int middle = start + (end - start) / 2;

    slowsort(A, start, middle);
    slowsort(A, middle + 1, end);

    if (A[middle] > A[end]) {
        swap(&A[middle], &A[end]);
    }

    slowsort(A, start, end - 1);
}

int main() {
    const int size = 10000;
    int arr1[size];
    int arr2[size];
    for (int i = 0; i < size; i++) {
        arr1[i] = rand() % size;
        arr2[i] = arr1[i];
    }

    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;
    // for milliseconds, use using ms = std::chrono::duration<double, std::milli>;

    auto before = clock::now();

    std::sort(std::begin(arr2), std::end(arr2));

    sec duration = clock::now() - before;

    std::cout << "It took " << duration.count() << "s for std::sort" << std::endl;
    
    before = clock::now();

    slowsort(arr1, 0, size - 1);


    duration = clock::now() - before;

    std::cout << "It took " << duration.count() << "s for slowsort" << std::endl;


}