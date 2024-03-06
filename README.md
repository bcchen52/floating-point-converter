# floating-point-converter

-Description
This project is an extension of a project from Binghamton University's CS220. This takes a value as a double floating point value, and uses bit twiddling to store it into a `floatx` value with user-specified exponent and fraction bit sizes. The floatx value will be stored in the right most bits of a double value, meaning that the total bits(exponent bits, fraction bits, and sign bit) have a maximum of 64. There must be at least 1 fraction bit and 1 exponent bit, and the minimum number of total bits is 3.  

According to the IEEE standard, a double point floating values has 1 sign bit, 11 exponent bits, and 52 fraction bits. Some values may need more magnitude, i.e. more exponent bits, and less precision, i.e. less fraction bits, or vice versa. Or, if a value simply does not need the extent of precision and size given by a standard single or double floating point. 

-How to Use
MakeFile


-Files
In floatx.c lies the function 
`floatx doubleToFloatx(double val,int totBits,int expBits)'
which takes a double value, and expresses it in a floatx variable with totBits total bits, expBits exponent bits, and from that, totBits-expBits-1 fraction bits. 

In value.c, the function 
``
gives the value of a floatx value. For simplicity, we take floatx value and converts it back to a double and expresses that value, allowing us to assess any information that has been lost by changing the exponent and fraction bit field sizes. 

test1.txt has test values 

testFloatx.c 

Makefile



-Significant 
