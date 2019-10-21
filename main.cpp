
//#include "/home/fernando/Snap-5.0/snap-core/Snap.h"

//#include "/home/fernando/Snap5.0/snap-core/stdafx.h"

#include "stdafx.h"
//#include "Snap.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <limits>
#include <queue>

typedef PNGraph Graph;  //   directed graph
//typedef PNEGraph PGraph;  //   directed multigraph
//typedef TNEGraph PGraph;  //   directed multigraph
//typedef PUNGraph PGraph; // undirected graph
//PGraph G = PGraph::TObj::New();
//typedef TPt<TNEANet> G;
//visited.assign(n, false);
PGraph G = PGraph::TObj::New();

using namespace TSnap;
using namespace std;
using namespace std::chrono;

void insertVertex(int valor){
	G->AddNode(valor);
}

void deleteVertex(int valor){
	G->DelNode(valor);
}

void deleteEdge(int v, int d){
	G->DelEdge(v, d);
}

void insertEdge(int v, int d, int w){
	G->AddEdge(v, d);
}




int main(int argc, char* argv[]){
return 0;
}
