#include <iostream>

#include "Graph.h"
#include "RandomGraphFactory.h"

using namespace std;

int main(int argc,      // Number of strings in array argv
    char* argv[],   // Array of command-line argument strings
    char* envp[])  // Array of environment variable strings
{
    const unsigned int graph_size = 10;
    const double density = 0.5;
    RandomGraphFactory graph_factory(density);
    auto graphPtr = graph_factory.CreateGraph(graph_size);
    cout << (*graphPtr).ToJson();

    return 0;
}
