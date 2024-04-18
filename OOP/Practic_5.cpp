#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

//Вариант 26
vector<int> DFS(vector<vector<int>> mat) {
	int size_mat = mat.size();
	vector<int> used(size_mat, 0);
	//0 – вершина не посещена при поиске, 
	// 1 – помещена в структуру данных для вершин, 
	//но не обработана, 
	// 2 – обработана, смежные вершины помещены в структуру данных
	vector<int> result;

	//DFS – поиск в глубину
	stack<int> Stack;
	int iter = 0;
	Stack.push(0); // помещаем в очередь первую вершину
	while (!Stack.empty())
	{
		// пока стек не пуст
		int node = Stack.top(); // извлекаем вершину
		Stack.pop();
		//cout << "\nDFS at vertex " << node << endl;
		if (used[node] == 2) continue;
		used[node] = 2; // отмечаем ее как посещенную
		iter++;
		for (int j = 0; j < size_mat; j++)
		{ 
			// проверяем для нее все смежные вершины
			if (mat[node][j] > 0 && used[j] != 2)
			{ // если вершина смежная и не обнаружена
				Stack.push(j); // добавляем ее в cтек
				used[j] = 1; // отмечаем вершину как обнаруженную
			}
		}
		result.push_back(node);
		//cout << node << endl; // выводим номер вершины
	}
	return result;
	//cout << "\nVisited vertices\n";
	//for (int i = 0; i < size_mat; i++) cout << used[i] << " ";
	//for (int i = 0; i < size_mat; i++) used[i] = 0;
}
vector<int> BFS(vector<vector<int>> mat) {
	int size_mat = mat.size();
	queue<int> Queue;
	vector<int> result;

	//BFS – поиск в ширину
	vector <int> used(size_mat, 0);
	Queue.push(0); //в качестве начальной вершины используем 0.
	used[0] = 0; //2
	vector<int> dist(size_mat, 10000); //расстояния до вершин от 0 - й в числе ребер
	dist[0] = 0;
	int iter = 0;
	while (!Queue.empty())
	{
		int node = Queue.front(); //извлекаем из очереди текущую вершину
		Queue.pop();
		/*cout << "\nBFS at vertex " << node << endl;*/
		if (used[node] == 2) continue;
		used[node] = 2;
		iter++;
		for (int j = 0; j < size_mat; j++)
		{ 
			// проверяем для нее все смежные вершины
			if (mat[node][j] > 0 && used[j] != 2)
			{ // если вершина смежная и не обнаружена
				Queue.push(j); // добавляем ее в очередь
				used[j] = 1; // отмечаем вершину как обнаруженную
				if (dist[j] > dist[node] + 1)
					dist[j] = dist[node] + 1;
			}
		}
		result.push_back(node);
	}
	return result;
	//cout << "\nVisited vertices\n";
	//for (int i = 0; i < size_mat; i++) cout << used[i] << " ";
	//cout << "\nDistances\n";
	//for (int i = 0; i < size_mat; i++) cout << dist[i] << " ";
}


//Поиск минимального пути через алгоритм Дейкстры (Задача 5.2)
vector<int> MinWays(vector<vector<int>> graph, int start) {
	if (start > (graph.size()-1) or start < 0) {
		throw "The vertex isn't correct";
	}
	int n = graph.size();
	vector<int> min_dist(n, INT_MAX);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	min_dist[start] = 0;
	pq.push({ 0, start });
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		for (int v = 0; v < n; v++) {
			if (graph[u][v] != 0 && min_dist[v] > min_dist[u] + graph[u][v]) {
				min_dist[v] = min_dist[u] + graph[u][v];
				pq.push({ min_dist[v], v });
			}
		}
	}
	return min_dist;
}

// Задание 5.3
vector<int> Degree(vector<vector<int>> mat) {
	int size_mat = mat.size();
	vector<int> deg(size_mat, 0);
	queue<int> Queue;
	vector <int> used(size_mat, 0);
	Queue.push(0); //в качестве начальной вершины используем 0.
	used[0] = 0;
	int iter = 0;
	while (!Queue.empty())
	{
		int node = Queue.front(); //извлекаем из очереди текущую вершину
		Queue.pop();


		if (used[node] == 2) 
			continue;
		used[node] = 2;
		iter++;


		for (int j = 0; j < size_mat; j++)
		{
			// проверяем для нее все смежные вершины
			if (mat[node][j] > 0 && used[j] != 2)
			{ 
				// если вершина смежная и не обнаружена
				Queue.push(j); // добавляем ее в очередь
				used[j] = 1; // отмечаем вершину как обнаруженную
				deg[node] += 1;
				deg[j] += 1;
			}
		}
	}
	return deg;
}
double AverageDegree(vector<vector<int>> mat) {
	vector<int> deg = Degree(mat);
	int n = deg.size();
	double sum = 0;
	for (int d : deg) {
		sum += d;
	}
	return sum / n;
}


vector<vector<int>> MinOstov(vector<vector<int>> adj) {
	int n = adj.size();
	vector<int> parent(n, -1);
	vector<int> key(n, INT_MAX);
	vector<bool> visited(n, false);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	key[0] = 0;
	pq.push({ 0, 0 });
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		visited[u] = true;
		for (int v = 0; v < n; v++) {
			if (adj[u][v] > 0 && !visited[v] && adj[u][v] < key[v]) {
				key[v] = adj[u][v];
				parent[v] = u;
				pq.push({ key[v], v });
			}
		}
	}
	vector<vector<int>> mst(n, vector<int>(n, 0));
	for (int i = 1; i < n; i++) {
		mst[i][parent[i]] = mst[parent[i]][i] = adj[i][parent[i]];
	}
	return mst;
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
		// матрица смежности
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

		//Задание 5.1
		vector<int> v1 = DFS(mat);
		cout << "\nDFS\n";
		for (int i = 0; i < size_mat; i++) cout << v1[i] << " ";

		vector<int> v2 = BFS(mat);
		cout << "\nBFS\n";
		for (int i = 0; i < size_mat; i++) cout << v2[i] << " ";


		//Задание 5.2
		cout << "\n\nMinimum ways:\n";
		print_vector(MinWays(mat, 0));

		// Задание 5.3
		print_vector(Degree(mat));
		cout << "\n\nAverage degree:\n" << AverageDegree(mat);

		// Задание 5.4
		vector<vector<int>> ostov = MinOstov(mat);
		print_matrix(ostov);
		DFS(ostov);
		cout << "\n\nMinimum ways:\n";
		print_vector(MinWays(ostov, 0));
		print_vector(Degree(mat));
		cout << "\n\nAverage degree:\n" << AverageDegree(ostov);

		return 0;
	}
	catch (const char* error) {
		cout << error;
	}
}


