using namespace std;
#include <iostream>
#include <queue>
#include <list>

class Human {
protected:
	string pseudonym;
	string address;
	int age;
	int numoffriends;
	string interests;
	string favquote;
public:
	//Конструкторы
	Human() {
		pseudonym = "Pseudo"; address = "Moscow"; age = 27; numoffriends = 100;
		interests = "bowling"; favquote = "your advertisement could be here";
	}
	Human(const string& pm, const string& as, int ag, int ns, const string& inter, const string& fav) {
		pseudonym = pm; address = as; age = ag; numoffriends = ns;
		interests = inter; favquote = fav;
	}

	//Геттеры
	int getNumFriends() const { return numoffriends; }
	string getPseud() const { return pseudonym; }

	string getAd() const { return address; }
	int getAge() const { return age; }
	string getInter() const { return interests; }
	string getFav() const { return favquote; }
};

//Для списка из задания 1.2
//Перегрузки операторов
bool operator< (const Human& value1, const Human& value2) {
	if (value1.getNumFriends() > value2.getNumFriends())
		return 1;
	else if (value1.getNumFriends() == value2.getNumFriends() && value1.getPseud() < value2.getPseud()) {
		return 1;
	}
	return 0;
}
//Для "правильного" использования встроенной функции сортировки (list.sort())
bool operator> (const Human& value1, const Human& value2) {
	if (value1.getNumFriends() < value2.getNumFriends())
		return 1;
	else if (value1.getNumFriends() == value2.getNumFriends() && value1.getPseud() > value2.getPseud()) {
		return 1;
	}
	return 0;
}
ostream& operator<< (ostream& stream, const Human& user) {
	stream << "User information:\n\n";
	stream << "Pseudoname: " << user.getPseud() << "\n";
	stream << "Friends: " << user.getNumFriends() << "\n";

	stream << "Address: " << user.getAd() << "\n";
	stream << "Age: " << user.getAge() << "\n";
	stream << "Interests: " << user.getInter() << "\n";
	stream << "Quote: " << user.getFav() << "\n";
	stream << "=================================\n";

	return stream;
}


bool operator== (const Human& value1, const Human& value2) {
	if (value1.getPseud() == value2.getPseud() && value1.getAd() == value2.getAd() && value1.getAge() == value2.getAge()
		&& value1.getNumFriends() == value2.getNumFriends() && value1.getInter() == value2.getInter() && value1.getFav() == value2.getFav()) {
		return 1;
	}
	return 0;
}
bool operator!= (const Human& value1, const Human& value2) {
	if (value1.getPseud() != value2.getPseud() || value1.getAd() != value2.getAd() || value1.getAge() != value2.getAge()
		|| value1.getNumFriends() != value2.getNumFriends() || value1.getInter() != value2.getInter() || value1.getFav() != value2.getFav()) {
		return 1;
	}
	return 0;
}




template<typename T>
void print_queue(T& q) {
	while (!q.empty()) {
		cout << q.top() << "\n";
		q.pop();
	}
	cout << '\n';
}

//узел дерева
template <class T>
class Node
{
private:
	T value;
public:
	//установить данные в узле
	T getValue() { return value; }
	void setValue(T v) { value = v; }
	//сравнение узлов
	int operator<(Node N)
	{
		return (value < N.getValue());
	}
	int operator>(Node N)
	{
		return (value > N.getValue());
	}
	int operator<=(Node N)
	{
		return (value <= N.getValue());
	}
	int operator>=(Node N)
	{
		return (value >= N.getValue());
	}
	int operator==(Node N)
	{
		return (value == N.getValue());
	}
	//вывод содержимого одного узла
	void print()
	{
		cout << value << "\n";
	}
};


template <class T>
void print(Node<T>* N)
{
	cout << N->getValue() << "\n";
}

