/*
 * main.cpp
 *
 *  Created on: Apr 24, 2020
 *      Author: AdrianVazquez
 */
/*
 *
 MIT License

Copyright (c) [2020] [Adrian Vazquez]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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

typedef struct {
	int key;
	int value;
}queue_elem;
typedef struct{
	queue_elem q[PQ_SIZE];
	int n;
}queue;
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
}


class p_queue{
public:
	p_queue(){
		q = new queue;
	}
	void insert(int x, int k);
	void make(int  *s , int *k, int n);
	void q_print(void);
	int extract_min(void);
	void heapsort(int *s,int *k,int n);
	int size(void);
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
		prev = new int[n];
		path = new int[n];
		pathSize = 0;
		cout<<"Class Constructed , empty matrix, size :"<<n<<endl;
		hops = 0;
	};
	void init(int n = 0, bool directed = false);
	void print_graph(void);
	int  *getPath(int u, int w );
	int getSize(int w);
	void MonteCarlo(double density, int initialCost, int Range);
	int *ShortestPath(int start);


	~graph(){
		release();
		cout<<"Class Destructed"<<endl;
	}

private:
	AdjancencyList *List;
	int *distance;
	int *path;
	int pathSize;
	int hops;
	int *prev;

	void find_path(int start, int end);
	void putIn(int p);
	int genCost(int initialCost,int  Range);
	void release(void){
		delete [] List->degree;
		delete [] List->edges;
		delete List;
		delete [] distance;
		delete [] prev ;
		delete [] path;
	}
};
int graph::genCost(int initialCost,int  Range){
	double aux = rand();
	aux= aux/RAND_MAX *(Range -initialCost);
	int result = initialCost+static_cast<int>(aux);
	return result;
}

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
int *graph::ShortestPath(int start){
	int i;
	edgenode *p;
	int v;
	int w;
	int weight;
	p_queue Q; // xxx Dynamic allocation of size
	distance= new int[List->nvertices];
	for (i=0; i <List->nvertices;i++){
		distance[i] = INT_MAX;
		prev[i] = -1;
	}
	distance[start] =0;
	v = start;
	Q.insert(v,distance[v]);
	p = List->edges[v];
	while(Q.size()!=0){
		v = Q.extract_min();
		p = List->edges[v];
			while(p!=NULL){
				w = p->y;
				weight = p->weight;
				if (distance[w] > (distance[v]+ weight)){
					distance[w] = distance[v]+ weight;
					Q.insert(w,distance[w]);
					prev[w] =v;
				}
				p = p ->next;
			}
	}
	for(i = 0; i < List->nvertices;i ++)
		if(distance[i] ==INT_MAX)
			distance[i] =-1;
return distance;
}

void graph::find_path(int start, int end){
	if ((start == end)||(end == -1)){
		putIn(start);
		cout<<endl;
	}
	else{
		find_path(start,prev[end]);
		putIn(end);
	}
}

void graph::putIn(int p){
	hops++;
	path[hops] = p;
}
int  p_queue::parent(int n){
	if (n==1)
		return -1;
	else
		return n/2;
}
void p_queue::insert(int x, int k){
	if (q->n >PQ_SIZE)
		cout<<"Warning, priority queue overflow "<<endl;
	else {
		q->n ++;
		q->q[q->n].value =x;
		q->q[q->n].key =k;
		bubble_up(q->n);
	}
}

void p_queue::bubble_up(int p){
	if (parent(p) == -1)
		return;
	if(q->q[parent(p)].key > q->q[p].key){
		swap(p,parent(p));
		bubble_up(parent(p));
	}
}
void p_queue::swap(int a , int b){
	queue_elem aux = p_queue::q->q[a];
	p_queue::q->q[a] = p_queue::q->q[b];
	p_queue::q->q[b] = aux;
}
void p_queue::make(int  *s , int *k ,int n){
	q->n = 0;
	for(int i =0; i<n; i++){
		insert(s[i],k[i]);
	}
}

void p_queue::q_print(void){
	for(int i =1; i<=p_queue::q->n; i++)
		cout<<" "<<p_queue::q->q[i].value;
	cout<<endl;
}

int p_queue::extract_min(void){
	int min = -1;   /* Minumun value*/
	if (q->n <=0)
		cout<<"Warning: empty priority queue"<<endl;
	else {

		min = q->q[1].value;
		q->q[1] = q->q[q->n];
		q->n = q->n -1;
		bubble_down(1);
	}
	return min;
}

void p_queue::bubble_down(int p){

	int c;
	int min_index;
	c = young_child(p);
	min_index = p;
	for(int i = 0;i<=1;i++)
		if (((c+i)<= q->n))
			if ((q->q[min_index].key > q->q[c+i].key))
				min_index= c+i;
	if (min_index!=p){
		swap(p, min_index);
		bubble_down(min_index);
	}
}
void p_queue::heapsort(int *s,int *k,int n){
	make(s,k,n);
	for(int i=0;i<n;i++)
		s[i] = extract_min();
}
int p_queue::young_child(int n){
	return 2*n;
}
int p_queue::size(void){
	return q->n;
}


int *graph::getPath(int u, int w){
	hops =0;
	find_path(u,w);
	return path;
}
int graph::getSize(int w){
	return distance[w];
}

int main() {
	srand(time(0));  /* initialize some variables*/
	int n = 50;		/* Graph size*/
	int *a;
	double density =0.4;
	int range =9;
	a = new int[n];

	graph g(n,false);       /* Initialize the graph */
	g.MonteCarlo(density,1,range); /* Fill graph,( precision, start range, range) */
	g.print_graph();        /*  Print graph in Adjacency List mode*/

	a=g.ShortestPath(0);    /* Shortest path starting in 0*/
	cout<<"Cost array: ";    /* Print cost array */
	for (int i = 0; i <n;i++){
	cout<<a[i]<<" ";
	}
	cout<<endl;
	/* Calculate average */
	int len = 0;
	int p = 0;
	int count = 0;
	for(int i = 0; i < n ; i++){
		p = g.getSize(i);
		if ( p>0){                 /*  Only count with are connected*/
			len = p +len ;
			count ++;
		}
	}
	double promedio = static_cast<double>(len)/static_cast<double>(count);
	cout<<"The average Cost is: "<<promedio<<endl;

	delete [] a;
	return 0;
}


