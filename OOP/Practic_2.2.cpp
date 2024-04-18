#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <string>
using namespace std;

//Вариант 26 (четный вариант, 
//			  элементы с одинаковыми ключами храняться справа в классе из задачи 2.4)

class Human {
protected:
	string pseudoname;
	string address;
	int age;
	int numoffriends;
	string interests;
	string favquote;
public:
	//Конструкторы
	Human() {
		pseudoname = "Pseudo"; address = "Moscow"; age = 27; numoffriends = 100;
		interests = "bowling"; favquote = "your advertisement could be here";
	}
	Human(const string& pm, const string& as, int ag, int ns, const string& inter, const string& fav) {
		pseudoname = pm; address = as; age = ag; numoffriends = ns;
		interests = inter; favquote = fav;
	}

	//Геттеры
	int getNumFriends() { return numoffriends; }
	string getPseudoname() { return pseudoname; }

	string getAddress() { return address; }
	int getAge() { return age; }
	string getInterests() { return interests; }
	string getFavqote() { return favquote; }

	string getKey() { return pseudoname; }
};

//функция для сравнения ключей (псевдонимов) в классе "Human"
bool CompareKeys(Human human, string key) {
	if (human.getPseudoname() == key) return 1;
	return 0;
}


//Перегрузки операторов
//сравнения нужны, чтобы значение псевднима работало как ключ
bool operator< (Human value1, Human value2) {
	if (value1.getPseudoname() < value2.getPseudoname()) return 1;
	return 0;
}
bool operator> (Human value1, Human value2) {
	if (value1.getPseudoname() > value2.getPseudoname()) return 1;
	return 0;
}

bool operator<= (Human value1, Human value2) {
	if (value1.getPseudoname() <= value2.getPseudoname()) return 1;
	return 0;
}
bool operator>= (Human value1, Human value2) {
	if (value1.getPseudoname() >= value2.getPseudoname()) return 1;
	return 0;
}

bool operator== (Human value1, Human value2) {
	if (value1.getNumFriends() == value2.getNumFriends() and
		value1.getPseudoname() == value2.getPseudoname() and
		value1.getAddress() == value2.getAddress() and
		value1.getAge() == value2.getAge() and
		value1.getInterests() == value2.getInterests() and
		value1.getFavqote() == value2.getFavqote()) { return 1; }
	return 0;
}

bool operator!= (Human value1, Human value2) {
	if (value1.getNumFriends() == value2.getNumFriends() and
		value1.getPseudoname() == value2.getPseudoname() and
		value1.getAddress() == value2.getAddress() and
		value1.getAge() == value2.getAge() and
		value1.getInterests() == value2.getInterests() and
		value1.getFavqote() == value2.getFavqote()) {
		return 0;
	}
	return 1;
}

ostream& operator<< (ostream& stream, Human& user) {
	stream << "Pseudoname: " << user.getPseudoname() << "\n";
	stream << "Friends: " << user.getNumFriends() << "\n";

	stream << "Address: " << user.getAddress() << "\n";
	stream << "Age: " << user.getAge() << "\n";
	stream << "Interests: " << user.getInterests() << "\n";
	stream << "Quote: " << user.getFavqote() << "\n";

	return stream;
}



//узел
template<class T>
class Node
{
protected:
	T data;
	//не можем хранить Node, но имеем право хранить указатель
	Node* left;
	Node* right;
	Node* parent;
	int height;

