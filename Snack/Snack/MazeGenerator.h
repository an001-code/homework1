//
// Created by 涂清锐 on 25-7-11.
//

#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H



#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

struct SnakeNode {
    int x, y;
    SnakeNode(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    bool operator<(const SnakeNode& other) const {
        return x == other.x ? y < other.y : x < other.x;
    }
};

class MazeGenerator {
public:
    MazeGenerator(int width, int height, int blockSize);
    std::vector<SnakeNode> generate();

private:
    int WIDTH;
    int HEIGHT;
    int SIZE;
    std::set<SnakeNode> mazeDots;

    bool inBound(int x, int y);
    void carveMaze(SnakeNode current);
};



#endif //MAZEGENERATOR_H
