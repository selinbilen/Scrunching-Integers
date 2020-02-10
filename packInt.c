#include "packInt.h"
#include <assert.h>

union ovl {
	long vl;
	short vi[2];
} val;

void putInt(short value,long store[]) {
	val.vl=store[0];
	short nUsed=val.vi[0];
	assert(nUsed>=0); // Error if called after getInt
	nUsed++;
	assert(nUsed<=4096);
	val.vi[0]=nUsed;
	store[0]=val.vl;
	short ndx=nUsed/2;
	val.vl=store[ndx];
	short ndi=nUsed%2;
	val.vi[ndi]=value;
	store[ndx]=val.vl;
}

int storeUsed(long store[]) {
	val.vl=store[0];
	short nUsed=val.vi[0];
	assert(nUsed>0); // Error if called after getInt
	return 1+nUsed/4;
}

int getInt(long store[]) {
	val.vl=store[0];
	short nUsed=val.vi[0];
	assert(nUsed!=0);
	if (nUsed>0) { nUsed=-1; } // Special case for first time!
	val.vi[0]=nUsed-1; // Set up for next time
	store[0]=val.vl;
	nUsed=-nUsed;
	short ndx=nUsed/2;
	val.vl=store[ndx];
	short ndi=nUsed%2;
	return val.vi[ndi]; // C will automatically expand this to int
}
