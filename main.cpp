#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

void count_distances(std::vector<std::vector<int>>& graph, int start, std::vector<int>& distances) {
    std::queue<int> to_visit;
    to_visit.push(start);
    distances[start] = 0;
    while (!to_visit.empty()) {
        int cur_vertex = to_visit.front();
        to_visit.pop();
        for (int& neighbour : graph[cur_vertex]) {
            if (distances[neighbour] == -1) {
                distances[neighbour] = distances[cur_vertex] + 1;
                to_visit.push(neighbour);
            }
        }
    }
}

int main() {
    std::ifstream file("graph.txt");

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл\n";
        return 1;
    }

    int count_of_vertices;
    int count_of_edges;

    file >> count_of_vertices >> count_of_edges;

    std::vector<std::vector<int>> graph(count_of_vertices);

    int from;
    int to;

    for (int i = 0; i < count_of_edges; ++i) {
        file >> from >> to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    int vertex;

    file >> vertex;

    std::vector<int> distances(graph.size(), -1);

    count_distances(graph, vertex, distances);

    for (int& elem : distances) {
        std::cout << elem << std::endl;
    }
}
