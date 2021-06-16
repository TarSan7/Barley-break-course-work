/* ----------------------------------------------------------------<Header>-
 Name: Barley-break.cpp
 Title: Barley-break
 Group: TV-91
 Student: Taratonova. O. S.
 Description: Перевірка на існування рішення гри П'ятнадцять
 ------------------------------------------------------------------</Header>-*/
#include <iostream>
#include <ctime>
#include <cstdlib>
//#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

//функція-генератор випадкових чисел
void generate(int &trying, int &size, bool *checkit){ 
	trying = rand() % (size * size); 	
//перевірка на існування сгенерованого элемента;
	if(!checkit[trying]){					
//якщо зустрічаеться в перший раз, робимо відмітку в масиві
		checkit[trying] = true;
	} else{
//якщо элемент вже зустрічався, ще раз генеруєм
		generate(trying, size, checkit);	
	}
}


void enter(int &size, char &ch){
cout << "Do you want to examine a random matrix or matrix from a file?(enter 'r' for random or 'f' for file):  ";
	cin >> ch;
	if(ch != 'r' && ch != 'f'){
		cout << "Incorrect input! Try again, please!\n";
// при вводі некоректних даних повторно запускаемо функцію для ввода
		enter(size, ch);	

	} else {
		cout << "Enter size of field, please (the size can be 3, 4 or 100): ";
		cin >> size; 
//розмір поля може бути тільки 3, 4 або 100
		if(size == 3 || size == 4 || size == 100){
			system("cls");	//очистка экрана після введення правильных даних
			cout << "Thank you for your choise!\n";
		} else {
			cout << "Incorrect input! Try again, please!\n";
			enter(size, ch);
//при вводі некоректних даних повторно запускаемо функцію для ввода
		}
	}
}


int main(){
	ifstream fin("Barley-break.txt");

	while(1){
		cout << "Hello, user!\n";
		char ch;
		int size;				//розмір поля пятнашек
		enter(size, ch);			//функція для ввода розміру поля
		bool checkit[size * size] = {0};	
//масив для перевірки на існування елемента
		vector <int> field;		//вектор для зберігання пятнашек
		int temp[size];
//задаємо масив, який знадобиться при заповненні вектора для економії місця
		srand(time(NULL));
		int trying = 0, ind = 0;
//змінна для зберігання сгенерованого елемента та індекс для заповнення масива //temp[]
		if(size == 100) cout << "Field size is too large for printing.\n";
		else cout << "Your field:\n";

		for(int i = 0; i < size * size; i++){
//функція заповнення масива числами
			if(ch == 'r') generate(trying, size, checkit);
			else{
				if(!fin.eof()) fin >> trying;
				else{
					cout << "\nSorry! Error! Try again...";
					return 0;
				}
				if(trying >= size * size){
					cout << "\nSorry! Error! Try again...";
					return 0;
				}
			}
			if(i / size % 2 == 0) { 		//заповнення в прямому порядку
				if(trying != 0) field.push_back(trying); 
//додавання елемента в вектор
				if(size != 100) cout << setw(4) << trying;
//розмір дуже великий для виводу на екран
			}
			else{ 			//заповнення строки поля в зворотному порядку
				temp[ind] = trying;
				if(size != 100) cout << setw(4) << temp[ind];
				ind++;
				if((i + 1) % size == 0){	//перенесення строки поля в вектор
				    for(int j = size - 1; j >= 0; j--){
				        if(temp[j] != 0) field.push_back(temp[j]);
//не вносим порожню клітку
				    }
				  ind = 0;
			     }
			}
		    if((i + 1) % size == 0 && size != 100) cout << '\n';
		}

		int number = 1;			//елемент для пошуку в векторі
		while(1){
		    for(int i = number - 1; i < field.size(); i++){
		       if(field[i] == number && i != number - 1){ 
//перенос елемента на парну кількість елементів
			   field.insert(field.begin() + number - 1 + (i - number + 1) % 2, field[i]);
//видалення перенесеного елементу
					field.erase(field.begin() + i + 1);									//якщо перенесли не на своє місце, а на поруч стояче
					if((i - number + 1) % 2 == 1){		
					   field.insert(field.begin() + number + 2, field[number - 1]);
					   field.erase(field.begin() + number - 1);
					}
					break;
				}
			}
			number++;
//умова на вихід з циклу(елемент для пошуку - кінець вектора)
			if(number == field.size() - 1) break;
		}

		cout << endl;	

//чи стоять останні 2 елемента правильно чи ні
		if(field[size * size - 3] - field[size * size - 2] == 1) cout << "Solution of this location exists!\n";
		else cout << "No exist solution of this location.....\n";

		cout << "Enter 'e' for exit or 'r' for repeat.\n";       //можливість перезапустити
		cin >> ch;
		if(ch == 'e'){
			cout << "Goodbye!"; 
			fin.close();
			return 0;
		}
		system("cls");
	}
}

