# Overview

In this project, you will implement a multithreaded version of the
mergesort algorithm using the pthread library.  We have provided you
with a single-threaded version of mergesort that you will be
converting to use threads. Makefiles have been provided that you can
use directly.


## Learning Objectives

- Take a singled threaded algorithm and safely convert it to threaded
  to see a performance gain.
- To gain more experience writing concurrent code.
- Explore the pthread library


## Book references

Read these chapters carefully in order to prepare yourself for this project.

- [Intro to Threads](http://pages.cs.wisc.edu/~remzi/OSTEP/threads-intro.pdf)
- [Threads API](http://pages.cs.wisc.edu/~remzi/OSTEP/threads-api.pdf)

## Make Concurrent (ABET outcome 1)

Convert the serial mergesort code to use multiple threads using the
pthread library. Your program should limit the number of threads it
uses via a command line argument (for example, this could be the total
number of threads or number of levels before cutting off new thread
generation). You must get a speedup of at least 2 with 4 or more cores
to get full credit on this project.  Use n = 100,000,000 elements for
your testing.

NOTE: Just because you see a speedup of 2 does not guarantee full
credit. You can easily hardcode the number of threads and hardcode the
branches to get a speedup of 2. Your code MUST work with a variable
number of threads!  Simply getting a speedup of 2 does not indicate
that you did the assignment correctly.

You will need to update mytests.c to accept a number of threads a
command line argument. The updated version of mytests should include
timing results for both the serial and parallel versions of merge
sort.

## Implementation Analysis (ABET outcome 6)

Create a file named speedup.pdf (in the root directory) that analyses
the following two aspects of your mergesort solution.

**Efficiency** - Analyse the thread efficiency by examining how the
threaded implementation’s performance compares to the single threaded
implementation. Include a chart showing the speedups obtained with
varying number of threads (from 1 to 8). The speedups should relative
to the serial mergesort. Please also note the number of cores on the
system that you are testing.  All tests cases should be run with 100
million elements. Please discuss whether the speedup increases
linearly as the number of threads are increased.

**Effectiveness** - Analyse the effectiveness of your threaded
implementation by comparing sorting time of your threaded solution to
the single threaded solution. Run both the serial mergesort and
threaded mergesort with elements in the range from 1,000,000 to
100,000,000, incrementing by 1M each time.  The threaded version of
merge sort should be run with 5 threads for all test cases.  Plot the
timing results in a line chart (google sheets or excel) and compare
the results. Please discuss whether the threaded version always
performs better than the serial version.

HINT: You can make the chart using any tool want (excel, google docs,
etc.) as long as you can create a pdf as your final
deliverable. Look in the folder example for what your chart should
look like.

## Hints

- Do not modify the given serial_mergesort function. Instead create a
  new parallel_mergesort function that will call serial_mergesort as a
  base case.
- You can stop the recursion using the number of levels in the sorting
  tree or by number of threads. It is simpler to stop it by the number
  of levels.
- It may be useful to add an option to mytests.c to output timing
  results speedup calculation in a CSV format.  This will make it
  significantly easier to generate the required data for the
  implementation analysis report.


## Grading Rubric

All grading will be executed on onyx.boisestate.edu Submissions
that fail to compile will not being graded.

- [30 pts] Make concurrent (ABET outcome 1)
  - [10 pts] You got a speedup of at least 2 with 4 or more cores 
  - [10 pts] mytests.c accepts a number of threads as a command line argument
  - [10 pts] Correctly creates new threads
- [30 pts] Implementation analysis (speedup.pdf ABET outcome 6)
  - Score will reflect the quality of the analysis.
- [10 pts] Code quality for **lab.c**
  - [4 pts] Code is formatted correctly and follows a consistent style
  - [2 pts] Code is commented when necessary
  - [4 pts] There is more than just the main function in **mytests.c**
- [20 pts] Compiler warnings **ALL files**
  - Each compiler warning will result in a 3 point deduction.
  - You are not allowed to suppress warnings
  - You must build with the flags ```-Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=gnu89```
- [10 pts] Valgrind reports no memory leaks or read/write errors
  - As reported by **runval.sh**
  - This is a **PASS/FAIL** score. 1 read/write error or leaking 1
    byte will result in a zero for this section. There is no partial
    credit for this section.

