// Консольная программа для демонстрации

#include <fcntl.h>

#include <chrono>
#include <complex>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cwchar>

#include "binarytree.h"
#include "common.h"
#include "menu.h"
#include "set.h"
#include "tree.h"
#include "BinaryHeap.h"

using namespace std;

template <class T>
T map_function(T x) {
    return x * x;
}

std::wstring map_function(std::wstring x) {
    return x + L"!";
}

bool where_function(int x) {
    bool result = (x % 2) == 0;
    std::wcout << L"  where: число " << x << L" чётное: " << result << std::endl;
    return result;
}

bool where_function(double x) {
    bool result = abs(x) < 5;
    std::wcout << L"  where: число |" << x << L"| < 5: " << result << std::endl;
    return result;
}

bool where_function(std::complex<double> x) {
    bool result = abs(x) < 5;
    std::wcout << L"  where: число |" << x << L"| < 5: " << result << std::endl;
    return result;
}

bool where_function(const std::wstring x) {
    bool result = x.size() < 4;
    std::wcout << L"  where: длина строки " << x << L" < 4: " << result << std::endl;
    return result;
}

template <class T>
T reduce_function(T a, T b) {
    T result = a + b;
    std::wcout << L"  reduce: " << a << L" + " << b << " = " << result << std::endl;
    return result;
}


// Замеряем время работы дерева
void treeImplementationSpeed() {
    BinaryTree<int> tree;       // Создаём дерево
    const int numbers = 10000;  // Добавим числа
    wcout << L"Количество элементов для тестирования: " << numbers << endl;
    auto begin = chrono::steady_clock::now();  // Засекаем начало работы
    for (int i = 1; i <= numbers; i++) {
        tree.insert(i);
    }
    auto end = chrono::steady_clock::now();  // Конец работы
    auto elapsed_mcs = chrono::duration_cast<chrono::microseconds>(end - begin);
    // Вычисляем разницу в секундах времени начала и окончания работы
    const double t = elapsed_mcs.count() / 1e6;
    // Выводим результат в секундах на экран (в консоль)
    wcout << typeid(tree).name() << " time = " << t << endl;
}

template <class T>
void stack_addElementSpeed(BinaryTree<T> &tree) {
    wprintf(L"Сравнение времени добавления элементов в дерево\n");
    treeImplementationSpeed();
}

template <class T>
void tree_base_operations(BinaryTree<T> &tree) {
    while (true) {
        tree.printAsTree();
        wcout << L"Операции с деревом:" << endl;
        wcout << L"1. Вставка" << endl;
        wcout << L"2. Удаление" << endl;
        wcout << L"3. Поиск" << endl;
        wcout << L"0. Выход" << endl;
        int choice;
        wcin >> choice;
        T element;
        switch (choice) {
            case 1:
                wcout << L"Вставка: введите элемент для вставки: ";
                wcin >> element;
                tree.insert(element);
                break;
            case 2:
                wcout << L"Удаление: введите элемент для удаления: ";
                wcin >> element;
                tree.remove(element);
                break;
            case 3:
                wcout << L"Поиск: введите элемент для поиска: ";
                wcin >> element;
                if (tree.find(element)) {
                    wcout << L"Элемент найден" << endl;
                } else {
                    wcout << L"Элемент не найден" << endl;
                }
                break;
            case 0:
                return;
            default:
                wcout << L"Нет такого пункта меню" << endl;
        }
    }
}

