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
double floatxTodouble(floatx val, int totBits, int expBits);
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

`setBitFld` takes the rightmost `len` bits of `new` and inserts them into position `bs` in `val`. 

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

The results from running 
```console
make test 
```
are ...
```console
./testFloatx 32 8 <test1.txt
            -0 = floatx(32,8) : 0000000080000000 =  -0.000000e+00,
             1 = floatx(32,8) : 000000003f800000 =  1.000000e+00,
           100 = floatx(32,8) : 0000000042c80000 =  1.000000e+02,
     1.3333333 = floatx(32,8) : 000000003faaaaaa =  1.333333e+00,
   1.27563e+45 = floatx(32,8) : 000000007f800000 =  inf,
      6.23e+22 = floatx(32,8) : 00000000655314a2 =  6.230000e+22,
       7.9e-39 = floatx(32,8) : 00000000005605fc =  9.827471e-39,
 3.4028235e+38 = floatx(32,8) : 000000007f7fffff =  3.402823e+38,
 3.4028236e+38 = floatx(32,8) : 000000007f7fffff =  3.402823e+38,
Input : q not recognized as a double... 	quitting
./testFloatx 16 4 <test1.txt
            -0 = floatx(16,4) : 0000000000008000 =  -0.000000e+00,
             1 = floatx(16,4) : 0000000000003800 =  1.000000e+00,
           100 = floatx(16,4) : 0000000000006c80 =  1.000000e+02,
     1.3333333 = floatx(16,4) : 0000000000003aaa =  1.333008e+00,
   1.27563e+45 = floatx(16,4) : 0000000000007800 =  inf,
      6.23e+22 = floatx(16,4) : 0000000000007800 =  inf,
       7.9e-39 = floatx(16,4) : 0000000000000560 =  1.306152e-02,
 3.4028235e+38 = floatx(16,4) : 0000000000007800 =  inf,
 3.4028236e+38 = floatx(16,4) : 0000000000007800 =  inf,
Input : q not recognized as a double... 	quitting
./testFloatx 64 11 <test1.txt
            -0 = floatx(64,11) : 8000000000000000 =  -0.000000e+00,
             1 = floatx(64,11) : 3ff0000000000000 =  1.000000e+00,
           100 = floatx(64,11) : 4059000000000000 =  1.000000e+02,
     1.3333333 = floatx(64,11) : 3ff5555555555555 =  1.333333e+00,
   1.27563e+45 = floatx(64,11) : 494c99c1d2cbef3a =  1.275630e+45,
      6.23e+22 = floatx(64,11) : 44aa62945c60e828 =  6.230000e+22,
       7.9e-39 = floatx(64,11) : 3805817f18b75025 =  7.900000e-39,
 3.4028235e+38 = floatx(64,11) : 47efffffe54daff8 =  3.402823e+38,
 3.4028236e+38 = floatx(64,11) : 47effffff514a7bc =  3.402824e+38,
Input : q not recognized as a double... 	quitting

```