	//ключ - псевдоним пользователя, который можно получить из data
public:
	//доступные извне переменные и функции
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }
	int getHeight() { return height; }
	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }
	virtual void setLeft(Node * N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }

	//Конструктор. Устанавливаем стартовые значения для указателей
	Node<T>(T n)
	{
		data = n;
		left = right = parent = NULL;
		height = 1;
	}
	Node<T>()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		height = 1;
	}
	virtual void print()
	{
		cout << "\n" << data;
	}
	virtual void setHeight(int h)
	{
		height = h;
	}

	Node* successor()
	{
		Node<T>* Current = this;
		if (right != NULL)
		{
			for (Current = right; Current->getLeft() != NULL; Current = Current->getLeft());
			return Current;
		}
		else
		{
			T val = Current->getData();
			if (Current->getParent() != NULL && Current->getParent()->getData() > val)
				return Current->getParent();
			while (Current->getParent() != NULL)
			{
				Current = Current->getParent();
				if (Current->getData() > val) return Current;
			}
			if (val > Current->getData()) return NULL;
			return Current;
		}
	}
	Node<T>* predecessor()
	{
		Node<T>* Current = this;
		if (left != NULL)
		{
			for (Current = left; Current->getRight() != NULL; Current = Current->getRight());
			return Current;
		}
		else
		{
			T val = Current->getData();
			if (Current->getParent() != NULL && Current->getParent()->getData() > val)
				return Current->getParent();
			while (Current->getParent() != NULL)
			{
				Current = Current->getParent();
				if (Current->getData() > val) return Current;
			}
			if (val > Current->getData()) return NULL;
			return Current;
		}
	}
	template<class T> friend ostream& operator<< (ostream& stream, Node<T>& N);
	template<class T> friend ostream& operator<< (ostream& stream, Node<T>* N);
};
template<class T>
bool operator> (Node<T>& N1, Node<T>& N2)
{
	if (N1.getData() > N2.getData()) { return 1; }
	return 0;
}
template<class T>
bool operator< (Node<T>& N1, Node<T>& N2)
{
	if (N1.getData() < N2.getData()) { return 1; }
	return 0;
}
template<class T>
bool operator== (Node<T>& N1, Node<T>& N2)
{
	if (N1.getData() == N2.getData()) { return 1; }
	return 0;
}


template<class T>
ostream& operator<< (ostream& stream, Node<T>& N)
{
	stream << "\n" << "\nNode data============" << "\nHeight:" << N.height << "\n" << N.data << "=====================";
	return stream;
}
template<class T>
ostream& operator<< (ostream& stream, Node<T>* N)
{
	stream << "\n" << "\nNode data============" << "\nHeight:" << N->height << "\n" << N->data << "=====================";
	return stream;
}

template<class T>
void print(Node<T>* N) {
	cout << "\n" << N->getData();
}

