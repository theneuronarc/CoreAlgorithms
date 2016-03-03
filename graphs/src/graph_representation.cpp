/*
Graph Representation
*/

#include "std_headers.h"

struct Edge;

typedef struct {
	int key;
	int color;
	struct Edge* head;
}Vertex;

typedef struct Edge{
	Vertex* src;
	Vertex* dst;
	int weight;
	struct Edge* next;
}Edge;

typedef struct {
	int vertexCount;
	Vertex* vertices;
}Graph;

Graph* createGraph(int vertexCount) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->vertexCount = vertexCount;
	g->vertices = (Vertex*)malloc(sizeof(Vertex)*vertexCount);
	for (int i = 0; i < vertexCount; i++) {
		g->vertices[i].head = 0;
		g->vertices[i].key = i;
		g->vertices[i].color = 0;
	}
	return g;
}

void destroyGraph(Graph* g) {
	for (int i = 0; i < g->vertexCount; i++) {
		Edge* t, * head = g->vertices[i].head;
		while (head) {
			t = head;
			head = head->next;
			free(t);
		}
	}

	free(g->vertices);
	free(g);
}

void addEdgeUndirected(Graph* g, int src, int dest, int weight) {
	Edge* e = (Edge*)malloc(sizeof(Edge));

	e->src = &(g->vertices[src]);
	e->dst = &(g->vertices[dest]);
	e->weight = weight;

	e->next = g->vertices[src].head;
	g->vertices[src].head = e;


	e = (Edge*)malloc(sizeof(Edge));

	e->src = &(g->vertices[dest]);
	e->dst = &(g->vertices[src]);
	e->weight = weight;

	e->next = g->vertices[dest].head;
	g->vertices[dest].head = e;
}

void addEdgeDirected(Graph* g, int src, int dest, int weight) {
	Edge* e = (Edge*)malloc(sizeof(Edge));

	e->src = &(g->vertices[src]);
	e->dst = &(g->vertices[dest]);
	e->weight = weight;

	e->next = g->vertices[src].head;
	g->vertices[src].head = e;
}

void printGraph(Graph* graph)
{
	int v;
	for (v = 0; v < graph->vertexCount; ++v)
	{
		Edge* pCrawl = graph->vertices[v].head;
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl)
		{
			printf("-> %d(%d)", pCrawl->dst->key, pCrawl->weight);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}

void BFS(Graph* g, Vertex* source) {
	//Vertex* source = &(g->vertices[0]);
	std::queue<Vertex*> fifo;
	source->color = 1;
	fifo.push(source);

	while (!fifo.empty()) {
		Vertex* node = fifo.front();
		printf("%d ", node->key);
		Edge* e = node->head;
		fifo.pop();

		while (e) {
			if (!e->dst->color) {
				fifo.push(e->dst);
				e->dst->color = 1;
			}
			e = e->next;
		}		
	}
}

void DFS(Graph* g, Vertex* source) {
	Edge* e = source->head;
	printf("\n%d ", source->key);
	while (e) {
		if (!e->dst->color) {
			e->dst->color = 1;
			DFS(g, e->dst);
		}	
		else {
			if (e->dst->color == 1)
				printf("\nCycle");

			if (e->dst->color == 2)
				printf("\nSibling");
		}
		e = e->next;
	}
	source->color = 2;
}

bool isCycleDFS(Graph* g, Vertex* source) {
	Edge* e = source->head;
	printf("\n%d ", source->key);
	while (e) {
		if (!e->dst->color) {
			e->dst->color = 1;
			if (isCycleDFS(g, e->dst))
				return true;
		}
		else {
			if (e->dst->color == 1) {
				printf("\nCycle");
				return true;
			}

			if (e->dst->color == 2)
				printf("\nSibling");
		}
		e = e->next;
	}

	source->color = 2;
	return false;
}

bool isCycle(Graph* g) {
	return isCycleDFS(g, &g->vertices[0]);
}

int main() {
	// create the graph given in above fugure
	int V = 5;
	Graph* graph = createGraph(V);
	addEdgeDirected(graph, 0, 1, 1);
	addEdgeDirected(graph, 4, 0, 2);
	addEdgeDirected(graph, 1, 2, 3);
	addEdgeDirected(graph, 1, 3, 4);
	addEdgeDirected(graph, 1, 4, 5);
	addEdgeDirected(graph, 2, 3, 6);
	addEdgeDirected(graph, 3, 4, 7);

	// print the adjacency list representation of the above graph
	printGraph(graph);
	//BFS(graph, &graph->vertices[0]);
	printf("\n");
	graph->vertices[0].color = 1;
	DFS(graph, &graph->vertices[0]);
	printf("\n");
	destroyGraph(graph);
	return 0;
}