#include "CustomGraphFactory.h"

void CustomGraphFactory::adjMatrixInit(const int size, std::vector<std::vector<bool>> &adjacency_matrix) {
    for (auto &row: adjacency_matrix) {
        row = std::vector<bool>(size, false);
    }
}

/// <summary>
/// �������� 5 ���������� ����� �� ���� ������
/// </summary>
IGraphPtr CustomGraphFactory::CreateHouseGraph() {
    constexpr int size = 5;
    std::vector<std::vector<bool>> adjacency_matrix(size);
    adjMatrixInit(size, adjacency_matrix);

    //5 ��������� ���� �����
    adjacency_matrix[0][1] = true;
    adjacency_matrix[0][4] = true;
    adjacency_matrix[1][0] = true;
    adjacency_matrix[1][2] = true;
    adjacency_matrix[1][4] = true;
    adjacency_matrix[2][1] = true;
    adjacency_matrix[2][3] = true;
    adjacency_matrix[3][2] = true;
    adjacency_matrix[3][4] = true;
    adjacency_matrix[4][0] = true;
    adjacency_matrix[4][1] = true;
    adjacency_matrix[4][3] = true;

    return IGraphPtr(new Graph(adjacency_matrix));
}


/// <summary>
/// �������� 6 ���������� ����� �� ���� �������� � �������������� ����� �� ���� ������
/// </summary>
IGraphPtr CustomGraphFactory::CreateSquareWithShortChain() {
    constexpr int size = 6;
    std::vector<std::vector<bool>> adjacency_matrix(size);
    adjMatrixInit(size, adjacency_matrix);

    // 6-���������: ������� � ������� �� ���� �������
    adjacency_matrix[0][3] = true;
    adjacency_matrix[0][4] = true;
    adjacency_matrix[1][3] = true;
    adjacency_matrix[1][4] = true;
    adjacency_matrix[1][5] = true;
    adjacency_matrix[2][5] = true;

    adjacency_matrix[3][0] = true;
    adjacency_matrix[4][0] = true;
    adjacency_matrix[3][1] = true;
    adjacency_matrix[4][1] = true;
    adjacency_matrix[5][1] = true;
    adjacency_matrix[5][2] = true;

    return IGraphPtr(new Graph(adjacency_matrix));
}

/// <summary>
/// �������� 4 ���������� ����� �� ���� K_4 ��� ������ �����
/// </summary>
IGraphPtr CustomGraphFactory::CreateDiamondGraph() {
    constexpr int size = 4;
    std::vector<std::vector<bool>> adjacency_matrix(size);
    adjMatrixInit(size, adjacency_matrix);

    // 4 ��������� �����
    adjacency_matrix[0][1] = true;
    adjacency_matrix[0][2] = true;
    adjacency_matrix[0][3] = true;

    adjacency_matrix[1][0] = true;
    adjacency_matrix[1][2] = true;

    adjacency_matrix[2][0] = true;
    adjacency_matrix[2][1] = true;
    adjacency_matrix[2][3] = true;

    adjacency_matrix[3][0] = true;
    adjacency_matrix[3][2] = true;

    return std::make_shared<Graph>(adjacency_matrix);
}
