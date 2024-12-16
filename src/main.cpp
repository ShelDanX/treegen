#include "gentree.h"
#include <iostream>

using namespace std;

int main()
{
    genTree gtree;
    int amount, height;
    cout << "Height of tree: ";
    cin >> height;
    cout << "Amount of elements (nodes): ";
    cin >> amount;
    if (gtree.generate(height, amount)) {
        gtree.print();
        cout << endl;
        gtree.printCode();
    }
    else {
        cout << "Failed to create tree with these parameters" << endl;
    }   
}
