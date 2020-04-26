/*
 * main.cpp
 *
 *  Created on: Apr 24, 2020
 *      Author: adrian-estelio
 */

#include <iostream>
using namespace std;
class graph{
public:
	graph(int n = 0){
		size = n;
		matrix = new bool*[size];
		for(int i = 0; i < size;  i++ )
			matrix[i] = new bool[size];
		cout<<"Class Constructed , empty matrix, size :"<<size<<endl;
	};


	~graph(){
		for(int i = 0; i < size;  i++ )
			 delete [] matrix[i];
		delete [] matrix;
		cout<<"Class Destructed"<<endl;
	}

private:
	bool **matrix;
	int size;
};
int main() {
	graph g(4);
	return 0;
}


