#include <iostream>
#include <memory>

template<typename T>
void print(T val);


//We need a function that will clear our 2D array
void populateMatrix(int** arr){
	int m = 0;
	for(int i = 0; i < 10; i++){
		for(int j = 0 ; j < 5;  j++){
			arr[i][j] = m;
			++m;
		}
	}
} 


class Node {
public:
	int data;
	Node* leftChild;
	Node* rightChild;

	Node(int num);
	~Node();
};

Node::Node(int num) {
	this->data = num;
	leftChild = nullptr;
	rightChild = nullptr;
}

Node::~Node() {
	std::cout << "We are deleting the node with the value: " << this->data << "\n\n";
}



int main() {

	//Let allocate an object in the heap, 
	//normally therefore we have to make sure that we delete it in the end
	Node* myNode = new Node(5);
	Node* mySecNode = new Node(11);
	//We will now delete the two nodes that in the heap
	delete myNode;
	delete mySecNode;
	
	//We will now work with an array where every index is a Node pointer.
	Node* theArr[10];
	
	//We need to populate the given array
	for(int i = 0; i < 10; i++)
		theArr[i] = new Node(i*10);
	//Display the data of every Node pointer in the given array
	for (int i = 0; i < 10; i++) {
		Node* curr = theArr[i];
		std::cout << "At " << i << " : " << curr->data << "\n";
	}

	//We need to traverse the array and delete every single Node
	for (int i = 0; i < 10; i++)
		delete theArr[i];
	


	//Our unique pointer will automatically delete the object in the heap 
	//Set a local scope for our unique pointer
	{
		std::unique_ptr<Node> theMainPtr = std::make_unique<Node>(100);
		std::cout << "\n\nThe unique pointer is pointing to the Node : "<< theMainPtr->data;
		std::cout << "\n";
	}
	//Note that you will not be able to share this pointer or pass it to a function
	//It will only live in the given scope


	//TO SOLVE THIS WE CAN USE A SHARED POINTER
	//(Ref count go up with every single shared pointer, 
	//To delete the object, all the shared pointers must die, 
	//Therefore the ref count must go to zero.
	
	{
		std::shared_ptr<Node> sharingTwoPtr;
		std::shared_ptr<Node> sharingThreePtr;
		{
			std::shared_ptr<Node> sharingOnePtr = std::make_shared<Node>(500);

			sharingTwoPtr = sharingOnePtr;
			sharingThreePtr = sharingOnePtr;


			std::cout << "\n\nShared One Points to: " << sharingOnePtr->data << "\n";
			std::cout << "Shared Two Points to: " << sharingTwoPtr->data << "\n";
			std::cout << "Shared Three Points to: " << sharingThreePtr->data << "\n\n";

		}
		//The inner local scope will not delete 
		//the object from the heap because we still have two shared pointers alive

		std::cout << "The node in the heap is still alive\n";
		std::cout << "We now exit the outer scope:\n";
	}
	//All the shared pointers are dead and therefore our object in the heap has been deleted.

	//For a weak point, You can combine a shared pointer, but the reference count will increase.

	//We are now going to work with Templates specifically for a function.
	//We are telling the compiler to write code for us.
	print<int>(3);
	print<std::string>("Hola");
	print<double>(33.4);


	//How do we deal with a 2D Matrix that is placed in the heap
	int** arr = new int*[10];
	for(int i = 0; i< 10; i++){
		arr[i] = new int[5];
	}
	//I defined a function that will populate our 2D matrix
	populateMatrix(arr);

	//Print the 2D array
	for(int i = 0; i< 10; i++){
		std::cout << "\n";	
		for(int j = 0 ; j < 5 ; j++)
			std::cout << arr[i][j] << "\t";
	}
	
	//Delete the 2D matrix that was placed in the heap
	for(int i =0; i < 10; i++){
		delete[] arr[i];
	}

	delete[] arr;
	//The heap has been cleared, we are done with the 2D Matrix
}

template<typename T>
void print(T val){
	std::cout << val << "\n";
}
