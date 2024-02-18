/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    if (first[curDim] < second[curDim]) {
      return true;
    } else if (first[curDim] > second[curDim]) {
      return false;
    }
    return first < second;
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    double potDis = 0;
    double curDis = 0;
    for (int i = 0; i < Dim; i++) {
      potDis = potDis += ((potential[i]-target[i])*(potential[i]-target[i]));
      curDis = curDis += ((currentBest[i]-target[i])*(currentBest[i]-target[i]));
    }
    if (potDis < curDis) {
      return true;
    } else if (potDis > curDis) {
      return false;
    }
    return potential < currentBest;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.size() == 0){
      return;
    }

    vector<Point<Dim>> arr = newPoints;
    construct(arr, 0, arr.size()-1, 0, root);
}

template <int Dim>
void KDTree<Dim>::construct(vector<Point<Dim>>& arr, int start, int end, int dms, KDTreeNode *& root) {  
  if (start <= end) {
    int middle = (start + end) / 2;
    auto start1 = arr.begin() + start;
    auto end1 = arr.begin() + end + 1;
    auto middle1 = arr.begin() + middle;
    
    
    auto cmp = [dms](const Point<Dim>& a, const Point<Dim>& b) {
      return smallerDimVal(a, b, dms);
    };
    select(start1, end1, middle1, cmp);

    root = new KDTreeNode(arr[middle]);
    construct(arr, start, middle - 1, (dms + 1) % Dim, root->left); // middle-- -> middle - 1 
    construct(arr, middle + 1, end, (dms + 1) % Dim, root->right); // middle++ -> middle + 1 
  }
}



template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  if (other == NULL) {
    return;
  }
  destroy(root);
  root = copy(other.root);
  size = other.size;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* otherNode) {
    if (otherNode == NULL) {
        return NULL;
    }
    KDTreeNode * newNode = new KDTreeNode(otherNode->point);

    newNode->left = copy(otherNode->left);
    newNode->right = copy(otherNode->right);

    return newNode;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs){
    destroy(root);
    copy(rhs.root);
  }
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   destroy(root);
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode* node) {
    if (node == NULL) {
        return;
    }

    destroy(node->left);
    destroy(node->right);

    delete node;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    if (root == NULL) {
      return Point<Dim>();
    }
    return find(root, query, 0);
    
}

template <int Dim>
Point<Dim> KDTree<Dim>::find(KDTreeNode *subroot, const Point<Dim>& query, int dms) const {
    bool left = false;
    if (subroot -> left == NULL && subroot -> right == NULL) {
      return subroot->point;
    }
    Point<Dim> best = subroot -> point;
    Point<Dim> other = subroot -> point;
    if (smallerDimVal(query, subroot->point, dms)) {
      
      if (subroot->left != NULL) {
        left = true;
        best = find(subroot->left, query, (dms + 1) % Dim);
      } else {
        return subroot->point;
      }
    } else {
      if (subroot->right != NULL) {
        best = find(subroot->right, query, (dms + 1) % Dim);
      } else {
        return subroot->point;
      }
    }
    if (shouldReplace(query, best, subroot->point)) {
      best = subroot->point;
    }
    double rSquare = 0.0;
    for (int i = 0; i < Dim; ++i) {
      rSquare += ((best[i] - query[i]) * (best[i] - query[i]));
    }
    double dSquare = (subroot->point[dms] - query[dms]) * (subroot->point[dms] - query[dms]);

    if (dSquare <= rSquare) {
      if(!left && subroot->left != NULL) { 
        other = find(subroot->left, query, (dms + 1) % Dim);
      } else if (left && subroot->right != NULL) {
        other = find(subroot->right, query, (dms + 1) % Dim);
      }
    }
    if (shouldReplace(query, best, other)) {
      best = other;
    }
    return best;
    
}

template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{   
     /**
     * @todo Implement this function!
     */
    bool found = false;  
    while (!found) {
      RandIter pivot = std::prev(end);
      RandIter partition = start;
      for (RandIter it = start; it != pivot; ++it) {
        if (cmp(*it, *pivot)) {
          std::iter_swap(it, partition);
          ++partition;
        }
      }
      std::iter_swap(partition, pivot);
      if (partition == k) {
        found = true;
        break;
      } else if (k < partition) {
        end = partition;
      } else {
        start = partition + 1;
      }
    }
}

