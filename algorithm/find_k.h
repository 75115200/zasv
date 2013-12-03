#pragma once
#include <vector>
#include <iterator>
#include <algorithm>

/*
寻找一组数中第k小的数字算法实现
*/

const int THRESHOLDS = 6;

//adapted to arrays
template <typename T>
//k <= 0 for middle
T find_k(T* begin, T* end, std::size_t k)
{
	using std::vector;
	vector<T> *v = new vector<T>();
	//if k is not proper set to middle
	const std::size_t len  = distance(begin, end);
	if (k > len || k < 0)
		k = 0;
	copy(begin, end,
		 back_inserter(*v));

	return _find_k(v, k);
}


//adapted to iterators
template <typename _ForwardIterator>
typename std::iterator_traits<_ForwardIterator>::value_type
find_k(_ForwardIterator begin, _ForwardIterator end, std::size_t k)
{
	using std::vector;
	typedef
		typename std::iterator_traits<_ForwardIterator>::value_type
		T;
	const std::size_t len = distance(begin, end);
	vector<T> *v = new vector<T>();
	if (k > len || k < 0)
		k = 0;
	copy(begin, end,
		 back_inserter(*v));
	return _find_k(v, k);
}

template <typename T>
T _find_k(std::vector<T> *v, std::size_t k)
{
	using namespace std;
	const std::size_t v_s = v->size();
	if (k <= 0) {
		if ((v_s / 2 * 2) == v_s) {
			//even
			k = v_s / 2;
		} else {
			//odds
			k = (v_s + 1) / 2;
		}
	}
	if (v_s <= THRESHOLDS) {
		sort(v->begin(), v->end());
		T ret = v->at(k - 1);
		delete v;
		return ret;
	}
	const std::size_t group_cs = v_s / 5;
	std::size_t group_s;
	vector<T> **groups;
	if (group_cs * 5 == v_s) {
		group_s = group_cs;
	} else {
		group_s = group_cs + 1;
	}
	groups = new vector<T>*[group_s];
	std::size_t i = 0;
	for (; i < group_s - 1; ++i) {
		groups[i] = new vector<T>();
		//copy(v->begin() + (i * 5), v->begin() + (i * 5 + 5),
		copy(&v->at(i * 5), &v->at(i * 5 + 5),

			 back_inserter(*groups[i]));
	}
	groups[group_s - 1] = new vector<T>();
	copy(v->begin() + (i * 5), v->end(),
		 back_inserter(*groups[i]));

	vector<T>* mids = new vector<T>();
	for (i = 0; i < group_s; ++i) {
		mids->push_back(_find_k(groups[i], 0));
	}
	T mid = _find_k(mids, 0);
	delete[] groups;

	vector< vector<T>* > class_3(3);
	for (i = 0; i < 3; ++i) {
		class_3[i] = new vector<T>();
	}

	vector<T>::iterator it;
	for (it = v->begin(); it != v->end(); ++it) {
		T tmp = *it;
		if (tmp > mid) {
			class_3[2]->push_back(tmp);
		} else if (tmp < mid) {
			class_3[0]->push_back(tmp);
		} else {
			class_3[1]->push_back(tmp);
		}
	}
	delete v;

	if (k <= class_3[0]->size()) {
		// elements is in class_3[0] 
		delete class_3[1];
		delete class_3[2];
		return _find_k(class_3[0], k);
	} else if (k <= class_3[0]->size() + class_3[1]->size()) {
		// elements is in group1
		delete class_3[0];
		delete class_3[1];
		delete class_3[2];
		return mid;
	} else {
		//elements is in group3
		std::size_t sizeSum = class_3[0]->size() + class_3[1]->size();
		delete class_3[0];
		delete class_3[1];
		return _find_k(class_3[2], k - sizeSum);
	}
}