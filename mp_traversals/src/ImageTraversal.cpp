#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_front(point);
  }

  /**
  * Removes the current Point in the bfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_front();

  }

  /**
  * Removes the current Point in the dfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_front();
  }

  /**
   * Returns the current Point in the bfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point bfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    Point p = work_list.front();
    return p;
  }

  /**
   * Returns the current Point in the dfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point dfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    Point p = work_list.front();
    return p;
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param fns the set of functions describing a traversal's operation
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) {  
    /** @todo [Part 1] */
    png_ = png;
    start_ = start;
    tolerance_ = tolerance;
    fns_ = fns;
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
  
    return Iterator(png_, start_, tolerance_, fns_);;
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    Iterator it(png_, start_, tolerance_, fns_);
    it.curr_ = Point(-1,-1);
    return it;
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
    visited_.resize(png_.width(), std::vector<bool>(png_.height(), false));
  }


  /**
  * Iterator increment operator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    unsigned x = curr_.x;
    unsigned y = curr_.y;
    visited_[x][y] = true;
    // std::cout << "current (x, y): " << "(" << x << "," << y<< ")"<< std::endl;
    if (x + 1 < png_.width()) {
      if (calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(x + 1, y)) < tolerance_) {
        if (visited_[x + 1][y] == false) {
          fns_.add(work_list_, Point(x + 1, y));
          // std::cout << "1add (" << x+1 << "x" << y << ")"<< std::endl;
        }
      }
    }
    if (y + 1 < png_.height()) {
      if (calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(x, y + 1)) < tolerance_) {
        if (visited_[x][y + 1] == false) {
          fns_.add(work_list_, Point(x, y + 1));
          // std::cout << "2add (" << x << "x" << y+1 << ")"<< std::endl;
        }
      }
    }
    if (x>= 1) {
      if (calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(x - 1, y)) < tolerance_) {
        if (visited_[x - 1][y] == false) {
          fns_.add(work_list_, Point(x - 1, y));
          // std::cout << "3add (" << x-1 << "x" << y << ")"<< std::endl;
        }
      }
    }
    if (y >= 1) {
      if (calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(x, y - 1)) < tolerance_) {
        if (visited_[x][y - 1] == false) {
          fns_.add(work_list_, Point(x, y - 1));
          // std::cout << "4add (" << x << "x" << y-1 << ")"<< std::endl;
        }
      }
    }
    
    if (!work_list_.empty()) { // if list is not empty
      curr_ = fns_.peek(work_list_); //get next
      while (visited_[curr_.x][curr_.y] && !work_list_.empty()) { //while visited and hasNext
        fns_.pop(work_list_); //delete it
        if (work_list_.empty()) { //if list is empty, done
          break;
        }
        curr_ = fns_.peek(work_list_); //get next
      }
    }
    if (work_list_.empty()) {
      curr_ = Point(-1, -1);
    }

    return *this;
    
  }

  /**
  * Iterator accessor operator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return curr_;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    return !(curr_ == other.curr_);
  }

  /**
   * Iterator size function.
   *
   * @return size_t the size of the iterator work queue.
   */
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  /**
   * Iterator empty function.
   *
   * @return bool whether the iterator work queue is empty.
   */
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }

  ImageTraversal::Iterator::Iterator(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) {
    png_ = png;
    start_ = start;
    fns_ = fns;
    fns_.add(work_list_, start);
    tolerance_ = tolerance;
    curr_ = start;
    visited_.resize(png_.width(), std::vector<bool>(png_.height(), false));

  }
}