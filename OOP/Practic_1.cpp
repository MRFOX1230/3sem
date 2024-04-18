//Вариант 26

//Задание 1.1
//Постройте связный список(используйте класс list библиотеки STL),
//который содержит объекты указанного в таблице 1.1 типа T.Постройте
//функции добавления push() и удаления pop() элементов таким образом, чтобы
//список оставался отсортированным при выполнении этих операций
//(допустимо удаление из начала контейнера, с конца и из произвольного
//места).Постройте функцию filter(), которая принимает предикат P(см. таблицу 1.1)
//и возвращает новый список с объектами, для которых предикат
//принимает истинное значение.Постройте функцию вывода содержимого
//списка с помощью итераторов.
// 
//Примечание: В этом задании не требуется создавать класс списка, нужно
//использовать класс list из библиотеки STL и написать отдельно требуемые
//функции(не методы класса).

//Тип T: Complex
//Услоовие предиката: Только комплексные числа с нечетной действительной и 
//мнимой частью. Сортировка по модулю комплексного числа.


//Задание 1.2
//Заполните список из пункта 1 объектами класса С (таблица 1.2),
//сохраняя убывание по приоритету : полю или группе полей, указанных в
//варианте.Функция pop() должна удалять объект из контейнера и возвращать
//как результат объект с наибольшим приоритетом(определяется по полям,
//указанным в третьем столбце таблицы 1.2: больший приоритет имеет объект
//с большим значением первого поля; если значение первого поля совпадает,
//то сравниваются значения второго поля и так далее).Если больший
//приоритет имеют объекты с меньшим значением поля(упорядоченность по
//возрастанию), это указано в скобках.
// 
//Пример из варианта 1: объекты недвижимости сортируются по
//убыванию цены.Если цена совпадает, то сравниваем по адресу, но для
//адреса уже используется упорядочение по возрастанию(“меньший” адрес -
//больший приоритет, строки сравниваются в лексикографическом порядке,
//“как в словаре”).

//Класс C:
//«Профиль в соц.сети».
//Минимальный набор полей : псевдоним, адрес страницы, возраст, количество друзей, интересы, любимая цитата.

//Приоритет: Количество друзей; псевдоним (по возрастанию)
#include <list>
#include <iostream>
#include <fstream>
#include <complex>
#include <math.h>
#include <typeinfo>
#include <string>
using namespace std;

//Задание 1.1

//Перегрузка операторов сравнения и вывода в консоль
//Для списка из задания 1.1
bool operator<(const complex<double>& value1, const complex<double>& value2) {
	if ((pow(value1.real(), 2) + pow(value1.imag(), 2)) < (pow(value2.real(), 2) + pow(value2.imag(), 2)))
		return 1;
	return 0;
}
bool operator>(const complex<double>& value1, const complex<double>& value2) {
	if ((pow(value1.real(), 2) + pow(value1.imag(), 2)) > (pow(value2.real(), 2) + pow(value2.imag(), 2)))
		return 1;
	return 0;
}
ostream& operator<<(ostream& stream, list<complex<double>>& lst) {
	list<complex<double>>::iterator it = lst.begin();
	while (it != lst.end())
	{
		stream << *it << "\n";
		it++;
	}
	return stream;
}

//Функция вставки элемента в список
template<class T>
void push(list<T>& lst, T& element) {
	typename list<T>::iterator it = lst.begin();
	while (it != lst.end())
	{
		if (*it > element) break;
		it++;
	}
	lst.insert(it, element);
}

////Функция удаления элемента из списка
//template<class T>
//void pop(list<T>& lst, T& element) {
//	typename list<T>::iterator it = lst.begin();
//	while (it != lst.end())
//	{
//		if (*it == element)
//			lst.erase(it);
//		break;
//		it++;
//	}
//	if (*it != element) throw "There isn't the element in the list";
//}