//Дерево
template<class T>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<T>* root;
public:
	//доступ к корневому элементу
	virtual Node<T>* getRoot() { return root; }
	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree<T>() { root = NULL; }
	//рекуррентная функция добавления узла. Устроена аналогично, 
	// но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* Add_R(Node<T>* N)
	{
		return Add_R(N, root);
	}
	virtual Node<T>* Add_R(Node<T>* N, Node<T>* Current)
	{
		if (N == NULL) return NULL;
		if (root == NULL) { root = N; return N; }
		if (Current->getData() > N->getData())
		{
			//идем влево
			if (Current->getLeft() != NULL)
				Current->setLeft(Add_R(N, Current -> getLeft()));
			else
				Current->setLeft(N);
			Current->getLeft()->setParent(Current);
		}
		if (Current->getData() < N->getData())
		{
			//идем вправо
			if (Current->getRight() != NULL)
				Current->setRight(Add_R(N, Current->getRight()));
			else
				Current->setRight(N);
			Current->getRight()->setParent(Current);
		}
		if (Current->getData() == N->getData()) { 
			throw "Such an element already exists in the tree";}
		//для несбалансированного дерева поиска
		return Current;
	}

	//Функция для добавления нового элемента в ветвь дерева. Делаем новый узел с
	//этими данными и вызываем нужную функцию добавления в дерево
	virtual void Add(T newelement)
	{
		Node<T>* N = new Node<T>;
		N->setData(newelement);
		Add_R(N);
	}

	virtual Node<T>* Min(Node<T>* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) return NULL;
		if (Current == NULL)
			Current = root;
		while (Current->getLeft() != NULL)
			Current = Current->getLeft();
		return Current;
	}
	virtual Node<T>* Max(Node<T>* Current = NULL)
	{
		//максимум - это самый "правый" узел. Идём по дереву всегда вправо
		if (root == NULL) return NULL;
		if (Current == NULL)
			Current = root;
		while (Current->getRight() != NULL)
			Current = Current->getRight();
		return Current;
	}

	//Поиск по значению
	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<T>* Find(T data, Node<T>* Current)
	{
		//база рекурсии
		if (Current == NULL) return NULL;
		if (Current->getData() == data) return Current;
		//рекурсивный вызов
		if (Current->getData() > data) return Find(data, Current->getLeft());
		if (Current->getData() < data) return Find(data, Current->getRight());
	}
	virtual Node<T>* SearchByValue(T data)
	{
		Node<T>* result = Find(data, root);
		if (result == NULL) { throw "There isn't so value in the tree"; }
		return result;
	}


	//Поиск по ключу
	template<typename KeyType>
	Node<T>* FindKey(KeyType searchkey, Node<T>* Current) {
		//база рекурсии
		if (Current == NULL) return NULL;
		if (Current->getData().getKey() == searchkey) return Current;
		//рекурсивный вызов
		if (Current->getData().getKey() > searchkey) return FindKey(searchkey, Current->getLeft());
		if (Current->getData().getKey() < searchkey) return FindKey(searchkey, Current->getRight());
	}
	template<typename KeyType>
	Node<T>* SearchByKey(KeyType searchkey) {
		Node<T>* result = FindKey(searchkey, root);
		if (result == NULL) { throw "There isn't so key in the tree"; }
		return result;
	}


	//три обхода дерева
	virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}
	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);
	}
	virtual void PostOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}

	//удаление узла
	virtual Node<T>* Remove(Node<T>* N)
	{
		Node<T>* N1 = N;
		Node<T>* Parent = N->getParent();
		Node<T>* Left = N->getLeft();
		Node<T>* Right = N->getRight();
		if (Right == NULL && Left == NULL)
		{
			if (Parent != NULL)
				(Parent->getData() > N->getData()) ? Parent->setLeft(NULL) : Parent->setRight(NULL);
			return N1;
		}
		else if (Right != NULL && Left != NULL)
		{
			T val = N->successor()->getData();
			Remove(N->successor());
			N->setData(val);
			return N1;
		}
		else
		{
			Node<T>* child = (Right == NULL) ? Left : Right;
			if (Right == NULL)
			{
				if (Parent != NULL)
				{
					(Parent->getData() > N->getData()) ? Parent->setLeft(Left) : Parent->setRight(Left);
					Left->setParent(Parent);
					return N1;
				}
				Left->setParent(NULL);
				root = Left;
				return N1;
			}
			if (Left == NULL)
			{
				if (Parent != NULL)
				{
					(Parent->getData() > N->getData()) ? Parent->setLeft(Right) : Parent->setRight(Right);
					Right->setParent(Parent);
					return N1;
				}
				Right->setParent(NULL);
				root = Right;
				return N1;
			}
		}
		return N1;
	}
};







//Дочерний класс от Tree для задачи 2.4
template<typename T>
class MultiTree : public Tree<T>
{
public:
	MultiTree<T>() : Tree<T>() {};
	Node<T>* root = this->root;
	virtual Node<T>* getRoot() { return root; }
	
	// в данном классе можем добавлять в дерево одинаковые элементы
	virtual Node<T>* Add_R(Node<T>* N)
	{
		return Add_R(N, root);
	}
	virtual Node<T>* Add_R(Node<T>* N, Node<T>* Current)
	{
		if (N == NULL) return NULL;
		if (root == NULL) { root = N; return N; }
		if (Current->getData() > N->getData())
		{
			//идем влево
			if (Current->getLeft() != NULL)
				Current->setLeft(Add_R(N, Current->getLeft()));
			else
				Current->setLeft(N);
			Current->getLeft()->setParent(Current);
		}
		// в этом моменте класс отличается от обычного Tree, так как одинаковые значения храняться
		// с правой стороны
		if (Current->getData() <= N->getData())
		{
			//идем вправо
			if (Current->getRight() != NULL)
				Current->setRight(Add_R(N, Current->getRight()));
			else
				Current->setRight(N);
			Current->getRight()->setParent(Current);
		}
		//для несбалансированного дерева поиска
		return Current;
	}
	virtual void Add(T newelement)
	{
		Node<T>* N = new Node<T>;
		N->setData(newelement);
		Add_R(N);
	}

