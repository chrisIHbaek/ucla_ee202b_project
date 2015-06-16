#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

int main(){

	// Read the txt file which contains two n*n matrix
	ifstream file("matrix.txt");

	// Error message
	if (!file){
		cout << "error: can't open the file" << endl;
		return 1;
	}	

	// Obtain the number of rows in the txt file and read all the integers in the txt file
	string file_row;
	int count = 0;
	queue<int> iqueue; 
	while (file) {
		getline(file, file_row);
		if (file_row.length()>0){
			count++;
			string integer = "";
			for (size_t i = 0; i < file_row.length(); i++){				
				if (file_row[i]!=' '){
					integer += file_row[i];
				}
				else if (file_row[i]==' '){
					char *temp = new char[integer.length()];
					for (size_t i = 0; i < integer.length(); i++){
						temp[i] = integer[i];
					}
					int result = atoi(temp);
					iqueue.push(result);
					integer = "";
					delete[] temp;
				}				
			}
		}
	}

	// Calucalte the dimension of the n*n matrix in the txt file
	int dim = count / 2;

	// Dynamically allocate memory for matrix a, matrix b and matrix c
	int **a = new int*[dim];
	for (int i = 0; i < dim; i++){
		a[i] = new int[dim];
	}
	int **b = new int*[dim];
	for (int i = 0; i < dim; i++){
		b[i] = new int[dim];
	}
	int **c = new int*[dim];
	for (int i = 0; i < dim; i++){
		c[i] = new int[dim];
	}

	// Initialize matrix a, matrix b and matrix c
	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){
			a[i][j] = iqueue.front();
			iqueue.pop();
		}
	}
	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){
			b[i][j] = iqueue.front();
			iqueue.pop();
		}
	}
	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){
			c[i][j] = 0;
		}
	}

	// Matrix multiplication
	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){
			for (int k = 0; k < dim; k++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	// Store the result of matrix multiplication in a new txt file
	FILE* result = fopen("result.txt","w");
	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){
			if (j == dim - 1){
				fprintf(result, "%d\n", c[i][j]);
			}
			else{
				fprintf(result, "%d ", c[i][j]);
			}
		}
	}
	fclose(result);

	// Verification
/*	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){
			cout << b[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
*/

	// Free the dynamically allocated memory
	for (int i = 0; i < dim; i++){
		delete[] a[i];
	}
	delete[] a;
	for (int i = 0; i < dim; i++){
		delete[] b[i];
	}
	delete[] b;
	for (int i = 0; i < dim; i++){
		delete[] c[i];
	}
	delete[] c;

	return 0;
}