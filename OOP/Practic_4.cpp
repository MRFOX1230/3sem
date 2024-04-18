//Задание 4.1
//Создайте класс «Декартово дерево» («Курево»).Реализуйте операции
//объединения деревьев merge(), разрезания деревьев по ключу split().При
//выполнении операции L.Merge(R) предполагается, что в левом дереве L все
//ключи меньше любого ключа из правого дерева R.
// 
//Чтобы операция split() корректно использовала слияние деревьев,
//введите в дерево обработку указателя родителя parent в каждой операции,
//операцию successor() (получение следующего элемента по возрастанию
//ключа), итератор по дереву(с перегрузкой операций++, *) и функции
//min() / max() – получение минимального / максимального элемента в дереве или
//поддереве по ключу.В операции split() элементы левого дерева перечислять
//от минимума до элемента - разделителя, в правом дереве – от разделителя до
//максимума(в операции разделения деревьев split() элементы должны
//перечисляться в порядке увеличения ключа, чтобы слияние с деревом результатом было корректным).
// 
//Приоритет и ключи можно считать целыми числами.

//Задание 4.2
//Создайте класс «Декартово дерево по неявному ключу», унаследовав
//его с ключевым словом protected от класса из задания 4.1.Переопределите
//слияние деревьев(работает так же, как merge() в родителе, но без учёта
//ключей).
// 
//Введите групповую функции size() – число элементов в дереве, корнем
//которого является текущий узел.
// 
//Переопределите разделение дерева split() так, чтобы оно работало по
//значению групповой функции size().
// 
//Введите поддержку групповой функции на отрезке массива, указанной в
//варианте(см.таблицу 4.1), с учётом отложенного исполнения команд.
// 
//Продемонстрируйте применение построенной структуры данных для
//быстрого выполнения групповой операции на массиве вещественных чисел
//(приоритет можно считать целым числом).

//Вариант 26 - 2k+2 (минимум)


#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <chrono> // для функций из std::chrono
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include <set>
#include <unordered_set>
#include <queue>

#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

class Exception : public exception
{
protected:
	char* str;
public:
	//конструкторы и деструктор
	Exception(const char* s) {
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e) {
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception() { if (str != "\0") { delete[] str; } }

	virtual void print() { cout << "Exception: " << str << endl; }
};
//класс узел
class Node
{
private:
	//закрытые переменные Node N; N.key = 10 вызовет ошибку
	double key;
	int priority;
	int size;
	double min;
	//не можем хранить Node, но имеем право хранить указатель
	Node* left;
	Node* right;
	Node* parent;
public:
	//доступные извне переменные и функции
	double getKey() { return key; }
	int getPriority() { return priority; }
	int getSize() { return size; }
	double getMin() { return min; }

	void setSize(int s) { size = s; }
	void setMin(double m) { min = m; }

	Node* getLeft() { return left; }
	Node* getRight() { return right; }
	Node* getParent() { return parent; }

	void setLeft(Node* N) { left = N; }
	void setRight(Node* N) { right = N; }
	void setParent(Node* N) { parent = N; }

	//конструктор устанавливает стартовые значения для указателей
	Node(double k, int p)
	{
		key = k;
		priority = p;
		size = 1;
		min = k;
		left = right = NULL;
		parent = NULL;
	}

	Node(double k)
	{
		key = k;
		srand(time(NULL));
		priority = rand();
		size = 1;
		min = k;
		left = right = NULL;
		parent = NULL;
	}

	Node()
	{
		key = 0;
		priority = 0;
		size = 0;
		min = 0;
		left = right = NULL;
		parent = NULL;
	}

	bool operator<=(Node const& other) const { return key <= other.key; }
	bool operator==(Node const& other) const { return key == other.key; }

	Node* successor()
	{
		Node* Current = this;
		if (right != NULL) //if(right)
		{
			for (Current = right; Current->getLeft() != NULL; Current = Current->getLeft());
			return Current;
		}
		else
		{
			int val = Current->getKey();
			while (Current->getParent() != NULL)
			{
				if (Current->getParent()->getKey() > val)
					return Current->getParent();
				Current = Current->getParent();
			}
			return NULL;
		}
	}
	Node* predecessor()
	{
		Node* Current = this;
		if (left != NULL)
		{
			for (Current = left; Current->getRight() != NULL; Current = Current->getRight());
			return Current;
		}
		else
		{
			double val = Current->getKey();
			if (Current->getParent() != NULL && Current->getParent()->getKey() < val)
				return Current->getParent();
			while (Current->getParent() != NULL)
			{
				Current = Current->getParent();
				if (Current->getKey() < val) return Current;
			}
			if (val < Current->getKey()) return NULL;
			return Current;
		}
	}