	template<typename KeyType>
	vector<T> operator[] (KeyType key) {
		return SearchByKey(key);
	}

	virtual Node<T>* Min(Node<T>* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) return NULL;
		if (Current == NULL)
			Current = root;
		while (Current->getLeft() != NULL)
			Current = Current->getLeft();
		return Current;
	}
	virtual Node<T>* Max(Node<T>* Current = NULL)
	{
		//максимум - это самый "правый" узел. Идём по дереву всегда вправо
		if (root == NULL) return NULL;
		if (Current == NULL)
			Current = root;
		while (Current->getRight() != NULL)
			Current = Current->getRight();
		return Current;
	}

	//Поиск по значению
	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<T>* Find(T data, Node<T>* Current)
	{
		//база рекурсии
		if (Current == NULL) return NULL;
		if (Current->getData() == data) return Current;
		//рекурсивный вызов
		if (Current->getData() > data) return Find(data, Current->getLeft());
		if (Current->getData() < data) return Find(data, Current->getRight());
	}
	virtual Node<T>* SearchByValue(T data)
	{
		Node<T>* result = Find(data, root);
		if (result == NULL) { throw "There isn't so value in the tree"; }
		return result;
	}


	//Поиск по ключу
	template<typename KeyType>
	Node<T>* FindKey(KeyType searchkey, Node<T>* Current) {
		//база рекурсии
		if (Current == NULL) return NULL;
		if (Current->getData().getKey() == searchkey) return Current;
		//рекурсивный вызов
		if (Current->getData().getKey() > searchkey) return FindKey(searchkey, Current->getLeft());
		if (Current->getData().getKey() < searchkey) return FindKey(searchkey, Current->getRight());
	}
	template<typename KeyType>
	vector<T> SearchByKey(KeyType searchkey) {
		vector<T> result;
		Node<T>* foundvalue = FindKey(searchkey, root);
		if (foundvalue == NULL) { throw "There isn't so key in the tree"; }

		while (1) {
			result.push_back(foundvalue->getData());
			foundvalue = FindKey(searchkey, foundvalue->getRight());
			if (foundvalue == NULL) { break; }
		}
		return result;
	}


	//три обхода дерева
	virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}
	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);
	}
	virtual void PostOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}

	//удаление узла
	virtual Node<T>* Remove(Node<T>* N)
	{
		Node<T>* N1 = N;
		Node<T>* Parent = N->getParent();
		Node<T>* Left = N->getLeft();
		Node<T>* Right = N->getRight();
		if (Right == NULL && Left == NULL)
		{
			if (Parent != NULL)
				(Parent->getData() > N->getData()) ? Parent->setLeft(NULL) : Parent->setRight(NULL);
			return N1;
		}
		else if (Right != NULL && Left != NULL)
		{
			T val = N->successor()->getData();
			Remove(N->successor());
			N->setData(val);
			return N1;
		}
		else
		{
			Node<T>* child = (Right == NULL) ? Left : Right;
			if (Right == NULL)
			{
				if (Parent != NULL)
				{
					(Parent->getData() > N->getData()) ? Parent->setLeft(Left) : Parent->setRight(Left);
					Left->setParent(Parent);
					return N1;
				}
				Left->setParent(NULL);
				root = Left;
				return N1;
			}
			if (Left == NULL)
			{
				if (Parent != NULL)
				{
					(Parent->getData() > N->getData()) ? Parent->setLeft(Right) : Parent->setRight(Right);
					Right->setParent(Parent);
					return N1;
				}
				Right->setParent(NULL);
				root = Right;
				return N1;
			}
		}
		return N1;
	}
};

