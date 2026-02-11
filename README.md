# Philosophers

*This project has been created as part of the 42 curriculum by VACUCCU.*

## Description

The **Philosophers** project is a simulation of the classic "Dining Philosophers" problem, originally formulated by Edsger Dijkstra. It is a fundamental exercise in concurrent programming, synchronization, and resource sharing.

### Goal

The primary objective of this project is to learn how to manipulate **threads** and **mutexes**. The challenge lies in managing shared resources (forks) among concurrent threads (philosophers) while avoiding common concurrency issues such as:

* **Data Races:** Concurrent access to shared memory without protection.
* **Deadlocks:** A state where threads are blocked forever, waiting for each other.
* **Starvation:** A state where a thread is perpetually denied access to resources.

### Overview

In this simulation:

* Several philosophers sit at a round table.
* There is a fork between each pair of philosophers.
* A philosopher needs **two forks** to eat.
* The simulation stops if a philosopher dies of starvation.
* Each philosopher is a thread, and each fork is protected by a mutex.

## Instructions

### Compilation

To compile the project, clone the repository and run `make` at the root of the directory:

```bash
git clone <repository_url>
cd philo
make

```

This will generate the executable file named `philo`.

### Execution

The program takes the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

```

#### Arguments Reference:

| Argument | Description |
| --- | --- |
| `number_of_philosophers` | The number of philosophers and also the number of forks. |
| `time_to_die` | (in ms) If a philosopher doesn't start eating `time_to_die` ms after the beginning of their last meal (or the start of the simulation), they die. |
| `time_to_eat` | (in ms) The time it takes for a philosopher to eat. During this time, they will hold two forks. |
| `time_to_sleep` | (in ms) The time a philosopher will spend sleeping. |
| `[number_of_times...]` | (Optional) If all philosophers have eaten at least this many times, the simulation stops. If not specified, the simulation stops only when a philosopher dies. |

### Usage Examples

**Standard simulation (infinite until death):**

```bash
./philo 5 800 200 200

```

*5 philosophers. No one should die because 200 (eat) + 200 (sleep) < 800 (die).*

**Simulation with meal limit:**

```bash
./philo 5 800 200 200 7

```

*The simulation stops when all philosophers have eaten at least 7 times.*

**Simulation where a philosopher should die:**

```bash
./philo 4 310 200 100

```

*A philosopher will likely die because the cycle (eat+sleep) is close to the death timer.*

## Resources

### References

* **The Dining Philosophers Problem:** [Wikipedia Article](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
* **POSIX Threads (pthreads):** [Official Man Pages](https://man7.org/linux/man-pages/man7/pthreads.7.html)
* **Mutexes in C:** [GeeksforGeeks Guide](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)
* **Unix Threads in C:** [Youtube Playlist by CodeVault](https://www.google.com/search?q=https://www.youtube.com/watch%3Fv%3Dd9s_d28yJq0%26list%3DPLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)

### AI Usage

AI tools (specifically ChatGPT/Gemini) were used in the development of this project for the following tasks:

1. **Log Analysis:** AI was used to parse lengthy simulation logs to verify that timestamps were accurate and to confirm that no philosopher skipped a meal or died prematurely.
2. **Debugging Concurrency:** AI helped explain edge cases regarding `usleep` precision and how small CPU delays can affect the "Time to die" condition.
3. **Concept Clarification:** AI was used to better understand the difference between race conditions and deadlocks in the context of C mutexes.

*Note: The core logic, thread management, and mutex implementation were written manually to ensure a deep understanding of the curriculum requirements.*