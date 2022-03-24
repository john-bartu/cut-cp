//
// Created by jamabaiz on 3/17/2022.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <mutex>
#include <map>
#include <atomic>
#include <iostream>
#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <utility>
#include <vector>

#define NO_BEARS 5

using namespace std;

bool DEBUG = false;

mutex forks[NO_BEARS];

std::atomic<int> tableCount;
mutex tableLock;
condition_variable cv;

int clock_time = 0;

int randomInt(int min = 0, int max = 10) {
    return min + (rand() % (max - min));
}

string names[] = {"Tales 👩",
                  "Pitagoras 🧓",
                  "Herakles 🤶",
                  "Platon 👳",
                  "Filip 👨",
                  "Artur 🤶",
                  "Oskar 👶",
                  "Jakub 👲",
                  "Dawid 👴",
                  "Patryk 🙍"};

bool chairAvailable() { return tableCount > 0 && clock_time < 22 && clock_time > 6; }

mutex printLock;


class Client {
private:
    int id;
    string name;

    mutex &getBear() {
        while (true) {
            for (auto &fork: forks) {
                if (fork.try_lock()) {
                    return fork;
                }
            }
        }
    }

public:

    Client();

    Client(int id) : id(id) { this->name = names[randomInt(0, names->size())]; }

    Client(int id, string name) : id(id), name(std::move(name)) {}

    static void randomSleep() {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 500));
    }

    void operator()() {

        {
            const lock_guard<mutex> lock(printLock);
            cout << setw(20) << name << " id: " << id << ", want's enter bar, wait's for seat" << endl;
        }

        {
            unique_lock<mutex> tempLock(tableLock);

            if (!cv.wait_for(tempLock, chrono::seconds(1), chairAvailable)) {
                {
                    const lock_guard<mutex> lock(printLock);
                    cout << setw(20) << name << " id: " << id << ", i wait longer than hour, bye!" << endl;
                }
                return;
            }

            {
                const lock_guard<mutex> lock(printLock);
                cout << setw(20) << name << " id: " << id << ", has a seat." << endl;
                cout << setw(20) << "There left " << tableCount << " seats." << endl;
            }

            tableCount--;
        }

        if (DEBUG) printf("Client id: %i, joined the table\n", id);

        randomSleep();

        for (int j = 0; j < 2; j++) {
            if (DEBUG) printf("Client id: %i, acquiring %i 🍺\n", id, j);
            auto &bear = getBear();

            if (DEBUG) printf("Client id: %i, acquired %i 🍺\n", id, j);


            {
                const lock_guard<mutex> lock(printLock);
                cout << setw(20) << name << ", is drinking " << j + 1 << " 🍺 now" << endl;
            }

            randomSleep();

            bear.unlock();
            if (DEBUG) printf("Client id: %i, released 🍺\n", id);
        }


        {
            const lock_guard<mutex> lock(printLock);
            cout << setw(20) << name << " id: " << id << ", is full 🤮" << endl;

            {
                lock_guard<mutex> tempLock(tableLock);
                tableCount++;
            }

            if (DEBUG) printf("Client id: %i, left the table\n", id);
        }
    }
};

int main(int argc, char *argv[]) {

    DEBUG = (argc == 2 && strcmp(argv[1], "-d") == 0);

    cout << "Bar simulator, waiter, limited glass count" << endl;

    if (DEBUG) printf("In debugging mode...\n");

    tableLock.lock();
    tableCount = NO_BEARS + 2;
    tableLock.unlock();


    cout << "Create threads... " << endl;


    vector<thread> threads;
    int client_count = 0;


    cout << "Bar is open between 6 and 22!" << endl;
    while (clock_time < 24) {

        {
            const lock_guard<mutex> lock(printLock);
            cout << " Time: " << clock_time << ":00\n";
        }


        threads.emplace_back(Client(client_count));
        client_count++;
        this_thread::sleep_for(chrono::seconds(1));
        clock_time++;
    }

    for (auto &thread: threads) {
        thread.join();
    }

    cout << "Seats count: " << tableCount << endl;
    printf("Thank you for attention.\n");
    return 0;
}
