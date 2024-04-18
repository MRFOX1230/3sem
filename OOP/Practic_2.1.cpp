//Вариант 26

//Задание 2.1
//Постройте сбалансированное дерево(используйте класс map библиотеки
//STL), которое содержит значения V по ключам K(таблица 2.1).Постройте
//функции поиска элемента по значению и по ключу.Постройте функцию
//вывода содержимого дерева с помощью итераторов.Постройте функцию
//filter(), которая принимает предикат P и возвращает новое дерево с
//объектами, для которых предикат принимает истинное значение(для всех
//вариантов условие предиката : значение поля V выше некоторого порога
//threshold, в случае хранения нескольких полей достаточно проверить одно из
//них).Введите исключения для случаев, когда пользователь пытается
//добавить новый элемент с ключом, уже присутствующим в дереве.
//Напишите функцию, которая возвращает вектор из различных значений,
//которые встречаются в объекте класса map, заполненном при решении задачи
//(рекомендуется использовать класс set).
//Примечание: В этом задании не требуется создавать класс дерева,
//нужно использовать класс map из библиотеки STL и написать отдельно
//требуемые функции(не методы класса).

//Ключ K: Псевдоним
//Хранимая информация:
//"Профиль в соц. сети"
//V: кол-во друзей


//Задание 2.2
//Постройте сбалансированное дерево(используйте класс multimap
//библиотеки STL), которое содержит значения V по ключам K(таблица 2.1).
//Продемонстрируйте работу контейнера при наличии нескольких элементов с
//одинаковыми ключами.Решите задачу 2.1 для класса multimap.Введите
//функцию, возвращающую все элементы дерева с одинаковыми ключами
//(ключ передаётся в функцию как параметр).


#include <iostream>

//красно-черное (сблансированное) дерево map, есть интерфейс доступа к значению по ключу
using namespace std;
#include <map>
#include <set>

class Profile {
public:
    int friendscount;
public:
    Profile(int newvalue = 0) { friendscount = newvalue; }

    int getValue() { return friendscount; }
};

bool operator> (const Profile& p1, const Profile& p2) {
    if (p1.friendscount > p2.friendscount) { return 1; }
    return 0;
}
bool operator< (const Profile& p1, const Profile& p2) {
    if (p1.friendscount < p2.friendscount) { return 1; }
    return 0;
}
bool operator!= (const Profile& p1, const Profile& p2) {
    if (p1.friendscount != p2.friendscount) { return 1; }
    return 0;
}


//Функции для map и multimap
//Функция нахождения пользователя с данным псевдонимом
template< template<typename, typename, typename, typename> class M,
typename KeyType, typename ValueType,
typename Traits = less<KeyType>, typename Alloc = allocator<pair <const KeyType, ValueType>> >

pair<KeyType, ValueType>  searchpseudoname(M<KeyType, ValueType, Traits, Alloc>& users,
                                           KeyType key) 
{
    auto it = users.find(key);
    if (it == users.end()) { throw "There isn't the element with the key"; }
    return *it;
}

//Функция поиска пользователя с данным профилем
template< template<typename, typename, typename, typename> class M,
typename KeyType, typename ValueType,
typename Traits = less<KeyType>, typename Alloc = allocator<pair <const KeyType, ValueType>> >
 
pair<KeyType, ValueType> searchfriends(M<KeyType, ValueType, Traits, Alloc>& users,
                                                   ValueType value) 
{
    typename M<KeyType, ValueType, Traits, Alloc>::iterator it_m = users.begin();
    while (it_m != users.end())
    {
        if (it_m->second == value) {
            return *it_m;
        }
        it_m++;
    }
    throw "There isn't a user with that count of friends in the map";
}

template<typename M>
void mapprint(M m) {
    cout << "\nMap:\n";
    typename M::iterator it_m = m.begin();
    while (it_m != m.end())
    {
        //перемещение по списку с помощью итератора, нет операции [i]
        cout << "Key: " << it_m->first << ", value: " << it_m->second.getValue() << "\n";
        it_m++;
    }
}


//Предикат для фильтра
template<typename KeyType, typename ValueType>
bool predicat(pair<KeyType, ValueType> user) {
    int threshold = 50;
    if (user.second.getValue() > threshold) { return 1; }
    return 0;
}
//Фильтр
template< template<typename, typename, typename, typename> class M,
typename KeyType, typename ValueType,
typename Traits = less<KeyType>, typename Alloc = allocator<pair <const KeyType, ValueType>> >

M<KeyType, ValueType, Traits, Alloc> filter(M<KeyType, ValueType, Traits, Alloc>& m,
                                            bool(*predicat)(pair<KeyType, ValueType>))
{
    M<KeyType, ValueType, Traits, Alloc> newusers;
    typename M<KeyType, ValueType, Traits, Alloc>::iterator it_m = m.begin();
    while (it_m != m.end())
    {
        if (predicat(*it_m)) {
            newusers.emplace(it_m->first, it_m->second);
            newusers[it_m->first] = it_m->second;
        }
        it_m++;
    }
    return newusers;
}


//Функция возврата вектора значений объектов в map и multimap
template< template<typename, typename, typename, typename> class M,
typename KeyType, typename ValueType,
typename Traits = less<KeyType>, typename Alloc = allocator<pair <const KeyType, ValueType>> >

set<pair<KeyType, ValueType>> getvector(M<KeyType, ValueType, Traits, Alloc>& users) {
    set<pair<KeyType, ValueType>> result;
    result.insert(users.begin(), users.end());
    return result;
}

//Функция, возвращающая элементы с одинаковыми ключами
template< template<typename, typename, typename, typename> class M,
typename KeyType, typename ValueType,
typename Traits = less<KeyType>, typename Alloc = allocator<pair <const KeyType, ValueType>> >

M<KeyType, ValueType, Traits, Alloc> samekeys(M<KeyType, ValueType, Traits, Alloc>& users, KeyType key)
{
    M<KeyType, ValueType, Traits, Alloc> newmap;

    auto it = users.equal_range(key);
    for (auto itr = it.first; itr != it.second; ++itr) {
        newmap.insert(pair<KeyType, ValueType>(itr->first, itr->second));
    }
    if (newmap.size() == 0) { throw "There aren't elements with the key in the map"; }
    return newmap;
}


int main()
{
    try {
        //map<string, int> users;
        //users["Petrov"] = 50;
        //users["Ivanov"] = 100;
        //users["Sidorov"] = 98;
        //users["Nikolaev"] = 546;
        //users["Abramov"] = 357;
        //mapprint(users);
        //mapprint(filter(users, predicat));
        //
        //for (pair<string, int> item : users) {
        //    cout << item.first << ", " << item.second << ";";
        //}

        multimap<string, Profile> multiusers;
        Profile a1(50); 
        Profile a2(100);
        Profile a3(237);
        Profile a4(98);
        Profile a5(546);
        Profile a6(357);
        multiusers.insert(pair<string, Profile> ("Sidorov", a1));
        multiusers.insert(pair<string, Profile> ("Ivanov", a2));
        multiusers.insert(pair<string, Profile> ("Ivanov", a3));
        multiusers.insert(pair<string, Profile> ("Sidorov", a4));
        multiusers.insert(pair<string, Profile> ("Sidorov", a5));
        multiusers.insert(pair<string, Profile> ("Abramov", a6));

        mapprint(multiusers);
        //getvector(multiusers);
        mapprint(samekeys<multimap, string, Profile>(multiusers, "Sidorov"));
        searchpseudoname<multimap, string, Profile>(multiusers, "Sidorov");

    }
    catch (const char* error) { cout << error; }
}

