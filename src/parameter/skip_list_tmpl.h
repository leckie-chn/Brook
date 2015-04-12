// Copyright 2015 PKU-Cloud
// Author : Yan Ni <leckie.dove@gmail.com>
//
#ifndef PARAMETER_SKIP_LIST_TMPL_H_
#define PARAMETER_SKIP_LIST_TMPL_H_

#include "src/util/common.h"

#include <string>

namespace brook {

template <class ValueType>
class SkipListQueueTmpl {

	struct node_t {
		ValueType value;
		node_t *next;

		node_t(ValueType _value) 
        : value(_value), next(NULL) {}
		
        ~node_t() {}
	};

	struct index_t {
		node_t *head;
		node_t *tail;
		index_t *next;
		unsigned int elem_cnt;

		index_t()
        :head(NULL), tail(NULL), next(NULL), elem_cnt(0) {}
		
        ~index_t(){}
	};

public:
	SkipListQueueTmpl(int step = 8):
		head(NULL),
		tail(NULL),
        skip_step_(step),
        size_(0) {}

	~SkipListQueueTmpl() {
		index_t *ip = this->head;
		node_t *np = (this->head == NULL) ? NULL : this->head->head;

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

	void Push(ValueType value) {
		node_t *p = new node_t(value);
		if (!this->insertnode(this->tail, p)) {
			if (this->tail != NULL) {
				this->tail->tail->next = p;
            }
			index_t *q = new index_t;
			this->insertindex(q);
			this->insertnode(q, p);
		}
        size_++;
	}

	ValueType Pop() {
		node_t *p;
		if (!this->removenode(this->head, &p)){
			this->removeindex();
			this->removenode(this->head, &p);
		}
		ValueType _ret = p->value;
		delete p;
		this->size_--;
		return _ret;
	}

	void Set(std::size_t index, ValueType value) { this->get_elem(index) = value; }

	ValueType Get(std::size_t index) { return this->get_elem(index); }

	std::size_t Size() { return size_; }

private:
	index_t * head;
	index_t * tail;
    const int skip_step_;
    size_t size_;

	// return false if the number of element of index is full
	inline bool insertnode(index_t * index, node_t * node) {
		if (index == NULL || index->elem_cnt == skip_step_)
			return false;

		if (index->head == NULL)
			index->head = index->tail = node;
		else {
			index->tail->next = node;
			index->tail = node;
		}
		index->elem_cnt++;

		return true;
	}

	inline void insertindex(index_t * index) {
		if (this->head == NULL){
			this->head = this->tail = index;
		} else {
			this->tail->next = index;
			this->tail = index;
		}
	}

	// return false if there is no nodes left in index
	inline bool removenode(index_t * index, node_t ** node) {
		if (index == NULL || index->elem_cnt == 0)
			return false;

		*node = index->head;
		index->head = index->head->next;
		if (index->head == NULL){
			index->tail = NULL;
		}
		index->elem_cnt--;
		(*node)->next = NULL;
		return true;
	}

	// remove index node from head
	inline void removeindex() {
		index_t *hd = this->head;
		if (hd == NULL) return;
		this->head = this->head->next;

		if (this->head == NULL){
			this->tail = NULL;
		}

		hd->next = NULL;
		delete hd;
	}

	inline ValueType & get_elem(std::size_t index) {
		index_t *p = this->head;
		std::size_t i = 0;
		node_t *tp;
		while (p != NULL && i + p->elem_cnt < index) {
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

} // namespace brook

#endif // PARAMETER_SKIP_LIST_TMPL_H_ 
