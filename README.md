# C++ OOP - Lesson 2

## Task

Your task is to create a `ILogger` interface in `EXERCISE.h` 

You **do not** need to look at any other source code to complete the tasks. In
fact, unless you are familiar with template metaprogramming, you will find both
`main.cpp` and `private/Checker.h` to be _extremely_ confusing.

Implement the following:

## Part 1:

This covers writing a basic interface class.

### Member Functions:

All of the functions below should be `public` and _pure_ `virtual`

#### LogInfo()

This function should return a _reference_ to an `ILogger`.
It should take a `const ` _reference_ to an `std::string`

#### LogError()

This should work exactly the same as `LogInfo()`

### GetLastError()

This function should return a `const` _reference_ to an `std::string`.
It should not take any arguments. The function should be `const`-accessible.

### The Destructor
Write a `virtual` destructor for `ILogger` that is explicitly `default`ed.

## Part 2

This covers implementing your interface by editing the `StringLogger` class.

### Interface Implementation

Make `StringLogger` inherit from `ILogger` publicly.

### Data Members

The class should have three private data members:

An `std::ostream&` which we will be writing log messages into called `stream`

An `std::string` which we will store the last Error into called `lastError`

The names are suggestions, you are free to use your own.

### Constructor

The constructor should take an `std::ostream&` and use it to construct the `stream` member
mentioned above.

### LogInfo()

This function should match the specification of the one in the interface and also
be marked `override`.
It should write the passed `std::string` to the `stream` using the `<<` operator with `INFO: `
prepended (there is a space after the `:`)
It should return a reference to itself via de-referencing the `this` operator.

### LogError()

This function should again match the specification of the one in the interface and also
be marked `override`.
It should write the passed `std::string` to the `stream` using the `<<` operator with `ERROR: `
prepended (again, there should be a space after the `:`)
It should also copy the passed string into `lastError` *without* any prepending.

### GetLastError()

Again, it should match the interface specification and `override` it.
It should return `lastError`.

## Part 3

This is a stretch goal! **Compile-time checking is not implemented
for these so please share them with us for evaluation.**

### Version()

Implement a `static` function that takes no arguments and
returns an `int` - It should always return `2`

### Split the declarations from the definitions.

Create a `.cpp` file in the project and move all member function
definitions of `StringLogger` to that file.

### Static Data

Create a static int that is set to `2` and have `Version()` return 
that instead.