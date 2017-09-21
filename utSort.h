#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

using namespace std;

void initial(list<Shape *> &shapeList){
    shapeList.push_back(new Rectangle(0, 0, 2, 2, "rectangle_1"));
    shapeList.push_back(new Triangle({0, 0}, {0, 1}, {1, 0}, "triangle_1"));
    shapeList.push_back(new Circle(0, 0, 6, "circle_1"));
}

void clear(list<Shape *> &shapeList) {
    while (shapeList.size() > 0) {
        delete shapeList.back();
        shapeList.pop_back();
    }
}

TEST (Sort, sortByIncreasingPerimeter) {
    list<Shape *> shapeList;
    initial(shapeList);

    Sort::sortByIncreasingPerimeter(&shapeList);

    list<Shape *>::iterator i = shapeList.begin();

    ASSERT_EQ("triangle_1", (*i)->name); i++;
    ASSERT_EQ("rectangle_1", (*i)->name); i++;
    ASSERT_EQ("circle_1", (*i)->name);

    clear(shapeList);
}

TEST (Sort, sortByDecreasingPerimeter) {
    list<Shape *> shapeList;
    initial(shapeList);

    Sort::sortByDecreasingPerimeter(&shapeList);

    list<Shape *>::iterator i = shapeList.begin();

    ASSERT_EQ("circle_1", (*i)->name); i++;
    ASSERT_EQ("rectangle_1", (*i)->name); i++;
    ASSERT_EQ("triangle_1", (*i)->name);

    clear(shapeList);
}

TEST (Sort, sortByIncreasingArea) {
    list<Shape *> shapeList;
    initial(shapeList);

    Sort::sortByIncreasingArea(&shapeList);

    list<Shape *>::iterator i = shapeList.begin();

    ASSERT_EQ("triangle_1", (*i)->name); i++;
    ASSERT_EQ("rectangle_1", (*i)->name); i++;
    ASSERT_EQ("circle_1", (*i)->name);

    clear(shapeList);
}

TEST (Sort, sortByDecreasingArea) {
    list<Shape *> shapeList;
    initial(shapeList);

    Sort::sortByDecreasingArea(&shapeList);

    list<Shape *>::iterator i = shapeList.begin();

    ASSERT_EQ("circle_1", (*i)->name); i++;
    ASSERT_EQ("rectangle_1", (*i)->name); i++;
    ASSERT_EQ("triangle_1", (*i)->name);

    clear(shapeList);
}

TEST (Sort, sortByIncreasingCompactness) {
    list<Shape *> shapeList;
    initial(shapeList);

    Sort::sortByIncreasingCompactness(&shapeList);

    list<Shape *>::iterator i = shapeList.begin();

    ASSERT_EQ("triangle_1", (*i)->name); i++;
    ASSERT_EQ("rectangle_1", (*i)->name); i++;
    ASSERT_EQ("circle_1", (*i)->name);

    clear(shapeList);
}

#endif
