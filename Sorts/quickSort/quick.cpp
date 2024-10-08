#include <iostream>

class SortAlgo {
private:
    int data[10];
    int lenD;
public:
    SortAlgo(int data[], int lenD);
    void selectionSort();
    void quickSort();
    void printArray();
};

SortAlgo::SortAlgo(int data[], int lenD) {
    for (int i = 0; i < lenD; i++) {
        this->data[i] = data[i];
    }
    this->lenD = lenD;
}
//1
void SortAlgo::selectionSort() {
    int j = 0;
    int tmp = 0;
    for (int i = 0; i < this->lenD; i++) {
        j = i;
        for (int k = i; k < this->lenD; k++) {
            if (this->data[j] > this->data[k]) {
                j = k;
            }
        }
        tmp = this->data[i];
        this->data[i] = this->data[j];
        this->data[j] = tmp;
    }
}
//2
void SortAlgo::quickSort() {
    int pivot = 0;
    int ind = lenD / 2;
    int i, j = 0, k = 0;
    if (lenD > 1) {
        int* L = new int[lenD];
        int* R = new int[lenD];
        pivot = data[ind];
        for (i = 0; i < lenD; i++) {
            if (i != ind) {
                if (data[i] < pivot) {
                    L[j] = data[i];
                    j++;
                }
                else {
                    R[k] = data[i];
                    k++;
                }
            }
        }
        quickSort(L, j);
        quickSort(R, k);
        for (int cnt = 0; cnt < lenD; cnt++) {
            if (cnt < j) {
                data[cnt] = L[cnt];;
            }
            else if (cnt == j) {
                data[cnt] = pivot;
            }
            else {
                data[cnt] = R[cnt - (j + 1)];
            }
        }
    }
}


void SortAlgo::printArray() {
    for (int i = 0; i < lenD; i++) {
        std::cout << this->data[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int data[] = { 5, 2, 8, 3, 1, 6, 4 };
    int lenD = sizeof(data) / sizeof(data[0]);
    SortAlgo sorter(data, lenD);
    std::cout << "before sort" << std::endl;
    sorter.printArray();
    sorter.quickSort();
    std::cout << "after sort" << std::endl;
    sorter.printArray();
    return 0;
}