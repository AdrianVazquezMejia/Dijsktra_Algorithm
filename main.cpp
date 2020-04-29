/*
 * main.cpp
 *
 *  Created on: Apr 24, 2020
 *      Author: adrian-estelio
 */

#include <iostream>
#include <time.h>
#include <limits.h>
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
void dijkstra(graph g, int start, int distance[]){
	int i;
	bool intree[g.size];
	//int distance[g.size];
	int v;
	int w;
	int weight;
	int dist;
	int parent[g.size];

	for (i=1; i <= g.size;i++){
		intree[i] = false;
		distance[i] = INT_MAX;
		parent[i] = -1;
	}
	distance[start] =0;
	v = start;
	while(!intree[v]){
		intree[v] = true;
		for(i =1;i <=g.size;i++){
			weight = g.matrix[v][i];
			while(weight!=0){
				w = i;
				if (distance[w] > (distance[v]+ weight)){
					distance[w] = distance[v]+ weight;
					parent[w] = v;
				}
			}
		}
		v =1;
		dist = INT_MAX;
		for(i =1; i <=g.size; i++){
			if ((intree[i]==false)&&(dist>distance[i])){
				dist = distance[i];
				v = i;
			}

		}
	}

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


