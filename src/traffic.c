#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "input.h"

void avid(Graph *G, Graph *new_color) {
	int founded;
	Vertex *v, *w;

    v = G->V;
	while (v != NULL) {
		if (v->is_colored) { // Ignore colored vertex
			v = v->next;
			continue;
		}
		founded = 0;
		w = new_color->V;
		while (w != NULL) {
			if (its_connected_vertex(G, v, w)) {
				founded = 1;
				break;
			}
			w = w->next;
		}
		if (!founded) {
			v->is_colored = (int*) 1;
		    add_vertex_to_graph(new_color, clone_vertex(v));
		}
		v = v->next;
	}
}

int main(int argc, char const *argv[]) {

	/* Start input process */
	if (argc == 1) fprintf(stderr, "traffic <filename>\n");
	const char *filename = argv[1];
	printf("\n");
	printf("\n");
	printf("Starting process for: %s\n", filename);
	printf("\n");

    Graph *G = read_input_from_file(filename);

    printf("Graph vertex(s) (Giros):\n");
    print_vertex_graph(G);
    printf("\n");

    printf("Graph edge(s) (Giros incompatibles):\n");
    print_edge_graph(G);
    printf("\n");

    /* Start algorithm process */
    int i = 0;
    Graphlist *GL = (Graphlist*) malloc(sizeof(Graphlist));
    GL->G = NULL;
    GL->next = NULL;
    while (!is_graph_colored(G)) {
    	Graph *phase = create_graph();
	    phase->color = ++i;
	    avid(G, phase);
	    append_to_graphlist(GL, phase);
    }
    print_graphlist(GL);

	return 0;
}