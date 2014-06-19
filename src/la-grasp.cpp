#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib> 
#include <vector>
#include <queue>

using namespace std;

#define MAXSOL 999999999
#define THREADS 1
#define FREE 1

typedef vector<int> vi;

vector<vi> adj_list;
vector<int>::iterator it_adj_list;

int tentativas = 0;
int best_x = MAXSOL;
int x;
int n,m;
int it,r;
string infile;
//vi vertex_degree;
priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > vertex_degree;
//priority_queue< pair<int,int>, vector< pair<int,int> >  > vertex_degree;
int null;
vi sol;
ofstream logfile;
//hashtable com solucoes iniciais jah testadas


void read_input() {
	// n vertexes
	cin >> n;
	// m edges
	cin >> m;

	int temp;
	for (int i=0; i<n; ++i) {
		cin >> temp;
		vertex_degree.push( make_pair(temp,i) );
		//vertex_degree.push_back(temp);
	}
	
	adj_list.assign(n,vi());
	int it_m = m;
	int v1,v2;
	while (it_m--) {
		cin >> v1;
		cin >> v2;
		//adj_list[v1].push_back(v2);
		adj_list[v2].push_back(v1);
	}

	//-1
	cin >> null;

}

int is_new_initial_solution() {
	return 1;
}

int solution_cost() {
	int cost=0;
	int x;
	for (int u=0; u<n; ++u) {
		for (int v=0; v < (int) adj_list[u].size(); ++v) {
			x = sol[u] - sol[adj_list[u][v]];
			if (x<0) { x=x*-1; };
			cost += x;
		}
	}
	tentativas++;
	return cost;
}

void print_solution() {
	for (int i=0; i<n; ++i) {
		printf("%d -> %d\n",i,sol[i]);
	}
}

void print_status() {
	cout << "############" << endl;
	cout << "tentativas: " << tentativas << endl;
	cout << "x: " << x << endl;
	cout << "best_x: " << best_x << endl;
	cout << "############" << endl;
	logfile.open("out/logfile.txt",ios::app);
	logfile << infile << ";" << best_x << ";" << it << ";" << r << endl;
	logfile.close();
}

void construct(int r) {
	//priority_queue< pair<int,int>, vector< pair<int,int> > > rcl;
	priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > rcl;
	rcl = vertex_degree;
	int i=0;
	int next_candidate; //next_candidate = vertex with high degree (more neighbor)
	int candidate_neighbor;
//	int neighbors;


	sol.assign(n,FREE);
	while(i<n) {
		// next_candidate vertex
		next_candidate=rcl.top().second;
		//neighbors=rcl.top().first;
		rcl.pop();

		if (sol[next_candidate]==FREE) {
			// STEP1: randomness
			// next_candidate can be rejected and its priority decremented
			//if (r!=0) {
			//	//some code
			//}

			//STEP2: select candidate to linear arrangement 
			sol[next_candidate]=i;
			++i;
			if (i==n) { break; }

			//STEP3: j neighbors must be near from candidate selected
			//for (int j=0; j<neighbors; ++j) {
			for (it_adj_list = adj_list[next_candidate].begin(); it_adj_list != adj_list[next_candidate].end(); ++it_adj_list) {
				candidate_neighbor=sol[*it_adj_list];

				if (sol[candidate_neighbor]==FREE) {
					sol[candidate_neighbor]=i;
					++i;
					if(i==n) { break; }
				}
			} 

		}
	}

	x = solution_cost();
	if (x < best_x) {
		best_x = x;
	}
}

//move
void invert(int i, int j) {
	int temp = sol[i];
	sol[i] = sol[j];
	sol[j] = temp;
}

int local_search() {
	int temp;
	int local_x = MAXSOL;	
	int partitions = n/THREADS;
	
	for (int i=0; i<partitions-1; ++i) {
		for (int j=0; j<THREADS; ++j) { 
			invert(j+i,j+i+1);
			temp = solution_cost();
			if (temp < local_x) {
				local_x = temp;
			}  
		}
	}
	return local_x;
}

int main(int argc, char* argv[]) {

	if (argc!=4) {
		fprintf(stderr,"exatos 3 argumentos.\n");
		return 1;
	}

	it = atoi(argv[1]); //iterations
	r = atoi(argv[2]);	//randomness
	infile = argv[3];

	read_input();

	//GRASP
	int _it = it;
	while(_it--) {
		construct(r);
		if (is_new_initial_solution()) {
			x = local_search();
			if (x < best_x) {
				best_x = x;
				cout << "CONGRATULATIONS! new best!" << endl;
			}
		}
	}
	print_status();
}
