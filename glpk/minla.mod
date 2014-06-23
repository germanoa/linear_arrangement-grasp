######################################################################
# Formulacao de Arranjo Linear Minimo (MinLA)
######################################################################

## Numero de vertices
param n;

## Conjunto de vertices
set V := 0..n-1;

## Conjunto de arestas
set A within V cross V;

## Variaveis de decisao
var x {V,V} binary;
var d {A};

minimize totalDistance:
	sum {(u,v) in A} d [u,v];

subject to map {v0 in V}:
	sum {v1 in V} x[v0,v1] = 1;

subject to injective {v1 in V}:
	sum {v0 in V} x[v0,v1] = 1;

subject to distance1 {(u,v) in A}:
	d[u,v] >= sum {v1 in V} (v1*x[u,v1]-v1*x[v,v1]);

subject to distance2 {(u,v) in A}:
	d[u,v] >= sum {v1 in V} (v1*x[v,v1]-v1*x[u,v1]);

end;
