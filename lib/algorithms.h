#include <iterator>
template<class InputIt, class UnaryPredicate>
constexpr InputIt my_find_if_not(InputIt first, InputIt last, UnaryPredicate p) {
  while (first != last && p(*first)) {
	++first;
  }
  return first;
}

template<class InputIt, class UnaryPredicate>
constexpr InputIt my_find_if(InputIt first, InputIt last, UnaryPredicate p) {
  while (first != last && !p(*first)) {
	++first;
  }
  return first;
}

template<class InputIt, class UnaryPredicate>
constexpr bool my_all_of(InputIt first, InputIt last, UnaryPredicate p) {
  return my_find_if_not(first, last, p) == last;
}

template<class InputIt, class UnaryPredicate>
constexpr bool my_any_of(InputIt first, InputIt last, UnaryPredicate p) {
  return my_find_if(first, last, p) != last;
}

template<class InputIt, class UnaryPredicate>
constexpr bool my_none_of(InputIt first, InputIt last, UnaryPredicate p) {
  return my_find_if(first, last, p) == last;
}

template<class InputIt, class UnaryPredicate>
constexpr bool my_one_of(InputIt first, InputIt last, UnaryPredicate p) {
  int counter = 0;
  while (first != last) {
	if (p(*first)) {
	  if (counter == 1) {
		return false;
	  }
	  counter++;
	}
	++first;
  }
  return counter == 1;
}

template<typename ForwardIterator, typename Compare>
constexpr bool my_is_sorted(ForwardIterator first, ForwardIterator last, Compare comp) {
  if (first == last) {
	return true;
  }
  ForwardIterator next = first;
  while (++next != last) {
	if (!comp(*first, *next)) {
	  return false;
	}
	++first;
  }
  return true;
}

template<class InputIt, class UnaryPredicate>
constexpr bool my_is_partitioned(InputIt first, InputIt last, UnaryPredicate p) {
  if (p(*first)) {
	first = my_find_if_not(first, last, p);
	first = my_find_if(first, last, p);
	if (first != last) {
	  return false;
	}
  }
  else {
	first = my_find_if(first, last, p);
	first = my_find_if_not(first, last, p);
	if (first != last) {
	  return false;
	}
  }
  return true;
}

template<class InputIt, typename T>
constexpr InputIt my_find_not(InputIt first, InputIt last, const T& p) {
  return my_find_if_not(first, last, [&p](const auto& x) { return x == p; });
}

template<class InputIt, typename T>
constexpr InputIt my_find_backward(InputIt first, InputIt last, const T& p) {
  auto it = --last;
  auto pred = [&p](const auto& x) { return x == p; };
  while (it != first - 1 && !pred(*it)) {
	--last;
  }
  if (it < first) {
	return it;
  }
  return last;
}

template <typename InputIt, typename UnaryPredicate>
bool my_is_palindrome(InputIt first, InputIt last, UnaryPredicate p) {
  while (first != last && first != --last) {
	if (p(*first) != p(*last)) {
	  return false;
	}
	++first;
  }
  return true;
}

template <typename T>
class xrange_class {
 private:
  T start_;
  T end_;
  T step_;

 public:
  class iterator {
   private:
	T current_;
	T step_;

   public:
	using iterator_category = std::input_iterator_tag;
	using value_type = T;
	using difference_type = T;
	using pointer = const T*;
	using reference = const T&;

	iterator(T current, T step) : current_(current), step_(step) {}

	bool operator==(const iterator& other) const {
	  return abs(current_ - other.current_) < abs(step_);
	}

	bool operator!=(const iterator& other) const {
	  return !(*this == other);
	}

	reference operator*() const {
	  return current_;
	}

	pointer operator->() const {
	  return &current_;
	}

	iterator& operator++() {
	  current_ += step_;
	  return *this;
	}

	iterator operator++(int) {
	  iterator temp = *this;
	  ++(*this);
	  return temp;
	}
  };
  xrange_class(T start, T end, T step = 1) : start_(start), end_(end), step_(step) {}

  xrange_class(T end) : start_(0), end_(end), step_(1) {}

  xrange_class(const xrange_class<T>& other) : start_(other.start_), end_(other.end_), step_(other.step_) {}

  xrange_class<T>& operator=(const xrange_class<T>& other) {
	if (this != &other) {
	  start_ = other.start_;
	  end_ = other.end_;
	  step_ = other.step_;
	}
	return *this;
  }



  iterator begin() const {
	return iterator(start_, step_);
  }

  iterator end() const {
	return iterator(end_, step_);
  }
};

template<typename T>
xrange_class<T> xrange(const T& start, const T& end, const T& step = 1) {
	return xrange_class<T>(start, end, step);
}

template<typename T>
xrange_class<T> xrange(const T& end) {
  return xrange_class<T>(end);
}

template <typename Container1, typename Container2>
class Zip {
 public:
  Zip(const Container1& container1, const Container2& container2)
	  : container1_(container1), container2_(container2) {}
  template <typename Iterator1, typename Iterator2>

  class ZipIterator {
   public:
	using value_type = std::pair<typename std::iterator_traits<Iterator1>::value_type,
								 typename std::iterator_traits<Iterator2>::value_type>;
	using difference_type = typename std::iterator_traits<Iterator1>::difference_type;
	using pointer = value_type*;
	using reference = value_type&;
	using iterator_category = std::forward_iterator_tag;
	ZipIterator(Iterator1 begin1, Iterator2 begin2)
		: it1_(begin1), it2_(begin2) {}

	std::pair<typename Iterator1::value_type, typename Iterator2::value_type> operator*() const {
	  return std::make_pair(*it1_, *it2_);
	}

	ZipIterator& operator++() {
	  ++it1_;
	  ++it2_;
	  return *this;
	}

	ZipIterator operator++(int) {
	  ZipIterator temp = *this;
	  ++(*this);
	  return temp;
	}

	bool operator!=(const ZipIterator& other) const {
	  return it1_ != other.it1_ && it2_ != other.it2_;
	}

   private:
	Iterator1 it1_;
	Iterator2 it2_;
  };

  template<typename Iterator1 = typename Container1::const_iterator, typename Iterator2 = typename Container2::const_iterator>
  ZipIterator<Iterator1, Iterator2> begin() const {
	return ZipIterator<Iterator1, Iterator2>(container1_.begin(), container2_.begin());
  }

  template<typename Iterator1 = typename Container1::const_iterator, typename Iterator2 = typename Container2::const_iterator>
  ZipIterator<Iterator1, Iterator2> end() const {
	return ZipIterator<Iterator1, Iterator2>(container1_.end(), container2_.end());
  }

 private:
  const Container1& container1_;
  const Container2& container2_;
};


template <typename Container1, typename Container2>
Zip<Container1, Container2> zip(Container1& container1, Container2& container2) {
  return Zip<Container1, Container2>(container1, container2);
}