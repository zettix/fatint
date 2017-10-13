# Fatint
## A C++ library for arbitrary precision integers.

## Sean Brennan, 2017

This was inspired by Java's BigInteger library but there are notable differnces.
The underlying datastructure is vector<unit32_t> with a boolean sign, while
BigInteger uses 2's complement.

The following operators and utilities are available:  
* +, -, *, /, %, <<, >>, ==, !=, >, <, >=, <=
* +=, -=, *=, /=, %=, <<=, >>=
* Redirection via << and >> is supported.  
* Various bit access functions.

## Constrution
Strings with bases 2 through 36 are available for initialization as well as long
long ints.

## Using the long long int interface
In this implementation, the long long int returned is always 63 bits
with the last bit reserved for the sign.  Therefore Fatint objects should not be
treated as 64 bit numbers via the long long int interfaces, but only as 63 bit
 valued signed integers.  That's [−9,223,372,036,854,775,807, +9,223,372,036,854,775,807].

## Examples
* The code in /examples is for a Lehmer Random Number Generator and shows a simple example.
* The fatint_test.cc code contains many examples.

## Testing
The unit testing is adequite but not thorough.

## Time and Space Limits
* Addition and subtraction are O(n) in time and space complexity when n is the data size, or number of digits.
* Multiply, Divide and Modulo are O(n log n).   
* Bit shifting is O(n).
