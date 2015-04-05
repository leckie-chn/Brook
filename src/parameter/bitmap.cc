// Copyright 2015 PKU-Cloud
// Author Yan Ni(leckie.dove@gmail.com)


#include "src/parameter/bitmap.h"
#include "src/util/common.h"
#include "snappy.h"

#include <cstring>
#include <cstdio>

#define INDEX(x) ((x) / (sizeof(char) * 8))
#define OFFSET(x) ((x) % (sizeof(char) * 8))

using namespace std;


namespace brook {

bitmap::bitmap(size_t sz):size(sz), array_len((sz - 1) / (sizeof(char) << 3) + 1){
	this->data = new char [ this->array_len ];
	memset(this->data, 0, this->array_len * sizeof(char));
}

bitmap::bitmap(const string & init, size_t sz):size(sz), array_len((sz - 1) / (sizeof(char) << 3) + 1){
	this->data = new char [ this->array_len ];
	snappy::RawUncompress(init.data(), init.length(), (char *)this->data);
}

bitmap::~bitmap() {
	delete [] this->data;
}

string * bitmap::Compress(){
	string *ret = new string;
	snappy::Compress(this->data, this->array_len, ret);
	return ret;
}

vector<size_t> * bitmap::ListGen(){
	vector<size_t> *ret = new vector<size_t>;
	for (size_t i = 0; i < this->size; i++)
		if ((this->data[INDEX(i)] & (1 << OFFSET(i))) > 0)
			ret->push_back(i);
	return ret;
}

void bitmap::set(size_t index){
	CHECK_LT(index, this->size);
	this->data[INDEX(index)] |= 1 << OFFSET(index);
}

void bitmap::unset(size_t index){
	CHECK_LT(index, this->size);
	this->data[INDEX(index)] &= ~(1 << OFFSET(index));
}

bool bitmap::test(size_t index){
	CHECK_LT(index, this->size);
	return (this->data[INDEX(index)] & (1 << OFFSET(index))) > 0;
}

} /* namespace brook */
