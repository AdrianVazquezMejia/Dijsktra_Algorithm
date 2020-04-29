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

void insert_edge(AdjancencyList *g ,int x, int y, bool directed){
	edgenode *p;
	p = new edgenode;
	p ->weight = 0;
	p ->y =y;
	p ->next = g->edges[x];
	g->edges[x] = p;
	g->degree[x] ++;
	if (directed==false)
		insert_edge(g,y,x,true);
	else g->nedges++;
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
		cout<<"Class Constructed , empty matrix, size :"<<n<<endl;
	};
	void init(int n = 0, bool directed = false);
	void print_graph(void);
	//	cout<<"se puede"<<endl;
	//};
	void MonteCarlo(double density, int initialCost, int Range);
	//void printt(void);
	void release(void){
		delete [] List->degree;
		delete [] List->edges;
		delete List;
	}

	~graph(){
		cout<<"Class Destructed"<<endl;
	}

private:
	AdjancencyList *List;
};

void graph::MonteCarlo(double density, int initialCost, int Range){
	for(int i=0; i< graph::List->nvertices;++i)
		for(int j = i+1;j<graph::List->nvertices;++j)
			if ((prob()<density))
				insert_edge(List, i, j, false);

}


void graph::print_graph( void ){
	edgenode *p;
	for(int i=0; i< graph::List->nvertices;++i){
		cout<<i<<" :";
		p=graph::List->edges[i];
		while(p != NULL){
			cout<<" "<<p->y;
			p = p->next;
		}
	cout<<endl;
	}
}/*
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

}*/
int main() {
	srand(time(0));
	graph g(1000,false);
	//g.init(1, false);
	g.MonteCarlo(0.01,2,3);
	bool f = true;
	cout<<f<<endl;
	g.print_graph();
	return 0;
}


