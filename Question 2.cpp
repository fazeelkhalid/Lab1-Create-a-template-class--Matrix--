//Note I'm using 2017 visual studio
#include<iostream>
using namespace std;
template<typename T>

class Matrix {
private:
	T ** matrix;
	int row;
	int coloum;
	int stringSize(char*); // return string size
	bool compare(char *, char *); //compare two pointer arraies of char type

public:
	Matrix(int rows, int columns);
	Matrix(Matrix const &obj); // copy constructor
	void insertElement(T const &element, int rowNo, int colNo); // insert element in array
	Matrix<T> operator+(Matrix const& obj); // add two objects
	void print(); // print matrices in rows and coloum 
	void transpose(); //take transpose of matericies
	Matrix<char*> operator=(Matrix<char*>const& obj); // perform assignment operation
	bool operator==(Matrix<char*>const& obj); // check is teo objects are equal or not
	~Matrix(); // destructor
};
template<typename T>
Matrix<T>::Matrix(int rows, int coloums) { // parametarized constructor
	matrix = new T*[rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new T[coloums];
	}
	coloum = coloums;
	row = rows;
}

template<typename T>
Matrix <T>::Matrix(Matrix const &obj) { // copy constructor
	this->coloum = obj.coloum;
	this->row = obj.row;

	matrix = new T*[row];
	for (int i = 0; i < row; i++) { // assign memory
		matrix[i] = new T[coloum];
	}

	for (int i = 0; i < row; i++) { // copy data 
		for (int j = 0; j < coloum; j++) {
			matrix[i][j] = obj.matrix[i][j];
		}
	}
}

template<typename T>
void Matrix<T>::insertElement(T const &element, int rowNo, int colNo) { // putting data in matrix on given indexes
	matrix[rowNo][colNo] = element;
}


template<typename T>
Matrix<T> Matrix<T>:: operator+(Matrix const& obj) {
	Matrix<T>temp(this->row, this->coloum);
	if (this->row == obj.row && this->coloum == obj.coloum) { //check is rows and coloums are equal
		for (int i = 0; i < this->row; i++) { // add two matrices element by element
			for (int j = 0; j < this->coloum; j++) {
				temp.matrix[i][j] = this->matrix[i][j] + obj.matrix[i][j];
			}
		}
	}
	else {
		cout << "Rows and coloums of both matices are not same : ";
	}
	return temp;
}

template<typename T>
void Matrix <T>::print() { // print the matrices
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < coloum; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

template<typename T>
void Matrix<T>::transpose() {
	Matrix<T>temp(this->coloum, this->row);
	int tempColoum = 0;
	for (int i = 0; i < this->row; i++) { // copy row of matix 1 and store it into the coloum of temp. matrix
		int tempRow = 0;
		for (int j = 0; j < this->coloum; j++) {
			temp.matrix[tempRow][tempColoum] = this->matrix[i][j];
			tempRow++;
		}
		tempColoum++;
	}
	int tem = row;
	row = coloum;
	coloum = tem;
	for (int i = 0; i < coloum; i++) { // delete matix before initializing to avoid memory leakage
		delete[]matrix[i];
	}
	delete[]matrix;
	matrix = new T*[row];
	for (int i = 0; i < row; i++) { // allocate memory
		matrix[i] = new T[coloum];
	}

	for (int i = 0; i < row; i++) { // copy data form temp object to caller object
		for (int j = 0; j < coloum; j++) {
			matrix[i][j] = temp.matrix[i][j];
		}
	}
}

template<typename T>
Matrix<T>::~Matrix() { // destructor
	for (int i = 0; i < row; i++) {
		delete[]matrix[i];
	}
	delete[]matrix;
	row = 0;
	coloum = 0;
}
//specialized class functions start from here
template<>
Matrix<char*>::~Matrix() { // destructor
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < coloum; j++) {
			delete[]matrix[i][j];
		}
	}
	for (int i = 0; i < row; i++) {
		delete[]matrix[i];
	}
	delete[]matrix;
	row = 0;
	coloum = 0;
}
template<>
Matrix <char *>::Matrix(Matrix const &obj) { // specialized copy constructor
	this->coloum = obj.coloum;
	this->row = obj.row;

	matrix = new char**[row]; // allocate memory
	for (int i = 0; i < row; i++) {
		matrix[i] = new char*[coloum];
	}
	for (int i = 0; i < row; i++) { // copy data
		for (int j = 0; j < coloum; j++) {
			int size = stringSize(obj.matrix[i][j]);
			matrix[i][j] = new char[size + 1];
			matrix[i][j][size] = '\0';
			for (int k = 0; k < size; k++) {
				matrix[i][j][k] = obj.matrix[i][j][k];
			}
		}
	}
}

