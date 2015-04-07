// Copyright 2015 PKU-Cloud
// Author Yan Ni(leckie.dove@gmail.com)
//
//

#ifndef SRC_UTIL_BITMAP_H_
#define SRC_UTIL_BITMAP_H_

#include "src/util/common.h"
#include "src/util/scoped_ptr.h"

#include <string>
#include <vector>

namespace brook {

class bitmap {
private:
	scoped_array<char> data;
	const scoped_array<char> compressed;
	const std::size_t size;
	const std::size_t array_len;
	std::size_t comp_len;
	DISALLOW_COPY_AND_ASSIGN(bitmap);
	bool allocate(bool, bool);
public:
	bitmap(std::size_t);
	virtual ~bitmap();

	void decompress();
	void compress();
	void ListGen(std::vector<std::size_t> &);

	void set(std::size_t, bool force_decomp = true);
	void unset(std::size_t, bool force_decomp = true);
	bool test(std::size_t, bool force_decomp = false);
};

} /* namespace brook */

#endif /* SRC_UTIL_BITMAP_H_ */
