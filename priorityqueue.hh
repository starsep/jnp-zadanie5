#ifndef PRIORITYQUEUE_HH
#define PRIORITYQUEUE_HH

#include <cstddef>
#include <set>
#include <memory>

struct PriorityQueueNotFoundException : public std::exception {
	virtual const char *what() const noexcept {
		return "PriorityQueueNotFoundException";
	}
};

struct PriorityQueueEmptyException : public std::exception {
	virtual const char *what() const noexcept {
		return "PriorityQueueEmptyException";
	}
};

template<typename K, typename V>
class PriorityQueue {
private:
	using key_shared = std::shared_ptr<K>;
	using value_shared = std::shared_ptr<V>;
	using key_value = std::pair<key_shared, value_shared>;
	using value_key = std::pair<value_shared, key_shared>;

	template<typename T>
	struct cmp {
		bool operator()(const T &a, const T &b) {
			if (*a.first < *b.first) {
				return true;
			}
			if (*b.first < *a.first) {
				return false;
			}
			return *a.second < *b.second;
		}
	};

	std::multiset <key_value, cmp<key_value>> containerKV;
	std::multiset <value_key, cmp<value_key>> containerVK;
public:
	using size_type = std::size_t;
	using key_type = K;
	using value_type = V;

	/*Konstruktor bezparametrowy tworzący pustą kolejkę
	  Złożoność: O(1)
	  Exception safety: no-throw */
	PriorityQueue() = default;

	/*Desktruktor
	  Exception safety: no-throw */
	~PriorityQueue() {
		containerKV.clear();
		containerVK.clear();
	}

	/*Konstruktor kopiujący
	  Złożoność: O(queue.size())
	  Exception safety: no-throw */
	PriorityQueue(const PriorityQueue<K, V> &queue)
		: containerKV(queue.containerKV),
		  containerVK(queue.containerVK) {
	}

	/*Konstruktor przenoszący
	  Złożoność: O(1)
	  Exception safety: no-throw */
	PriorityQueue(PriorityQueue<K, V> &&queue)
		: containerKV(std::move(queue.containerKV)),
		  containerVK(std::move(queue.containerVK)) {
	}

	/*Operator przypisania dla użycia P = Q
	  Złożoność: O(queue.size())
	  Exception safety: strong */
	PriorityQueue<K, V> &operator=(const PriorityQueue<K, V> &queue) {
		if (&queue == this) {
			return *this;
		}
		decltype(containerKV) copyKV(containerKV);
		decltype(containerVK) copyVK(containerVK);
		copyKV = queue.containerKV;
		copyVK = queue.containerVK;
		containerKV.swap(copyKV);
		containerVK.swap(copyVK);
		return *this;
	}

	/*Operator przypisania dla użycia P = move(Q)
	  Złożoność: O(1)
	  Exception safety: no-throw */
	PriorityQueue<K, V> &operator=(PriorityQueue<K, V> &&queue) {
		containerKV = std::move(queue.containerKV);
		containerVK = std::move(queue.containerVK);
		return *this;
	}

	/*Metoda zwracająca true wtedy i tylko wtedy, gdy kolejka jest pusta
	  Złożoność: O(1)
	  Exception safety: no-throw */
	bool empty() const {
		return containerKV.empty();
	}

	/*Metoda zwracająca liczbę par (klucz, wartość) przechowywanych w kolejce
	  Złożoność: O(1)
	  Exception safety: no-throw */
	size_type size() const {
		return containerKV.size();
	}

	/*Metoda wstawiająca do kolejki parę o kluczu key i wartości value
	  Złożoność: O(log size())
	  Exception safety: strong */
	void insert(const K &key, const V &value) {
		K new_key = key;
		V new_value = value;
		key_shared k_shared = std::make_shared<K>(new_key);
		value_shared v_shared = std::make_shared<V>(new_value);
		auto it = containerKV.insert(std::make_pair(k_shared, v_shared));
		try {
			containerVK.insert(std::make_pair(v_shared, k_shared));
		}
		catch (...) {
			containerKV.erase(it);
		}
	}

