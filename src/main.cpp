#include "gentree.h"
#include <iostream>

using namespace std;

int main()
{
    genTree gtree;
    int amount, height;
    cout << "Height of tree: ";
    cin >> height;
    cout << "Amount of elements: ";
    cin >> amount;
    gtree.generate(height, amount);
    gtree.print();
}
