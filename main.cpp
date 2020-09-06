#include "graph.h"

int main(void)
{
    int NumberVertex = readGraph("soc-dolphins.mtx");

    if (NumberVertex != -1)
    {
        printDegreeGraph();
        printMaximalCliques();
        printCoefficient();
    }

    return 0;
}
