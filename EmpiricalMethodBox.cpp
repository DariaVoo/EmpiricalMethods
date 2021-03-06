#include "pch.h"
#include <iostream>
using namespace std;
/* 
Первый способ упаковки.
-Упаковываем исходную(неупорядоченную последовательность).
-Сравнение только с одним предыдущем шагом.

1й предмет помещается в первый ящик. 2й,если возможно,то помещается в 1й,иначе во 2й и т.д.
*/
int packageFirst(const int* const items, const int countItems, const int sizeBox) {
	int countBox = 1;//количеств коробок
	int box = sizeBox;

	for (int i = 0;i < countItems; i++) {
		if (items[i] <= box)
			box -= items[i];
		else {
			box = sizeBox - items[i];
			countBox++;
		}
	}
	return countBox;
}
/*
Второй способ упаковки.
-Упорядочиваем исходную последвательность предметов в порядке убывания их веса;
-В остальном совпадает с первым способом.
*/
int comp(const int *i, const int *j)//сравнение двух целых 
{
	return *i - *j;
}

int packageSecond(int* const items, const int countItems, const int sizeBox) {
	int countBox = 1;
	int box = sizeBox;

	qsort(items, countItems,sizeof(int), (int(*) (const void *, const void *))comp);
	for (int i = countItems-1; i >=0; i--) {
		if (items[i] <= box)
			box -= items[i];
		else {
			box = sizeBox - items[i];
			countBox++;
		}
	}
	return countBox;
}
/*
Третий способ упаковки.
-Исходная неупоряоченная последовательность;
-Поступивший для анализа предмет сравнивается с возможностью
размещения начиная с самого первого ящика.
*/
void push_back(int *&array, int &size, const int value) {//добавление элемента в массив
	int *newArray = new int[size + 1];

	for (int i = 0; i < size; i++) {
		newArray[i] = array[i];
	}
	newArray[size] = value;
	size++;
	delete[] array;
	array = newArray;

}
int packageThird(int* items, const int countItems, const int sizeBox) {
	int countBox = 1;
	int *boxes = new int[countBox];
	boxes[0] = sizeBox;
	bool flag = false;//уместился ли предмет в существующие коробки

	for (int i = 0; i < countItems; i++) {
		for (int j = 0; j < countBox; j++) {
			if (items[i] <= boxes[j]) {
				boxes[j] -= items[i];
				flag = true;
				break;
			}
		}
		if (!flag) 
			push_back(boxes, countBox, sizeBox - items[i]);
			
		flag = false;	
	}

	delete[] boxes;
	return countBox;
}

/*
Четвёртый способ упаковки.
-Упорядочиваем исходную последовательность предметов в порядке убывания их веса;
-В остальном совпадает со вторым способом.
*/
int packageFourth(int* const items, const int countItems, const int sizeBox) {
	int countBox = 1;
	int *boxes = new int[countBox];
	boxes[0] = sizeBox;
	bool flag = false;//уместился ли предмет в существующие коробки

	qsort(items, countItems, sizeof(int), (int(*) (const void *, const void *))comp);
	for (int i = countItems - 1; i >= 0; i--) {
		for (int j = 0; j < countBox; j++) {
			if (items[i] <= boxes[j]) {
				boxes[j] -= items[i];
				flag = true;
				break;
			}
		}
		if (!flag)
			push_back(boxes, countBox, sizeBox - items[i]);

		flag = false;
	}

	delete[] boxes;
	return countBox;
}
//Проверка на дурака
template <typename T>
void cinParse(T &param) {
	cin >> param;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "!!!Invalid input!!!"<<endl;
		cin >> param; cin.ignore();
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	while (true) {
		int sizeBox, countItems;
		cout << "Enter size of the box:\t";
		cinParse(sizeBox);
		cout << "Enter count of the items:\t";
		cinParse(countItems);

		cout << "Enter the items:" << endl;
		int *items = new int[countItems];
		for (int i = 0; i < countItems; i++) {
			cout << "J" << i << "\t";
			cinParse(items[i]);
		}

		int first = packageFirst(items, countItems, sizeBox);
		int third = packageThird(items, countItems, sizeBox);

		int second = packageSecond(items, countItems, sizeBox);
		int fourth = packageFourth(items, countItems, sizeBox);
		cout << "To fill the boxes, you must have\t BOX" << endl;
		cout << "By first way\t" << first << endl;
		cout << "By second way\t" << second << endl;
		cout << "By third way\t" << third << endl;
		cout << "By fourth way\t" << fourth << endl;
		delete[] items;
		items = nullptr;

		cout << "Do you want package smth else?" << endl;
		cout << "1 - Yes." << endl;
		cout << "2 - No." << endl;
		int ans; cinParse(ans);
		if (ans == 2)
			break;
	}

}
