[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/EMoZf6wU)
# Homework 3

## How To Run Our Code

TODO (Part 5)

(Keep reading, this will make sense later)


## Overview

In the recent past, the United States Postal Service has provided an opportunity where each US household
(identified by a street address)
can order up to $N$ free at-home COVID testing kits.
You will use a `Dictionary` in a computer program
that manages the orders and keeps track of the number of kits delivered to each address.
The orders are stored in data/orders100k.csv.

In lecture, we learned of three high-level ways to implement the `Dictionary` ADT:
1. Sequential search on an unsorted list of Records
2. Binary search on a sorted list of Records
3. Hashing

The different methods had different asymptotic complexities.
In this homework, you will compare methods (1) and (3)
to see how they affect performance as the problems scale, in practice.

There are 5 main parts to this Homework (1-3 can be done in any order):
1. Implement the Dictionaries
2. Implement the USPS simulator
3. Implement a main function to tie everything together
4. Perform timing benchmarks and summarize your results
5. Document how to run your code to reproduce your results


## Part 1: Dictionary Implementations

You need to implement two subclasses of the `Dictionary` ADT:
* The Open Hash Table data structure (Lab 15).
* An Array-Based Dictionary that uses sequential search.
    - **This is not exactly the same as Lab 13's implementation!**
      The order of elements don't matter for Sequential Search.
      When you implement `remove`, make it much more efficient
      by replacing the to-be-removed element with the last element.
      (This is a single move, instead of $\mathcal{O}(n)$ moves.)

Write code to test your implementations--convince yourself they're correct before you try to use them
in a more complicated program!

### Notes

* You may re-use code from the labs, where applicable.
* Your implementations need to `throw` exceptions when they cannot complete their tasks:
    - `find` and `remove`: if the key is not present
    - `insert`: if the key is already present 


## Part 2: USPS Simulator

The `USPS` class (USPS.hpp/.cpp) is where you will implement
the logic for processing COVID test kit orders (COVIDTestOrder.hpp/.cpp).
`USPS::run` takes two arguments:
* a `Queue` of the `COVIDTestOrder`s,
* and a (should-be-empty) `Dictionary`. By passing a pointer,
  you can provide different implementations while reusing the same function. Neat!

You should dequeue one order at a time
and process it, using the `Dictionary` to keep track of how many test kits
each address has ordered.
The logic should be as follows:
* Each street address is allowed **at most 4 test kits total**. This can be spread across multiple orders.
* When an order comes in for a street address, you should check the Dictionary to see how many they've already ordered.
    * If the new total will be <= 4, accept the order and update the Dictionary
    * Otherwise, reject the order and do not update the Dictionary

### Notes

* To accept or reject an order, simply `cout` an appropriate message (see the sample output)
    - You need to provide a way for the user to control whether or not to see these messages.
      See Parts 3 and 4.
* `find` will `throw` an exception when the key isn't found. You will need to catch this exception
      in your code as part of handling the first order for any particular street address.
* Updating a record requires `find`ing the existing value, `remove`ing that record, and then `insert`ing the new value for that key.
* You should make the maximum number of a test kits a `USPS` member variable--that way it's easy to change!

### Sample Output

When you have a main program that lets you run the simulator,
the first 10 orders should result in the following actions:

```
#1 accepted: 4 kits to 948 Cliff Ln, Union City 95533 (4 total)
#2 accepted: 1 kits to 4262 5th St, Mountain View 29818 (1 total)
#3 accepted: 4 kits to 842 60th Ave, Oakland 68088 (4 total)
#4 accepted: 1 kits to 923 7th St, Emeryville 68284 (1 total)
#5 accepted: 2 kits to 1630 4th St, Milpitas 29706 (2 total)
#6 accepted: 2 kits to 4262 5th St, Mountain View 29818 (3 total)
#7 accepted: 3 kits to 8529 Violet Rd, Fremont 90880 (3 total)
#8 REJECTED: 4 kits to 923 7th St, Emeryville 68284 (1 already)
#9 REJECTED: 5 kits to 9160 3rd St, Sunnyvale 30057 (0 already)
#10 accepted: 2 kits to 1630 4th St, Milpitas 29706 (4 total)
```

Note the same addresses occur in lines 2 and 6, in lines 4 and 8, and in lines 5 and 10.


## Part 3: The Main Program

Once you have the `USPS` simulator working, it's time to stress-test it!
You need to write a main function which does the following:
* Read data from `data/orders100k.csv` and place them into a `LinkedQueue` object
* Run the USPS simulator on the queue, reporting how long it takes to run (see `USPS::timedRun`)

Further, it should allow the user to specify the following things:
* How many orders from the file to process
* Whether or not to `cout` the action taken on each order
* Which of the two `Dictionary` implementations to use


### Notes

* Break your code into multiple functions, as makes sense.
  A good rule of thumb is that each function should be responsible for one single thing.
* If you use `getline` to get `string` lines from the file,
  you can pass such a string directly to the overloaded `COVIDTestOrder` constructor.
* You will have to add a way to hash `StreetAddress` objects.
  Try to make a good hash function!


## Part 4: Timing Benchmarks

Run your simulator on all combinations of:
* Two `Dictionary` implementations: Open Hashing versus Array-Based Sequential Search.
* The first $M$ orders in the data file, for each of $M = 10, 100, 1000, 10000, 100000$.

Include a `results.txt` file where you report the run time (in milliseconds)
for each of these combinations.
Important: don't `cout` actions for each order when doing these experiments.
(`cout` is very slow.)

Also in `results.txt`, provide the asymptotic complexity for your `USPS::run` function
under three scenarios:
* The worst-case complexity when using the Array-Based Dictionary
* The worst-case complexity when using Open Hashing
* The average-case complexity when using Open Hashing

Summarize the results of your experiments,
and explain the trends you see by referring to your asymptotic analyses.
(2-3 sentences)

### Notes

* Do not report the time spent reading the data from the file or putting things into the `Queue`
  before running the simulation. See `USPS::timedRun`.
* The 100,000 orders might take a while to complete! You may be waiting for a minute.
* Your analysis of `USPS::run` will depend on the analysis of your other data structures.
    * State the complexities for each of the methods used in your `USPS::run` implementation
      as part of your analysis
* Use an open hash table with `2 * M` slots for an experiment with $M$ orders.
* If you wish, you're welcome to put this discussion in this README,
  alongside your documentation (see Part 5), instead of in a text file.


## Part 5: Documentation

This homework is a little more open-ended:
you have to write your own `main` function.
Provide some documentation on how I (or anyone else who did not write your program)
can run your code
to reproduce the experimental results you reported in Part 4.

Write your documentation in the provided section at the top of this README file.
Use some markdown formatting! Things like headings, bulleted lists, code blocks...
[Here](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
is a guide, for your reference.

Your documentation must include:
* How to run your program
    - what options are available and how to specify them
    - how to reproduce the results you reported in Part 4
* Some sample output so the user can be confident it's running correctly

### Notes

* To edit this README.md in eclipse, change the tab beneath the editor window from "Preview" to "Markdown Source"
* Or, you can edit the README.md directly in github (make sure to `git pull` aftewards)
