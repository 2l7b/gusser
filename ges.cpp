#include <iostream>
#include <pthread.h>
#include <chrono>

const int NUM_THREADS = 4;
const int HIGH = 10000;
const int LOW = 0;

struct ThreadData {
    int start;
    int end;
    int guess;
    int* found;
    pthread_mutex_t* found_mutex;
};

void* thread_guess(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->start; i <= data->end; ++i) {
        pthread_mutex_lock(data->found_mutex);
        if (*(data->found)) {
            pthread_mutex_unlock(data->found_mutex);
            break;
        }
        // Print thread ID and guess
        std::cout << "Thread " << pthread_self() << " guesses " << i << std::endl;
        if (i == data->guess) {
            std::cout << "Found it! The number is " << i << std::endl;
            *(data->found) = 1;
            pthread_mutex_unlock(data->found_mutex);
            break;
        }
        pthread_mutex_unlock(data->found_mutex);
    }
    return nullptr;
}

int main() {
    int found = 0;
    pthread_mutex_t found_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    int guess;
    std::cout << "Enter the number to guess (between " << LOW << " and " << HIGH << "): ";
    std::cin >> guess;
    if (guess < LOW || guess > HIGH) {
        std::cerr << "Invalid guess. Exiting." << std::endl;
        return 1;
    }

    int range = (HIGH - LOW + 1) / NUM_THREADS;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].start = LOW + i * range;
        thread_data[i].end = (i == NUM_THREADS - 1) ? HIGH : (LOW + (i + 1) * range - 1);
        thread_data[i].guess = guess;
        thread_data[i].found = &found;
        thread_data[i].found_mutex = &found_mutex;
        pthread_create(&threads[i], nullptr, thread_guess, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], nullptr);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}