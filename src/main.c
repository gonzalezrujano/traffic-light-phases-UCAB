#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "utils.h"

/*
Case 1:
2 vertex AB AC
1 edge   AB - AC
*/

void avid(Graph *G, Graph *new_color) {
	int founded;
	Vertex *v, *w;

    v = G->V;
	while (v != NULL) {
		//printf("Ite:%s\n", v->name);
		if (v->is_colored) { // Ignore colored vertex
			v = v->next;
			continue;
		}
		founded = 0;
		w = new_color->V;
		while (w != NULL) {
			if (its_connected_vertex(G, v, w)) {
				// printf("Vertices: %s y %s conectados\n", v->name, w->name);
				founded = 1;
				break;
			}
			w = w->next;
		}
		if (!founded) {
			// printf("Agregar: %s a new_color\n", v->name);
			v->is_colored = (int*) 1;
		    add_vertex_to_graph(new_color, clone_vertex(v));
		}
		v = v->next;
	}
}

int main(int argc, char const *argv[]) {
	/* Start input process */
    // Graph *G = read_input_from_file("case.dat");
    // Case 1
    Graph *G = create_graph();
    Vertex *v = new_vertex("AB");
    Vertex *w = new_vertex("AC");
    add_vertex_to_graph(G, v);
    add_vertex_to_graph(G, w);
    add_edge_to_graph(G, new_edge("AB", "AC"));

    printf("%d\n", len_vertex_graph(G));
    printf("%d\n", len_edge_graph(G));

    /* End input process */

    /* Start algorith process */
    int i = 0;
    Graphlist *GL = (Graphlist*) malloc(sizeof(Graphlist));
    printf("len_graphlist: %d\n", len_graphlist(GL));
    while (!is_graph_colored(G)) {
    	Graph *phase = create_graph();
	    phase->color = (int*)(++i);
	    avid(G, phase);
	    append_to_graphlist(GL, phase);
    }
    printf("len_graphlist: %d\n", len_graphlist(GL));
    print_graphlist(GL);

	return 0;
}