template <class T>
void apply_map_where_reduce(BinaryTree<T> &tree) {
    wcout << L"Применение функций map, where, reduce - ручной ввод данных" << endl;
    if (tree.getRoot() == nullptr) {  // Если дерево пустое
        wcout << L"Пустое дерево. Введите значения." << endl;
        wcout << L"Введите количество элементов: ";
        int N;
        wcin >> N;
        for (int i = 1; i <= N; i++) {
            T element;
            wcout << L"Введите элемент номер " << i << ": ";
            wcin >> element;
            tree.insert(element);
        }
        tree.printAsTree();
    }

    wprintf(L"Применяем операцию map (построить новое дерево поэлементным преобразованием)\n");
    BinaryTree<T> mapRes = tree.map(map_function);
    mapRes.printAsTree();  // Печатаем дерево

    wprintf(L"Применяем операцию where\n");
    BinaryTree<T> whereRes = tree.where(where_function);
    whereRes.printAsTree();

    wprintf(L"Применяем операцию reduce - сложение для всех чисел\n");
    T reduceRes = tree.reduce(reduce_function);
    std::wcout << L"Результат reduce: " << reduceRes << std::endl << std::endl;

    wcout << endl;
}

template <class T>
BinaryTree<T> input_tree() {
    BinaryTree<T> tree;  // Дерево из элементов типа T
    wcout << L"Введите количество элементов: ";
    int N;
    wcin >> N;
    for (int i = 1; i <= N; i++) {
        T element;
        wcout << L"Введите элемент номер " << i << ": ";
        wcin >> element;
        tree.insert(element);
    }
    tree.printAsTree();
    return tree;
}

template <class T>
void threaded_by_fixed_traversal(BinaryTree<T> &tree) {
    wprintf(L"Прошивка по фиксированному обходу\n");
    if (tree.getRoot() == nullptr) {  // Если дерево пустое
        wcout << L"Пустое дерево. Введите значения." << endl;
        wcout << L"Введите количество элементов: ";
        int N;
        wcin >> N;
        for (int i = 1; i <= N; i++) {
            T element;
            wcout << L"Введите элемент номер " << i << ": ";
            wcin >> element;
            tree.insert(element);
        }
        tree.printAsTree();
    }

    wprintf(L"Прошиваем дерево в порядке Корень Левое Правое\n");
    tree.thread();

    wprintf(L"Выводим прошивку - узлы в порядке прошивки\n");
    for (auto cur = tree.first; cur != nullptr; cur = cur->next) {
        wcout << cur->value << endl;
    }
    wcout << endl;
}

template <class T>
void threaded_by_any_traversal(BinaryTree<T> &tree) {
    wcout << L"Прошивка по обходу, задаваемому параметром метода" << endl;
    if (tree.getRoot() == nullptr) {  // Если дерево пустое
        wcout << L"Пустое дерево. Введите значения." << endl;
        wcout << L"Введите количество элементов: ";
        int N;
        wcin >> N;
        for (int i = 1; i <= N; i++) {
            T element;
            wcout << L"Введите элемент номер " << i << ": ";
            wcin >> element;
            tree.insert(element);
        }
        tree.printAsTree();
    }

    wcout << L"Введите порядок обхода N-корень L-левое поддерево R-правое, например LNR: ";
    wstring order;  // Переменная для порядка обхода
    wcin >> order;  // Вводим порядок обхода с консоли
    wprintf(L"Прошиваеем дерево в заданном порядке обхода\n");
    string s(order.begin(), order.end());
    tree.thread(s.c_str());

    wprintf(L"Выводим прошивку - узлы в порядке прошивки\n");
    for (auto cur = tree.first; cur != nullptr; cur = cur->next) {
        wcout << cur->value << endl;
    }
    wcout << endl;
}

wstring toWS(string s) {
    return wstring(s.begin(), s.end());
}
string toS(wstring s) {
    return string(s.begin(), s.end());
}