//Куча (heap)
template <class T>
class Heap
{
private:
	//массив
	Node<T>* arr;
	//сколько элементов добавлено
	int len;
	//сколько памяти выделено
	int size;
public:
	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }
	Node<T>& operator[](int index)
	{
		if (index < 0 || index >= len)
			throw "Index isn't correct";
		return arr[index];
	}
	//конструктор
	Heap<T>(int MemorySize = 100)
	{
		arr = new Node<T>[MemorySize];
		len = 0;
		size = MemorySize;
	}
	//поменять местами элементы arr[index1], arr[index2]
	void Swap(int index1, int index2)
	{
		if (index1 < 0 || index1 >= len)
			throw "The first index isn't correct";
		if (index2 < 0 || index2 >= len)
			throw "The second index isn't correct";
		//здесь нужна защита от дурака
		Node<T> temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}
	//скопировать данные между двумя узлами
	void Copy(Node<T>* dest, Node<T>* source)
	{
		dest->setValue(source->getValue());
	}
	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
	Node<T>* GetLeftChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			throw "Index isn't correct";
		//здесь нужна защита от дурака
		return &arr[index * 2 + 1];
	}
	Node<T>* GetRightChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			throw "Index isn't correct";
		//здесь нужна защита от дурака
		return &arr[index * 2 + 2];
	}
	Node<T>* GetParent(int index)
	{
		if (index <= 0 || index >= len)
			throw "Index isn't correct";
		//здесь нужна защита от дурака
		if (index % 2 == 0)
			return &arr[index / 2 - 1];
		return &arr[index / 2];
	}
	int GetLeftChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			throw "Index isn't correct";
		//здесь нужна защита от дурака
		return index * 2 + 1;
	}
	int GetRightChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			throw "Index isn't correct";
		//здесь нужна защита от дурака
		return index * 2 + 2;
	}
	int GetParentIndex(int index)
	{
		if (index <= 0 || index >= len)
			throw "Index isn't correct";
		//здесь нужна защита от дурака
		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}


	//просеять элемент вверх
	void SiftUp(int index = -1)
	{
		if (index == -1) index = len - 1;

		//нужно сравнить элементы и при необходимости произвести просеивание вверх
		if (index == 0) return;
		int parent_index = GetParentIndex(index);

		if (arr[parent_index] < arr[index])
		{
			Swap(parent_index, index);
			SiftUp(parent_index);
		}
	}
	void SiftDown(int index = 0) 
	{
		//нужно сравнить элементы и при необходимости произвести просеивание вниз
		int leftChild;
		int rightChild;
		int largestChild;

		leftChild = 2 * index + 1;
		rightChild = 2 * index + 2;

		//нужно сравнить элементы и при необходимости произвести просеивание вниз
		if (leftChild == len - 1)
		{
			//1 дочерний элемент
			if (arr[leftChild] > arr[index])
			{
				Swap(leftChild, index);
				return;
			}
			else return;
		}
		if (leftChild >= len)
		{
			//детей нет
			return;
		}
		int max_index = arr[leftChild] > arr[rightChild] ? leftChild : rightChild;
		if (arr[max_index] > arr[index])
		{
			Swap(max_index, index);
			SiftDown(max_index);
		}

	}

	//добавление элемента - вставляем его в конец массива и просеиваем вверх
	template <class T>
	void push(T v)
	{
		Node<T>* N = new Node<T>;
		N->setValue(v);
		push(N);
	}
	template <class T>
	void push(Node<T>* N)
	{
		if (len < size)
		{
			Copy(&arr[len], N);
			len++; 
			SiftUp();
		}
		else throw "Memory is full";
	}
	//перечислить элементы кучи и применить к ним функцию
	void Straight(void (*f)(Node<T>*))
	{
		int i;
		for (i = 0; i < len; i++)
		{
			f(&arr[i]);
		}
	}
	//перебор элементов, аналогичный проходам бинарного дерева
	void InOrder(void (*f)(Node<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	T ExtractMax() {
		T result = arr[0].getValue();
		arr[0] = arr[len - 1];
		len--;
		SiftDown();
		return result;
	}
	T ExtractSelected(int index) {
		T result = arr[index];
		arr[index] = arr[len - 1];
		len--;
		SiftDown();
		return result;
	}


	void PrintHeap() {
		for (int i = 0; i < len; i++) { arr[i].print(); }
	}

};


//узел фибоначчиевой кучи
template <class T>
class FibonacciNode
{
private:
	T value;
	//доп. параметры для фибоначчиевой кучи
	list<FibonacciNode<T>*> childs;
	int numberchilds;
	FibonacciNode<T>* parent;
public:
	FibonacciNode<T>() { childs = list<FibonacciNode<T>>{}; numberchilds = 0; parent = NULL; }
	//установить данные в узле
	T getValue() { return value; }
	void setValue(T v) { value = v; }
	list<FibonacciNode<T>*> getChilds() {
		return childs;
	}

	//сравнение узлов
	int operator<(FibonacciNode N)
	{
		return (value < N.getValue());
	}
	int operator>(FibonacciNode N)
	{
		return (value > N.getValue());
	}
	int operator<=(FibonacciNode N)
	{
		return (value <= N.getValue());
	}
	int operator>=(FibonacciNode N)
	{
		return (value >= N.getValue());
	}
	int operator==(FibonacciNode N)
	{
		return (value == N.getValue());
	}
	//вывод содержимого одного узла
	void print()
	{
		cout << value << "\n";
	}
};

//фибоначчиева куча
template <typename T>
class FibonacciHeap {
private:
	//список из корней куч (деревьев)
	list<FibonacciNode<T>*> roots;
public:
	FibonacciHeap<T>() { roots = list<FibonacciNode<T>*> {}; }
	list<FibonacciNode<T>*> getRoots() { return roots; }
	void setRoots(list<FibonacciNode<T>*> r) { roots = r; }
};

//функция удаления элемента из списка list
list<int> delete_list_elem(list<int> list1, int k)
{
	int i = 0;
	list<int>::iterator it = list1.begin();
	while (i <= k)
	{
		if (i == k)
		{
			cout << *it << " ";
			list1.remove(*it);

			cout << "\n deleted" << endl;
		}
		it++;
		i++;
	}
	return list1;
}



//функция удаления одного из корней фибоначчиевой кучи по индексу
template <class T>
FibonacciHeap<T> ExtractMax(FibonacciHeap<T> tree, int index) {
	list<FibonacciNode<T>*> newroots = ((tree.getRoots())[index]).getChilds();
	FibonacciHeap<T> resulttree = delete_list_elem(tree.getRoots(), index);
	resulttree.insert(resulttree.end(), newroots.begin(), newroots.end());
	return resulttree;
}


int main()
{
	try {
		//priority_queue<int> q;
		//for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
		//	q.push(n);
		//print_queue(q);


		//Human human1("Hlath", "Klow", 76, 67, "Tennis", "What?");
		//Human human2("Alan", "New-York", 34, 605, "Golf", "Nothing");
		//Human human3("Cser", "Paris", 12, 32, "Video-games", "Ok, Jacques Fresco");
		//Human human4("Baltazar", "Germany", 39, 1089, "Tetris", "Yep");
		//Human human5("Genry", "Estonia", 32, 605, "Working", "What does it mean?");

		//priority_queue<Human> q;
		//for (Human n : {human1, human2, human3, human4, human5})
		//	q.push(n);
		//print_queue(q);


		Heap<int> Tree;
		Tree.push(1);
		Tree.push(-1);
		Tree.push(-2);
		Tree.push(2);
		Tree.push(5);
		Tree.push(6);
		Tree.push(-3);
		Tree.push(-4);
		Tree.ExtractMax();
		Tree.PrintHeap();
		//cout << "\n-----\nStraight:";
		//void(*f_ptr)(Node<int>*); 
		//f_ptr = print;
		//Tree.Straight(f_ptr);
	}
	catch (const char* error) { cout << error; }
}