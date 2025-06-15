# Parallel Number Guesser

This project is a simple parallel number guessing program written in C++ using POSIX threads (`pthread`). The program divides the search range among multiple threads, and each thread tries to guess the target number. When any thread finds the number, all threads stop.

## Features

- Multi-threaded guessing using POSIX threads
- User inputs the number to be guessed
- Each thread prints its guesses and thread ID
- Measures and displays the time taken to find the number

## How to Build

1. Make sure you have `g++` and `make` installed.
2. Place `ges.cpp` and the provided `Makefile` in the same directory.
3. Build the program using:

   ```sh
   make
   ```

   Or compile manually:

   ```sh
   g++ -Wall -O2 -pthread -o ges ges.cpp
   ```

## How to Run

```sh
./ges
```

You will be prompted to enter a number between 0 and 10000 for the threads to guess.

## How It Works

- The range `[0, 10000]` is divided among 4 threads.
- Each thread checks its assigned numbers and prints each guess.
- When a thread finds the correct number, it prints the result and stops all threads.
- The program prints the time taken for the search.

## Customization

- Change `NUM_THREADS`, `HIGH`, or `LOW` in `ges.cpp` to adjust the behavior.
