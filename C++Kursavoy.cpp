#include <iostream>
class UnionFind {
private:
	int* parent;
	int count;
	int* rank; // rank[i] represents the number of layers with i as the root set
public:
	UnionFind(int count_) {
		parent = new int[count_];
		rank = new int[count_];
		this->count = count_;
		for (int i = 0; i < count_; i++) {
			parent[i] = i;
			rank[i] = 1;
		}

	}

	~UnionFind() {
		delete[] parent;
		delete[] rank;
	}

	int find(int p) {
		//assert(p >= 0 && p < count);
		while (p != parent[p]) {
			parent[p] = parent[parent[p]];
			p = parent[p];
		}
		return p;
	}

	bool isConnected(int p, int q) {

		return find(p) == find(q);
	}

	void unionElements(int p, int q) {

		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot)
			return;
		if (rank[pRoot] < rank[qRoot])
			parent[pRoot] = qRoot;

		else if (rank[qRoot] < rank[pRoot])
			parent[qRoot] = pRoot;
		else {
			parent[pRoot] = qRoot;
			rank[qRoot]++;
		}
		count--;

	}
	int size() {
		return count;
	}

};


bool HasEulerCircuit(UnionFind& Union, int degree[], int V) {
	if (Union.size() - 1 != 1)
		return false;
	for (int i = 0; i < V; i++) {

		if (degree[i] % 2)
			return false;
	}
	return true;
}

int main()
{
	int V, E, V1, V2;
	int degree[1010] = { 0 };
	std::cin >> V >> E;
	UnionFind Union = UnionFind(V + 1);
	for (int i = 0; i < E; i++) {
		std::cin >> V1 >> V2;
		Union.unionElements(V1, V2);
		degree[V1]++;
		degree[V2]++;

	}
	if (HasEulerCircuit(Union, degree, V))
		std::cout << 1 << std::endl;
	else
		std::cout << 0 << std::endl;
}