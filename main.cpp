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
	p ->weight = 2;
	p ->y =y;
	p ->next = g->edges[x];
	g->edges[x] = p;
	g->degree[x] ++;
	if (directed==false){
		insert_edge(g,y,x,true);
	}
	else g->nedges++;
	//cout<<"Edge inserted<< " <<x<<"<->"<<y<<" peso :"<< p ->weight<<endl;
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

private:
	AdjancencyList *List;
	int *distance;
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
		cout<<v<<endl;
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

	graph::distance = distance;
	for (int i = 0; i <4;i++){
	if (distance[i] != INT_MAX)
	cout<<distance[i]<<" ";
	else cout<<-1<<" ";

	}
	cout<<endl;
	delete [] distance;

return graph::distance = distance;;
}
int main() {
	srand(time(0));
	graph g(4,false);
	//g.init(1, false);
	g.MonteCarlo(1,2,3);
	int *a;
	a = new int[10];
	//bool f = true;

	g.print_graph();
	a=g.dijkstra(0);


	delete[] a;
	return 0;
}


