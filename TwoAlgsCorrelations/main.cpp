#include <iostream>

#include "Graph.h"
#include "RandomGraphFactory.h"
#include "CustomGraphFactory.h"
#include "FlowersAlg/Edmonds.h"
#include "IlyevAlgs/A2Alg.h"

using namespace std;

int main(int argc,      // Number of strings in array argv
    char* argv[],   // Array of command-line argument strings
    char* envp[])  // Array of environment variable strings
{
    const unsigned int graph_size = 5;
/*    const double density = 0.5;
    RandomGraphFactory graph_factory(density);
    auto graphPtr = graph_factory.CreateGraph(graph_size);
    cout << (*graphPtr).ToJson();
    */
   
    CustomGraphFactory c_graph_factory = CustomGraphFactory();
    auto newGraphPtr = c_graph_factory.CreateGraph(graph_size);
    cout << (*newGraphPtr).ToJson();

	/*edmonds.PreliminaryGreedyMatchBuilding(newGraphPtr);
    cout << edmonds.ToJson();
    */

    A2Alg a2 = A2Alg(newGraphPtr, 3);
    a2.startCreateCluster();
    return 0;
}
