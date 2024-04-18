//Вариант 26 (четный - Стек)

//Задание 1.3
//Постройте шаблон класса двусвязного списка путём наследования от
//класса IteratedLinkedList. Реализуйте функции добавления элемента push() и
//удаления элемента pop() в классе-наследнике D (для четных вариантов D –
//Стек, для нечетных – Очередь) согласно схеме: для класса Стек элементы
//добавляются в конец, извлекаются с конца; для класса Очереди элементы
//добавляются в конец, извлекаются с начала. Введите очистку памяти,
//выделенной под элементы списка, в деструкторе.
//Постройте наследник класса D. Переопределите функцию добавления
//нового элемента таким образом, чтобы контейнер оставался упорядоченным.
//Реализуйте функцию filter() из пункта 1 – результатом должен стать
//объект типа D. Реализуйте функцию универсального фильтра,
//принимающего список произвольного типа (участвующего в схеме
//наследования) и возвращающего список произвольного типа (тип
//обрабатываемого списка не обязан совпадать с типом списка-результата).

//Задание 1.4
//Постройте итераторы для перемещения по списку (введите операции
//чтение элемента списка по итератору *, операции перемещения по списку ++
//и --, вспомогательные операции). Переопределите функцию вывода
//содержимого списка с помощью итераторов. Итератор не должен быть полем
//в контейнере. Введите исключение для попытки чтения значения в случае,
//когда итератор не связан ни с каким элементом.

//Задание 1.5
//Постройте шаблон класса списка D (из задания в пункте 3), который
//хранит объекты класса C (из задания в пункте 2), сохраняя упорядоченность
//по приоритету: полю или группе полей, указанных в варианте.
//Переопределите операции добавления и удаления элементов с
//использованием итераторов.



#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <typeinfo>
using namespace std;

//Класс C из варианта
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

//Перегрузки операторов
bool operator<(const Human value1, const Human value2) {
	if (value1.getNumFriends() > value2.getNumFriends())
		return 1;
	else if (value1.getNumFriends() == value2.getNumFriends() && value1.getPseud() < value2.getPseud()) {
		return 1;
	}
	return 0;
}
//Для "правильного" использования встроенной функции сортировки (list.sort()) по условию задачи
bool operator>(const Human value1, const Human value2) {
	if (value1.getNumFriends() < value2.getNumFriends())
		return 1;
	else if (value1.getNumFriends() == value2.getNumFriends() && value1.getPseud() > value2.getPseud()) {
		return 1;
	}
	return 0;
}
ostream& operator<<(ostream& stream, list<Human>& lst) {
	typename list<Human>::iterator it = lst.begin();
	while (it != lst.end())
	{
		stream << (*it).getNumFriends() << "\n";
		stream << (*it).getPseud() << "\n" << "////////////////////////////////" << "\n";
		it++;
	}
	return stream;
}
bool operator==(const Human& value1, const Human& value2) {
	if (value1.getPseud() == value2.getPseud() && value1.getAd() == value2.getAd() && value1.getAge() == value2.getAge()
		&& value1.getNumFriends() == value2.getNumFriends() && value1.getInter() == value2.getInter() && value1.getFav() == value2.getFav()) {
		return 1;
	}
	return 0;
}



template <class T>
class Element
{
//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* next;
	Element* prev;

	//информация, хранимая в поле
	T field;
public:
	Element(T value = 0, Element<T>* next_ptr = NULL, Element<T>* prev_ptr = NULL)
	{
		field = value;
		next = next_ptr;
		prev = prev_ptr;
	}
	//доступ к полю *next
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }
	//доступ к полю *prev
	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }
	//доступ к полю с хранимой информацией field
	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }

	template<class T> friend ostream& operator<< (ostream& ustream, Element<T>& obj);
};
template<class T>
ostream& operator << (ostream& ustream, Element<T>& obj)
{
	ustream << obj.field;
	return ustream;
}



template <class T>
class LinkedListParent
{
protected:
	//достаточно хранить начало и конец
	Element<T>* head;
	Element<T>* tail;
	//для удобства храним количество элементов
	int num;
public:
	LinkedListParent()
	{
		//конструктор без параметров
		cout << "\nParent constructor";
		head = NULL;
		tail = NULL;
		num = 0;
	}

	virtual int Number() { return num; }
	virtual Element<T>* getBegin() { return head; }
	virtual Element<T>* getEnd() { return tail; }

	virtual ~LinkedListParent()
	{
		//деструктор - освобождение памяти
		cout << "\nParent destructor";

		Element<T>* delelement = this->head;
		while (delelement != NULL) {
			Element<T>* temp = delelement->getNext();
			delete delelement;
			delelement = temp;
		}
	}
	virtual Element<T>* operator[](int i)
	{
		//индексация
		if (i<0 || i>num) return NULL;
		int k = 0;
		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T>* cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}
	template<class T> friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj);
	template<class T> friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj);
};


