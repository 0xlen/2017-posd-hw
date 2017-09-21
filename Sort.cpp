#include "include/Sort.h"

/**
 * In the sorting, use lambda expressions to describe the sorting relations between the shapes for C++0x (C++11)
 *
 * [](firstShape, secondShape) {
 *
 * Compile (GCC 4.8 recommended)
 *
 *   g++ -std=gnu++0x -c Sort.cpp
 */

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList) {
    shapeList->sort([](Shape *firstShape, Shape *secondShape) {
            return firstShape->perimeter() < secondShape->perimeter();
        }
    );
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList) {
    shapeList->sort([](Shape *firstShape, Shape *secondShape) {
            return firstShape->perimeter() > secondShape->perimeter();
        }
    );
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList) {
    shapeList->sort(
        [](Shape *firstShape, Shape *secondShape) {
            return firstShape->area() < secondShape->area();
        }
    );
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList) {
    shapeList->sort([](Shape *firstShape, Shape *secondShape) {
            return firstShape->area() > secondShape->area();
        }
    );
}

void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList) {
    shapeList->sort([](Shape *firstShape, Shape *secondShape) {
            return firstShape->area() / firstShape->perimeter() < secondShape->area() / secondShape->perimeter();
        }
    );
}
