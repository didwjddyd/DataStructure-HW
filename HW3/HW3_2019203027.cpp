// Student ID: 2019203027
// Name: ¾çÁ¤¿ë

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void rotatedForm(const vector<char>& vec, int depthCount); // print heap's rotated form
void notRotatedForm(const vector<char>& vec); // print heap's not rotated form
void HTreeForm(const vector<char>& vec); // pring heap's h-tree form
int maxDepth(int size); // get heap's maximum depth
void makeSubtree(const vector<char>& vec, vector<char>& left, vector<char>& right); // make subtrees
int center(int size); // get center position of h-tree
int depth(int size); // get depth of h-tree
void HTree(char** h_tree, const vector<char>& vec, int index, int col, int row, int depth, int up, int down, int right, int left); // make H-tree

const int N = 0, S = 1, E = 2, W = 3;
const int V[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

int main() {
	string command;
	char c;
	vector<char> heap;

	// Console Input
	while (1) {
		cin >> command;

		if (command == "EOI") {
			if (heap.size() > 0) break;
			else return 0;
		}
		else if (command == "INS") {
			cin >> c;
			heap.push_back(c);
			push_heap(heap.begin(), heap.end());
		}
		else if (command == "DEL") {
			if (heap.size() != 0) {
				pop_heap(heap.begin(), heap.end());
				heap.pop_back();
			}
		}
	}

	// rotated form
	cout << "rotated form" << endl;
	rotatedForm(heap, 0);
	cout << endl;

	// not-rotated form
	cout << "not-rotated form" << endl;
	notRotatedForm(heap);
	cout << endl;

	// H-tree form
	cout << "H-tree form" << endl;
	HTreeForm(heap);
	cout << endl;

	return 0;
}

// print heap's rotated form
void rotatedForm(const vector<char>& vec, int depthCount) {
	vector<char> leftSub, rightSub;

	if (vec.size() > 1) {
		makeSubtree(vec, leftSub, rightSub);
		rotatedForm(rightSub, depthCount + 1);

		cout << setw(depthCount * 3) << "" << vec[0] << endl;

		rotatedForm(leftSub, depthCount + 1);
	}
	else if(vec.size() == 1) {
		cout << setw(depthCount * 3) << "" << vec[0] << endl;
	}
}

// print heap's not rotated form
void notRotatedForm(const vector<char>& vec) {
	int index = 0;
	int depthCount = 0;
	int max_depth = maxDepth(vec.size());

	while (index < vec.size() && depthCount <= max_depth) {
		for (int i = 0; i != pow(2, depthCount); ++i) {
			cout << setw(pow(2, max_depth - depthCount) - 1) << "" << vec[index]
				<< setw(pow(2, max_depth - depthCount)) << "";
			if (index < vec.size() - 1) {
				index++;
			}
			else {
				break;
			}
		}

		cout << endl;

		depthCount++;
	}
}

void HTreeForm(const vector<char>& vec) {
	char** h_tree = new char*[vec.size() + 1];
	int count = 0;

	for (int i = 0; i < vec.size(); ++i) {
		h_tree[i] = new char[vec.size()];
		memset(h_tree[i], ' ', sizeof(char) * vec.size());
	}

	HTree(h_tree, vec, 1, center(vec.size()), center(vec.size()), depth(vec.size()), N, S, E, W);

	for (int i = 0; i < vec.size(); ++i) {
		if (count == vec.size()) break;
		for (int j = 0; j < vec.size(); ++j) {
			cout << h_tree[i][j] << " ";
			if (h_tree[i][j] != ' ') count++;
		}
		cout << endl;
	}
}

// make subtrees
void makeSubtree(const vector<char>& vec, vector<char>& left, vector<char>& right) {
	int index = 1;
	int depthCount = 1;
	int max_depth = maxDepth(vec.size());

	while (depthCount <= max_depth) {
		for (int i = 0; i < pow(2, depthCount - 1); ++i) {
			if (index >= vec.size()) {
				break;
			}
			
			left.push_back(vec[index]);
			index++;
		}

		for (int i = 0; i < pow(2, depthCount - 1); ++i) {
			if (index >= vec.size()) {
				break;
			}

			right.push_back(vec[index]);
			index++;
		}

		depthCount++;
	}
}

// get heap's maximum depth
int maxDepth(int size) {
	int depthCount = -1;
	int count = 0;
	while (size > 0) {
		size -= pow(2, count);
		count++;
		depthCount++;
	}

	return depthCount;
}

int center(int size) { return size <= 1 ? 0 : 2 * center(size / 4) + 1; }
int depth(int size) { return size <= 7 ? 1 : 2 * depth(size / 4); }

void HTree(char** h_tree, const vector<char>& vec, int index, int col, int row, int depth, int up, int down, int right, int left) {
	if (index > vec.size()) return;

	h_tree[col][row] = vec[index - 1];

	if (2 * index <= vec.size()) {
		h_tree[col + depth * V[left][0]][row + depth * V[left][1]] = vec[2 * index - 1];

		HTree(h_tree, vec, index * 4, col + depth * (V[left][0] + V[up][0]), 
			row + depth * (V[left][1] + V[up][1]), depth / 2, down, up, left, right);

		HTree(h_tree, vec, index * 4 + 1, col + depth * (V[left][0] + V[down][0]),
			row + depth * (V[left][1] + V[down][1]), depth / 2, up, down, right, left);
	}
	
	if (2 * index + 1 <= vec.size()) {
		h_tree[col + depth * V[right][0]][row + depth * V[right][1]] = vec[2 * index];

		HTree(h_tree, vec, index * 4 + 2, col + depth * (V[right][0] + V[down][0]),
			row + depth * (V[right][1] + V[down][1]), depth / 2, up, down, right, left);

		HTree(h_tree, vec, index * 4 + 3, col + depth * (V[right][0] + V[up][0]),
			row + depth * (V[right][1] + V[up][1]), depth / 2, down, up, left, right);
	}
}