template<class T>
class AVL_Tree : public Tree<T>
{
protected:
	//определение разности высот двух поддеревьев
	int bfactor(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		return (hr - hl);
	}

	//при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
	//после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
	//значение могло поменяться
	void fixHeight(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		p->setHeight((hl > hr ? hl : hr) + 1);
	}

	//краеугольные камни АВЛ-деревьев - процедуры поворотов
	Node<T>* RotateRight(Node<T>* p) // правый поворот вокруг p
	{
		Node<T>* q = p->getLeft();

		p->setLeft(q->getRight());
		q->setRight(p);

		if (p == Tree<T>::root)
			Tree<T>::root = q;
		else
		{
			if (p->getParent()->getLeft() == p)
				p->getParent()->setLeft(q);
			else
				p->getParent()->setRight(q);
		}

		q->setParent(p->getParent());
		p->setParent(q);
		if (p->getLeft() != NULL) p->getLeft()->setParent(p);

		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node<T>* RotateLeft(Node<T>* q) // левый поворот вокруг q
	{
		Node<T>* p = q->getRight();

		q->setRight(p->getLeft());
		p->setLeft(q);

		if (q == Tree<T>::root)
			Tree<T>::root = p;
		else
		{
			if (q->getParent()->getLeft() == q)
				q->getParent()->setLeft(p);
			else
				q->getParent()->setRight(p);
		}

		p->setParent(q->getParent());
		q->setParent(p);
		if (q->getRight() != NULL) q->getRight()->setParent(q);

		fixHeight(q);
		fixHeight(p);
		return p;
	}

	//балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
	Node<T>* Balance(Node<T>* p) // балансировка узла p
	{
		fixHeight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->getRight()) < 0) RotateRight(p->getRight());
			return RotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->getLeft()) > 0) RotateLeft(p->getLeft());
			return RotateRight(p);
		}

		return p; // балансировка не нужна
	}

public:
	//конструктор AVL_Tree вызывает конструктор базового класса Tree
	AVL_Tree<T>() : Tree<T>() {}

	virtual Node<T>* push_R(Node<T>* N)
	{
		return push_R(N, Tree<T>::root);
	}

	//рекуррентная функция добавления узла. Устроена аналогично, 
	//но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* push_R(Node<T>* N, Node<T>* Current)
	{
		//вызываем функцию Add_R из базового класса
		Node<T>* pushedNode = Tree<T>::Add_R(N, Current);
		//применяем к добавленному узлу балансировку
		if (Current != NULL)
			return Balance(Current);
		return pushedNode;
	}

	//Функция для добавления нового элемента. 
	//Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T>* push(T n)
	{
		Node<T>* N = new Node<T>;
		N->setData(n);
		return push_R(N);
	}

	//Удаление узла
	virtual Node<T>* Remove(Node<T>* N)
	{
		Node<T>* Parent = N->getParent();
		Tree<T>::Remove(N);
		for (; Parent != NULL; Parent = Parent->getParent())
			Balance(Parent);
		return N;
	}
};






//Класс перегрузок итераторов
template<typename ValueType>
class TreeIterator : public iterator<input_iterator_tag, ValueType>
{
private:
	Node<ValueType>* ptr;
public:
	TreeIterator() { ptr = NULL; }
	TreeIterator(Node<ValueType>* p) { ptr = p; }
	TreeIterator(const TreeIterator& it) { ptr = it.ptr; }

	TreeIterator& operator=(const TreeIterator& it) { ptr = it.ptr; return *this; }
	TreeIterator& operator=(Node<ValueType>* p) { ptr = p; return *this; }

	bool operator!=(TreeIterator const& other) const { return ptr != other.ptr; }
	bool operator==(TreeIterator const& other) const { return ptr == other.ptr; }
	Node<ValueType>& operator*() { return *ptr; }
	TreeIterator& operator++() //++p
	{
		if (ptr != NULL)
			ptr = ptr->successor();
		return *this;
	}
	TreeIterator operator++(int v)
	{
		Node<ValueType>* previous = ptr;
		if (ptr != NULL)
			ptr = ptr->successor();
		return TreeIterator<ValueType>(previous);
	}

