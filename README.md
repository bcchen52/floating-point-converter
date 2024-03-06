# floating-point-converter

## Description
This project is an extension of a project from Binghamton University's CS220. 

This program uses C to take a double floating point value and use bit twiddling to store it into a `floatx` value with user-specified exponent and fraction bit sizes. 

The floatx value will be stored in the right most bits of a double value, meaning that the total bits(exponent bits, fraction bits, and sign bit) have a maximum of 64. There must be at least 1 fraction bit and 1 exponent bit, and the minimum number of total bits is 3.  

According to the IEEE standard, a double point floating values has 1 sign bit, 11 exponent bits, and 52 fraction bits. Some values may need more magnitude, i.e. more exponent bits, and less precision, i.e. less fraction bits, or vice versa. A value simply may not need the extent of precision and size given by a standard single or double floating point. 

## Files

### floatx.c 

floatx.c has the functions

```c
floatx doubleToFloatx(double val,int totBits,int expBits);
```

and 

```c
double FloatxTodouble(floatx val, int totBits, int expBits);
```


which store a double value into a bit size specified `floatx` value and convert that `floatx` value back into a double, respectively. `totBits` represents the total bits, `expBits` represents exponent bits, and from that, `totBits-expBits-1` represents the fraction bits. 

As previously mentioned, the restrictions for the parameters are:
- totBits <= 64
- expBits >= 1
- totBits-expBits >= 2  **This is because fraction bits >= 1, and there is also 1 sign bit*

### bitField.c

bitField.c contains the functions
```c
int getBit(int bn,unsigned long val);
void setBit(int bn,int new,unsigned long *val);
unsigned long getBitFldU(int bs,int len,unsigned long val);
void setBitFld(int bs,int len,unsigned long new,unsigned long *val);
```
which are used in `floatx.c` to aid with bit manipulation. 

`getBit` and `setBit` get and set bits, respectively, at bit `bn` from an unsigned long `val`. 

`getBitFldU` gets `len` bits starting at bit `bs` and going to the right, returning an unsigned long with the bits being represented in the rightmost `len` bits of the output.

`setBitFld`

### test1.txt 

test1.txt contains values to be tested. 

### testFloatx.c 

testFloatx.c runs `doubleToFloatx` on the values in test1.txt with specific totBits and expBits parameters, and `floatxToDouble` displays the resulting `floatx` values. 

### Makefile

The commands below...
- `testFloatx` - creates and compiles the testFloatx executable from testFloatx.c, floatx.c, and bitField.c.
- `test` - runs the testFloatx executable using the parameters 32 and 8, 16 and 4, and 64 and 11, for `totBits` and `expBits`, respectively.
- `clean` - removes any files created by Makefile. 





## Results and Significance