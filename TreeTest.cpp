#include <iostream>
using std::cout, std::endl;
#include "badkan.hpp"
#include "Tree.hpp"

int main() {
    // Testing objects
    ariel::Tree fbtree1; ariel::Tree fbtree2;
    ariel::Tree emptytree;
    ariel::Tree threetree;
    threetree.insert(5);
    threetree.insert(7);
    threetree.insert(3);
    ariel::Tree mytree;
    badkan::TestCase tc("Binary tree");
    tc
    .CHECK_EQUAL(emptytree.size(), 0)
    .CHECK_OK(emptytree.insert(5))
    .CHECK_EQUAL(emptytree.size(), 1)
    .CHECK_EQUAL(emptytree.contains(5), true)
    .CHECK_OK(emptytree.remove(5))
    .CHECK_EQUAL(emptytree.contains(5), false)
    .CHECK_THROWS(emptytree.remove(5))
    .CHECK_EQUAL(emptytree.size(), 0)
    .CHECK_EQUAL(threetree.size(), 3)
    .CHECK_EQUAL(threetree.root(), 5)
    .CHECK_EQUAL(threetree.parent(3), 5)
    .CHECK_EQUAL(threetree.parent(7), 5)
    .CHECK_EQUAL(threetree.left(5), 3)
    .CHECK_EQUAL(threetree.right(5), 7)
    .CHECK_THROWS(threetree.insert(3))
    .CHECK_THROWS(threetree.left(6))
    .CHECK_OK(threetree.print())
    .CHECK_THROWS(fbtree1.remove(5))
    .CHECK_THROWS(fbtree1.left(5))
    .CHECK_THROWS(fbtree1.right(5))
    .CHECK_THROWS(fbtree1.parent(5))//
    .CHECK_EQUAL(fbtree1.size(), 0)
    .CHECK_OK(fbtree1.insert(666))
    .CHECK_OK(fbtree1.insert(555))
    .CHECK_OK(fbtree1.insert(444))
    .CHECK_OK(fbtree1.insert(110))
    .CHECK_EQUAL(fbtree1.size(), 4)
    .CHECK_THROWS(fbtree1.insert(666))
    .CHECK_EQUAL(fbtree1.parent(555), 666)
    .CHECK_EQUAL(fbtree1.parent(444), 555)
    .CHECK_EQUAL(fbtree1.parent(110), 444)
    .CHECK_THROWS(fbtree1.right(666))
    .CHECK_THROWS(fbtree1.right(444))
    .CHECK_EQUAL(fbtree1.left(444), 110)
    .CHECK_OK(fbtree1.print())
    .CHECK_EQUAL(fbtree1.contains(5), false)
    .CHECK_EQUAL(fbtree1.contains(666), true)
    .CHECK_EQUAL(fbtree1.contains(444), true)
    .CHECK_EQUAL(fbtree1.contains(110), true)
    .CHECK_EQUAL(fbtree1.contains(555), true)
    .CHECK_OK(fbtree1.remove(666))
    .CHECK_OK(fbtree1.print())
    .CHECK_OK(fbtree1.insert(666))
    .CHECK_OK(fbtree1.print())
    .CHECK_OK(fbtree1.remove(444))
    .CHECK_OK(fbtree1.print())
    .CHECK_OK(fbtree1.remove(110))
    .CHECK_OK(fbtree1.print())
    .CHECK_THROWS(fbtree2.root())
    .CHECK_OK(fbtree2.insert(777))
    .CHECK_EQUAL(fbtree2.root(), 777)
    .CHECK_OK(fbtree2.print())
    .CHECK_OK(fbtree2.remove(777))
    .CHECK_THROWS(fbtree2.root())
    .CHECK_OK(fbtree2.print())
    .CHECK_OK(fbtree2.insert(500))
    .CHECK_EQUAL(fbtree2.root(), 500)
    .CHECK_OK(fbtree2.insert(600))
    .CHECK_EQUAL(fbtree2.root(), 500)
    .CHECK_OK(fbtree2.insert(400))
    .CHECK_EQUAL(fbtree2.root(), 500)
    .CHECK_EQUAL(fbtree2.parent(400), 500)
    .CHECK_EQUAL(fbtree2.parent(600), 500)
    .CHECK_EQUAL(fbtree2.right(500), 600)
    .CHECK_EQUAL(fbtree2.left(500), 400)
    .CHECK_OK(fbtree2.print())
    .CHECK_OK(fbtree2.remove(500))
    .CHECK_EQUAL(fbtree2.root(), 600)
    .CHECK_OK(fbtree2.print())
    .CHECK_THROWS(fbtree2.right(600))
    .CHECK_EQUAL(fbtree2.parent(400), 600)
    .CHECK_OK(fbtree2.insert(700))
    .CHECK_OK(fbtree2.insert(650))
    .CHECK_OK(fbtree2.insert(800))
    .CHECK_OK(fbtree2.print())
    .CHECK_EQUAL(fbtree2.root(), 600)
    .CHECK_OK(fbtree2.remove(600))
    .CHECK_OK(fbtree2.print())
    .CHECK_THROWS(fbtree2.parent(650))
    .CHECK_EQUAL(fbtree2.parent(700), 650)
    .CHECK_EQUAL(fbtree2.root(), 650);
    cout << "You have " << tc.right() << " right answers and " << tc.wrong() << " wrong answers so your grade is " << tc.grade() << ". Great!" << endl;
}

