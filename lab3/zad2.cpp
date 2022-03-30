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


using namespace std;

bool DEBUG = false;

vector<mutex> bears_mutex;

std::atomic<int> tableCount;
mutex tableLock;
condition_variable cv;


chrono::steady_clock::time_point start_time = chrono::steady_clock::now();

static long elapsed_from_start() {
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    return chrono::duration_cast<std::chrono::milliseconds>(end - start_time).count();
}

static long elapsed_from_start_hours() {
    return elapsed_from_start() / 1000;
}

int max_drinking_time = 0;

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

bool isBarOpen() { return elapsed_from_start_hours() < 22 && elapsed_from_start_hours() >= 6; }

bool chairAvailable() { return tableCount > 0 && isBarOpen(); }

mutex printLock;

class Client {
private:
    int id;
    string name;
    int bear_id;

    mutex &getBear() {
        while (true) {
            int index = 0;
            for (auto &bear: bears_mutex) {
                if (bear.try_lock()) {
                    this->bear_id = index;
                    return bear;
                }
                index++;
            }
        }
    }

public:

    Client();

    Client(int id) : id(id) { this->name = names[randomInt(0, names->size())]; }

    Client(int id, string name) : id(id), name(std::move(name)) {}

    static int randomSleep() {
        auto time = rand() % 1000 + 500;
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        return time;
    }

    void operator()() {

        {
            const lock_guard<mutex> lock(printLock);
            cout << setw(20) << name << " id: " << id << ", enter bar." << endl;
        }

        {
            unique_lock<mutex> tempLock(tableLock);
            if (!cv.wait_for(tempLock, chrono::seconds(1), chairAvailable)) {
                {
                    const lock_guard<mutex> lock(printLock);

                    if (isBarOpen())
                        cout << setw(20) << name << " id: " << id << ", i wait one hour, bye! (no seat)" << endl;
                    else
                        cout << setw(20) << name << " id: " << id << ", i wait one hour, bye! (bar closed)" << endl;
                }
                return;
            }

            {
                const lock_guard<mutex> lock(printLock);
                cout << setw(20) << name << " id: " << id << ", has a seat." << endl;
            }

            tableCount--;
        }

        randomSleep();

        for (int j = 0; j < 2; j++) {
            auto &bear = getBear();

            {
                const lock_guard<mutex> lock(printLock);
                cout << setw(20) << name << " id: " << id << ", is drinking " << j + 1 << " 🍺:" << this->bear_id
                     << "  now" << endl;
            }

            auto drinking_time = randomSleep();

            bear.unlock();

            {
                const lock_guard<mutex> lock(printLock);
                cout << setw(20) << name << " id: " << id << ", released " << j + 1 << " 🍺:" << this->bear_id
                     << " after " << drinking_time << "ms." << endl;
            }
        }


        {
            const lock_guard<mutex> lock(printLock);
            cout << setw(20) << name << " id: " << id << ", is full 🤮" << endl;

            {
                lock_guard<mutex> tempLock(tableLock);
                tableCount++;
            }

            cout << setw(20) << name << " id: " << id << ", left bar" << endl;
        }
    }
};

int main(int argc, char *argv[]) {

    if (argc != 4) {
        cout << "Run with: <client_count|int> <bear_count|int> <max_drinking_time(ms)|int>";
        return 0;
    }

    int total_client_count = atoi(argv[1]);
    int bear_count = atoi(argv[2]);
    max_drinking_time = atoi(argv[3]);

    int delay_between_clients = 26000 / total_client_count;

    cout << "Arguments:" << endl
         << "Clients: " << total_client_count << " time between clients: " << delay_between_clients << "ms" << endl
         << "Bears: " << bear_count << endl
         << "Max drinking time: " << max_drinking_time << endl << endl;


    std::vector<std::mutex> new_mutexes(bear_count);
    bears_mutex.swap(new_mutexes);

    cout << "Bar simulator, waiter, limited glass count" << endl;

    tableCount = bear_count + 5;

    cout << "Create threads... " << endl;

    vector<thread> threads;
    int client_count = 0;


    cout << "Bar is open between 6 and 22!" << endl;
    start_time = chrono::steady_clock::now();



    while (elapsed_from_start_hours() < 26) {
        if (elapsed_from_start() % 1000 < 250) {
            const lock_guard<mutex> lock(printLock);
            cout << " Time: " << elapsed_from_start_hours() << ":00\n";
        }

        threads.emplace_back(Client(client_count));
        client_count++;
        this_thread::sleep_for(chrono::milliseconds(delay_between_clients));
    }

    for (auto &thread: threads) {
        thread.join();
    }

    printf("Thank you for attention.\n");
    return 0;
}