	TreeIterator& operator--() //--p
	{
		if (ptr != NULL)
			ptr = ptr->predecessor();
		return *this;
	}
	TreeIterator operator--(int v)
	{
		Node<ValueType>* next = ptr;
		if (ptr != NULL)
			ptr = ptr->predecessor();
		return TreeIterator<ValueType>(next);
	}

};
template <class T>
class IteratedTree : public Tree<T>
{
public:
	IteratedTree<T>() : Tree<T>() {}
	IteratedTree<T>(Tree<T> tree) { this->root = tree.getRoot(); }


	TreeIterator<T> begin() { return TreeIterator<T>(Tree<T>::Min()); }
	TreeIterator<T> end() { return TreeIterator<T>(Tree<T>::Max()); }
};

template <class T>
class MultiIteratedTree : public MultiTree<T>
{
public:
	MultiIteratedTree<T>() : MultiTree<T>() {}
	MultiIteratedTree<T>(MultiTree<T> tree) { this->root = tree.getRoot(); }


	TreeIterator<T> begin() { return TreeIterator<T>(MultiTree<T>::Min()); }
	TreeIterator<T> end() { return TreeIterator<T>(MultiTree<T>::Max()); }
};
//класс итерируемое дерево поиска
template<class T>
class AVLIteratedTree : public AVL_Tree<T>
{
public:
	AVLIteratedTree<T>() : AVL_Tree<T>() {}

	TreeIterator<T> begin() { return TreeIterator<T>(AVL_Tree<T>::Min()); }
	TreeIterator<T> end() { return TreeIterator<T>(AVL_Tree<T>::Max()); }

	virtual TreeIterator<T> Find_data(T d, bool (*p)(T, Node<T>))
	{
		TreeIterator<T> it = this->begin();
		while (it != NULL)
		{
			if (p(d, *it))
				return it;
			++it;
		}
		throw "There isn't node with the data";
	}
};


//Дерево из задания 2.5
template<class T>
class Splay : public AVLIteratedTree<T>
{
public:
	Splay<T>() : AVLIteratedTree<T>() {}
	TreeIterator<T> begin() { return AVLIteratedTree<T>::begin(); }
	TreeIterator<T> end() { return AVLIteratedTree<T>::end(); }

	TreeIterator<T> find(T data)
	{
		if (Tree<T>::root == NULL) return NULL;
		Node<T>* found = Tree<T>::find(data);

		if (found == NULL) return TreeIterator<T>();
		found = Tree<T>::remove(found);
		if (data > Tree<T>::root->getValue())
			found->setLeft(Tree<T>::root);
		else
			found->setRight(Tree<T>::root);
		Tree<T>::root->setParent(found);
		Tree<T>::root = found;
		return TreeIterator<T>(Tree<T>::root);
	}


