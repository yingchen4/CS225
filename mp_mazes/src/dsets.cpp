/* Your code here! */
#include "dsets.h"

using namespace std;

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; ++i) {
        v_.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (v_[elem]<0) {
        return elem;
    } else {
        v_[elem] = find(v_[elem]);
        return find(v_[elem]);
    }
}

void DisjointSets::setunion(int a, int b) {
    int root1 = find(a);
    int root2 = find(b);
    int newSize = v_[root1] + v_[root2];

    if (v_[root1] < v_[root2] ) {
        v_[root2] = root1;
        v_[root1] = newSize;
    } else {
        v_[root1] = root2;
        v_[root2] = newSize;
    }
}

int DisjointSets::size(int elem) {
    int root = find(elem);
    return 0-v_[root];
}