//
// Created by 涂清锐 on 25-7-11.
//

#include "MazeGenerator.h"

#include <algorithm>
#include <stack>

MazeGenerator::MazeGenerator(int width, int height, int blockSize)
    : WIDTH(width / blockSize), HEIGHT(height / blockSize), SIZE(blockSize) {
    srand((unsigned int)time(NULL));
}

bool MazeGenerator::inBound(int x, int y) {
    return x > 0 && x < WIDTH && y > 0 && y < HEIGHT;
}

void MazeGenerator::carveMaze(SnakeNode current) {
    std::stack<SnakeNode> stack;
    stack.push(current);
    mazeDots.insert(current);

    const int dx[] = { 2, -2, 0, 0 };
    const int dy[] = { 0, 0, 2, -2 };

    while (!stack.empty()) {
        SnakeNode cur = stack.top();
        std::vector<int> dirs = { 0, 1, 2, 3 };
        std::random_shuffle(dirs.begin(), dirs.end());
        bool carved = false;

        for (int i : dirs) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (inBound(nx, ny) && mazeDots.count(SnakeNode(nx, ny)) == 0) {
                SnakeNode wall(cur.x + dx[i] / 2, cur.y + dy[i] / 2);
                mazeDots.insert(wall);
                mazeDots.insert(SnakeNode(nx, ny));
                stack.push(SnakeNode(nx, ny));
                carved = true;
                break;
            }
        }

        if (!carved) {
            stack.pop();
        }
    }
}

std::vector<SnakeNode> MazeGenerator::generate() {
    int startX = 1 + 2 * (rand() % ((WIDTH - 1) / 2));
    int startY = 1 + 2 * (rand() % ((HEIGHT - 1) / 2));
    carveMaze(SnakeNode(startX, startY));

    std::vector<SnakeNode> result;
    for (auto& node : mazeDots) {
        result.push_back(SnakeNode(node.x * SIZE, node.y * SIZE));
    }
    return result;
}