	friend ostream& operator<<(ostream& stream, Node& N);
};

ostream& operator<<(ostream& stream, Node& N)
{
	stream << N.key << "; " << N.priority << "\n";
	if (N.getLeft() != NULL)
		stream << *N.getLeft();
	if (N.getRight() != NULL)
		stream << *N.getRight();
	return stream;
}

//Класс перегрузок итераторов
class TreapIterator : public std::iterator<std::input_iterator_tag, int, int>
{
private:
	Node* ptr;
public:
	TreapIterator() { ptr = NULL; }
	TreapIterator(Node* p) { ptr = p; }
	TreapIterator(const TreapIterator& it) { ptr = it.ptr; }

	TreapIterator& operator=(const TreapIterator& it) { ptr = it.ptr; return *this; }
	TreapIterator& operator=(Node* p) { ptr = p; return *this; }

	bool operator!=(TreapIterator const& other) const { return ptr != other.ptr; }
	bool operator==(TreapIterator const& other) const { return *ptr == *other.ptr; }
	bool operator<=(TreapIterator const& other) const { return *ptr <= *other.ptr; }
	Node& operator*() { return *ptr; }
	Node* operator&() { return ptr; }
	TreapIterator& operator++() //++p
	{
		if (ptr != NULL)
			ptr = ptr->successor();
		return *this;
	}
	TreapIterator operator++(int v)
	{
		Node* previous = ptr;
		if (ptr != NULL)
			ptr = ptr->successor();
		return TreapIterator(previous);
	}
	TreapIterator& operator--() //--p
	{
		if (ptr != NULL)
			ptr = ptr->predecessor();
		return *this;
	}
	TreapIterator operator--(int v)
	{
		Node* next = ptr;
		if (ptr != NULL)
			ptr = ptr->predecessor();
		return TreapIterator(next);
	}
};


//класс дерево
class Treap
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node* root;

	Node* merge(Node* L, Node* R)
	{
		if (L->getPriority() > R->getPriority())
		{
			if (L->getRight() != NULL)
				L->setRight(merge(L->getRight(), R));
			else
			{
				L->setRight(R);
				R->setParent(L);
			}
		}
		else
		{
			if (R->getLeft() != NULL)
				R->setLeft(merge(L, R->getLeft()));
			else
			{
				R->setLeft(L);
				R->setParent(L->getParent());
				L->setParent(R);
			}
			L = R;
		}
		return L;
	}

	Node* split(Node* Current, double x, Treap* Left, Treap* Right)
	{
		if (root == NULL || Current == NULL)
		{
			Left = NULL;
			Right = NULL;
			return NULL;
		}

		TreapIterator it;
		for (it = this->begin(); (*it).getKey() < x; it++)
		{
			Left->Merge((*it).getKey(), (*it).getPriority());
		}

		Node* out;
		if ((*it).getKey() == x)
		{
			out = &it;
			it++;
		}
		else
			out = NULL;

		for (it; it != NULL; it++)
		{
			Right->Merge((*it).getKey(), (*it).getPriority());
		}
		root = NULL;
		return out;
	}
public:

	TreapIterator begin() { return TreapIterator(Min()); }
	TreapIterator end() { return TreapIterator(Max()); }

	//доступ к корневому элементу
	Node* getRoot() { return root; }
	void setRoot(Node* r) { root = r; }
	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Treap() { root = NULL; }

