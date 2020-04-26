/*
 * main.cpp
 *
 *  Created on: Apr 24, 2020
 *      Author: adrian-estelio
 */

#include <iostream>
#include <time.h>
using namespace std;
double  prob(void){
	double result = rand();
	result= result/RAND_MAX;
return result ;
}
class graph{
public:
	graph(int n = 0){
		size = n;
		matrix = new bool*[size];
		for(int i = 0; i < size;  i++ )
			matrix[i] = new bool[size];
		cout<<"Class Constructed , empty matrix, size :"<<size<<endl;
	};
	void print(void){
		cout<<"se puede"<<endl;
	};
	void MonteCarlo(double density, int initialCost, int Range);
	void printt(void);


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
void graph::MonteCarlo(double density, int initialCost, int Range){
	for(int i=0; i< graph::size;++i)
		for(int j = i;j<graph::size;++j)
			if (i==j)
				graph::matrix[i][j]=graph::matrix[j][i]=false;
			else
				graph::matrix[i][j]=graph::matrix[j][i]=(prob()<density);
	return ;
}

void graph::printt( void ){
	for(int i=0; i< graph::size;++i){
		cout<<endl;
		for(int j = 0;j<graph::size;++j)
			cout<<graph::matrix[i][j];
	}
	cout<<endl;
}

int main() {
	srand(time(0));
	graph g(3);
	g.MonteCarlo(0.1,2,3);
	bool f = true;
	cout<<f<<endl;
	g.printt();
	return 0;
}


