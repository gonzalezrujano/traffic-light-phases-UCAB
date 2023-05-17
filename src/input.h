#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

char *vertexs[MAXLINE];

char line[MAXLINE];

char *readline(FILE *fp) {
	int c, i;

	for (i = 0; i < MAXLINE-1 && (c = getc(fp)) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';

	return line;
}

void a_to_vertex(Graph *G, char *format) {
	int i = 0; int j = 0; int k = 0;
	char c, word[MAXLINE];

	while ((c = format[i++]) != '\0' && i < MAXLINE-1) {
		if (!isalnum(c)) {
			word[j] = '\0'; // End word extraction
			// Protect vertex name reference
			vertexs[k] = malloc(strlen(word) + 1);
			strcpy(vertexs[k], word);
			// Add vertex to graph
		    add_vertex_to_graph(G, new_vertex(vertexs[k++]));
		    // Reset word
		    word[0] = '\0';
		    j = 0;
		    continue;
		}
		word[j++] = c;
	}
}

void a_to_edges(Graph *G, FILE *fp) {
	char *result = readline(fp);
	int i = 0;
	int limit = 2 * len_vertex_graph(G);

	while (result[0] != '.' && i < limit) {
		printf("%s\n", result);
		result = readline(fp);
		i++;
	}
}

Graph *read_input_from_file(char *filename) {
	Graph *G = create_graph();
	FILE  *fp;
	char *result;

	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "read_input_from_file: fopen error\n");
		exit(1);
	}

	// Extract len vertex
    result = readline(fp);
    int nvertex = atoi(result);

    // Extract vertex
    result = readline(fp);
    a_to_vertex(G, result);

    // Extract edges
    a_to_edges(G, fp);

	fclose(fp);

	return G;
}