//Предикат из условия задачи
bool predicat(const complex<double>& value) {
	if (fmod((value).real(), 2) && fmod((value).imag(), 2))
		return 1;
	return 0;
}

//Функция фильтра по условию предиката
template<class T>
list<T> filter(list<T>& lst, bool(*pred)(const T&)) {
	list<T> newlst;

	typename list<T>::iterator it = lst.begin();
	typename list<T>::iterator newit = newlst.end();
	while (it != lst.end())
	{
		if (pred(*it)) { newlst.push_back(*it); }
		it++;
	}

	return newlst;
}


//Функция вывода списка в консоль
template<class T>
void printlist(const list<T>& lst) { cout << lst; }

//Задание 1.2

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
	int getNumFriends() { return numoffriends; }
	string getPseud() { return pseudonym; }

	string getAd() { return address; }
	int getAge() { return age; }
	string getInter() { return interests; }
	string getFav() { return favquote; }
};

//Для списка из задания 1.2
//Перегрузки операторов
bool operator<(Human& value1, Human& value2) {
	if (value1.getNumFriends() > value2.getNumFriends())
		return 1;
	else if (value1.getNumFriends() == value2.getNumFriends() && value1.getPseud() < value2.getPseud()) {
		return 1;
	}
	return 0;
}
//Для "правильного" использования встроенной функции сортировки (list.sort()) по условию задачи
bool operator>(Human& value1, Human& value2) {
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

bool operator==(Human& value1, Human& value2) {
	if (value1.getPseud() == value2.getPseud() && value1.getAd() == value2.getAd() && value1.getAge() == value2.getAge()
		&& value1.getNumFriends() == value2.getNumFriends() && value1.getInter() == value2.getInter() && value1.getFav() == value2.getFav()) {
		return 1;
	}
	return 0;
}
bool operator!=(Human& value1, Human& value2) {
	if (value1.getPseud() != value2.getPseud() || value1.getAd() != value2.getAd() || value1.getAge() != value2.getAge()
		|| value1.getNumFriends() != value2.getNumFriends() || value1.getInter() != value2.getInter() || value1.getFav() != value2.getFav()) {
		return 1;
	}
	return 0;
}

//Удаление элемента из списка и возврат наибольшего по приоритету объекта
template<class T>
T pop(list<T>& lst) {
	T result = lst.front();
	lst.erase(lst.begin());
	return result;
}



int main()
{
	try {
		//1.1
		//complex<double> c1(1, 6);
		//complex<double> c2(9, 16);

		//list<complex<double>> mylist;

		//mylist.push_back(c1);
		//mylist.push_back(c2);

		//complex<double> c3(100, 16);
		//complex<double> c4(1, 5);
		//push(mylist, c3);
		//push(mylist, c4);

		//complex<double> c5(1, 9);
		//complex<double> c6(3, 3);
		//mylist.push_back(c5);
		//mylist.push_back(c6);

		//list<complex<double>> newlist = filter(mylist, predicat);
		//cout << mylist << "\n////////////////\n\n" << newlist;

		//1.2
		list<Human> humans;
		Human human1("Hlath", "Klow", 76, 67, "Tennis", "What?");
		Human human2("Alan", "New-York", 34, 605, "Golf", "Nothing");
		Human human3("Cser", "Paris", 12, 32, "Video-games", "Ok, Jacques Fresco");
		Human human4("Baltazar", "Germany", 39, 1089, "Tetris", "Yep");
		Human human5("Genry", "Estonia", 32, 605, "Working", "What does it mean?");

		humans.push_back(human1); humans.push_back(human2); humans.push_back(human3); humans.push_back(human4);
		humans.push_back(human5);
		cout << humans;

		humans.sort();
		cout << "\n\n";
		cout << humans;
		cout << "\n\n";
		cout << pop(humans).getNumFriends() << "\n";

		return 0;
	}
	catch (const char* error) { cout << error; };

}
