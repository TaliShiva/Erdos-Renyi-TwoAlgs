#include <iostream>

#include "Graph.h"
#include "RandomGraphFactory.h"
#include "CustomGraphFactory.h"
#include "BnB/BnB.h"
#include "Common/MatrixWriter.h"
#include "FlowersAlg/Edmonds.h"
#include "IlyevAlgs/A2Alg.h"
#include "Tests/CustomTests.h"

using namespace std;

int main(int argc, // Number of strings in array argv
         char *argv[], // Array of command-line argument strings
         char *envp[]) // Array of environment variable strings
{
    /*const double density = 0.5;
    RandomGraphFactory graph_factory(density);
    auto graphPtr = graph_factory.CreateGraph(graph_size);
    cout << (*graphPtr).ToJson();

    edmonds.PreliminaryGreedyMatchBuilding(newGraphPtr);
    cout << edmonds.ToJson();
    */

    TestEnvironment te;
    te.Al2AlgOnDiamondGraphCorrectnessTest();
    te.Al2AlgOnHouseGraphCorrectnessTest();
    te.Al2SquareWithShortChainGraphCorrectnessTest();
    te.BnBAlgDiamondGraphCorrectnessTest();
    te.BnBAlgHouseGraphCorrectnessTest();
    te.BnBAlgSquareWithShortChainGraphCorrectnessTest();
    te.BnBAlgRandomTest();
    return 0;
}
