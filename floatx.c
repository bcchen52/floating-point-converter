#include "floatx.h"
#include "bitField.h"
#include <assert.h>
#include <limits.h> // for CHAR_BIT - number of bits per byte
#include <math.h> // for isinf and isnan

floatx doubleToFloatx(double val,int totBits,int expBits) {
	assert(totBits<=64);
	assert((totBits-expBits)>=2);

	floatx result = 0; //empty float
	unsigned long val_expBits;
	unsigned long val_fracBits;
	int fracBits = totBits - expBits - 1; 
	int expStart = totBits - 2;
	int fracStart = expStart - expBits;
	int maxExp = (1 << (expBits-1))-1; // 2^(expBits-1) - 1, also the bias for expBits bits
	
	union ULDouble {
		double dbl;
		unsigned long lng;
	} unionVal;

	unionVal.dbl = val;

	setBit(totBits-1, getBit(63, unionVal.lng), &result);

	if(val == 0.0){
		val_expBits = (1UL>>1); //00...00
		val_fracBits = (1UL>>1); //00...00
	} else { if(isnan(val)){
		val_expBits =~ (1UL>>1); //11...11
		val_fracBits = 1UL; //00...01
	} else { if(isinf(val)){
		val_expBits =~ (1UL>>1); //11...11
		val_fracBits = (1UL>>1); //00...00
	} else {
		val_expBits = getBitFldU(62, 11, unionVal.lng);
		val_expBits -= 1023; //unbias with double bias
		val_fracBits = getBitFldU(51, 52, unionVal.lng);

		//-----**adjusting fraction field to size**-----
		if((fracBits) < 52){ //more fracBits than floatx can hold
			val_fracBits >>= (52-(fracBits)); 
		} 
		
		/*if larger, already adjusted for with setBitFld and fracBits
			val_frac_bits = 0...0(value of frac bits), 
			a larger fracBits means that 0...0000(value of frac bits) will be inserted
			depending on the size of fracBits with the extra 0s needed
		*/

		//-----**adjusting for underflow and overflow**-----
		if((int)val_expBits < -(maxExp)+1){ //subnormal
			val_expBits = 0; //set exp to 0
			val_fracBits >>= 1;
			setBit(fracStart, 1, &val_fracBits);
		} else { if((int)val_expBits > maxExp){ //too large
			val_expBits = ~(1UL>>1); //make an UL of ..001, >>1 to ..000 and ~ for ..111
			val_fracBits = 0;
		} else {
			val_expBits += maxExp; //rebias
		}}
	}}}
	setBitFld(expStart, expBits, val_expBits, &result);
	setBitFld(fracStart, fracBits, val_fracBits, &result);
	return result; 
}

double floatxTodouble(floatx val, int totBits, int expBits){
	assert(totBits<=64);
	assert((totBits-expBits)>=2);

	union ULFloatx {
		floatx flt;
		unsigned long lng;
	} unionVal;

	union ULDouble {
		double dbl;
		unsigned long lng;
	} unionVal2;

	unionVal.flt = val;

	unsigned long result = 0; //empty float
	unsigned long val_expBits;
	unsigned long val_fracBits;
	int fracBits = totBits - expBits - 1; 
	int expStart = totBits - 2;
	int fracStart = expStart - expBits;
	int maxExp = (1 << (expBits-1))-1;


	setBit(63, getBit(totBits-1, unionVal.lng), &result);

	val_expBits = getBitFldU(expStart, expBits, unionVal.lng);

	val_fracBits = getBitFldU(fracStart, fracBits, unionVal.lng);

	//-----**check special cases**-----
	if(val_expBits == (1UL>>1) && val_fracBits == (1UL>>1)){ //0.0
		unionVal2.lng = result;
		return unionVal2.dbl;
	} else { if(val_expBits == getBitFldU(expStart,expBits,~(1UL>>1))){
		val_expBits = getBitFldU(62,11,~(1UL>>1));
		if(val_fracBits == getBitFldU(fracStart,fracBits,(1UL>>1))){ //NaN
			val_fracBits = getBitFldU(52,51,(1UL>>1)); 
		} else { //inf
			val_fracBits = 1UL; 
		}
	} else {
		val_expBits -= maxExp; //unbias

		if(fracBits<52){ //adjust fraction field
			val_fracBits <<= 52-fracBits;
		} else { if(fracBits>52){
			val_fracBits >>= fracBits-52;
		}}

		if((int)val_expBits < -(1023)+1){ //subnormal
			val_expBits = 0; //set exp to 0
			val_fracBits >>= 1;
			setBit(51, 1, &val_fracBits);
		} else { if((int)val_expBits > 1023){ //overflow, turn into inf
			val_expBits = ~(1UL>>1); 
			val_fracBits = 0;
		} else {
			val_expBits += 1023; //rebias
		}}
	}}
	setBitFld(62, 11, val_expBits, &result);
	setBitFld(51, 52, val_fracBits, &result);

	unionVal2.lng = result;

	return unionVal2.dbl;
}


