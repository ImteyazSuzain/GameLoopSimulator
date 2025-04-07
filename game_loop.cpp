#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mtx;
int playerX = 0, playerY = 0;
int enemyX = 10, enemyY = 10;
bool gameOver = false;

void updatePlayer() {
    for (int i = 0; i < 10 && !gameOver; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            playerX += 1;
            playerY += 2;
            cout << "Player: (" << playerX << ", " << playerY << ")\n";
        }
        this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void updateEnemy() {
    for (int i = 0; i < 10 && !gameOver; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (enemyX > playerX) enemyX -= 2;
            else if (enemyX < playerX) enemyX += 2;
            if (enemyY > playerY) enemyY -= 2;
            else if (enemyY < playerY) enemyY += 2;
            cout << "Enemy: (" << enemyX << ", " << enemyY << ")" << endl;
            cout << "Distance: " << abs(enemyX - playerX) + abs(enemyY - playerY) << endl;
            if (enemyX == playerX && enemyY == playerY) {
                gameOver = true;
                cout << "Enemy caught Player! Game Over!" << endl;
                break;
            }
        }
        this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    cout << "Starting chase game...\n";
    thread t1(updatePlayer);
    thread t2(updateEnemy);
    t1.join();
    t2.join();
    if (!gameOver) cout << "Player escaped! Game Over!\n";
    return 0;
}