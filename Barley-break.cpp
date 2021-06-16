/* ----------------------------------------------------------------<Header>-
 Name: Barley-break.cpp
 Title: Barley-break
 Group: TV-91
 Student: Taratonova. O. S.
 Description: �������� �� ��������� ������ ��� �'���������
 ------------------------------------------------------------------</Header>-*/
#include <iostream>
#include <ctime>
#include <cstdlib>
//#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

//�������-��������� ���������� �����
void generate(int &trying, int &size, bool *checkit){ 
	trying = rand() % (size * size); 	
//�������� �� ��������� ������������� ��������;
	if(!checkit[trying]){					
//���� ������������ � ������ ���, ������ ������ � �����
		checkit[trying] = true;
	} else{
//���� ������� ��� ����������, �� ��� �������
		generate(trying, size, checkit);	
	}
}


void enter(int &size, char &ch){
cout << "Do you want to examine a random matrix or matrix from a file?(enter 'r' for random or 'f' for file):  ";
	cin >> ch;
	if(ch != 'r' && ch != 'f'){
		cout << "Incorrect input! Try again, please!\n";
// ��� ���� ����������� ����� �������� ���������� ������� ��� �����
		enter(size, ch);	

	} else {
		cout << "Enter size of field, please (the size can be 3, 4 or 100): ";
		cin >> size; 
//����� ���� ���� ���� ����� 3, 4 ��� 100
		if(size == 3 || size == 4 || size == 100){
			system("cls");	//������� ������ ���� �������� ���������� �����
			cout << "Thank you for your choise!\n";
		} else {
			cout << "Incorrect input! Try again, please!\n";
			enter(size, ch);
//��� ���� ����������� ����� �������� ���������� ������� ��� �����
		}
	}
}


int main(){
	ifstream fin("Barley-break.txt");

	while(1){
		cout << "Hello, user!\n";
		char ch;
		int size;				//����� ���� ��������
		enter(size, ch);			//������� ��� ����� ������ ����
		bool checkit[size * size] = {0};	
//����� ��� �������� �� ��������� ��������
		vector <int> field;		//������ ��� ��������� ��������
		int temp[size];
//������ �����, ���� ����������� ��� ��������� ������� ��� �����쳿 ����
		srand(time(NULL));
		int trying = 0, ind = 0;
//����� ��� ��������� ������������� �������� �� ������ ��� ���������� ������ //temp[]
		if(size == 100) cout << "Field size is too large for printing.\n";
		else cout << "Your field:\n";

		for(int i = 0; i < size * size; i++){
//������� ���������� ������ �������
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
			if(i / size % 2 == 0) { 		//���������� � ������� �������
				if(trying != 0) field.push_back(trying); 
//��������� �������� � ������
				if(size != 100) cout << setw(4) << trying;
//����� ���� ������� ��� ������ �� �����
			}
			else{ 			//���������� ������ ���� � ���������� �������
				temp[ind] = trying;
				if(size != 100) cout << setw(4) << temp[ind];
				ind++;
				if((i + 1) % size == 0){	//����������� ������ ���� � ������
				    for(int j = size - 1; j >= 0; j--){
				        if(temp[j] != 0) field.push_back(temp[j]);
//�� ������ ������� �����
				    }
				  ind = 0;
			     }
			}
		    if((i + 1) % size == 0 && size != 100) cout << '\n';
		}

		int number = 1;			//������� ��� ������ � ������
		while(1){
		    for(int i = number - 1; i < field.size(); i++){
		       if(field[i] == number && i != number - 1){ 
//������� �������� �� ����� ������� ��������
			   field.insert(field.begin() + number - 1 + (i - number + 1) % 2, field[i]);
//��������� ������������ ��������
					field.erase(field.begin() + i + 1);									//���� ��������� �� �� ��� ����, � �� ����� ������
					if((i - number + 1) % 2 == 1){		
					   field.insert(field.begin() + number + 2, field[number - 1]);
					   field.erase(field.begin() + number - 1);
					}
					break;
				}
			}
			number++;
//����� �� ����� � �����(������� ��� ������ - ����� �������)
			if(number == field.size() - 1) break;
		}

		cout << endl;	

//�� ������ ������ 2 �������� ��������� �� �
		if(field[size * size - 3] - field[size * size - 2] == 1) cout << "Solution of this location exists!\n";
		else cout << "No exist solution of this location.....\n";

		cout << "Enter 'e' for exit or 'r' for repeat.\n";       //��������� �������������
		cin >> ch;
		if(ch == 'e'){
			cout << "Goodbye!"; 
			fin.close();
			return 0;
		}
		system("cls");
	}
}

