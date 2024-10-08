#include <iostream>

int main() 
{
    const int Nmax = 1000;
    int c[100] = { 0 };
    int a[Nmax];
    //...

    int n;
    std::cout << "n="; std::cin >> n;

    // Write array
    std::cout << "write array: ";
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::cout << std::endl;

    for (int i = 0; i < n; i++)
        c[a[i]]++;

    int k = 0;
    for (int i = 0; i < 100; i++)
        while (c[i] != 0)
        {
            a[k] = i;
            k++;
            c[i]--;
        };
    
    //Print array
    std::cout << "after sort" << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
	return 0;
}