template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}
	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL;
		current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";
	return ustream;
}
template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{
	//чтение из файла и консоли совпадают
	int len;
	ustream >> len;
	//здесь надо очистить память под obj, установить obj.num = 0
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

//Класс перегрузок итераторов
template<typename ValueType>
class ListIterator : public iterator<input_iterator_tag, ValueType>
{
private:
	Element<ValueType>* ptr;
public:
	ListIterator() { ptr = NULL; }
	ListIterator(ValueType* p) { ptr = p; }
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }

	bool operator!=(ListIterator const& other) const {
		return ptr != other.ptr;
	}
	bool operator==(ListIterator const& other) const {
		return ptr == other.ptr;
	}//need for BOOST_FOREACH
	Element<ValueType>& operator*()
	{
		if (ptr == NULL) throw "ptr isn't connected with something element";
		return *ptr;
	}
	ListIterator& operator++() {
		ptr = ptr->getNext();
		if (ptr == NULL) throw "ptr is empty";
		return *this;
	}
	//В этом случае только возвращаем следующее значение, текущее не меняем
	ListIterator& operator++(int v) {
		if (ptr->getNext() == NULL) throw "ptr is empty";
		ListIterator res(ptr->getNext());
		return res;
	}
	ListIterator& operator--() {
		ptr = ptr->getPrevious();
		if (ptr == NULL) throw "ptr is empty";
		return *this;
	}
	ListIterator& operator--(int v) {
		if (ptr->getPrev() == NULL) throw "ptr is empty";
		ListIterator res(ptr->getPrev());
		return res;
	}
	ListIterator& operator=(const ListIterator& it) {
		ptr = it.ptr;
		if (ptr == NULL) throw "ptr is empty";
		return *this;
	}
	ListIterator& operator=(Element<ValueType>* p) {
		ptr = p;
		if (ptr == NULL) throw "ptr is empty";
		return *this;
	}
};

template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
	IteratedLinkedList() : LinkedListParent<T>() {
		cout << "\nIteratedLinkedList constructor";
	}

	virtual ~IteratedLinkedList() {
		cout << "\nIteratedLinkedList destructor";
	}
	ListIterator<T> begin() {
		ListIterator<T> it = LinkedListParent<T>::head; return it;
	}
	ListIterator<T> end() {
		ListIterator<T> it = LinkedListParent<T>::tail; return it;
	}
};

//Класс D
template <class T>
class D : public IteratedLinkedList<T> {
public:
	D() : IteratedLinkedList<T>() { cout << "\nD constructor"; };
	~D() { cout << "\nD destructor"; }

	//добавление элемента с учетом упорядоченности
	ListIterator<T> push(T& value) {
		ListIterator<T> nextelement;
		if (this->head == NULL && this->tail == NULL)
		{
			//пустой список
 			Element<T>* newelement = new Element<T>(value);
			this->head = this->tail = newelement;
			if (this->head == NULL)
				throw "\nNo memory";
		}
		else
		{
			nextelement = IteratedLinkedList<T>::begin();
			while (nextelement != IteratedLinkedList<T>::end()) {
				if (value > (*nextelement).getValue()) {
					Element<T>* newelement = new Element<T>(value);

					(*(nextelement++)).setPrevious(newelement);
					(*nextelement).setNext(newelement);
					break;
				}
				++nextelement;
			}
		}
		return nextelement;
	}

	//Извлечение элемента из конца списка
	ListIterator<T> pop() {
		if (IteratedLinkedList<T>::head == NULL && IteratedLinkedList<T>::tail == NULL) {
			throw "The list is empty";
		}
		else {
			ListIterator<T> temp = IteratedLinkedList<T>::end();
			--(IteratedLinkedList<T>::tail);
			IteratedLinkedList<T>::tail->setNext(NULL);

			return temp;
		}
	}
};

template <class T>
class ChildrenD : public D<T> {

	ListIterator<T> push(Element<T>& element) override {
		ListIterator<T> nextelement = IteratedLinkedList<T>::begin();
		if (nextelement == NULL) {
			IteratedLinkedList<T>::head = new Element[element];
		}
		while (nextelement != IteratedLinkedList<T>::end()) {
			if (element->getValue() > (*nextelement).getValue()) {
				element->setPrevious(&(*nextelement));
				element->setNext(*(nextelement++));

				(*(nextelement++)).setPrevious(element);
				(*nextelement).setNext(element);
				break;
			}
			++nextelement;
		}
		return nextelement;
	}
};

//Функция фильтра по условию предиката
template<template <typename> class gettype, typename T>
D<T> filter(gettype<T>& lst, bool(*pred)(const T&)) {
	D<T> result;
	typename gettype<T>::iterator it = lst.begin();
	while (it != lst.end())
	{
		if (pred(*it)) { result.push(*it); }
		it++;
	}
	return result;
}

template<class T, class resulttype>
resulttype universalfilter(IteratedLinkedList<T>* lst, resulttype (*pred)(const T&)) {
	return pred(lst);
}


int main()
{
	try {
		Human h1;
		Human h2;
		Human h3;
		D<Human> humans;
		humans.push(h1);
		humans.push(h2);
		humans.push(h3);

	}
	catch (const char* error) { cout << error; };
}
