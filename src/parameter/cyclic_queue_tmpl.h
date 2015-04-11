/**
 * @file
 * @author Yan Ni <leckie.dove@gmail.com>
 */



#ifndef SRC_PARAMETER_CYCLIC_QUEUE_TMPL_H_
#define SRC_PARAMETER_CYCLIC_QUEUE_TMPL_H_

#include "src/util/common.h"
#include "src/util/scoped_ptr.h"
#include <string>


namespace brook {

#define _CYCLIC_QUEUE_INIT_ELEMS 8			// initial buffer size in element numbers
#define _CYCLIC_QUEUE_FACTOR 2
#define _CYCLIC_QUEUE_SHRINK_FACTOR 4

template <class value_t>
class CyclicQueueTmpl{
public:
	CyclicQueueTmpl():
		buff_len(_CYCLIC_QUEUE_INIT_ELEMS),
		head_idx(0),
		tail_idx(0),
		buff(new value_t [buff_len]){

	}

	~CyclicQueueTmpl(){
	}

	void push(const value_t & value){
		this->expand();
		this->buff[ this->tail_idx++ % this->buff_len ] = value;
	}

	value_t pop(){
		value_t _ret = this->buff[ this->head_idx++ % this->buff_len ];
		this->shrink();
		return _ret;
	}

	value_t get(std::size_t index) {
		return this->get_elem(index);
	}

	void set(std::size_t index, const value_t & value) {
		this->get_elem(index) = value;
	}


	inline bool empty(){
		return this->size() == 0;
	}
	/**
	 * Get the number of the elements that the queue currently holds,
	 * used in loops & memory checking
	 */
	std::size_t size(){
		return this->size(this->head_idx, this->tail_idx);
	}
	/**
	 * Get the memory size of the CyclicQueue data buffer, in bytes
	 */
	std::size_t capacity(){
		return this->buff_len * sizeof(value_t);
	}

private:
	scoped_array<value_t> buff;
	size_t buff_len;
	size_t head_idx, tail_idx;


	inline std::size_t size(std::size_t _head, std::size_t _tail){
		CHECK_LE(_head, _tail);
		return _tail - _head;
	}

	// get element reference by index
	// @param
	inline value_t & get_elem (
			std::size_t index,
			scoped_array<value_t> _buff = this->buff,
			std::size_t _buff_len = this->buff_len,
			std::size_t _head = this->head_idx,
			std::size_t _tail = this->tail_idx){
		CHECK_NE(_buff.get(), NULL);
		CHECK_NE(_buff_len, 0);
		CHECK_LT(index, this->size(_head, _tail));
		return this->buff[ (index + _head) % _buff_len ];
	}

	// reallocate buffer, for buffer expansion or shrink
	// @param new buffer size, in element numbers
	inline void re_alloc(std::size_t new_buf_size){
		CHECK_LE(this->size(), new_buf_size);
		scoped_array<value_t> old_buff(this->buff.release());
		this->buff.reset(new value_t [new_buf_size]);
		std::size_t _size = this->size();

		for (std::size_t i = 0; i < _size; i++){
			this->get_elem(i,
					this->buff,
					new_buf_size) \
							= \
			this->get_elem(i,
					old_buff,
					this->buff_len);
		}

		this->buff_len = new_buf_size;
	}

	inline void expand(){
		if (this->size() >= this->buff_len)
			this->re_alloc(this->buff_len * _CYCLIC_QUEUE_FACTOR);
	}

	inline void shrink(){
		if (this->buff_len > _CYCLIC_QUEUE_INIT_ELEMS && \
				this->size() * _CYCLIC_QUEUE_SHRINK_FACTOR <= this->buff_len )
			this->re_alloc(this->buff_len / _CYCLIC_QUEUE_FACTOR);
	}
};
}



#endif /* SRC_PARAMETER_CYCLIC_QUEUE_TMPL_H_ */
