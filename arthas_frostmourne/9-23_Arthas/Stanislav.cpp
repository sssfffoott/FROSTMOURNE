#include <iostream>

class Node {

	std::unique_ptr<int>data;
	std::shared_ptr<Node>next;

public:

	Node(int value) : data{ std::make_unique<int>(value) }, next{ nullptr } {std::cout << "n" << value << "Created"; }
	~Node() {
		std::cout << "n" << *data << "Destroyed\n";
	}

	void setData(int value) { *data = value; }
	void setNext(std::shared_ptr<Node>next) { this->next = next; }
	int& getData() { if (data)return *data; else throw std::exception("Data is empty"); }
	std::shared_ptr<Node>& getNext() { return next; }


};

class List {

	std::shared_ptr<Node>first, last;
public:
	List() :first{ nullptr }, last{ nullptr } {};
	void addNode(int value) {
		if (!first) {
			first = last = std::make_unique<Node>(value);
		}
		else {
			last->setNext(std::make_shared<Node>(value));
			last = last->getNext();
		}
	}
	int& operator[](int index) {
		if (first) {
			std::shared_ptr<Node>temp = first;
			for (int i = 0; i < index; i++) {
				if (temp)  temp->getNext();
				else throw std::out_of_range("куда");
			}
			return temp->getData();
		}
		else throw std::out_of_range("куда");
	}

	friend std::ostream& operator<< (std::ostream& out, const List& list) {
		std::shared_ptr<Node>temp = list.first;
		while (temp)
			if (temp) {
				out << temp->getData() << " ";
				temp = temp->getNext();
			}
			else throw std::out_of_range("куда");
	}


};

int main() {
	system("chcp 1251");
	List l1;
	l1.addNode(-14); l1.addNode(55); l1.addNode(70); l1.addNode(0);
	std::cout << l1[0] << " " << l1[1] << std::endl;
}