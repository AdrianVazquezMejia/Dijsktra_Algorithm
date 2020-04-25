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
	graph(int n = 0 ){
		size = n;
		cout<<"Class Constructed"<<endl;
		for(int i = 0; i < size;++i )
				matrix[i] = NULL;
	};

	~graph(){
		cout<<"Class Destructed"<<endl;
	}

private:
	bool **matrix;
	int size;
};
int main() {
	graph g;
}