template<>
int Matrix<char *>::stringSize(char* string) { // return string size
	int size = 0;
	for (int i = 0; string[i] != '\0'; i++) {
		size++;
	}
	return size;
}

template<>
Matrix<char *>::Matrix(int rows, int coloums) { // specialized parametarized constructor for char*
	matrix = new char**[rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new char*[coloums];
	}
	coloum = coloums;
	row = rows;
}

template<>
void Matrix<char*>::insertElement(char* const &element, int rowNo, int colNo) { //enter data in matrices
	int size = stringSize(element);
	matrix[rowNo][colNo] = new char[size + 1];
	for (int i = 0; i <= size; i++) {
		matrix[rowNo][colNo][i] = element[i];
	}
}
template<>
Matrix<char*> Matrix<char*>:: operator+(Matrix const& obj) { // concatinate 2 strings
	Matrix<char*>temp(this->row, this->coloum);
	int index = 0; // temp third index;
	if (this->row == obj.row && this->coloum == obj.coloum) { //concatinate 2 string and store into temp objects.
		for (int i = 0; i < this->row; i++) {
			for (int j = 0; j < this->coloum; j++) {
				index = 0;
				int size1 = stringSize(this->matrix[i][j]);
				int size2 = stringSize(obj.matrix[i][j]);
				int size3 = size1 + size2;
				temp.matrix[i][j] = new char[size3 + 1];
				temp.matrix[i][j][size3] = '\0';
				for (int k = 0; k < size1; k++) {
					temp.matrix[i][j][index] = this->matrix[i][j][k];
					index++;
				}
				for (int k = 0; k < size2; k++) {
					temp.matrix[i][j][index] = obj.matrix[i][j][k];
					index++;
				}
			}
		}
	}
	else {
		cout << "Rows and coloums of both matices are not same : ";
	}
	return temp;
}

template<>
Matrix<char*> Matrix<char*> :: operator=(Matrix<char*>const& obj) { // perform assignment operation
	this->coloum = obj.coloum;
	this->row = obj.row;

	matrix = new char**[row];
	for (int i = 0; i < row; i++) { // allocate memory
		matrix[i] = new char*[coloum];
	}
	for (int i = 0; i < row; i++) { // copy data
		for (int j = 0; j < coloum; j++) {
			int size = stringSize(obj.matrix[i][j]);
			matrix[i][j] = new char[size + 1];
			matrix[i][j][size] = '\0';
			for (int k = 0; k < size; k++) {
				matrix[i][j][k] = obj.matrix[i][j][k];
			}
		}
	}
	return *this;
}

