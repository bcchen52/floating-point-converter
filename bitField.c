#include "bitField.h"
#include <assert.h>

int getBit(int bn,unsigned long val) {
	assert(bn>=0 && bn<64);
	if (1UL<<bn & val) return 1;
	return 0;
}

void setBit(int bn,int new,unsigned long *val) {
	assert(bn>=0 && bn<64);
	if (new) (*val)|=1UL<<bn;
	else (*val)&=~(1L<<bn);
}

unsigned long getBitFldU(int bs,int len,unsigned long val) {
	assert(bs>=0 && bs<64);
	assert(0<len && len<=bs+1);
	int be=bs-len+1;
	unsigned long mask=((1L<<len) - 1)<<be;
	return (val & mask)>>be;
}

void setBitFld(int bs,int len,unsigned long new,unsigned long *val) {
	assert(bs>=0 && bs<64);
	assert(0<len && len<=bs+1);
	int be=bs-len+1;
	unsigned long mask=((1L<<len) - 1);
	new &=mask; 
	new<<=be; 
	mask<<=be;
	(*val) &= ~mask; 
	(*val) |= new;
}

