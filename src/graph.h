

typedef struct vertex {
	char *name;
	int *is_colored;
	struct vertex *next;
} Vertex;

typedef struct edge {
	char *v1;
	char *v2;
	struct edge *next;
} Edge;

typedef struct graph {
	struct vertex *V;
	struct edge *E;
	int *color;
} Graph;

typedef struct graphlist {
	struct graph *G;
	struct graphlist *next;
} Graphlist;

Graph *create_graph(void) {
	Graph *G = (Graph*) malloc(sizeof(Graph));
	// if ((G = (Graph*) malloc(sizeof(Graph))) == NULL)
	// 	print_stderr("create_graph: malloc error");
	return G;
}

int len_vertex_graph(Graph *G) {
	if (G->V == NULL) // Graph empty
		return 0;

	int i = 0;
	Vertex *p = G->V; // Graph with data
	while (p != NULL) { p = p->next; i++; }

	return i;
}

int len_edge_graph(Graph *G) {
	if (G->E == NULL) // Graph empty
		return 0;

	int i = 0;
	Edge *p = G->E; // Graph with data
	while (p != NULL) { p = p->next; i++; }

	return i;
}

Vertex *new_vertex(char *name) {
	Vertex *ver;
	ver = (Vertex*) malloc(sizeof(Vertex));
	// if ((ver = (Vertex*) malloc(sizeof(Vertex))) == NULL)
	// 	print_stderr("new_vertex: malloc error");
	ver->name = name;
	ver->is_colored = 0;
	ver->next = NULL;

	return ver;
}

Edge *new_edge(char *v1, char *v2) {
	Edge *edge;
	edge = (Edge*) malloc(sizeof(Edge));
	// if ((ver = (Vertex*) malloc(sizeof(Vertex))) == NULL)
	// 	print_stderr("new_vertex: malloc error");
	edge->v1 = v1;
	edge->v2 = v2;
	edge->next = NULL;

	return edge;
}

void add_vertex_to_graph(Graph *G, Vertex *new_vertex) {
	// if (G == NULL)
	// 	print_stderr("add_vertex_to_graph: G is NULL");
	new_vertex->next = NULL;

	if (G->V == NULL) { // Graph empty
		G->V = new_vertex;
		return;
	}

	Vertex *p = G->V; // Graph with data
	while (1) {
		if (p->next == NULL) {
			p->next = new_vertex;
			break;
		}
		p = p->next;
	}
}

void add_edge_to_graph(Graph *G, Edge *new_edge) {
	// if (G == NULL)
	// 	print_stderr("add_vertex_to_graph: G is NULL");
	new_edge->next = NULL;

	if (G->E == NULL) { // Graph empty
		G->E = new_edge;
		return;
	}

	Edge *p = G->E; // Graph with data
	while (1) {
		if (p->next == NULL) {
			p->next = new_edge;
			break;
		}
		p = p->next;
	}
}

void append_to_graphlist(Graphlist *GL, Graph *nw_graph) {
	if (GL->G == NULL) { // Graphlist empty
		GL->G = nw_graph;
		return;
	}

	Graphlist *p = GL; // Graphlist with data
	while (1) {
		if (p->next == NULL) {
			Graphlist *nw_grlst = (Graphlist*) malloc(sizeof(Graphlist));
			nw_grlst->G = nw_graph;
			p->next = nw_grlst;
			break;
		}
		p = p->next;
	}
}

int len_graphlist(Graphlist *GL) {
	if (GL->G == NULL) // Graphlist empty
		return 0;

	int i = 0;
	Graphlist *p = GL; // Graph with data
	while (p != NULL) { p = p->next; i++; }

	return i;
}

void print_graphlist(Graphlist *GL) {
	Graphlist *p = GL;
	while (p != NULL && p->G != NULL) { 
		printf("color%d\n", p->G->color);
		p = p->next;
	}
}

Vertex *clone_vertex(Vertex *src) {
	Vertex *dest = (Vertex*) malloc(sizeof(Vertex));
	dest->name = src->name;
	dest->is_colored = src->is_colored;
	dest->next = src->next;

	return dest;
}

void print_vertex_debug(Graph *G) {
    Vertex *p = G->V;
	while (p != NULL) {
		printf("%s\n", p->name);
		p = p->next;
	}
}

int is_graph_colored(Graph *G) {
	Vertex *p = G->V;
	while (p != NULL) {
		if (p->is_colored == 0)
			return 0;
		p = p->next;
	}
	return 1;
}

int its_connected_vertex(Graph *G, Vertex *v, Vertex *w) {
	Edge *p = G->E;

	while (p != NULL) {
		int have_to_v = (strcmp(v->name, p->v1) == 0 || strcmp(v->name, p->v2) == 0);
		int have_to_w = (strcmp(w->name, p->v1) == 0 || strcmp(w->name, p->v2) == 0);
		if (have_to_v && have_to_w) return 1;
		p = p->next;
	}

	return 0;
}