//    5
//  2   8
// 1 3 6
// 1. КЛП = Корень Левый Правый
// 5 2 1 3 8 6
// 2. КПЛ = Корень Правый Левый
// 5 8 6 2 3 1
// 3. ЛПК = Левый Правый Корень
// 1 3 2 6 8 5
// 4. ЛКП = Левый Корень Правый
// 1 2 3 5 6 8
// 5. ПЛК = Правый Левый Корень
// 6 8 3 1 2 5
// 6. ПКЛ = Правый Корень Левый
// 8 6 5 3 2 1
template <class T>
void to_string_in_fixed_traversal(BinaryTree<T> &tree) {
    wcout << L"Дерево:" << endl;
    tree.printAsTree();
    wcout << L"1. КЛП = Корень Левый Правый: " << toWS(tree.toNLR()) << endl;
    wcout << L"2. КПЛ = Корень Правый Левый: " << toWS(tree.toNRL()) << endl;
    wcout << L"3. ЛПК = Левый Правый Корень: " << toWS(tree.toLRN()) << endl;
    wcout << L"4. ЛКП = Левый Корень Правый: " << toWS(tree.toLNR()) << endl;
    wcout << L"5. ПЛК = Правый Левый Корень: " << toWS(tree.toRLN()) << endl;
    wcout << L"6. ПКЛ = Правый Корень Левый: " << toWS(tree.toRNL()) << endl;
}

template <class T>
void to_string_in_any_traversal(BinaryTree<T> &tree) {
    tree.printAsTree();
    wcout << L"Введите порядок обхода N-корень L-левое поддерево R-правое, например LNR: ";
    wstring order;  // Переменная для порядка обхода
    wcin >> order;  // Вводим порядок обхода с консоли
    wcout << L"Вывод в заданном порядке" << endl;
    wcout << toWS(tree.toString(toS(order).c_str())) << endl;
    wcout << endl;
}

template <class T>
void tree_extract_subtree(BinaryTree<T> &tree) {
    tree.printAsTree();
    if (tree.getRoot() == nullptr) {  // Если дерево пустое
        wcout << L"Пустое дерево. Введите значения." << endl;
        wcout << L"Введите количество элементов: ";
        int N;
        wcin >> N;
        for (int i = 1; i <= N; i++) {
            T element;
            wcout << L"Введите элемент номер " << i << ": ";
            wcin >> element;
            tree.insert(element);
        }
        tree.printAsTree();
    }
    T key;
    wcout << L"Значение в корне поддерева: ";
    wcin >> key;
    BinaryTree<T> *res = tree.subTree(key);
    res->printAsTree();
    delete res;
    wcout << endl;
}

template <class T>
void tree_find_subtree(BinaryTree<T> &tree) {
    tree.printAsTree();
    BinaryTree<T> subTreeToFind = input_tree<T>();
    if (tree.subTreeCheck(&subTreeToFind)) {
        wcout << L"Поддерево найдено" << endl;
    } else {
        wcout << L"Поддерево не найдено" << endl;
    };
}

template <class T>
void set_insert_find_delete(Set<T> &s) {
    while (true) {
        wcout << toWS(s.toString())<<endl;
        wcout << L"Операции с множеством (0. Выход из меню):" << endl;
        wcout << L"1. Вставка" << endl;
        wcout << L"2. Удаление" << endl;
        wcout << L"3. Поиск" << endl;
        int choice;
        wcin >> choice;
        T element;
        switch (choice) {
            case 1:
                wcout << L"Вставка: введите элемент для вставки: ";
                wcin >> element;
                s.insert(element);
                break;
            case 2:
                wcout << L"Удаление: введите элемент для удаления: ";
                wcin >> element;
                s.erase(element);
                break;
            case 3:
                wcout << L"Поиск: введите элемент для поиска: ";
                wcin >> element;
                if (s.find(element)) {
                    wcout << L"Элемент найден" << endl;
                } else {
                    wcout << L"Элемент не найден" << endl;
                }
                break;
            case 0:
                return;
            default:
                wcout << L"Нет такого пункта меню" << endl;
        }
    }
}



//n- tree
template <class T,int N>
void basic_operations_n_tree() {
    Tree<T, N> tree(L"Создание дерева");
}