	/*Metoda zwracająca najmniejszą wartość przechowywaną w kolejce
	  Złożoność: O(1)
	  Exception safety: strong */
	const V &minValue() const {
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		return *containerVK.begin()->first;
	}

	/*Metoda zwracająca największą wartość przechowywaną w kolejce
	  Złożoność: O(1)
	  Exception safety: strong */
	const V &maxValue() const {
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		return *containerVK.rbegin()->first;
	}

	/*Metoda zwracająca klucz o przypisanej najmniejszej wartości
	  Złożoność: O(1)
	  Exception safety: strong */
	const K &minKey() const {
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		return *containerVK.begin()->second;
	}

	/*Metoda zwracająca klucz o przypisanej największej wartości
	  Złożoność: O(1)
	  Exception safety: strong */
	const K &maxKey() const {
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		return *containerVK.rbegin()->second;
	}

	/*Metoda usuwająca z kolejki jedną parę o najmniejszej wartości
	  Złożoność: O(log size())
	  Exception safety: no-throw */
	void deleteMin() {
		if (empty()) {
			return;
		}
		auto it = containerVK.begin();
		key_value pair = std::make_pair(it->second, it->first);
		auto it2 = containerKV.find(pair);
		containerVK.erase(it);
		containerKV.erase(it2);
	}

	/*Metoda usuwająca z kolejki jedną parę o największej wartości
	  Złożoność: O(log size())
	  Exception safety: no-throw */
	void deleteMax() {
		if (empty()) {
			return;
		}
		auto it = containerVK.end();
		it--;
		key_value pair = std::make_pair(it->second, it->first);
		auto it2 = containerKV.find(pair);
		containerVK.erase(it);
		containerKV.erase(it2);
	}

	/*Metoda zmieniająca dotychczasową wartość przypisaną kluczowi key na nową wartość value
	  Złożoność: O(log size())
	  Exception safety: strong */
	void changeValue(const K &key, const V &value) {
		V tmp_value = minValue();
		key_value pair = std::make_pair(std::make_shared<K>(key), std::make_shared<V>(tmp_value));
		auto it = containerKV.lower_bound(pair);
		if (it == containerKV.end() || *it->first < key || key < *it->first) {
			throw PriorityQueueNotFoundException();
		}
		tmp_value = *it->second;
		value_key pair2 = std::make_pair(std::make_shared<V>(tmp_value), std::make_shared<K>(key));
		auto it2 = containerVK.lower_bound(pair2);
		containerKV.erase(it);
		containerVK.erase(it2);
		insert(key, value);
	}

	/*Metoda scalająca zawartość kolejki z podaną kolejką queue; ta operacja usuwa
	  wszystkie elementy z kolejki queue i wstawia je do kolejki *this
	  Złożoność: O(size() + queue.size() * log (queue.size() + size()))
	  Exception safety: strong */
	void merge(PriorityQueue<K, V> &queue) {
		if (&queue == this) {
			return;
		}
		while (!queue.empty()) {
			containerKV.insert(*queue.containerKV.begin());
			queue.containerKV.erase(queue.containerKV.begin());
			containerVK.insert(*queue.containerVK.begin());
			queue.containerVK.erase(queue.containerVK.begin());
		}
	}

	/*Metoda zamieniającą zawartość kolejki z podaną kolejką queue (tak jak
      większość kontenerów w bibliotece standardowej)
	  Złożoność: O(1)
	  Exception safety: no-throw */
	void swap(PriorityQueue<K, V> &queue) {
		containerKV.swap(queue.containerKV);
		containerVK.swap(queue.containerVK);
	}

	/*Operator porównania
	  Złożoność: O(size())
	  Exception safety: strong */
	bool operator==(const PriorityQueue &queue) const {
		return containerKV == queue.containerKV;
	}

	/*Operator porównania
	  Złożoność: O(size())
	  Exception safety: strong */
	bool operator<(const PriorityQueue &queue) const {
		return containerKV < queue.containerKV;
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

#endif //PRIORITYQUEUE_HH