	template<typename KeyType>
	TreeIterator<T> splay(TreeIterator<T> root, KeyType key)
	{
		// root == NULL или ключ находится в корне 
		if (&(*root) == NULL || (*root).getData().getKey() == key)
			return root;

		// Ключ лежит в левом поддереве
		if ((*root).getData().getKey() > key)
		{
			// Ключа нет в дереве, мы закончили
			if ((*root).getLeft() == NULL)
				return root;

			// Zig-Zig (Левый-левый) 
			if ((*root).getLeft()->getData().getKey() > key)
			{
				// Сначала рекурсивно поднимем ключ как корень left-left
				(*root).getLeft()->setLeft(&(*(splay((*root).getLeft()->getLeft(), key))));

				// Первый разворот для root, второй разворот выполняется после else
				root = TreeIterator<T>(AVL_Tree<T>::RotateRight(&(*root)));
			}
			else if ((*root).getLeft()->getData().getKey() < key) // Zig-Zag (Левый-правый) 
			{
				// Сначала рекурсивно поднимаем ключ как корень left-right
				(*root).getLeft()->setRight(&(*(splay((*root).getLeft()->getRight(), key))));

				// Выполняем первый разворот для root->left
				if ((*root).getLeft()->getRight() != NULL)
					(*root).setLeft(AVL_Tree<T>::RotateLeft((*root).getLeft()));
			}

			// Выполняем второй разворот для корня
			return ((*root).getLeft() == NULL) ? root : TreeIterator<T>(AVL_Tree<T>::RotateRight(&(*root)));
		}
		else // Ключ находится в правом поддереве
		{
			// Ключа нет в дереве, мы закончили
			if ((*root).getRight() == NULL)
				return root;

			// Zag-Zig (Правый-левый) 
			if ((*root).getRight()->getData().getKey() > key)
			{
				// Поднять ключ как корень right-left 
				(*root).getRight()->setLeft(&(*(splay(TreeIterator<T>((*root).getRight()->getLeft()), key))));

				// Выполняем первый поворот для root->right
				if ((*root).getRight()->getLeft() != NULL)
					(*root).setRight(AVL_Tree<T>::RotateRight((*root).getRight()));
			}
			else if ((*root).getRight()->getData().getKey() < key)// Zag-Zag (Правый-правый) 
			{
				// Поднимаем ключ как корень right-right и выполняем первый разворот
				(*root).getRight()->setRight(&(*(splay((*root).getRight()->getRight(), key))));
				root = TreeIterator<T>(AVL_Tree<T>::RotateLeft((&(*root))));
			}

			// Выполняем второй разворот для root
			return ((*root).getRight() == NULL) ? root : TreeIterator<T>(AVL_Tree<T>::RotateLeft(&(*root)));
		}
	}

	template<typename KeyType>
	TreeIterator<T> insert(KeyType k, T data)
	{
		Tree<T>::push(k, data);
		return TreeIterator<T>(splay(TreeIterator<T>(Tree<T>::root), k));
	}

	template<typename KeyType>
	Node<T>* find_r(KeyType key, Node <T>* Current)
	{
		//база рекурсии
		if (Current == NULL) return NULL;

		if (Current->getData().getKey() == key) return Current;

		//рекурсивный вызов
		if (Current->getData().getKey() > key) return find_r(key, Current->getLeft());

		return find_r(key, Current->getRight());
	}

	template<typename KeyType>
	TreeIterator<T> findkey(KeyType key)
	{
		if (Tree<T>::root == NULL) return NULL;
		Node<T>* found = Tree<T>::root;
		if (key == found->getData().getKey())
			found = Tree<T>::SearchByKey(key);
		else
			found = find_r(key, Tree<T>::root);
		if (found == NULL) return TreeIterator<T>();
		return splay(TreeIterator<T>(Tree<T>::root), key);
	}
	template<typename KeyType>
	Node<T>* operator[](KeyType k)
	{
		Node<T>* result = &(*(findkey(k)));
		if (result == NULL) { throw "There isn't value with the key"; }
		return result;
	}
	virtual Node<T>* find_data(T data, bool (*f)(T, Node<T>))
	{
		Node<T>* found = NULL;
		if (f)
		{
			found = &(*(AVLIteratedTree<T>::Find_data(data, f)));
		}
		else
		{
			TreeIterator<T> it = begin();
			while (it != NULL)
			{
				found = &(*it);
				if (found->getData() == data)
					break;
				++it;
			}
		}
		if (found->getData() != data)
			throw "There is not node with this data";
		return &(*(splay(TreeIterator<T>(Tree<T>::root), (found->getData()).getKey())));
	}
};




//Вывод всего дерева
//поднимаясь вверх
template<typename T>
void printtreeUp(Tree<T> tree)
{
	IteratedTree<T> ittree(tree);
	TreeIterator<T> it = ittree.begin();
	cout << *it << endl;
	do {
		++it;
		cout << *it << endl;
	} while (it != ittree.end());
}
//спускаясь вниз
template<typename T>
void printtreeDown(Tree<T> tree)
{
	IteratedTree<T> ittree(tree);
	TreeIterator<T> it = ittree.end();
	cout << *it << endl;
	do {
		--it;
		cout << *it << endl;
	} while (it != ittree.begin());
}

