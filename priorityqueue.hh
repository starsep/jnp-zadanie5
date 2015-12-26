#include <cstddef>

class PriorityQueueNotFoundException : public std::exception { };
class PriorityQueueEmptyException : public std::exception { };

template<typename K, typename V>
class PriorityQueue {
private:
public:
	using size_type = std::size_t;
	using key_type = K;
	using value_type = V;

	// Konstruktor bezparametrowy tworzący pustą kolejkę [O(1)]
	PriorityQueue() {
		//TODO
	}

	// Konstruktor kopiujący [O(queue.size())]
	PriorityQueue(const PriorityQueue<K, V> &queue) {
		//TODO
	}

	// Konstruktor przenoszący [O(1)]
	PriorityQueue(PriorityQueue<K, V> &&queue) {
		//TODO
	}

	// Operator przypisania [O(queue.size()) dla użycia P = Q, a O(1) dla użycia
	// P = move(Q)]
	PriorityQueue<K, V> &operator=(PriorityQueue<K, V> queue) {
		//TODO
	}

	// Metoda zwracająca true wtedy i tylko wtedy, gdy kolejka jest pusta [O(1)]
	bool empty() const {
		//TODO
		return true;
	}

	// Metoda zwracająca liczbę par (klucz, wartość) przechowywanych w kolejce
	// [O(1)]
	size_type size() const {
		//TODO
		return 0;
	}

	// Metoda wstawiająca do kolejki parę o kluczu key i wartości value
	// [O(log size())] (dopuszczamy możliwość występowania w kolejce wielu
	// par o tym samym kluczu)
	void insert(const K &key, const V &value) {
		//TODO
	}

	// Metody zwracające odpowiednio najmniejszą i największą wartość przechowywaną
	// w kolejce [O(1)]; w przypadku wywołania którejś z tych metod na pustej
	// strukturze powinien zostać zgłoszony wyjątek PriorityQueueEmptyException
	const V &minValue() const {
		//TODO
	}

	const V &maxValue() const {
		//TODO
	}

	// Metody zwracające klucz o przypisanej odpowiednio najmniejszej lub
	// największej wartości [O(1)]; w przypadku wywołania którejś z tych metod
	// na pustej strukturze powinien zostać zgłoszony wyjątek
	// PriorityQueueEmptyException
	const K &minKey() const {
		//TODO
	}

	const K &maxKey() const {
		//TODO
	}

	// Metody usuwające z kolejki jedną parę o odpowiednio najmniejszej lub
	// największej wartości [O(log size())]
	void deleteMin() {
		//TODO
	}

	void deleteMax() {
		//TODO
	}

	// Metoda zmieniająca dotychczasową wartość przypisaną kluczowi key na nową
	// wartość value [O(log size())]; w przypadku gdy w kolejce nie ma pary
	// o kluczu key, powinien zostać zgłoszony wyjątek
	// PriorityQueueNotFoundException(); w przypadku kiedy w kolejce jest kilka par
	// o kluczu key, zmienia wartość w dowolnie wybranej parze o podanym kluczu
	void changeValue(const K &key, const V &value) {
		//TODO
	}

	// Metoda scalająca zawartość kolejki z podaną kolejką queue; ta operacja usuwa
	// wszystkie elementy z kolejki queue i wstawia je do kolejki *this
	// [O(size() + queue.size() * log (queue.size() + size()))]
	void merge(PriorityQueue<K, V> &queue) {
		//TODO
	}

	// Metoda zamieniającą zawartość kolejki z podaną kolejką queue (tak jak
	// większość kontenerów w bibliotece standardowej) [O(1)]
	void swap(PriorityQueue<K, V> &queue) {
		//TODO
	}

	/*Klasa PriorityQueue<K, V> powinna zawierać publiczne definicje typów
		reprezentujących rozmiar oraz przechowywane klucze i wartości, o nazwach
		odpowiednio: size_type, key_type, value_type.

	Ponadto powinny być możliwe globalne operacje:

		- swap: przyjmujący dwie kolejki i zamieniający ich zawartość miejscami,
	- Porównania: ==, !=,
	- Porównania leksykograficzne kolejek <, >, <=, >=.*/
	bool operator==(const PriorityQueue &second) {
		//TODO
		return true;
	}
	bool operator!=(const PriorityQueue &second) {
		//TODO
		return true;
	}
	bool operator<(const PriorityQueue &second) {
		//TODO
		return true;
	}
	bool operator>(const PriorityQueue &second) {
		//TODO
		return true;
	}
	bool operator<=(const PriorityQueue &second) {
		//TODO
		return true;
	}
	bool operator>=(const PriorityQueue &second) {
		//TODO
		return true;
	}
};

template<typename K, typename V>
void swap(PriorityQueue<K, V> &first, PriorityQueue<K, V> &second) {
	first.swap(second);
}