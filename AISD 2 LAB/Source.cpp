#include<iostream>
#include<time.h>
#include"BinaryImage.h"


int main()
{
    try {
             BinaryImage<int, 3, 7> image(3, 3);
               image(0, 0) = true;
               image(1, 1) = 7;
               std::cout << image;
               std::cout << std::endl;
               !image;
               std::cout << image;
               image(1, 1) = 5; // FAIL: Should throw
         

       /* enum class CardinalDirection { NORTH, EAST, SOUTH, WEST };
        BinaryImage<CardinalDirection,
            CardinalDirection::NORTH,
            CardinalDirection::SOUTH> image(2, 2);
        std::cout << image; // ..
                            // ..
        image(0, 0) = CardinalDirection::SOUTH;//только один раз единичку записали и всё
        std::cout << image; // 1.
                            // ..
        image(0, 0) = CardinalDirection::EAST; // FAIL: Should throw
    */}
    catch (const char* msg) {
        std::cout << msg << '\n';
    }


}
