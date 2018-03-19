#include <iostream>
#include <vector>


void PocketSortByLastDigit(std::vector<int>& intArray)
{
    std::vector<int> pockets(10, 0);
    for(int i = 0; i < intArray.size(); ++i) {
        ++pockets[intArray[i] % 10];

    }
    int prevPocketSize = pockets[0];
    for(int i = 0; i < pockets.size(); ++i) {

    }
}

int main() {
    std::vector<int> intArray;
    int number = 0;
    while(std::cin >> number) {
        intArray.push_back(number);
    }
    return 0;
}