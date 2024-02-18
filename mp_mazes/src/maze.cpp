/* Your code here! */
#include "maze.h"
#include <random>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

SquareMaze::SquareMaze() {

}

void SquareMaze::makeMaze(int width, int height) {
    maze_.clear();
    width_ = width;
    height_ = height;
    int size = width_ * height_;
    maze_.resize(size);
    dset_.addelements(size);

    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> width_dist(0, width_ - 1);
    std::uniform_int_distribution<int> height_dist(0, height_ - 1);
    std::uniform_int_distribution<int> dir_dist(0, 1); // interval [0, 1]

    int x, y;
    while (dset_.size(0) != size) {
        x = width_dist(gen);
        y = height_dist(gen);
        int dir = dir_dist(gen); //0 = right; 1 = down
        if (dir == 0 && x>= 0 && x < width_ - 1 && maze_[x + y * height_].right) {
            if (dset_.find(x+y*width_) != dset_.find(x+y*width_+1)) {
                maze_[x + y * height_].right = false;
                dset_.setunion(x+y*width_, x+y*width_+1);
            }
        }
        if (dir == 1 && y >= 0 && y < height_ - 1 && maze_[x + y * height_].down) {
            if (dset_.find(x+y*width_) != dset_.find(x+((y+1)*width_))) {
                maze_[x + y * height_].down = false;
                dset_.setunion(x+y*width_, x+((y+1)*width_));  
            }
        }
    }
}
int SquareMaze::randomNumber(int max) {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> dist(0, max);
    return dist(gen) % max;
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if(x < 0 || y < 0 || x > width_ - 1 || y > height_ - 1) {
        return false;
    }
    //right
    if (dir == 0) {
        if (x < width_ - 1 && !maze_[x+y*width_].right) {
            return true;
        }
    }
    //down
    else if (dir == 1) {
        if(y < height_ - 1 && !maze_[x+y*width_].down) {
            return true;
        }
    }
    //left
    else if (dir == 2) {
        if (x > 0 && !maze_[x-1+y*width_].right) {
            return true;
        }
    }
    //up
    else if (dir == 3) {
        if (y > 0 && !maze_[x+(y-1)*width_].down) {
            return true;
        }
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    int pos = x+y*width_;
    if (dir == 0) { //right
        maze_[pos].right = exists;
    } else if (dir == 1) { //down
        maze_[pos].down = exists;
    }
}


std::vector<int> SquareMaze::solveMaze() {
    int curr;
    vector<bool> visited; //store if visited
    vector<int> path; //store the path
    vector<int> length; //store the length when reached
    queue<int> q;
    length.push_back(0);
    visited.push_back(true);
    path.push_back(0);
    for (int i = 0; i < width_ * height_ - 1; i++){
        length.push_back(0);
        visited.push_back(false);
        path.push_back(-1);
    }
    q.push(0);
    while (!q.empty()){
        curr = q.front();
        q.pop();
        
        if (canTravel(curr % width_, curr / width_, 0)){
            if (!visited[curr+1]){
                path[curr+1] = curr;
                q.push(curr+1);
                visited[curr+1] = true;
                length[curr+1] = length[curr] + 1;
            }
        }
        if (canTravel(curr % width_,curr / width_,1)){
            if (!visited[curr+width_]){
                path[curr+width_] = curr;
                q.push(curr+width_);
                visited[curr+width_] = true;
                length[curr+width_] = length[curr] + 1;
            }            
        }
        if (canTravel(curr % width_,curr / width_,2)){
            if (!visited[curr-1]){
                path[curr-1] = curr;
                q.push(curr-1);
                visited[curr-1] = true;
                length[curr-1] = length[curr] + 1;
            }
        }
        if (canTravel(curr % width_,curr / width_,3)){
            if (!visited[curr-width_]){
                path[curr-width_] = curr;
                q.push(curr-width_);
                visited[curr-width_] = true;
                length[curr-width_] = length[curr] + 1;
            }
        }
    }
    int maxDistance = 0;
    int maxPos = 0;
    for (int i = 0; i < width_; i++) {
        if (length[(height_-1)*width_ + i] > maxDistance) {
            maxDistance = length[(height_-1)*width_ + i];
            maxPos = (height_-1)*width_ + i;
        }
    }
    curr = maxPos;
    vector<int> result;
    result.resize(maxDistance);
    while (maxDistance != 0) {
        if (path[curr] + 1 == curr){
            result[maxDistance - 1] = 0;
        }
        if (path[curr] + width_ == curr){
            result[maxDistance - 1] = 1;
        }
        if (path[curr] - 1 == curr){
            result[maxDistance - 1] = 2;
        }
        if (path[curr] - width_ == curr){
            result[maxDistance - 1] = 3;
        }
        curr = path[curr];
        maxDistance--;
    }
    return result;
}

cs225::PNG* SquareMaze::drawMaze() const {
    cs225::PNG* p = new cs225::PNG(width_ * 10 + 1, height_ * 10 + 1);
    cs225::HSLAPixel black(0,0,0);
    for (unsigned x = 0; x < p->width(); x++) {
        if (x < 1 || x > 9) {
            p->getPixel(x,0) = black;
        }
    }
    for (unsigned y = 0; y < p->height(); y++) {
        p->getPixel(0,y) = black;
    }
    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            if (maze_[x+ width_*y].right) {
                for (int k = 0; k <= 10; k++) {
                    p->getPixel((x+1)*10,y*10+k) = black;
                }
            }
            if (maze_[x+ width_*y].down) {
                for (int k = 0; k <= 10; k++) {
                    p->getPixel(x*10+k, (y+1)*10) = black;
                }
            }
        }
    }
    return p;
}

cs225::PNG* SquareMaze::drawMazeWithSolution() {
    cs225::PNG* p = drawMaze();
    vector<int> sol = solveMaze();
    cs225::HSLAPixel red(0,1,0.5,1);
    cs225::HSLAPixel white(0,0,1);
    unsigned index = 0;
    int x = 5;
    int y = 5;
    int endx = 0;
    int endy = 0;
    while (index < sol.size()) {
        if (sol[index] == 0) {
            p->getPixel(x, y) = red;
            for (int k = 0; k < 10; k++) {
                x = x + 1;
                p->getPixel(x, y) = red;
            }
            endx++;
        } else if (sol[index] == 1) {
            p->getPixel(x, y) = red;
            for (int k = 0; k < 10; k++) {
                y = y + 1;
                p->getPixel(x, y) = red;
            }
            endy++;
        } else if (sol[index] == 2) {
            p->getPixel(x, y) = red;
            for (int k = 0; k < 10; k++) {
                x = x - 1;
                p->getPixel(x, y) = red;
            }
            endx--;
        } else if (sol[index] == 3) {
            p->getPixel(x, y) = red;
            for (int k = 0; k < 10; k++) {
                y = y - 1;
                p->getPixel(x, y) = red;
            }
            endy--;
        }
        index ++;
    }
    for (int k = 1; k < 10; k++){
        p->getPixel(endx * 10 + k, (endy + 1) * 10) = white;
    }

    return p;

}
