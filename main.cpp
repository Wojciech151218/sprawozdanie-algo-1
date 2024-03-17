#include <iostream>
#include <vector>
#include <chrono>
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
template <class T> void swap ( T& a, T& b )
{
    T c(a); a=b; b=c;
}

void display(int p,int q, std::vector<int> A){
    int vectorLength = A.size();
    for(int i = 0 ;i != vectorLength;i++){
        if(i == p or i == q){
            std::cout << RED << A[i] << " "<<RESET ;
        }else{
            std::cout<< A[i] << " " ;
        }

    }
    std::cout<<"\n";
}
void heapify(std::vector<int>* A, int n, int i, void (*display)(int, int, const std::vector<int>)) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && (*A)[left] > (*A)[largest]) {
        largest = left;
    }
    if (right < n && (*A)[right] > (*A)[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap<int>((A->at(i)), (A->at(largest)));
        display(i, largest, *A);
        heapify(A, n, largest, display);
    }
}

void heapSort(std::vector<int>* A, void (*display)(int, int, const std::vector<int>)) {
    int n = A->size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, i, display);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap<int>((A->at(i)), (A->at(0)));

        display(i, 0, *A);
        heapify(A, i, 0, display);
    }
}
void shellSort(std::vector<int>* A, void (*display)(int, int, const std::vector<int>)){
    int length = A->size();
    std::vector<int> sedgewickIncrements = {1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905,
                                            8929, 16001, 36289, 64769, 146305, 260609, 587521,
                                            1045505, 2354689, 4188161, 9427969};
    int sedgewickIndex = 0;
    while (sedgewickIncrements[sedgewickIndex] < A->size() / 3) {
        sedgewickIndex++;
    }

    int gap = sedgewickIncrements[sedgewickIndex];
    while (gap > 0) {
        for( int i  = gap ;i != length  ; i++){
            int temp = (*A)[i];
            int j = i;
            while (j >= gap and (*A)[j-gap] > temp){
                swap<int>((A->at(j)),(A->at(j-gap)));
                display(j,j-gap,*A);
                j -= gap;
            }
        }
        gap /= 2;

    }
}
void dontDisplay(int p,int q, std::vector<int> A){
    //ta funckja zostaje wywołana po zmianie elementów zbioru w algorytmach
    // p i q to indeksy zamienionych elementów A to zbiór
    // możesz tu coś zaimplementować jeśli potrzebujesz do zrobienia sprawozdania
    // jeśli nie to zostaw tak jak jest
    return;
}

int main() {
    srand(time(NULL));
    int n = 20;
    std::vector<int> A(n);
    for(int i = 0;i!=n;i++){
        A[i] = std::rand()%1000;
    }
    display(-1,-1,A);
    //heapSort(&A,display);
    //heapSort(&A,dontDisplay);// algorytm bez kosztów wyświetlania
    shellSort(&A,display);
    //shellSort(&A,dontDisplay);
    //display(-1,-1,A);
    return 0;
}
