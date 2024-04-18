#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <iomanip>  
#include <set>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <fstream>

using namespace std;


//bool check(vector<vector<int>>& residual, int source, int sink, vector<int>& parent) {
//	int n = residual.size();
//	vector<bool> visited(n, false);
//	queue<int> q;
//	q.push(source);
//	visited[source] = true;
//	parent[source] = -1;
//
//	while (!q.empty()) {
//		int u = q.front();
//		q.pop();
//		for (int v = 0; v < n; v++) {
//			if (!visited[v] && residual[u][v] > 0) {
//				q.push(v);
//				visited[v] = true;
//				parent[v] = u;
//			}
//		}
//	}
//	return visited[sink];
//}
bool check(vector<vector<int>>& residual, int source, int sink, vector<int>& parent) {
	int n = residual.size();
	vector<bool> visited(n, false);
	//очередь с приоритетом
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ INT_MAX, source });
	visited[source] = true;
	parent[source] = -1;

	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		for (int v = 0; v < n; v++) {
			if (!visited[v] && residual[u][v] > 0) {
				pq.push({ residual[u][v], v });
				visited[v] = true;
				parent[v] = u;
			}
		}
	}
	return visited[sink];
}

int MaxFlow(vector<vector<int>>& graph) {
	int n = graph.size();
	int source = 0;
	int sink = n - 1;
	int max_flow = 0;
	vector<vector<int>> residual(n, vector<int>(n, 0));
	vector<int> parent(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			residual[i][j] = graph[i][j];
		}
	}
	while (check(residual, source, sink, parent)) {
		int path_flow = INT_MAX;
		for (int v = sink; v != source; v = parent[v]) {
			int u = parent[v];
			path_flow = min(path_flow, residual[u][v]);
		}
		for (int v = sink; v != source; v = parent[v]) {
			int u = parent[v];
			residual[u][v] -= path_flow;
			residual[v][u] += path_flow;
		}

		max_flow += path_flow;
	}
	return max_flow;
}



// Функция, которая проверяет, можно ли добавить вершину v к пути path
bool is_safe(int v, vector<vector<int>>& graph, vector<int>& path, int pos) {
	if (graph[path[pos - 1]][v] == 0) {
		return false;
	}
	for (int i = 0; i < pos; i++) {
		if (path[i] == v) {
			return false;
		}
	}
	return true;
}

// Функция, которая рекурсивно ищет гамильтонов цикл в графе
bool ham_cycle_util(vector<vector<int>>& graph, vector<int>& path, int pos) {
	int n = graph.size();
	if (pos == n) {
		if (graph[path[pos - 1]][path[0]] != 0) {
			return true;
		}
		else {
			return false;
		}
	}
	for (int v = 1; v < n; v++) {
		if (is_safe(v, graph, path, pos)) {
			path[pos] = v;

			if (ham_cycle_util(graph, path, pos + 1)) {
				return true;
			}
			path[pos] = -1;
		}
	}
	return false;
}
// Функция нахождения гамильтонова пути
vector<int> Hamilton(vector<vector<int>>& graph) {
	int n = graph.size();
	vector<int> path(n, -1);
	path[0] = 0;

	if (ham_cycle_util(graph, path, 1)) {
		return path;
	}
	else {
		return {};
	}
}


void PaintGraph(vector<vector<int>>& matrix, vector<int>& color, int curr = 0)
{
	//структура данных для цветов смежных вершин с исследуемой
	set<int> neighbours;

	//аналоги поиска в ширину
	queue<int> q;
	q.push(curr);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		//вершина уже закрашена?
		if (color[curr] != 0)
			continue;
		neighbours.clear();

		for (int next = 0; next < matrix.size(); next++)
			if (matrix[curr][next] != 0)
			{
				//проверяем цвета всех смежных вершин
				neighbours.insert(color[next]);
				if (color[next] == 0)
					q.push(next);
			}

		//счетчик цветов - ищем допустимый цвет с наименьшим индексом
		int color_counter = 1;
		auto it = neighbours.begin();
		do
		{
			//есть ли этот номер цвета среди соседей?
			set<int>::iterator it = neighbours.find(color_counter);
			if (it == neighbours.end()) break;
			color_counter++;
		} while (true);

		//красим вершину в допустимый цвет
		color[curr] = color_counter;
	}
}


void print_matrix(vector<vector<int>> matrix) {
	cout << "\n\nMatrix:\n";
	int rows = matrix.size();
	int cols = matrix[0].size();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}



void print_vector(vector<int> vec) {
	cout << "\nVector:\n";
	for (int x : vec) {
		cout << x << " ";
	}
	cout << endl;
}





int main()
{
	try {
		// матрица смежности (значения - пропускные способности)
		vector<vector<int>> mat =
		{
		{ 0, 3, 8, 7, 6, 6, 0, 2, 0, 0 },
		{ 3, 0, 9, 6, 3, 9, 9, 5, 1, 4 },
		{ 8, 9, 0, 4, 2, 4, 9, 8, 8, 0 },
		{ 7, 6, 4, 0, 5, 8, 5, 0, 3, 7 },
		{ 6, 3, 2, 5, 0, 2, 8, 8, 9, 4 },
		{ 6, 9, 4, 8, 2, 0, 6, 9, 7, 6 },
		{ 0, 9, 9, 5, 8, 6, 0, 1, 8, 4 },
		{ 2, 5, 8, 0, 8, 9, 1, 0, 6, 7 },
		{ 0, 1, 8, 3, 9, 7, 8, 6, 0, 6 },
		{ 0, 4, 0, 7, 4, 6, 4, 7, 6, 0 } };
		int size_mat = mat.size();


		cout << "Max flow:\n" << MaxFlow(mat);

		cout << "\nHamilton way:";
		print_vector(Hamilton(mat));

		vector<int> color(size_mat, 0);
		PaintGraph(mat, color, 3);

		std::cout << "\nColor:\n";
		for (int i = 0; i < size_mat; i++) std::cout << color[i] << " ";
		return 0;
	}
	catch (const char* error) {
		cout << error;
	}
}


