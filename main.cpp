/*
 * main.cpp
 *
 *  Created on: Apr 24, 2020
 *      Author: adrian-estelio
 */

#include <iostream>
#include <time.h>
#include <limits.h>
#include <string.h>
using namespace std;
double  prob(void){
	double result = rand();
	result= result/RAND_MAX;
return result ;
}

struct edgenode {
	int y;
	int weight;
	struct edgenode *next;
};

typedef struct {
	edgenode **edges;
	int *degree;
	int nvertices;
	int nedges;
	bool directed;
}AdjancencyList;

void insert_edge(AdjancencyList *g ,int x, int y, int weight,bool directed){
	edgenode *p;
	p = new edgenode;
	p ->weight = weight;
	p ->y =y;
	p ->next = g->edges[x];
	g->edges[x] = p;
	g->degree[x] ++;
	if (directed==false){
		insert_edge(g,y,x,weight,true);
	}
	else g->nedges++;
	//cout<<"Edge inserted<< " <<x<<"<->"<<y<<" peso :"<< p ->weight<<endl;
}

int genCost(int initialCost,int  Range){
	double aux = rand();
	aux= aux/RAND_MAX *(Range -initialCost);
	int result = initialCost+static_cast<int>(aux);
	return result;
}
class graph{
public:

	graph(int n, bool directed){
		List= new AdjancencyList;
		int i;
		List->nvertices = n;
		List->nedges = 0;
		List->directed = directed;
		List->degree = new int[n];
		List->edges = new edgenode*[n];
		for (i=0; i<n; i++)
			List->degree[i] = 0;
		for (i=0; i<n; i++)
			List->edges[i] = NULL;
		distance = new int[n];
		cout<<"Class Constructed , empty matrix, size :"<<n<<endl;
	};
	void init(int n = 0, bool directed = false);
	void print_graph(void);
	//	cout<<"se puede"<<endl;
	//};
	void MonteCarlo(double density, int initialCost, int Range);
	//void printt(void);
	int *dijkstra(int start);
	void release(void){
		delete [] List->degree;
		delete [] List->edges;
		delete List;
		delete [] distance;
	}

	~graph(){
		cout<<"Class Destructed"<<endl;
	}
	int *distance;
private:
	AdjancencyList *List;

};

void graph::MonteCarlo(double density, int initialCost, int Range){
	int weight=0;
	for(int i=0; i< graph::List->nvertices;++i)
		for(int j = i+1;j<graph::List->nvertices;++j)
			if ((prob()<density)){
				weight = genCost(initialCost, Range);
				insert_edge(List, i, j,weight ,false);
			}
}


void graph::print_graph( void ){
	edgenode *p;
	for(int i=0; i< graph::List->nvertices;++i){
		cout<<i<<" :";
		p=graph::List->edges[i];
		while(p != NULL){
			cout<<"->"<<p->y;
			p = p->next;
		}
	cout<<endl;
	}
}
int *graph::dijkstra(int start){
	int i;
	edgenode *p;
	bool intree[graph::List->nvertices];
	//int distance[g.size];
	int v;
	int w;
	int weight;
	int dist;
	int *distance;
	distance= new int[graph::List->nvertices];
	for (i=0; i <graph::List->nvertices;i++){
		intree[i] = false;
		distance[i] = INT_MAX;
	}
	distance[start] =0;
	v = start;
	p = graph::List->edges[v];
	while(!intree[v]){
		intree[v] = true;
		p = graph::List->edges[v];
			while(p!=NULL){
				w = p->y;
				weight = p->weight;
				if (distance[w] > (distance[v]+ weight)){
					distance[w] = distance[v]+ weight;
				}
				p = p ->next;
			}

		v =1;
		dist = INT_MAX;
		for(i = 0; i < graph::List->nvertices ;i++)
			if ((intree[i]==false)&&(dist>distance[i])){
				dist = distance[i];
				v = i;
				break;
			}

	}

	//memcpy(graph::distance[0] , distance[0],4);
	for (int i = 0; i <graph::List->nvertices;i++){
	if (distance[i] != INT_MAX)
		graph::distance[i] = distance[i];
	else graph::distance[i] = -1;
	}

	delete [] distance;

return graph::distance;
}
int main() {
	srand(time(0));
	graph g(50,false);
	g.MonteCarlo(0.05,2,8);
	int *a;
	a = new int[50];
	g.print_graph();
	a=g.dijkstra(0);
	for (int i = 0; i <50;i++){
	cout<<a[i]<<" ";
	}
	cout<<endl;
	delete[] a;
	return 0;
}


