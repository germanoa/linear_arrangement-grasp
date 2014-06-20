#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib> 
#include <unistd.h>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

#define MAXSOL 999999999
#define THREADS 1
#define FREE 0
#define BUSY -1
#define MAXVERTEX 9800

#define NEIGHBOR 1

typedef vector<int> vi;

vector<vi> adj_list;
vector<int>::iterator it_adj_list;

int matrix[MAXVERTEX][MAXVERTEX];
int sol[MAXVERTEX];

int tentativas = 0;
int best_x = MAXSOL;
int x;
int n,m;
int it,r;
string infile;
priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > vertex_degree;
int null;
ofstream logfile;
//hashtable com solucoes iniciais jah testadas


void init_matrix() {
	for (int i=0; i<MAXVERTEX;++i) {
		for (int j=0; j<MAXVERTEX;++j) {
			matrix[i][j]=FREE;
		}
	}
}

void init_sol() {
	for (int i=0; i<MAXVERTEX;++i) {
		sol[i]=FREE;
	}
}

void read_input() {
	// n vertexes
	cin >> n;
	// m edges
	cin >> m;

	int temp;
	for (int i=0; i<n; ++i) {
		cin >> temp;
		vertex_degree.push( make_pair(temp,i) );
	}
	
	adj_list.assign(n,vi());
	int it_m = m;
	int v1,v2;
	while (it_m--) {
		cin >> v1;
		cin >> v2;
		adj_list[v1].push_back(v2);
		//adj_list[v2].push_back(v1);
		matrix[v1][v2]=NEIGHBOR;
		matrix[v2][v1]=NEIGHBOR;
	}

	//-1
	cin >> null;

}

int is_new_initial_solution() {
	return 1;
}

// objective function (Z)
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
	//cout << cost << endl;
	//sleep(1);
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

// construct with greedy and randomness
void construct(int r) {
	queue<int> pre_sol;
	vector<int> rcl; //value based scheme 
	int order=1;
	int selected, candidate;

	init_sol();

	//if ((rand() % n) <= 5 * r) { }

	//random part
	selected = rand() % n;
	cout << "first: " << selected << endl;
	pre_sol.push(selected);
	//pre_sol.push(vertex_degree.top().second);

	while(!pre_sol.empty()) {
		selected = pre_sol.front();
		pre_sol.pop();
		
		sol[selected]=order++;

		//greedy part
		for (int i=0;i<MAXVERTEX;++i) {
			if (matrix[selected][i]	== NEIGHBOR) {
				if (sol[i] == FREE) {
					sol[i]=BUSY;
					rcl.push_back(i);
				}
			}
		}	
	
		//random part
		while (!rcl.empty()) {
                        candidate = rand() % rcl.size();
                        selected = rcl[candidate];
                        pre_sol.push(selected);
                        rcl.erase(rcl.begin()+candidate);
		}
	
		// vertex whitout neighbors until now
		if (pre_sol.empty()) {
			if (order!=n) {
				for (int i=0;i<MAXVERTEX;++i) {
					if (sol[i]==FREE) {
						sol[i]=BUSY;
						pre_sol.push(i);
					}
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
	if (local_x < x) {
		cout <<" best local!\n" << endl;
	}
}

int main(int argc, char* argv[]) {

	if (argc!=4) {
		fprintf(stderr,"exatos 3 argumentos.\n");
		return 1;
	}

	it = atoi(argv[1]); //iterations
	r = atoi(argv[2]);	//randomness
	infile = argv[3];

		
	//random seed
	srand( static_cast<unsigned>( time( 0 ) ) );

	read_input();

	//GRASP
	for (int i=0; i<it; ++i) {
		//cout << "iteracao: " << i << endl;
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
