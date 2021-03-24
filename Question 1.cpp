#include<iostream>

using namespace std;
template<typename T>

class Matrix {
private:
	T ** matrix;
	int row;
	int coloum;
public:
	Matrix(int rows, int columns); // parameterized constructor
	Matrix(Matrix const &obj); // copy constructor
	void insertElement(T const &element, int rowNo, int colNo); // insert element in given index
	Matrix<T> operator+(Matrix const& obj); // add teo objects
	void print();//print matrices
	void transpose(); // take transpose of matrices
	~Matrix() { // destructor
		for (int i = 0; i < row; i++) {
			delete []matrix[i];
		}
		delete[]matrix;
		row = 0;
		coloum = 0;
	}
};
template<typename T>

Matrix<T>::Matrix(int rows, int coloums) {
	matrix = new T*[rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new T[coloums];
	}
	coloum = coloums;
	row = rows;
}
template<typename T>
Matrix <T>::Matrix(Matrix const &obj) {
	this->coloum = obj.coloum;
	this->row = obj.row;
	
	matrix = new T*[row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new T[coloum];
	}
	
	for(int i = 0; i< row; i++){
		for(int j = 0; j< coloum; j++){
			matrix[i][j] = obj.matrix[i][j];
		}
	}
}
template<typename T>
void Matrix<T>::insertElement(T const &element, int rowNo, int colNo) {
	matrix[rowNo][colNo] = element;
}

template<typename T>
Matrix<T> Matrix<T>:: operator+(Matrix const& obj) {
	if (this->row == obj.row && this->coloum == obj.coloum) {
		Matrix<T>temp(this->row,this->coloum);
		for (int i = 0; i < this->row; i++) {
			for (int j = 0; j < this->coloum; j++) {
				temp.matrix[i][j] = this->matrix[i][j] + obj.matrix[i][j];
			}
		}
		return temp;
	}
	else {
		cout << "Rows and coloums of both matices are not same : ";
	}
}

template<typename T>
void Matrix <T>:: print() {
	for(int i = 0;i< row; i++){
		for (int j = 0; j < coloum; j++) {
			cout << matrix[i][j]<<"\t";
		}
		cout << endl;
	}
}

template<typename T>
void Matrix<T>:: transpose() {
	
	Matrix<T>temp(this->coloum, this->row);
	int tempColoum = 0;
	for (int i = 0; i < this->row; i++) {
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
	for (int i = 0; i < coloum; i++) {
		delete[]matrix[i];
	}
	delete[]matrix;
	matrix = new T*[row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new T[coloum];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < coloum; j++) {
			matrix[i][j] = temp.matrix[i][j];
		}
	}
}

int main() {
	Matrix <int> m1(2, 3);
	m1.insertElement(1, 0, 0);
	m1.insertElement(1, 0, 1);
	m1.insertElement(1, 0, 2);
	m1.insertElement(0, 1, 0);
	m1.insertElement(0, 1, 1);
	m1.insertElement(0, 1, 2);

	cout << "M1\n";
	m1.print();

	m1.transpose();
	cout << "M1 Transpose\n";
	m1.print();

	Matrix <int> m2(2, 3);
	m2.insertElement(-1, 0, 0);
	m2.insertElement(-1, 0, 1);
	m2.insertElement(-1, 0, 2);
	m2.insertElement(10, 1, 0);
	m2.insertElement(5, 1, 1);
	m2.insertElement(1, 1, 2);
	cout << "M2\n";
	m2.print();

	m2.transpose();
	cout << "M2 Transpose\n";
	m2.print();

	Matrix <int> m3(m2);
	Matrix <int> m4(m1 + m3);

	cout << "M4 \n";
	m4.print();
	m4.transpose();
	cout << "M4 Transpose\n";
	m4.print();
}