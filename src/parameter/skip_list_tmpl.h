/**
 * @file
 * @author Yan Ni <leckie.dove@gmail.com>
 */

#ifndef SRC_PARAMETER_SKIP_LIST_TMPL_H_
#define SRC_PARAMETER_SKIP_LIST_TMPL_H_

#include "src/util/common.h"

#include <string>

namespace brook {

#define _SKIP_LIST_QUEUE_STEP 8

template <class value_t>
class SkipListQueue{
	struct node_t {
		value_t value;
		node_t * next;

		node_t(const value_t & _value):value(_value), next(NULL){}
		~node_t(){}
	};

	struct index_t {
		node_t * head;
		node_t * tail;
		index_t * next;
		unsigned int elem_cnt;

		index_t():head(NULL),tail(NULL),next(NULL),elem_cnt(0){}
		~index_t(){}
	};

public:
	SkipListQueue():
		_head(NULL),
		_tail(NULL){}

	~SkipListQueue(){
		index_t *ip = this->_head;
		node_t *np = (this->_head == NULL) ? NULL : this->_head->head;

		while (ip != NULL){
			index_t *nxt = ip->next;
			delete ip;
			ip = nxt;
		}

		while (np != NULL){
			node_t *nxt = np->next;
			delete np;
			np = nxt;
		}
	}

	void push(value_t value){
		node_t *p = new node_t(value);
		if (!this->insert_node(this->_tail, p)){
			if (this->_tail != NULL)
				this->_tail->tail->next = p;
			index_t *q = new index_t;
			this->insert_index(q);
			this->insert_node(q, p);
		}
	}

	value_t pop(){
		node_t *p;
		if (!this->remove_node(this->_head, &p)){
			this->remove_index();
			this->remove_node(this->_head, &p);
		}
		value_t _ret = p->value;
		delete p;
		return _ret;
	}

	void set(std::size_t index, value_t value){
		this->get_elem(index) = value;
	}

	value_t get(std::size_t index){
		return this->get_elem(index);
	}

	std::size_t size(){
		std::size_t cnt = 0;
		for (index_t *p = this->_head; p != NULL; p = p->next)
			cnt += p->elem_cnt;
		return cnt;
	}

private:
	index_t * _head;
	index_t * _tail;

	// return false if the number of element of _index is full
	inline bool insert_node(index_t * _index, node_t * _node){
		if (_index == NULL || _index->elem_cnt == _SKIP_LIST_QUEUE_STEP)
			return false;

		if (_index->head == NULL)
			_index->head = _index->tail = _node;
		else {
			_index->tail->next = _node;
			_index->tail = _node;
		}
		_index->elem_cnt++;
		return true;
	}

	inline void insert_index(index_t * _index){
		if (this->_head == NULL){
			this->_head = this->_tail = _index;
		} else {
			this->_tail->next = _index;
			this->_tail = _index;
		}
	}

	// return false if there is no nodes left in _index
	inline bool remove_node(index_t * _index, node_t ** _node){
		if (_index == NULL || _index->elem_cnt == 0)
			return false;

		*_node = _index->head;
		_index->head = _index->head->next;
		if (_index->head == NULL){
			_index->tail = NULL;
		}
		_index->elem_cnt--;
		(*_node)->next = NULL;
		return true;
	}

	// remove index node from head
	inline void remove_index(){
		index_t *hd = this->_head;
		if (hd == NULL) return;
		this->_head = this->_head->next;

		if (this->_head == NULL){
			this->_tail = NULL;
		}

		hd->next = NULL;
		delete hd;
	}

	inline value_t & get_elem(std::size_t index){
		index_t *p = this->_head;
		std::size_t i = 0;
		node_t *tp;
		while (p != NULL && i + p->elem_cnt < index){
				p = p->next;
				CHECK_NOTNULL(p);
				i += p->elem_cnt;
				continue;
		}
		for (tp = p->head; i < index; i++, tp = tp->next);
		CHECK_NOTNULL(tp);
		return tp->value;

	}
};

}



#endif /* SRC_PARAMETER_SKIP_LIST_TMPL_H_ */
