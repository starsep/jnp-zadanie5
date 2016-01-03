#include <cstddef>
#include <set>

class PriorityQueueNotFoundException : public std::exception {
public:
	virtual const char *what() const noexcept {
		return "PriorityQueueNotFoundException";
	}
};

class PriorityQueueEmptyException : public std::exception {
public:
	virtual const char *what() const noexcept {
		return "PriorityQueueEmptyException";
	}
};

template<typename K, typename V>
class PriorityQueue {
private:
	std::multiset <std::pair<V, K>> container;
public:
	using size_type = std::size_t;
	using key_type = K;
	using value_type = V;

	/*Konstruktor bezparametrowy tworzący pustą kolejkę
	  Złożoność: O(1)
	  Exception safety: no-throw */
	PriorityQueue() = default;

	/*Konstruktor kopiujący
	  Złożoność: O(queue.size())
	  Exception safety: no-throw */
	PriorityQueue(const PriorityQueue<K, V> &queue)
		: container(queue.container) {
	}

	/*Konstruktor przenoszący
	  Złożoność: O(1)
	  Exception safety: no-throw */
	PriorityQueue(PriorityQueue<K, V> &&queue)
		: container(std::move(queue.container)) {
	}

	/*Operator przypisania dla użycia P = Q
	  Złożoność: O(queue.size())
	  Exception safety: strong */
	PriorityQueue<K, V> &operator=(const PriorityQueue<K, V> &queue) {
		decltype(container) copy(container);
		copy = queue.container;
		container.swap(copy);
		return *this;
	}

	/*Operator przypisania dla użycia P = move(Q)
	  Złożoność: O(1)
	  Exception safety: no-throw */
	PriorityQueue<K, V> &operator=(PriorityQueue<K, V> &&queue) {
		container = std::move(queue.container);
		return *this;
	}

	/*Metoda zwracająca true wtedy i tylko wtedy, gdy kolejka jest pusta
	  Złożoność: O(1)
	  Exception safety: no-throw */
	bool empty() const {
		return container.empty();
	}

	/*Metoda zwracająca liczbę par (klucz, wartość) przechowywanych w kolejce
	  Złożoność: O(1)
	  Exception safety: no-throw */
	size_type size() const {
		return container.size();
	}

	/*Metoda wstawiająca do kolejki parę o kluczu key i wartości value
	  Złożoność: O(log size())
	  Exception safety: strong*/
	void insert(const K &key, const V &value) {
		container.insert(std::make_pair(value, key));
	}

	/*Metoda zwracająca najmniejszą wartość przechowywaną w kolejce
	  Złożoność: O(1)
	  Exception safety: strong */
	const V &minValue() const {
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		return container.begin()->first;
	}

	/*Metoda zwracająca największą wartość przechowywaną w kolejce
	  Złożoność: O(1)
	  Exception safety: strong */
	const V &maxValue() const {
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		return container.rbegin()->first;
	}

	/*Metoda zwracająca klucz o przypisanej najmniejszej wartości
	  Złożoność: O(1)
	  Exception safety: strong */
	const K &minKey() const {
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		return container.begin()->second;
	}

	/*Metoda zwracająca klucz o przypisanej największej wartości
	  Złożoność: O(1)
	  Exception safety: strong */
	const K &maxKey() const {
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		return container.rbegin()->second;
	}

	/*Metoda usuwająca z kolejki jedną parę o najmniejszej wartości
	  Złożoność: O(log size())
	  Exception safety: no-throw */
	void deleteMin() {
		if (empty()) {
			return;
		}
		container.erase(container.begin());
	}

	/*Metoda usuwająca z kolejki jedną parę o największej wartości
	  Złożoność: O(log size())
	  Exception safety: no-throw */
	void deleteMax() {
		if (empty()) {
			return;
		}
		auto it = container.end();
		it--;
		container.erase(it);
	}

	/*Metoda zmieniająca dotychczasową wartość przypisaną kluczowi key na nową wartość value
	  Złożoność: O(log size())
	  Exception safety: strong */
	void changeValue(const K &key, const V &value) {
		//TODO
		std::pair <V, K> pair(value, key);
		auto it = container.upper_bound(pair);
		if (it == container.begin()) {
			throw PriorityQueueNotFoundException();
		}
		it--;
		/*if (it->first != value) {
			throw PriorityQueueNotFoundException();
		}*/
		//std::cout << value << " " << key << " " << it->first << " " << it->second << "\n";
		container.erase(it);
		insert(key, value);
	}

	/*Metoda scalająca zawartość kolejki z podaną kolejką queue; ta operacja usuwa
	  wszystkie elementy z kolejki queue i wstawia je do kolejki *this
	  Złożoność: O(size() + queue.size() * log (queue.size() + size()))
	  Exception safety: strong */
	void merge(PriorityQueue<K, V> &queue) {
		while (!queue.empty()) {
			container.insert(*queue.container.begin());
			queue.container.erase(queue.container.begin());
		}
	}

	/*Metoda zamieniającą zawartość kolejki z podaną kolejką queue (tak jak
      większość kontenerów w bibliotece standardowej)
	  Złożoność: O(1)
	  Exception safety: no-throw */
	void swap(PriorityQueue<K, V> &queue) {
		container.swap(queue.container);
	}

	/*Operator porównania
	  Złożoność: O(size())
	  Exception safety: strong */
	bool operator==(const PriorityQueue &queue) const {
		return container == queue.container;
	}

	/*Operator porównania
	  Złożoność: O(size())
	  Exception safety: strong */
	bool operator<(const PriorityQueue &queue) const {
		return container < queue.container;
	}
};

/*Operator porównania
  Złożoność: O(size())
  Exception safety: strong */
template<typename K, typename V>
bool operator!=(const PriorityQueue<K, V> &first, const PriorityQueue<K, V> &second) {
	return !(first == second);
}

/*Operator porównania
  Złożoność: O(size())
  Exception safety: strong */
template<typename K, typename V>
bool operator>(const PriorityQueue<K, V> &first, const PriorityQueue<K, V> &second) {
	return second < first;
}

/*Operator porównania
  Złożoność: O(size())
  Exception safety: strong */
template<typename K, typename V>
bool operator>=(const PriorityQueue<K, V> &first, const PriorityQueue<K, V> &second) {
	return !(first < second);
}

/*Operator porównania
  Złożoność: O(size())
  Exception safety: strong */
template<typename K, typename V>
bool operator<=(const PriorityQueue<K, V> &first, const PriorityQueue<K, V> &second) {
	return !(second < first);
}

/*Funkcja zamieniającą zawartość dwóch kolejek
  Złożoność: O(1)
  Exception safety: no-throw */
template<typename K, typename V>
void swap(PriorityQueue<K, V> &first, PriorityQueue<K, V> &second) {
	first.swap(second);
}