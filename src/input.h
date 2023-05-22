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

void extract_edges(Graph *G, char *s) {
	int i = 0;
	int j = 0;
	char c, *word, *new_word, *v1, *v2;
	v1 = v2 = NULL;
	word = (char*) malloc(MAXLINE);

	while ((c = *(word + j) = *s++) != '\0' && i++ < MAXLINE-1) {
		if (!isalnum(c)) {
			*(word + j) = '\0';
			j = 0;
			new_word = malloc(strlen(word) + 1);
			strcpy(new_word, word);
			if (v1 == NULL) {
				v1 = new_word;
				for (;!isalnum(*s);*s++) ;
			} else 
		        v2 = new_word;
		    continue;
		}
		j++;
	}

	add_edge_to_graph(G, new_edge(v1, v2));
}

void a_to_edges(Graph *G, FILE *fp) {
	char *result = readline(fp);
	int i = 0;
	int limit = len_vertex_graph(G) - 1;

	while ((*result != '\0') && (result[0] != '.' && i < limit)) {
		extract_edges(G, result);
		result = readline(fp);
		i++;
	}
}

Graph *read_input_from_file(const char *filename) {
	Graph *G = create_graph();
	FILE  *fp;
	char *result;

    // Open case file
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