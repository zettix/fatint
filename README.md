# fatint

This is an integer library for very large integers.  The underlying datastructure is vector<unit32_t> with a boolean sign.
The following operators are available:  
* + - * / % << >> == != > < >= <=
And their assignment variations:  
* += -= *= /= %= <<= >>=
Also redirection via << and >> is supported.  

At the moment only hex strings are available for initialization.  
The unit testing is adequite but not thorough.

* Addition and subtraction are O(n) in time and space complexity when n is the data size, or number of digits.
* Multiply, Divide and Modulo are O(n log n).   
* Bit shifting is O(n).
