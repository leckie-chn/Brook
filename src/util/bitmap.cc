// Copyright 2015 PKU-Cloud
// Author Yan Ni(leckie.dove@gmail.com)


#include "src/util/bitmap.h"
#include "src/util/common.h"

#include <snappy.h>
#include <cstring>
#include <cstdio>

#define INDEX(x) ((x) / (sizeof(char) * 8))
#define OFFSET(x) ((x) % (sizeof(char) * 8))

using namespace std;


namespace brook {

// data allocated on demand, init NULL
bitmap::bitmap(size_t sz):
		size(sz),
		array_len((sz - 1) / (sizeof(char) << 3) + 1),
		data(NULL),
		comp_len(snappy::MaxCompressedLength(array_len)),
		compressed(new char [comp_len]){
}


bitmap::~bitmap() {
}

// returns whether this->data really holds an array
inline bool bitmap::allocate(bool force_allocate, bool zero_init = false){
	if (this->data.get() == NULL && force_allocate){
		this->data.reset(new char [this->array_len]);
		if (zero_init)
			memset(this->data.get(), 0, this->array_len);
		return true;
	}
	return this->data.get() != NULL;
}

void bitmap::compress() {
	if (this->data.get() == NULL) return;	// no need to compress
	snappy::RawCompress(this->data.get(), this->array_len, this->compressed.get(), &this->comp_len);
	this->data.reset();		// release the memory
}

void bitmap::decompress() {
	if (this->compressed.get() == NULL)
		LOG(ERROR) << "Trying to decompress a null bitmap" << endl;
	this->allocate(true, false);
	snappy::RawUncompress(this->compressed.get(), this->comp_len, this->data.get());
}

void bitmap::ListGen(vector<size_t> &vec){
	if (this->data.get() == NULL)
		this->decompress();
	for (int i = 0; i < this->array_len; i++){
		const char t = this->data[i];
		for (int j = 0; j < sizeof(char) * 8; j++)
			if (((unsigned char)t & (1 << j)) > 0)	vec.push_back(i * sizeof(char) * 8 + j);
	}
}

void bitmap::set(size_t index, bool force_decomp){
	if (this->allocate(force_decomp, true) == false) 	return;
	CHECK_LT(index, this->size);
	this->data[INDEX(index)] |= 1 << OFFSET(index);
}

void bitmap::unset(size_t index, bool force_decomp){
	if (this->allocate(force_decomp, true) == false) 	return;
	CHECK_LT(index, this->size);
	this->data[INDEX(index)] &= ~(1 << OFFSET(index));
}

bool bitmap::test(size_t index, bool force_decomp){
	if (this->allocate(force_decomp, true) == false) 	return false;
	CHECK_LT(index, this->size);
	return (this->data[INDEX(index)] & (1 << OFFSET(index))) > 0;
}

} /* namespace brook */
