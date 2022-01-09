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
class TestEnvironment
{
	MatrixWriter* _mw = new MatrixWriter();
	IGraphPtr _newGraphPtr;
public:

	
	void Al2AlgOnDiamondGraphCorrectnessTest()
	{
		std::cout << "START TEST Al2OnDiamondGraphCorrectnessTest" << std::endl;
		CustomGraphFactory c_graph_factory = CustomGraphFactory();
		_newGraphPtr = c_graph_factory.CreateDiamondGraph();
		constexpr int cluster_size = 3;
		std::cout << (*_mw).ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");

		
		A2Alg a2 = A2Alg(_newGraphPtr, cluster_size);
		a2.CreateMGraph();
		std::cout << (*_mw).ToJson(a2.GetCopyOfMGraph(), "MGraph");
		std::cout << "____________________________________________" << std::endl;
	}

	void Al2AlgOnHouseGraphCorrectnessTest()
	{
		std::cout << "START TEST AlOnHouseGraphCorrectnessTest" << std::endl;
		CustomGraphFactory c_graph_factory = CustomGraphFactory();
		_newGraphPtr = c_graph_factory.CreateHouseGraph();
		constexpr int cluster_size = 3;
		std::cout << (*_mw).ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");

		
		A2Alg a2 = A2Alg(_newGraphPtr, cluster_size);
		a2.CreateMGraph();
		std::cout << (*_mw).ToJson(a2.GetCopyOfMGraph(), "MGraph");
		std::cout << "____________________________________________" << std::endl;
	}

	void Al2SquareWithShortChainGraphCorrectnessTest()
	{
		std::cout << "START TEST Al2SquareWithShortChainGraphCorrectnessTest" << std::endl;
		CustomGraphFactory c_graph_factory = CustomGraphFactory();
		_newGraphPtr = c_graph_factory.CreateSquareWithShortChain();
		constexpr int cluster_size = 3;
		std::cout << (*_mw).ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");
				
		A2Alg a2 = A2Alg(_newGraphPtr, cluster_size);
		a2.CreateMGraph();
		std::cout << (*_mw).ToJson(a2.GetCopyOfMGraph(), "MGraph");
		std::cout << "____________________________________________" << std::endl;
	}

	void BnBAlgDiamondGraphCorrectnessTest()
	{
		std::cout << "START TEST BnBAlgDiamondGraphCorrectnessTest" << std::endl;
		CustomGraphFactory c_graph_factory = CustomGraphFactory();
		_newGraphPtr = c_graph_factory.CreateDiamondGraph();
		int graph_size = 4;
		std::cout << (*_mw).ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");

		BranchAndBounds bnb = BranchAndBounds(graph_size, _newGraphPtr);
		bnb.startCalclulating();
		std::cout << "____________________________________________" << std::endl;
	}

	void BnBAlgHouseGraphCorrectnessTest()
	{
		std::cout << "START TEST BnBAlgDiamondGraphCorrectnessTest" << std::endl;
		CustomGraphFactory c_graph_factory = CustomGraphFactory();
		_newGraphPtr = c_graph_factory.CreateHouseGraph();
		int graph_size = 5;
		std::cout << (*_mw).ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");

		BranchAndBounds bnb = BranchAndBounds(graph_size, _newGraphPtr);
		bnb.startCalclulating();
		std::cout << "____________________________________________" << std::endl;
	}

	void BnBAlgSquareWithShortChainGraphCorrectnessTest()
	{
		std::cout << "START TEST BnBAlgSquareWithShortChainGraphCorrectnessTest" << std::endl;
		CustomGraphFactory c_graph_factory = CustomGraphFactory();
		_newGraphPtr = c_graph_factory.CreateSquareWithShortChain();
		int graph_size = 6;
		std::cout << (*_mw).ToJson((*_newGraphPtr).GetCopyOfAdjacencyMatrix(), "Start Graph");

		BranchAndBounds bnb = BranchAndBounds(graph_size, _newGraphPtr);
		bnb.startCalclulating();
		std::cout << "____________________________________________" << std::endl;
	}
};
