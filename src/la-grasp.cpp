#include <iostream>
#include <stdio.h>
#include <cstdlib> 
#include <vector>

using namespace std;

//parametros
//numero iteracoes
// randomicidade p

typedef vector<int> vi;
//typedef pair<int,int> ii;
//typedef vector<ii> vii;

//estruturas dado global
vector<vi> adj_list;
int best_x = -1;
int n,m;
vi vertex_degree;
int null;
vi grasp_initial_solution;
//hashtable com solucoes iniciais jah testadas


// void read_input()
// popula a estrutura de dados (a escolher) que eh global
//popula com algum criterio de ordenacao (provavelmente grau dos vertices + proximidade)
// criacao da RCL

// sol_inicial = construct(p)
// constroi a solucao inicial com randomicidade p (0 = nada, 1 = 100% random)

void read_input() {
	// n vertexes
	cin >> n;
	// m edges
	cin >> m;

	
	int it_n = n;
	int temp;
	while (it_n--) {
		cin >> temp;
		vertex_degree.push_back(temp);
	}
	
	adj_list.assign(n,vi());
	int it_m = m;
	int v1,v2;
	while (it_m--) {
		cin >> v1;
		cin >> v2;
		adj_list[v1].push_back(v2);
		//adj_list[v2].push_back(v1);
	}

	//-1
	cin >> null;
	if (null==-1) {
		printf("ok\n");
	} else {
		printf("ops\n");
	}

}

int is_new_initial_solution() {
	return 1;
}

int solution_cost(vi s) {
	int cost=0;
	int x;
	for (int u=0; u<n; ++u) {
		for (int v=0; v < (int) adj_list[u].size(); ++v) {
			x = s[u] - s[adj_list[u][v]];
			if (x<0) { x=x*-1; };
			printf("cost: %d\n",cost);
			cost += x;
		}
	}
	return cost;
}

void print_solution() {
	for (int i=0; i<n; ++i) {
		printf("%d -> %d\n",i,grasp_initial_solution[i]);
	}
}

void construct(int p) {
	for (int i=0; i<n; ++i) {
		grasp_initial_solution[i]=i;
	}
}

int local_search() {
	return 0;
}

int main(int argc, char* argv[]) {

	if (argc!=3) {
		fprintf(stderr,"exatos 2 argumentos.\n");
		return 1;
	}

	int it = atoi(argv[1]);
	int p = atoi(argv[2]);	
	int x;

	read_input();

	
	grasp_initial_solution.assign(n,0);
	while(it--) {
		construct(p);
		if (is_new_initial_solution()) {
			x = solution_cost(grasp_initial_solution);
			//x = local_search();
			if (best_x < x) {
				best_x = x;
			}
		}
	}
	printf("%d\n",best_x);
	print_solution();
}
