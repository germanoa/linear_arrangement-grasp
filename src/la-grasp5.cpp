#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> 
#include <unistd.h>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

#define MAXSOL 999999999
#define THREADS 1
#define FREE 0
#define BUSY -1
#define MAXVERTEX 9800

typedef vector<int> vi;

vector<vi> al;
vector<int>::iterator it_al;

int tentativas = 0;
int first_x;
int best_x = MAXSOL;
vi degrees;
vi neighbors;
vi n_neighbors;
int x;
int n,m;
int it;
string infile;
int null;
int my_random;
int sol[MAXVERTEX];
ofstream logfile;
float exec_time;

void init_sol() {
        for (int i=0; i<MAXVERTEX;++i) {
                sol[i]=FREE;
        }
}

void read_input() {
	cin >> n;
	cin >> m;

	int temp;
	for (int i=0; i<n; ++i) {
		cin >> temp;
		degrees.push_back(temp);
	}

	for (int i=0; i<2*m; ++i) {
		cin >> temp;
		neighbors.push_back(temp);
	}

	//-1
	cin >> null;

	for (int i=0; i<n+1; ++i) {
		cin >> temp;
		n_neighbors.push_back(temp);
	}

	al.assign(n,vi());
	for (int i=0; i<n; ++i) {
		for (int j=n_neighbors[i]; j<n_neighbors[i+1]; ++j) {
			al[i].push_back(neighbors[j]);
			//al[neighbors[j]].push_back(i);
		}
	}

}

int is_new_initial_solution() {
	return 1;
}

int solution_cost() {
	int cost=0;
	for (int u=0; u<n; ++u) {
		for (int v=0; v < (int) al[u].size(); ++v) {
			cost +=abs(sol[u] - sol[al[u][v]]);
		}
	}

	cost = cost/2; //because double adj_list

	if (tentativas==0) {
		first_x = cost;
	}
	tentativas++;

	return cost;
}

//move: elementary modification
void static inline _invert(int i, int j) {
	int temp = sol[i];
	sol[i] = sol[j];
	sol[j] = temp;
}

void print_solution() {
	for (int i=0; i<n; ++i) {
		printf("%d -> %d\n",i,sol[i]);
	}
}

static inline int _diff_cost(int v1, int v2, int bigger, int _it, int _over) {
	int ret=0;
	for (int v=0; v < _it; ++v) {
		ret +=abs(sol[v1] - sol[al[v1][v]]);
		ret +=abs(sol[v2] - sol[al[v2][v]]);

	}
	for (int v=_it; v < _it+_over; ++v) {
		if (bigger==1) {
			ret +=abs(sol[v1] - sol[al[v1][v]]);
		} else {
			ret +=abs(sol[v2] - sol[al[v2][v]]);
		}
	}
	return ret;
}

void update_cost(int v1, int v2) {
	int v1_neighbors, v2_neighbors;

	//to save neighbors iterations
	v1_neighbors = (int) al[v1].size();
	v2_neighbors = (int) al[v2].size();
	int _it, _over, bigger;
	if (v1_neighbors>v2_neighbors) {
		_it=v2_neighbors;
		_over=v1_neighbors-v2_neighbors;
		bigger=1;
	} else {
		_it=v1_neighbors;
		_over=v2_neighbors-v1_neighbors;
		bigger=2;
	}

	int diff_to_del = _diff_cost(v1,v2,bigger,_it,_over);
	_invert(v1,v2);
	int diff_to_add = _diff_cost(v1,v2,bigger,_it,_over);


	if (diff_to_del>diff_to_add) {
		x = x - diff_to_del;
		x += diff_to_add;
	} else {
		_invert(v2,v1); //revert attempt
	}

	++tentativas;
}


void print_status() {
	cout << infile << ";" << first_x << ";" << best_x << ";" << setprecision(6) << exec_time << ";" << it << ";" << tentativas << endl;
}

void construct() {
        queue<int> pre_sol;
        vector<int> rcl; //value based scheme 
        int order=1;
        int selected, neighbor, candidate;

        init_sol();


        //my_random part
	if (my_random) {
	        selected = rand() % n;
	} else {
		selected=0;
	}
        pre_sol.push(selected);

        while(!pre_sol.empty()) {
                selected = pre_sol.front();
                pre_sol.pop();
     
                sol[selected]=order++;

                //greedy part
		for (int v=0; v < (int) al[selected].size(); ++v) {
                        neighbor = al[selected][v];
                        if (sol[neighbor] == FREE) {
                        	sol[neighbor]=BUSY;
                        	if (my_random) {
					rcl.push_back(neighbor);
				} else {
					pre_sol.push(neighbor);
				}
                        }
                }    
     
                //my_random part
		if (my_random) {
	                while (!rcl.empty()) {
				candidate = rand() % rcl.size();
	                        selected = rcl[candidate];
	                        pre_sol.push(selected);
	                        rcl.erase(rcl.begin()+candidate);
	                }
		}
                // vertex whitout neighbors until now
                if (pre_sol.empty()) {
                        if (order!=n) {
                                for (int i=0;i<n;++i) {
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

void local_search() {
	int partitions = n/THREADS;
	
	for (int i=0; i<partitions-1; ++i) {
		for (int j=0; j<THREADS; ++j) { 
			update_cost(j+i,j+i+1);
		}
	}
}

int parse_args(int argc, char* argv[]) {
	if (argc!=4) {
		fprintf(stderr,"it my_random(0,1) file < file.\n");
		return 0;
	}

	it = atoi(argv[1]);
	my_random = atoi(argv[2]);
	infile = argv[3];
	return 1;
}

int main(int argc, char* argv[]) {
	clock_t start_clock = clock();

	if (!parse_args(argc, argv)) {
		return 1;
	}

        //my_random seed
        srand(time(NULL));

	read_input();

	//GRASP
	for (int i=0; i<it; ++i) {
		construct();
		if (is_new_initial_solution()) {
			local_search();
			if (x < best_x) {
				best_x = x;
			}
		}
	}
	exec_time = 1.0 * (clock() - start_clock) / CLOCKS_PER_SEC;
	print_status();
}
