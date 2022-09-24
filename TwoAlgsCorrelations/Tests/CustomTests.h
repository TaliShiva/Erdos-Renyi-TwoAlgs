#pragma once

#include <iostream>

#include "../Graph/CustomGraphFactory.h"
#include "../Common/MatrixWriter.h"
#include "../IlyevAlgs/A2Alg.h"

/**
	TODO: чтобы тесты действительно имели реальный смысл, мне нужно уметь производить сравнение получаемой из тестов матрицы смежности,
	TODO: получается нужен класс ответственный за работы с матрицами смежности, умеющий считать расстояние между двумя матрицами,
	TODO: конструировать матрицы по необходимости
**/
class TestEnvironment {
    IGraphPtr _newGraphPtr;

public:

    void Al2AlgOnDiamondGraphCorrectnessTest() {
        std::cout << "START TEST Al2OnDiamondGraphCorrectnessTest" << std::endl;

        _newGraphPtr = CustomGraphFactory::CreateDiamondGraph();
        constexpr int cluster_size = 3;
        std::cout << MatrixWriter::ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");

        A2Alg a2 = A2Alg(_newGraphPtr, cluster_size);
        a2.CreateMGraph();
        std::cout << MatrixWriter::ToJson(a2.GetCopyOfMGraph(), "MGraph");
        std::cout << "____________________________________________" << std::endl;
    }

    void Al2AlgOnHouseGraphCorrectnessTest() {
        std::cout << "START TEST AlOnHouseGraphCorrectnessTest" << std::endl;

        _newGraphPtr = CustomGraphFactory::CreateHouseGraph();
        constexpr int cluster_size = 3;
        std::cout << MatrixWriter::ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");

        A2Alg a2 = A2Alg(_newGraphPtr, cluster_size);
        a2.CreateMGraph();
        std::cout << MatrixWriter::ToJson(a2.GetCopyOfMGraph(), "MGraph");
        std::cout << "____________________________________________" << std::endl;
    }

    void Al2SquareWithShortChainGraphCorrectnessTest() {
        std::cout << "START TEST Al2SquareWithShortChainGraphCorrectnessTest" << std::endl;

        _newGraphPtr = CustomGraphFactory::CreateSquareWithShortChain();
        constexpr int cluster_size = 3;
        std::cout << MatrixWriter::ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");

        A2Alg a2 = A2Alg(_newGraphPtr, cluster_size);
        a2.CreateMGraph();
        std::cout << MatrixWriter::ToJson(a2.GetCopyOfMGraph(), "MGraph");
        std::cout << "____________________________________________" << std::endl;
    }

    void BnBAlgDiamondGraphCorrectnessTest() {
        std::cout << "START TEST BnBAlgDiamondGraphCorrectnessTest" << std::endl;

        _newGraphPtr = CustomGraphFactory::CreateDiamondGraph();
        int graph_size = 4;
        std::cout << MatrixWriter::ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");

        BranchAndBounds bnb = BranchAndBounds(graph_size, _newGraphPtr);
        bnb.startCalclulating();
        std::cout << "____________________________________________" << std::endl;
    }

    void BnBAlgHouseGraphCorrectnessTest() {
        std::cout << "START TEST BnBAlgDiamondGraphCorrectnessTest" << std::endl;

        _newGraphPtr = CustomGraphFactory::CreateHouseGraph();
        int graph_size = 5;
        std::cout << MatrixWriter::ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");

        BranchAndBounds bnb = BranchAndBounds(graph_size, _newGraphPtr);
        bnb.startCalclulating();
        std::cout << "____________________________________________" << std::endl;
    }

    void BnBAlgSquareWithShortChainGraphCorrectnessTest() {
        std::cout << "START TEST BnBAlgSquareWithShortChainGraphCorrectnessTest" << std::endl;

        _newGraphPtr = CustomGraphFactory::CreateSquareWithShortChain();
        int graph_size = 6;
        std::cout << MatrixWriter::ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");

        BranchAndBounds bnb = BranchAndBounds(graph_size, _newGraphPtr);
        bnb.startCalclulating();
        std::cout << "____________________________________________" << std::endl;
    }
};