//Binary heap
template <class T>
void binary_heap_basic_operations() {
    wprintf(L"Введите размер кучи: ");
    int N;
    wcin >> N;
    MinHeap<T> h(N);
    wcout << L"Минимальная куча" << endl;
    for (int i = 1; i <= N; i++) {
        T element;
        wcout << L"Введите элемент номер " << i << ": ";
        wcin >> element;
        h.insert(element);
    }
    for (int i = 0; i < N; i=i+3){
        wcout <<h.parent(i) << endl;
        wcout <<h.left(i) <<" ";
        wcout <<h.right(i) << endl;
    }
}

template <class T>
void set_map_reduce_where(Set<T> &s) {
    wcout << L"Множество - применение функций map, where, reduce" << endl;
    wcout << toWS(s.toString())<<endl;
    if (s.size() == 0) {  // Если множество пустое
        wcout << L"Пустое множество. Введите значения." << endl;
        wcout << L"Введите количество элементов: ";
        int N;
        wcin >> N;
        for (int i = 1; i <= N; i++) {
            T element;
            wcout << L"Введите элемент номер " << i << ": ";
            wcin >> element;
            s.insert(element);
        }
        wcout << toWS(s.toString()) << endl;
    }
    wcout << L"Применяем операцию map (построить новое множество поэлементным преобразованием)" << endl;
    Set<T> mapRes = s.map(map_function);
    wcout << toWS(mapRes.toString())<< endl;  // Печатаем множество

    wcout << L"Применяем операцию where" << endl;
    Set<T> whereRes = s.where(where_function);
    wcout << toWS(whereRes.toString())<< endl;

    wcout << L"Применяем операцию reduce - сложение для всех чисел" << endl;
    T reduceRes = s.reduce(reduce_function);
    wcout << L"Результат reduce: " << reduceRes << endl << endl;
}

template <class T>
Set<T> input_set() {
    Set<T> res;
    wcout << L"Введите количество элементов: ";
    int N;
    wcin >> N;
    for (int i = 1; i <= N; i++) {
        T element;
        wcout << L"Введите элемент номер " << i << L": ";
        wcin >> element;
        res.insert(element);
    }
    wcout << toWS(res.toString())<< endl;
    return res;
}


template <class T>
void set_union_intersection_difference(Set<T> &A) {
    wcout << L"Операции над множествами: объединение, пересечение, вычитание" << endl;
    wcout << L"Множество A: " << toWS(A.toString()) << endl;
    Set<T> B = input_set<T>();
    wcout << L"Множество B: " << toWS(B.toString()) << endl;
    wcout << L"Объединение множеств: " << toWS(A.setUnion(B).toString()) << endl;
    wcout << L"Пересечение множеств: " << toWS(A.intersection(B).toString()) << endl;
    wcout << L"Вычитание множеств A-B: " << toWS(A.difference(B).toString()) << endl;
}

template <class T>
void set_subset_equals(Set<T> &A) {
    wcout << L"Множество A: " << toWS(A.toString()) << endl;
    Set<T> B = input_set<T>();
    wcout << L"Множество B: " << toWS(B.toString()) << endl;
    wcout << L"0-не является. 1-является. " << endl;
    wcout << L"A подмножество B: " << A.subSet(B) << endl;
    wcout << L"B подмножество A: " << B.subSet(A) << endl;
    wcout << L"A == B: " << A.equal(B) << endl;
}

template <class T>
void set5(Set<T> &s) {
    s.toString();
}

template <class T>
void binary_tree_menu() {
    BinaryTree<T> bt;
    MenuX<BinaryTree<T>> m{L"Возможные операции с деревом",
                           { {L"Базовые операции: вставка, поиск, удаление + Балансировка", tree_base_operations<T>},
                             {L"Применение функции map, where, reduce - ручной ввод данных", apply_map_where_reduce<T>},
                             {L"Прошивка по фиксированному обходу", threaded_by_fixed_traversal<T>},
                             {L"Прошивка по обходу, задаваемому параметром метода", threaded_by_any_traversal<T>},
                             {L"Сохранение в строку по фиксированному обходу", to_string_in_fixed_traversal<T>},
                             {
                                     L"Сохранение в строку по обходу, задаваемому строкой форматирования (например: «{К}(Л)[П]»)",
                                     to_string_in_any_traversal<T>
                             },
                             {L"Извлечение поддерева (по заданному корню)", tree_extract_subtree<T>},
                             {L"Поиск на вхождение поддерева", tree_find_subtree<T>},
                             {
                                     L"Время добавления элементов в дерево на основе LinkedList",
                                     stack_addElementSpeed<T>
                             }
                           },
                           bt};
}

