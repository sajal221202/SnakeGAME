#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
#include <conio.h>  // for _kbhit() and _getch()

using namespace std;

const int BOARD_SIZE = 20;

class SnakeGame {
    list<pair<int, int>> snake;
    pair<int, int> food;
    int dx, dy;
public:
    SnakeGame() {
        snake.push_back({ BOARD_SIZE / 2, BOARD_SIZE / 2 });
        dx = 0;
        dy = 1;
        generateFood();
    }

    void generateFood() {
        while (true) {
            food = { rand() % BOARD_SIZE, rand() % BOARD_SIZE };

            bool foundInSnake = false;
            for (auto segment : snake) {
                if (segment == food) {
                    foundInSnake = true;
                    break;
                }
            }

            if (!foundInSnake) break;
        }
    }

    bool move() {
        auto head = snake.front();

        head.first += dx;
        head.second += dy;

        // Check boundary collision
        if (head.first < 0 || head.first >= BOARD_SIZE || head.second < 0 || head.second >= BOARD_SIZE)
            return false;

        // Check self collision
        for (auto segment : snake) {
            if (segment == head)
                return false;
        }

        // Check food collision
        if (head == food) {
            snake.push_front(head);
            generateFood();
        } else {
            snake.push_front(head);
            snake.pop_back();
        }

        return true;
    }

    void changeDirection(char ch) {
        switch (ch) {
            case 'w':
                dx = -1; dy = 0;
                break;
            case 's':
                dx = 1; dy = 0;
                break;
            case 'a':
                dx = 0; dy = -1;
                break;
            case 'd':
                dx = 0; dy = 1;
                break;
        }
    }

    void printBoard() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                bool isSnake = false;
                for (auto segment : snake) {
                    if (segment.first == i && segment.second == j) {
                        cout << "S";
                        isSnake = true;
                        break;
                    }
                }

                if (i == food.first && j == food.second) {
                    cout << "F";
                } else if (!isSnake) {
                    cout << ".";
                }
            }
            cout << endl;
        }
    }

   void play() {
    // Introduction and controls
    cout << "Welcome to the Snake Game!" << endl << endl;
    cout << "Controls:" << endl;
    cout << "W: Move Up" << endl;
    cout << "S: Move Down" << endl;
    cout << "A: Move Left" << endl;
    cout << "D: Move Right" << endl;
    
    cout << endl << "Press any key to start the game...";
    _getch();  // Wait for the user to press a key before starting

    system("cls");  // clear the console

    while (true) {
        system("cls");  // clear the console
        printBoard();

        if (_kbhit()) {
            char ch = _getch();
            changeDirection(ch);
        }

        if (!move()) {
            cout << "Game Over!";
            break;
        }

        _sleep(200);  // wait for 200 milliseconds
    }
}


};

int main() {
    srand(time(0));
    SnakeGame game;
    game.play();

    return 0;
}
// write list of imp concepts used above?