template<>
void Matrix<char*>::transpose() { // specialized function for transpose 
	Matrix<char*>temp(this->coloum, this->row);
	int tempColoum = 0;
	for (int i = 0; i < this->row; i++) {
		int tempRow = 0;
		for (int j = 0; j < this->coloum; j++) {
			int size1 = stringSize(this->matrix[i][j]);
			temp.matrix[tempRow][tempColoum] = new char[size1 + 1];
			temp.matrix[tempRow][tempColoum][size1] = '\0';
			for (int k = 0; k < size1; k++) {
				temp.matrix[tempRow][tempColoum][k] = this->matrix[i][j][k];
			}
			tempRow++;
		}
		tempColoum++;
	}
	int tem = row;
	row = coloum;
	coloum = tem;

	for (int i = 0; i < row; i++) { // delete matrices
		for (int j = 0; j < coloum; j++) {
			delete[]matrix[i][j];
		}
	}
	for (int i = 0; i < row; i++) {
		delete[]matrix[i];
	}
	delete[]matrix;

	matrix = new char**[row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new char *[coloum];
	}

	for (int i = 0; i < row; i++) { // copy data
		for (int j = 0; j < coloum; j++) {
			int size = stringSize(temp.matrix[i][j]);
			matrix[i][j] = new char[size + 1];
			matrix[i][j][size] = '\0';
			for (int k = 0; k < size; k++) {
				matrix[i][j][k] = temp.matrix[i][j][k];
			}
		}
	}
}

template<>
bool Matrix<char*>::compare(char *s1, char *s2) { // specialized function for compare 2 matrices
	while (*s1 == *s2)
	{
		if (*s1 == '\0' && *s2 == '\0')
			return true;
		s1++;
		s2++;
	}

	return false;
}

template<>
bool Matrix<char*>:: operator==(Matrix<char*>const& obj) {
	int totalEntries = (this->row) * (this->coloum); // store total number of entries
	int match = 0; // count how many entries are same
	if (this->coloum == obj.coloum && this->row == obj.row) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < coloum; j++) {
				if (compare(matrix[i][j], obj.matrix[i][j])) {
					match++;
				}
				else {
					return 0;
				}
			}
		}
	}
	if (match == totalEntries) {
		return 1;
	}
	else {
		return 0;
	}

}



int main() {

	//Note I'm using 2017 visual studio
	Matrix <int> m1(2, 3);
	m1.insertElement(1, 0, 0);
	m1.insertElement(1, 0, 1);
	m1.insertElement(1, 0, 2);
	m1.insertElement(0, 1, 0);
	m1.insertElement(0, 1, 1);
	m1.insertElement(0, 1, 2);
	cout << "->M1\n";
	m1.print();
	m1.transpose();
	cout << "->M1Transpose \n";
	m1.print();

	Matrix <int> m2(2, 3);
	m2.insertElement(-1, 0, 0);
	m2.insertElement(-1, 0, 1);
	m2.insertElement(-1, 0, 2);
	m2.insertElement(10, 1, 0);
	m2.insertElement(5, 1, 1);
	m2.insertElement(1, 1, 2);
	cout << "->M2\n";
	m2.print();
	m2.transpose();
	cout << "->M2Transpose \n";
	m2.print();
	Matrix <int> m3(m2);
	Matrix <int> m4(m1 + m3);
	cout << "->M4\n";
	m4.print();
	m4.transpose();
	cout << "->M4 Transpose\n";
	m4.print();
	cout << "************************\n";

	Matrix <char*> mA(2, 2);
	mA.insertElement((char*)"Computer", 0, 0);
	mA.insertElement((char*)"Electrical", 0, 1);
	mA.insertElement((char*)"Business", 1, 0);
	mA.insertElement((char*)"Civil", 1, 1);
	cout << "->mA\n";
	mA.print();
	Matrix<char*>mB(2, 2);
	mB.insertElement((char*)"Science", 0, 0);
	mB.insertElement((char*)"Engineering", 0, 1);
	mB.insertElement((char*)"Administration", 1, 0);
	mB.insertElement((char*)"Engineering", 1, 1);
	cout << "->mB\n";
	mB.print();
	Matrix<char*> mC(2, 2);
	Matrix<char*> mD(2, 2);
	mC = mA + mB;
	cout << "->mC\n";
	mC.print();
	mD = mA + mB;
	mC.transpose();
	cout << "->mC Transpose \n";
	mC.print();
	cout << "-> mC == mD : ";
	cout << (mC == mD);
	cout << "\n\n\n";
	//Note I'm using 2017 visual studio
	return 0;
}