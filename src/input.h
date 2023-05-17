#include <stdio.h>
//#ifndef Graph
//#include "graph.h"
//#endif


Graph *read_input_from_file(char *filename) {
	Graph *G = create_graph();
	FILE  *fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "read_input_from_file: malloc error\n");
		exit(1);
	}
	fclose(fp);
}