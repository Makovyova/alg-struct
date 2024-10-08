#include <iostream>

class SortAlgo {
private:
    int data[10];
    int lenD;
public:
    SortAlgo(int data[], int lenD); 
    void selectionSort();
    void printArray();
};

SortAlgo::SortAlgo(int data[], int lenD) {
    for (int i = 0; i < lenD; i++) {
        this->data[i] = data[i];
    }
    this->lenD = lenD;
}

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
    sorter.selectionSort();
    std::cout << "after sort" << std::endl;
    sorter.printArray();
    return 0;
}