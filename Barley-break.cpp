/* ----------------------------------------------------------------<Header>-
 Name: Barley-break.cpp
 Title: Barley-break
 Group: TV-91
 Student: Taratonova. O. S.
 ------------------------------------------------------------------</Header>-*/
#include <iostream>
#include <ctime>
#include <cstdlib>
//#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

// function-generator of random numbers
void generate(int &trying, int &size, bool *checkit){ 
	trying = rand() % (size * size); 	
	// revision of the generated element;
	if(!checkit[trying]){					
		// it’s the first time to see it in the array
		checkit[trying] = true;
	} else{
		// if the element is already being played, again it is generated
		generate(trying, size, checkit);	
	}
}


void enter(int &size, char &ch){
cout << "Do you want to examine a random matrix or matrix from a file?(enter 'r' for random or 'f' for file):  ";
	cin >> ch;
	if(ch != 'r' && ch != 'f'){
		cout << "Incorrect input! Try again, please!\n";
		// when entering incorrect data, re-run the function to enter
		enter(size, ch);	

	} else {
		cout << "Enter size of field, please (the size can be 3, 4 or 100): ";
		cin >> size; 
		// field size can only be 3, 4 or 100
		if(size == 3 || size == 4 || size == 100){
			system("cls");	// clear the screen after entering the correct data
			cout << "Thank you for your choise!\n";
		} else {
			cout << "Incorrect input! Try again, please!\n";
			enter(size, ch);
			// when entering incorrect data, re-run the function to enter
		}
	}
}


int main(){
	ifstream fin("Barley-break.txt");

	while(1){
		cout << "Hello, user!\n";
		char ch;
		int size;				// size of the field of tags
		enter(size, ch);			// function for entering the size of the field
		bool checkit[size * size] = {0};
		// array for converting to an element
		vector <int> field;		
		int temp[size];
		// specify the array that will be needed when filling the vector to save space
		srand(time(NULL));
		int trying = 0, ind = 0;
		// variable to store the generated element and index to populate the array // temp []
		if(size == 100) cout << "Field size is too large for printing.\n";
		else cout << "Your field:\n";

		for(int i = 0; i < size * size; i++){
			// function to fill the array with numbers
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
			if(i / size % 2 == 0) { 		// fill in direct order
				if(trying != 0) field.push_back(trying); 
				// add an element to the vector
				if(size != 100) cout << setw(4) << trying; // the size is too large for display
			}
			else{ 			// fill in the field in the reverse order
				temp[ind] = trying;
				if(size != 100) cout << setw(4) << temp[ind];
				ind++;
				if((i + 1) % size == 0){	// transfer the field string to the vector
				    for(int j = size - 1; j >= 0; j--){
				        if(temp[j] != 0) field.push_back(temp[j]);
				    }
				  ind = 0;
			     }
			}
		    if((i + 1) % size == 0 && size != 100) cout << '\n';
		}

		int number = 1;			// element to search in vector
		while(1){
		    for(int i = number - 1; i < field.size(); i++){
		       if(field[i] == number && i != number - 1){ 
			       // transfer an element to an even number of elements
			   field.insert(field.begin() + number - 1 + (i - number + 1) % 2, field[i]);// delete the transferred item
					field.erase(field.begin() + i + 1);				
					if((i - number + 1) % 2 == 1){		
					   field.insert(field.begin() + number + 2, field[number - 1]);
					   field.erase(field.begin() + number - 1);
					}
					break;
				}
			}
			number++;
			if(number == field.size() - 1) break;
		}

		cout << endl;	

		if(field[size * size - 3] - field[size * size - 2] == 1) cout << "Solution of this location exists!\n";
		else cout << "No exist solution of this location.....\n";

		cout << "Enter 'e' for exit or 'r' for repeat.\n";      
		cin >> ch;
		if(ch == 'e'){
			cout << "Goodbye!"; 
			fin.close();
			return 0;
		}
		system("cls");
	}
}

