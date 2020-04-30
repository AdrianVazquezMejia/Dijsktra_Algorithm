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

const int PQ_SIZE = 500;
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
	for (int i = 0; i <graph::List->nvertices;i++){
	if (distance[i] != INT_MAX)
		graph::distance[i] = distance[i];
	else graph::distance[i] = -1;
	}

	delete [] distance;

return graph::distance;
}
typedef struct{
	int q[PQ_SIZE];
	int n;
}queue;


class p_queue{
public:
	p_queue(){
		q = new queue;
	}

	void insert(int x);
	void make(int  s[] , int n);
	void q_print(void);
	int extract_min(void);
	void heapsort(int *s,int n);
	~p_queue(){
		delete q;
	}
private:
	int  parent(int n);
	void bubble_up(int p);
	void swap(int a , int b);
	void bubble_down( int p);
	int young_child(int n);
	queue *q;
};

int  p_queue::parent(int n){
	if (n==1)
		return -1;
	else
		return n/2;
}
void p_queue::insert(int x){
	if (p_queue::q->n >PQ_SIZE)
		cout<<"Warning, prority queue overflow "<<endl;
	else {
		p_queue::q->n ++;
		p_queue::q->q[p_queue::q->n] =x;
		bubble_up(p_queue::q->n);
	}
}

void p_queue::bubble_up(int p){
	if (p_queue::parent(p) == -1)
		return;
	if(p_queue::q->q[p_queue::parent(p)]>p_queue::q->q[p]){
		p_queue::swap(p, p_queue::parent(p));
		bubble_up(p_queue::parent(p));
	}
}
void p_queue::swap(int a , int b){
	int aux = p_queue::q->q[a];
	p_queue::q->q[a] = p_queue::q->q[b];
	p_queue::q->q[b] = aux;
}
void p_queue::make(int  s[] , int n){
	p_queue::q->n = 0;

	for(int i =0; i<n; i++){
		p_queue::insert(s[i]);
	}
}

void p_queue::q_print(void){
	for(int i =1; i<=p_queue::q->n; i++)
		cout<<" "<<p_queue::q->q[i];
	cout<<endl;
}

int p_queue::extract_min(void){
	int min = -1;   /* Minumun value*/
	if (q->n <=0)
		cout<<"Warning: empty priority queue"<<endl;
	else {

		min = q->q[1];
		q->q[1] = q->q[q->n];
		q->n = q->n -1;
		bubble_down(1);
	}
	cout<<min<<endl;
	return min;
}

void p_queue::bubble_down(int p){

	int c;
	int min_index;
	c = young_child(p);
	min_index = p;
	for(int i = 0;i<=1;i++)
		if (((c+i)<= q->n))
			if ((q->q[min_index] > q->q[c+i]))
				min_index= c+i;
	if (min_index!=p){
		swap(p, min_index);
		bubble_down(min_index);
	}
}
void p_queue::heapsort(int s[],int n){
	make(s,n);
	for(int i=0;i<n;i++)
		s[i] = extract_min();
}
int p_queue::young_child(int n){
	return 2*n;
}
int main() {
	srand(time(0));
	graph g(50,false);
	g.MonteCarlo(0.2,2,8);
	int *a;
	a = new int[50];
	g.print_graph();
	a=g.dijkstra(0);
	//for (int i = 0; i <50;i++){
	//cout<<a[i]<<" ";
	//}
	cout<<endl;
	cout <<endl;
	p_queue Q;
	Q.make(a+1,49);
	cout<<"MIn is:"<<Q.extract_min()<<endl;
	Q.q_print();
	Q.heapsort(a,10);
	for (int i = 0; i <10;i++){
	cout<<a[i]<<" ";
	}
	cout<<endl;
	cout<<endl;
	delete[] a;
	return 0;
}


