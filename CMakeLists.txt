cmake_minimum_required(VERSION 3.23)
project(Erdos_Renyi_TwoAlgs)

set(CMAKE_CXX_STANDARD 14)

include_directories(TwoAlgsCorrelations/BnB)
include_directories(TwoAlgsCorrelations/Common)
include_directories(TwoAlgsCorrelations/FlowersAlg)
include_directories(TwoAlgsCorrelations/Graph)
include_directories(TwoAlgsCorrelations/IlyevAlgs)
include_directories(TwoAlgsCorrelations/Tests)

add_executable(Erdos_Renyi_TwoAlgs
        TwoAlgsCorrelations/BnB/BnB.h
        TwoAlgsCorrelations/BnB/BnBTreeNode.h
        TwoAlgsCorrelations/BnB/MatrixCoordinate.h
        TwoAlgsCorrelations/Common/MatrixWriter.cpp
        TwoAlgsCorrelations/Common/MatrixWriter.h
        TwoAlgsCorrelations/FlowersAlg/Edmonds.h
        TwoAlgsCorrelations/Graph/CustomGraphFactory.cpp
        TwoAlgsCorrelations/Graph/CustomGraphFactory.h
        TwoAlgsCorrelations/Graph/Graph.cpp
        TwoAlgsCorrelations/Graph/Graph.h
        TwoAlgsCorrelations/Graph/IGraph.h
        TwoAlgsCorrelations/Graph/IGraphFactory.h
        TwoAlgsCorrelations/Graph/RandomGraphFactory.cpp
        TwoAlgsCorrelations/Graph/RandomGraphFactory.h
        TwoAlgsCorrelations/IlyevAlgs/A2Alg.cpp
        TwoAlgsCorrelations/IlyevAlgs/A2Alg.h
        TwoAlgsCorrelations/Tests/CustomTests.h
        TwoAlgsCorrelations/main.cpp)
