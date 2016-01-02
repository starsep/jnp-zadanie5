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

	const std::pair <V, K> &min() const {
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		return *container.begin();
	};

	const std::pair <V, K> &max() const {
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		return *container.rbegin();
	};
public:
	using size_type = std::size_t;
	using key_type = K;
	using value_type = V;

	// Konstruktor bezparametrowy tworzący pustą kolejkę [O(1)]
	PriorityQueue() = default;

	// Konstruktor kopiujący [O(queue.size())]
	PriorityQueue(const PriorityQueue<K, V> &queue)
		: container(queue.container) {
	}

	// Konstruktor przenoszący [O(1)]
	PriorityQueue(PriorityQueue<K, V> &&queue)
		: container(std::move(queue.container)) {
	}

	// Operator przypisania [O(queue.size()) dla użycia P = Q, a O(1) dla użycia
	// P = move(Q)]
	PriorityQueue<K, V> &operator=(const PriorityQueue<K, V> &queue) {
		decltype(container) copy(container);
		copy = queue.container;
		std::swap(container, copy);
		return *this;
	}

	PriorityQueue<K, V> &operator=(PriorityQueue<K, V> &&queue) {
		container = std::move(queue.container);
		return *this;
	}

	// Metoda zwracająca true wtedy i tylko wtedy, gdy kolejka jest pusta [O(1)]
	bool empty() const {
		return container.empty();
	}

	// Metoda zwracająca liczbę par (klucz, wartość) przechowywanych w kolejce
	// [O(1)]
	size_type size() const {
		return container.size();
	}

	// Metoda wstawiająca do kolejki parę o kluczu key i wartości value
	// [O(log size())] (dopuszczamy możliwość występowania w kolejce wielu
	// par o tym samym kluczu)
	void insert(const K &key, const V &value) {
		//TODO
		container.insert(std::make_pair(value, key));
	}

	// Metody zwracające odpowiednio najmniejszą i największą wartość przechowywaną
	// w kolejce [O(1)]; w przypadku wywołania którejś z tych metod na pustej
	// strukturze powinien zostać zgłoszony wyjątek PriorityQueueEmptyException
	const V &minValue() const {
		return min().first;
	}

	const V &maxValue() const {
		return max().first;
	}

	// Metody zwracające klucz o przypisanej odpowiednio najmniejszej lub
	// największej wartości [O(1)]; w przypadku wywołania którejś z tych metod
	// na pustej strukturze powinien zostać zgłoszony wyjątek
	// PriorityQueueEmptyException
	const K &minKey() const {
		return min().second;
	}

	const K &maxKey() const {
		return max().second;
	}

	// Metody usuwające z kolejki jedną parę o odpowiednio najmniejszej lub
	// największej wartości [O(log size())]
	void deleteMin() {
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		//TODO
		container.erase(container.begin());
	}

	void deleteMax() {
		//TODO
		if (empty()) {
			throw PriorityQueueEmptyException();
		}
		auto it = container.end();
		it--;
		container.erase(it);
	}

	// Metoda zmieniająca dotychczasową wartość przypisaną kluczowi key na nową
	// wartość value [O(log size())]; w przypadku gdy w kolejce nie ma pary
	// o kluczu key, powinien zostać zgłoszony wyjątek
	// PriorityQueueNotFoundException(); w przypadku kiedy w kolejce jest kilka par
	// o kluczu key, zmienia wartość w dowolnie wybranej parze o podanym kluczu
	void changeValue(const K &key, const V &value) throw() {
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

	// Metoda scalająca zawartość kolejki z podaną kolejką queue; ta operacja usuwa
	// wszystkie elementy z kolejki queue i wstawia je do kolejki *this
	// [O(size() + queue.size() * log (queue.size() + size()))]
	void merge(PriorityQueue<K, V> &queue) {
		//TODO
		while (!queue.empty()) {
			container.insert(*queue.container.begin());
			queue.container.erase(queue.container.begin());
		}
	}

	// Metoda zamieniającą zawartość kolejki z podaną kolejką queue (tak jak
	// większość kontenerów w bibliotece standardowej) [O(1)]
	void swap(PriorityQueue<K, V> &queue) {
		//TODO
		std::swap(container, queue.container);
	}

	/*Klasa PriorityQueue<K, V> powinna zawierać publiczne definicje typów
		reprezentujących rozmiar oraz przechowywane klucze i wartości, o nazwach
		odpowiednio: size_type, key_type, value_type.

	Ponadto powinny być możliwe globalne operacje:

		- swap: przyjmujący dwie kolejki i zamieniający ich zawartość miejscami,
	- Porównania: ==, !=,
	- Porównania leksykograficzne kolejek <, >, <=, >=.*/
	bool operator==(const PriorityQueue &queue) const {
		return container == queue.container;
	}

	bool operator<(const PriorityQueue &queue) const {
		return container < queue.container;
	}
};

template<typename K, typename V>
bool operator!=(const PriorityQueue<K, V> &first, const PriorityQueue<K, V> &second) {
	return !(first == second);
}

template<typename K, typename V>
bool operator>(const PriorityQueue<K, V> &first, const PriorityQueue<K, V> &second) {
	return !(first <= second);
}

template<typename K, typename V>
bool operator>=(const PriorityQueue<K, V> &first, const PriorityQueue<K, V> &second) {
	return !(first < second);
}

template<typename K, typename V>
bool operator<=(const PriorityQueue<K, V> &first, const PriorityQueue<K, V> &second) {
	return first < second || first == second;
}

template<typename K, typename V>
void swap(PriorityQueue<K, V> &first, PriorityQueue<K, V> &second) {
	first.swap(second);
}