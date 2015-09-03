Genetic Algorithm
=========

A genetic algorithm implementation for evolving the [FSMDriver](https://github.com/bruno147/fsmdriver) driving parameters. Although it was developed for this specific application the code can be used in any application.

Usage
---------------------
There is a set of parameters arleady defined in Genetic_Algorithm/Chromosome.h those were used in the FSMDriver evolution. Feel free to try new combinations. The default fitness function is the distance covered (defined in FSMDriver/GADriver.cpp) you can also change that function to whatever fitness you want.

If you want to use the GA in a different application simply change the methods in GaAdapter class based on what you want to use.

Compiling & Executing
---------------------

Binary files will be created in the _bin_ directory. To compile:

    cd build
    cmake ..
    make

To execute:

    cd bin
    ./DriverGeneticAlgorithm