//Вывод всего дерева (для MultiTree)
//поднимаясь вверх
template<typename T>
void printtreeUp(MultiTree<T> tree)
{
	MultiIteratedTree<T> ittree(tree);
	TreeIterator<T> it = ittree.begin();
	cout << *it << endl;
	do {
		++it;
		cout << *it << endl;
	} while (it != ittree.end());
}

//Вывод всего дерева (для Splay)
//поднимаясь вверх
template<typename T>
void printtreeUp(Splay<T> tree)
{
	AVLIteratedTree<T> ittree(tree);
	TreeIterator<T> it = ittree.begin();
	cout << *it << endl;
	do {
		++it;
		cout << *it << endl;
	} while (it != ittree.end());
}

////Функции поиска в дереве (как вариант, через итеораторы)
////по ключу
//template<typename T, typename KeyType>
//Node<T> SearchByKeyFunc(Tree<T> tree, KeyType searchkey, bool (*f)(T, KeyType)) {
//	IteratedTree<T> ittree(tree);
//	TreeIterator<T> it = ittree.begin();
//	do {
//		++it;
//		if (f((*it).getData(), searchkey)) return *it;
//	} while (it != ittree.end());
//	throw "There isn't so key";
//}
////по значению
//template<typename T>
//Node<T> SearchByValueFunc(Tree<T> tree, T searchvalue) {
//	IteratedTree<T> ittree(tree);
//	TreeIterator<T> it = ittree.begin();
//	do {
//		++it;
//		if ((*it).getData() == searchvalue) return *it;
//	} while (it != ittree.end());
//	throw "There isn't so value";
//}


int main()
{
	try {
		//MultiTree<Human> multiusers;
		//Human h1;
		//Human h2;
		//Human h3("Nik", "Izhevsk", 23, 209, "Dancing", "jdfh");
		//Human h4("Jagami", "London", 25, 250, "Work", "Example of phrase");
		//Human h5("Suzune", "San-Francisco", 25, 250, "Work", "Example of phrase");
		//Human h6("Suzune", "San-Francisco", 25, 250, "Work", "Example of phrase");
		//multiusers.Add(h1);
		//multiusers.Add(h2);
		//multiusers.Add(h3);
		//multiusers.Add(h4);
		//multiusers.Add(h5);
		//multiusers.Add(h6);
		//cout << "MultiTree:\n\n";
		//printtreeUp(multiusers);

		//cout << "\n\nFound values:\n";
		//vector<Human> found = multiusers.SearchByKey("Suzune");
		//for (int i = 0; i < found.size(); i++) {
		//	cout << found[i];
		//	cout << "\n";
		//}


		Splay<Human> users; // Mожно считать, что Splay это и есть AVL, так как использует те же функции
		Human h1;
		Human h2;
		Human h3("Nik", "Izhevsk", 23, 209, "Dancing", "jdfh");
		Human h4("Jagami", "London", 25, 250, "Work", "Example of phrase");
		Human h5("Suzune", "San-Francisco", 25, 250, "Work", "Example of phrase");
		users.Add(h1);
		users.Add(h3);
		users.Add(h4);
		users.Add(h5);
		 
		//users.Add(h2);
		//users.Add(h3);

		Node<Human>* node = users.find_data(h4, NULL);
		Human human = node->getData();
		cout << human;


		//string pseudoname;
		//string address;
		//int age;
		//int numoffriends;
		//string interests;
		//string favquote;





		//printtreeUp(users);
		//cout << *users["Jagami"];

		//Node<Human>* removeelement = users.SearchByKey<string>("Nik");
		//users.Remove(removeelement);
		//printtreeUp(users);
		//printtreeDown(users);
		return 0;
	}
	catch (const char* error) {
		cout << error;
	}
}