template <class T>
void set_menu() {
    Set<T> s;
    MenuX<Set<T>> m{
            L"Возможные операции",
            {
                    {L"Базовые операции: вставка, поиск, удаление (на базе бинарного дерева поиска)", set_insert_find_delete<T>},
                    {L"map, reduce, where", set_map_reduce_where<T>},
                    {L"Операции над множествами: объединение, пересечение, вычитание", set_union_intersection_difference<T>},
                    {L"Проверка на включение (подмножества), на равенство (двух множеств)", set_subset_equals<T>},
            },
            s};
}

template <class T>
void binary_heap_menu() {
    MenuItem menu[] = {{L"Базовые операции",binary_heap_basic_operations<T>}};
    menuLoop(L"Возможные операции", _countof(menu), menu);
}
template<class T>
void tree_menu() {
    wprintf(L"Введите скольки арное дерево: \n");
    wprintf(L"1. 3-арное дерево\n");
    wprintf(L"2. 4-арное дерево\n");
    wprintf(L"3. 5-арное дерево\n");
    wprintf(L"4. 6-арное дерево\n");
    int k;
    wcout<< L"Ваш выбор: ";
    std::wcin >> k;
    switch (k) {
        case 1:{
            basic_operations_n_tree<T,3>();
            break;
        }
        case 2:{
            basic_operations_n_tree<T,4>();
            break;
        }
        case 3:{
            basic_operations_n_tree<T,5>();
            break;
        }
        case 4:{
            basic_operations_n_tree<T,6>();
            break;
        }
        default:{
            basic_operations_n_tree<T,2>();
            break;
        }
    }
//    MenuItem menu[] = {{L"Базовые операции",basic_operations_n_tree<T,N>}};
//    menuLoop(L"Возможные операции", _countof(menu), menu);
}

void binaryTreeMenu() {
    Menu m{
            L"Выберите тип элементов для бинарного дерева поиска",
            {{L"Целые числа (int)", binary_tree_menu<int>}, {L"Вещественные числа (double)", binary_tree_menu<double>}}
    };
}

void setMenu() {
    Menu m(L"Выберите тип элементов для множества", {
            {L"Целые числа (int)", set_menu<int>}, {L"Вещественные числа (double)", set_menu<double>}
    });
}

void treeMenu() {
    MenuItem menu[] = {{L"Целые числа (int)",tree_menu<int>},
                       {L"Вещественные числа (double)",tree_menu<double>}};
    menuLoop(L"Возможные операции", _countof(menu), menu);
}
void binaryHeapMenu() {


    Menu m(L"Выберите тип элементов для множества", {
            {L"Целые числа (int)", binary_heap_menu<int>}, {L"Вещественные числа (double)", binary_heap_menu<double>}
    });
}

int main() {
    // Задаём кодировку UTF-16 для всего вывода в программе
    // Все символы и строки будут wchar_t
#if WIN32 || WIN64
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
#endif
    wprintf(L"== Тестирование операций с деревом и множеством ==\n");

    Menu m{L"Выберите с какой структурой данных будем работать",
           { {L"Демонстрация работы с бинарным деревом поиска", binaryTreeMenu},
             {L"Демонстрация работы с множествами", setMenu},
             {L"Демонстрация работы с n-арным деревом поиска", treeMenu},
             {L"Демонстрация работы с бинарной кучей", binaryHeapMenu}
           }};
}
