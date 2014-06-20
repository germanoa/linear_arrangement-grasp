#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
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
int x;
int n,m;
int it;
string infile;
int null;
int sol[MAXVERTEX];
ofstream logfile;
float exec_time;
//hashtable com solucoes iniciais jah testadas

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
	}
	
	al.assign(n,vi());
	int it_m = m;
	int v1,v2;
	while (it_m--) {
		cin >> v1;
		cin >> v2;
		al[v1].push_back(v2);
		//al[v2].push_back(v1);
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
		for (int v=0; v < (int) al[u].size(); ++v) {
			x = sol[u] - sol[al[u][v]];
			if (x<0) { x=x*-1; };
			cost += x;
		}
	}

	if (tentativas==0) {
		first_x = cost;
	}

	tentativas++;
	return cost;
}

//move
void static inline _invert(int i, int j) {
	int temp = sol[i];
	sol[i] = sol[j];
	sol[j] = temp;
}

static inline int _diff_cost(int v1, int v2, int bigger, int _it, int _over) {
	int diff,ret=0;
	for (int v=0; v < _it; ++v) {
		diff = sol[v1] - sol[al[v1][v]];
		if (diff<0) { diff=diff*-1; };
		ret += diff;

		diff = sol[v2] - sol[al[v2][v]];
		if (diff<0) { diff=diff*-1; };
		ret += diff;
	}
	for (int v=_it; v < _over; ++v) {
		if (bigger==1) {
			diff = sol[v1] - sol[al[v1][v]];
			if (diff<0) { diff=diff*-1; };
			ret += diff;
		} else {
			diff = sol[v2] - sol[al[v2][v]];
			if (diff<0) { diff=diff*-1; };
			ret += diff;
		}
	}
	return ret;
}

int update_cost(int v1, int v2, int last_cost) {
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

	tentativas++;
	return last_cost - diff_to_del + diff_to_add;
}

void print_solution() {
	for (int i=0; i<n; ++i) {
		printf("%d -> %d\n",i,sol[i]);
	}
}

void print_status() {
	//logfile.open("out/logfile.txt",ios::app);
	//logfile << infile << ";" << first_x << ";" << best_x << ";" << setprecision(6) << exec_time << ";" << it << ";" << endl;
	//logfile.close();
	cout << infile << ";" << first_x << ";" << best_x << ";" << setprecision(6) << exec_time << ";" << it << ";" << tentativas << endl;
}

void construct() {
        queue<int> pre_sol;
        vector<int> rcl; //value based scheme 
        int order=1;
        int selected, neighbor, candidate;

        init_sol();

        //if ((rand() % n) <= 5 * r) { }

        //random part
        selected = rand() % n;
        pre_sol.push(selected);

        while(!pre_sol.empty()) {
                selected = pre_sol.front();
                pre_sol.pop();
     
                sol[selected]=order++;

                //greedy part
		//for (it_al = al[selected].begin(); it_al != al[selected].end(); ++it_al) {
                //        neighbor = *it_al;
		for (int v=0; v < (int) al[selected].size(); ++v) {
                        neighbor = al[selected][v];
                        if (sol[neighbor] == FREE) {
                        	sol[neighbor]=BUSY;
                        	rcl.push_back(neighbor);
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

int local_search() {
	int temp;
	int local_x = MAXSOL;	
	int partitions = n/THREADS;
	
	for (int i=0; i<partitions-1; ++i) {
		for (int j=0; j<THREADS; ++j) { 
			temp = update_cost(j+i,j+i+1,temp);
			//_invert(j+i,j+i+1);
			//temp = solution_cost();
			if (temp < local_x) {
				local_x = temp;
			}  
		}
	}
	return local_x;
}

int parse_args(int argc, char* argv[]) {
	if (argc!=3) {
		fprintf(stderr,"exatos 2 argumentos.\n");
		return 0;
	}

	it = atoi(argv[1]); //iterations
	infile = argv[2];
	return 1;
}

int main(int argc, char* argv[]) {
	clock_t start_clock = clock();

	if (!parse_args(argc, argv)) {
		return 1;
	}

        //random seed
        srand( static_cast<unsigned>( time( 0 ) ) );

	read_input();

	//GRASP
	for (int i=0; i<it; ++i) {
		construct();
		if (is_new_initial_solution()) {
			x = local_search();
			if (x < best_x) {
				best_x = x;
			}
		}
	}
	exec_time = 1.0 * (clock() - start_clock) / CLOCKS_PER_SEC;
	print_status();
}
