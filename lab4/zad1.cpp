#include <thread>
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

bool *is_not_prime;
long max_number;

void mark_multiples(long number) {
    long temp = number * number;
    while (temp <= max_number) {
        is_not_prime[temp] = true;
        temp = temp + number;
    }
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Run with: <max_number:int>";
        max_number = 100;
    } else {
        max_number = strtol(argv[1], nullptr, 10);
    }

    int square_root = (int) round(sqrt(max_number));
    cout << "Marking multiples of numbers up to: " << endl << "\t" << square_root << endl;


    is_not_prime = new bool[max_number];
    vector<thread> threads(square_root - 1);

    cout << "Spawn thread multiples of: " << endl << "\t";
    for (int i = 2; i <= square_root; i++) {
        cout << i << " ";
        threads[i - 2] = thread(mark_multiples, i);
    }
    cout << endl;

    for (auto &thread: threads) {
        thread.join();
    }

    cout << "Prime numbers:" << endl << "\t";

    int count = 0;
    for (int number = 2; number <= max_number; number++) {
        if (!is_not_prime[number]) {
            cout << setw(4) << number << ",";
            count++;
            if (count % 16 == 0) cout << endl << "\t";
        }
    }
    cout << endl;
    cout << "Count of primes: " << endl << "\t" << count;

    delete[] is_not_prime;
    return 0;
}