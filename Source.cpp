// 5-3 programa za rabota s orientiran graf, predstawen chrez spsyci na sysedstwo
// menu s osnowni operacii i funkciq koqto broi i wizualizira izolirani wyrhowe w grafa

#include <iostream>
#include <array>
using namespace std;

const int n = 10;
struct graph {
	int key;
	graph* next;
}*gr[n];

void init(graph* gr[n]) { //initialization
	for (int i = 0; i < n; i++) {
		gr[i] = NULL;
	}
}

int searchNode(graph* gr[n], int num) { //searching element num
	for (int i = 0; i < n; i++) {
		if (gr[i]) {
			if (gr[i]->key == num) {
				return 1;
			}
		}
	}
	return 0;
}

int searchArc(graph* gr[n], int node1, int node2) { //searching arc from element1 to element2
	if (searchNode(gr, node1) && searchNode(gr, node2)) {
		int i = 0;
		while (gr[i] == NULL || gr[i]->key != node1) {
			i++;
		}
		graph* p = gr[i];
		while (p->key != node2 && p->next != NULL) {
			p = p->next;
		}
		if (p->key == node2) {
			return 1;
		}
	}
	return 0;
}

void addNode(graph* gr[n], int node) { //adding a new node
	if (searchNode(gr, node)) {
		cout << "\n Already existing node.";
	}
	else {
		int j = 1;
		while (gr[j] && (j < n)) {
			j++;
		}
		if (gr[j] == NULL) {
			gr[j] = new graph;
			gr[j]->key = node;
			gr[j]->next = NULL;
		}
		else {
			cout << "\n Overflow.";
		}
	}
}

void addArc(graph* gr[n], int Node1, int Node2) { // adding arc between node1 and node2
	if (searchArc(gr, Node1, Node2)) {
		cout << "\n Already existing arc.";
	}
	else {
		int i = 0;
		graph* p = gr[i];
		if (!(searchNode(gr, Node1))) {
			addNode(gr, Node1);
		}
		if (!(searchNode(gr, Node2))) {
			addNode(gr, Node2);
		}
		while (gr[i] == NULL || gr[i]->key != Node1)
			i++;
		p = new graph;
		p->key = Node2;
		p->next = gr[i]->next;
		gr[i]->next = p;
	}
}

void delNode(graph* gr[n], int c) {
	if (searchNode(gr, c)) {
		int i = 0;
		while (gr[i]->key != c)
			i++;
		graph* p = NULL;
		graph* q = NULL;
		while (gr[i] != NULL) {
			p = gr[i];
			gr[i] = p->next;
			delete p;
		}
		for (i = 0; i < n; i++)
			if (gr[i]) {
				p = gr[i];
				while ((p->key != c) && (p->next != NULL)) {
					q = p;
					p = p->next;
				}
				if (p->key == c) {
					q->next = p->next;
					delete p;
				}
			} 
	}
	else
		cout << "\n There is not such node in the graph.";
}

void delArc(graph* gr[n], int c1, int c2) {
	if (searchArc(gr, c1, c2)) {
		int i = 0;
		while (gr[i]->key != c1)
			i++;
		graph* p = gr[i];
		graph* q = p;
		while (p->key != c2) {
			q = p;
			p = p->next;
		}
		q->next = p->next;
		delete p;
	}
	else
		cout << "\n There is no such arc in the graph.";
}


void print(graph* gr[n]) { //visualisation of a graph
	graph* p = NULL;
	cout << "\n Graph: " << endl;
	for (int i = 0; i < n; i++) {
		if (gr[i]) {
			cout << gr[i]->key << "-->";
		}
	}
}


int countIsolated(graph* gr[n]) {
	int broi = 0;
	int arr[20];
	int variable = 0;
	graph* p = NULL;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (gr[i] != NULL && gr[j] != NULL)
				if (gr[i]->key != gr[j]->key) {
					if (!searchArc(gr, gr[i]->key, gr[j]->key) && gr[j]->next == NULL) {
						if(arr[variable]!=gr[j]->key)
							arr[variable] = gr[j]->key;
							variable++;
					}
				}
		}
	}
	cout << endl;
	cout << "nadpis" << endl;
	for (int i = 0; i < variable; i++) {
			cout << arr[i]<<endl;
	}
	cout << "\n Potential isolated nodes:"<<endl;
	for (int i = 0; i < n; i++) {
		int j = 0;
		for (j = 0; j < i; j++) {
			if (arr[i] == arr[j])
				break;
		}
		if (i == j)
			cout << arr[i] << endl;
	}
	return broi;
}


int main() {
	int choice, numOfNode, count, node1, node2, nodeValue, isolated;
	do {
		cout << "\n\t Menu";
		cout << "\n 1. Graph initialisation";
		cout << "\n 2. Search node";
		cout << "\n 3. Search arc";
		cout << "\n 4. Add node";
		cout << "\n 5. Add arc";
		cout << "\n 6. Delete node";
		cout << "\n 7. Delete arc";
		cout << "\n 8. Visualise graph";
		cout << "\n 9. Count isolased nodes";
		cout << "\n 10. Print isolated nodes";
		cout << "\n 11. Exit";
		do
		{
			cout << "\n Your choice is: ";
			cin >> choice;
		} while (choice < 1 || choice>11);
		switch (choice) {
		case 1: init(gr);  break;
		case 2: 
			cout << "\n Which node do you want to find? ";
			cin >> numOfNode;
			if (searchNode(gr, numOfNode) == 1)
				cout << "\n Node found.";
			else
				cout << "\n There is no such node in the graph.";
			break;
		case 3: 
			cout << "\n Between witch nodes? "<<endl;
			cout << " ";
			cin >> node1;
			cout << " and ";
			cin >> node2;
			if (searchArc(gr, node1, node2) == 1)
				cout << "\n Arc found.";
			else
				cout << "\n There is no arc between these nodes.";
			break;
		case 4:
			cout << "\n How many nodes do you want to add? ";
			cin >> count;
			cout << "\n The values of the nodes you want to add are: "<<endl;
			while (count > 0) {
				cout << " ";
				cin >> nodeValue;
				addNode(gr, nodeValue);
				count--;
			}
			break;
		case 5:
			cout << "\n How many arcs do you want to add? ";
			cin >> count;
			while (count > 0) {
				cout << "\n Between which nodes you want to add an arc? "<<endl;
				cout << " ";
				cin >> node1;
				cout << " and ";
				cin >> node2;
				addArc(gr, node1, node2);
				count--;
			}
			break;
		case 6: 
			cout << "\n Which node do you want to delete? "<<endl;
			cin >> nodeValue;
			delNode(gr, nodeValue);
			break;
		case 7: 
			cout << "\n The arc between witch nodes do you want to delete? "<<endl;
			cin >> node1;
			cout << " and ";
			cin >> node2;
			delArc(gr, node1, node2);
			break;
		case 8: print(gr);  break;
		case 9: 
			isolated = countIsolated(gr);
			cout << "\n There are "<<isolated<<" isolated nodes.";
			 break;
		case 10: break;
		case 11: break;
		}
	} while (choice != 10);
	system("pause");
	return 0;
}