	void PreOrder(Node* N, void (*f)(Node*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}

	void Merge(Node* N)
	{
		Treap* R = new Treap();
		R->root = N;
		Merge(R);
	}

	void Merge(double key, int prior)
	{
		Node* N = new Node(key, prior);
		Merge(N);
	}

	void Merge(Treap* R)
	{
		if (root == NULL) { root = R->root; return; }
		if (R->root == NULL) return; //this;

		if (root->getPriority() > R->root->getPriority())
		{
			if (root->getRight() != NULL)
				root->setRight(merge(root->getRight(), R->root));
			else
			{
				root->setRight(R->root);
				R->root->setParent(root);
			}
		}
		else
		{
			if (R->root->getLeft() != NULL)
				R->root->setLeft(merge(root, R->root->getLeft()));
			else
			{
				R->root->setLeft(root);
				R->root->setParent(root->getParent());
				root->setParent(R->root);
			}
			root = R->root;
		}
	}

	Node* Split(int x, Treap* Left, Treap* Right)
	{
		return split(root, x, Left, Right);
	}

	Node* Min()
	{
		Node* n = root;
		if (root == NULL)
			return NULL;
		while (n->getLeft() != NULL)
			n = n->getLeft();
		return n;
	}

	Node* Max()
	{
		Node* n = root;
		if (root == NULL)
			return NULL;
		while (n->getRight() != NULL)
			n = n->getRight();
		return n;
	}

	friend ostream& operator<<(ostream& stream, Treap& T);
};

ostream& operator<<(ostream& stream, Treap& T)
{
	if (T.root != NULL)
		stream << *T.root;
	return stream;
}

class ImplicitTreap : protected Treap
{
protected:
	Node* merge(Node* L, Node* R)
	{
		if (!L || !R)
			return L ? L : R;
		if (L->getPriority() > R->getPriority())
		{
			L->setRight(merge(L->getRight(), R));
			Update(L);
			return L;
		}
		else
		{
			R->setLeft(merge(L, R->getLeft()));
			Update(R);
			return R;
		}
	}
	pair<Node*, Node*> split(Node* Current, double x)
	{
		if (Current == NULL)
			return { NULL, NULL };
		if (Size(Current) <= x)
		{
			root = NULL;
			return { Current, NULL };
		}
		if (x == 0)
		{
			root = NULL;
			return { NULL, Current };
		}
		if (Size(Current->getLeft()) >= x)
		{
			auto res = split(Current->getLeft(), x);
			Current->setLeft(res.second);
			Update(Current);
			return { res.first, Current };
		}
		else
		{
			auto res = split(Current->getRight(), x - Size(Current->getLeft()) - 1);
			Current->setRight(res.first);
			Update(Current);
			return { Current, res.second };
		}
	}
public:
	ImplicitTreap() : Treap() {}

	virtual ~ImplicitTreap() {}

	Node* getRoot()
	{
		return Treap::getRoot();
	}

	int Size(Node* root)
	{
		if (root)
			return root->getSize();
		else
			return 0;
	}

	double GetMin(Node* root)
	{
		if (root != NULL) { return root->getMin(); }
		return INFINITY;
	}

	void Update(Node* root)
	{
		if (root == NULL)
			return;
		root->setMin(min(root->getKey(), min(GetMin(root->getLeft()), GetMin(root->getRight()))));
		root->setSize(Size(root->getLeft()) + Size(root->getRight()) + 1);
	}

	void Merge(double key, int prior)
	{
		Node* N = new Node(key, prior);
		root = merge(getRoot(), N);
	}

	void Merge(Node* N)
	{
		root = merge(getRoot(), N);
	}

	pair<Node*, Node*> Split(double x)
	{
		return split(root, x);
	}

	int MinInSegment(int l, int r)
	{
		pair<Node*, Node*> p1;
		pair<Node*, Node*> p2;
		p1 = split(root, r);
		p2 = split(p1.first, l);
		int res = GetMin(p2.second);
		root = merge(p2.first, merge(p2.second, p1.second));
		return res;
	}
	friend ostream& operator<<(ostream& stream, ImplicitTreap& T);
};

ostream& operator<<(ostream& stream, ImplicitTreap& T)
{
	if (T.getRoot() != NULL)
		stream << *T.getRoot();
	return stream;
}
void print(Node* N) { cout << N->getKey() << "; " << N->getPriority(); }



int main()
{
	Treap T;
	ImplicitTreap IT;
	int arr[15];
	int i = 0;

	//заполнение дерева
	for (i = 0; i < 15; i++) arr[i] = (int)(100 * sin(15 * double(i)));
	cout << "------------------------------";
	cout << "\nArray:\n";
	for (i = 0; i < 15; i++)
	{
		//T.insert(i, arr[i]); 
		T.Merge(i, arr[i]);
		IT.Merge(i, arr[i]);
		cout << "(" << i << "; " << arr[i] << ")\n";
		//cout << "\n---\n" << i << "\n" << T;
	}
	cout << endl << "Treap:\n" << T;
	cout << "------------------------------";
	cout << "\ninserted\n";
	cout << T;
	Treap T1, T2;
	Node* N = T.Split(5, &T1, &T2);
	cout << "-------------------" << "\nLeft treap:\n" << T1;
	cout << "-------------------" << "\nRight treap:\n" << T2;
	cout << "----------------------";
	if (N != NULL)
		cout << "\nNode: " << *N;

	cout << endl << "ImplicitTreap:\n" << IT;
	//pair<Node*, Node*> p;
	//ImplicitTreap IT1, IT2;
	//p = IT.Split(6);
	//IT1.Merge(p.first);
	//IT2.Merge(p.second);
	//cout << "-------------------" << "\nLeft ImplicitTreap:\n" << IT1;
	//cout << "-------------------" << "\nRight ImplicitTreap:\n" << IT2;
	
	//Демонстрация работы групповой функции
	cout << "\n---\nMinimum in segment:\n" << IT.MinInSegment(3, 5);

	char c; cin >> c;
	return 0;
}