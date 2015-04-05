// Copyright 2015 PKU-Cloud
// Author Yan Ni(leckie.dove@gmail.com)
//
//

#ifndef SRC_PARAMETER_BITMAP_H_
#define SRC_PARAMETER_BITMAP_H_

#include <string>
#include <vector>

namespace brook {

class bitmap {
	char *data;
	const std::size_t size;
	const std::size_t array_len;
public:
	bitmap(std::size_t);
	bitmap(const std::string &, std::size_t);
	virtual ~bitmap();

	std::string * Compress();
	std::vector<std::size_t> * ListGen();

	void set(std::size_t);
	void unset(std::size_t);
	bool test(std::size_t);
};

} /* namespace brook */

#endif /* SRC_PARAMETER_BITMAP_H_ */
