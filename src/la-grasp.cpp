#include <iostream>
#include <stdio.h>
#include <cstdlib> 

using namespace std;

//parametros
//numero iteracoes
// randomicidade p

//estruturas dado global
//graph
//hashtable com solucoes iniciais jah testadas
int best_x = 0;

// void read_input()
// popula a estrutura de dados (a escolher) que eh global
//popula com algum criterio de ordenacao (provavelmente grau dos vertices + proximidade)
// criacao da RCL

// sol_inicial = construct(p)
// constroi a solucao inicial com randomicidade p (0 = nada, 1 = 100% random)

void read_input() {
	printf("input\n");
}

int is_new_initial_solution(int s) {
	return 0;
}

int construct(int p) {
	return 0;
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
	int grasp_initial_solution;

	read_input();
	
	while(it--) {
		grasp_initial_solution = construct(p);
		if (is_new_initial_solution(grasp_initial_solution)) {
			x = local_search();
			if (best_x < x) {
				best_x = x;
			}
		}
	}

}
