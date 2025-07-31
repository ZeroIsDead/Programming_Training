#include <iostream>
#include <string>
#include <iomanip>
#include <climits>

using namespace std;

struct node {
    string* data;
    node* left;
    node* right;

    node(string* data) : data(data), left(nullptr), right(nullptr) {}
};

class tree {
public:
    node* root = nullptr;

    tree(string** data, int size) {
        for (int i = 0; i < size; i++) {
            root = insert(root, data[i]);
        }
    }

    node* insert(node* currentRoot, string* data) {
        if (currentRoot == nullptr) {
            return new node(data);
        } else if (data[0] < currentRoot->data[0]) {
            currentRoot->left = insert(currentRoot->left, data);
        } else {
            currentRoot->right = insert(currentRoot->right, data);
        }
        return currentRoot;
    }

    void preorder(node* currentRoot) {
        if (currentRoot) {
            cout << currentRoot->data[0] << " ";
            preorder(currentRoot->left);
            preorder(currentRoot->right);
        }
    }

    void inorder(node* currentRoot) {
        if (currentRoot) {
            inorder(currentRoot->left);
            cout << currentRoot->data[0] << " ";
            inorder(currentRoot->right);
        }
    }

    void postorder(node* currentRoot) {
        if (currentRoot) {
            postorder(currentRoot->left);
            postorder(currentRoot->right);
            cout << currentRoot->data[0] << " ";
        }
    }

    int countNodes(node* currentRoot) {
        return currentRoot ? 1 + countNodes(currentRoot->left) + countNodes(currentRoot->right) : 0;
    }

    int treeHeight(node* currentRoot) {
        return currentRoot ? 1 + max(treeHeight(currentRoot->left), treeHeight(currentRoot->right)) : 0;
    }

    int sumPrices(node* currentRoot) {
        return currentRoot ? stoi(currentRoot->data[4]) + sumPrices(currentRoot->left) + sumPrices(currentRoot->right) : 0;
    }

    int sumQuantity(node* currentRoot) {
        return currentRoot ? stoi(currentRoot->data[5]) + sumQuantity(currentRoot->left) + sumQuantity(currentRoot->right) : 0;
    }

    int minQuantity(node* currentRoot) {
        if (!currentRoot) return INT_MAX;
        return min(stoi(currentRoot->data[5]), min(minQuantity(currentRoot->left), minQuantity(currentRoot->right)));
    }

    int maxQuantity(node* currentRoot) {
        if (!currentRoot) return INT_MIN;
        return max(stoi(currentRoot->data[5]), max(maxQuantity(currentRoot->left), maxQuantity(currentRoot->right)));
    }

    node* findMin(node* currentNode) {
        while (currentNode && currentNode->left) {
            currentNode = currentNode->left;
        }
        return currentNode;
    }

    node* deleteNode(node* root, const string& key) {
        if (!root) return nullptr;

        if (key < root->data[0]) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->data[0]) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->left && !root->right) {
                delete root;
                return nullptr;
            } else if (!root->left) {
                node* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                node* temp = root->left;
                delete root;
                return temp;
            } else {
                node* successor = findMin(root->right);
                root->data = successor->data;
                root->right = deleteNode(root->right, successor->data[0]);
            }
        }
        return root;
    }
};


int main() {
    string** data = new string*[6];

    data[0] = new string[6]{"Car0051", "Proton", "X50", "White", "95000", "5"};
    data[1] = new string[6]{"Car0302", "Honda", "Civic", "Red", "135000", "3"};
    data[2] = new string[6]{"Car0024", "Toyota", "Yaris", "Red", "87900", "2"};
    data[3] = new string[6]{"Car0101", "Toyota", "Corolla Cross", "Yellow", "125700", "5"};
    data[4] = new string[6]{"Car1001", "Perodua", "MyVi", "Blue", "48700", "2"};
    data[5] = new string[6]{"Car5051", "Mazda", "X30", "Black", "115000", "1"};

    tree cars(data, 6);

    cout << "Preorder: ";
    cars.preorder(cars.root);
    cout << endl;

    cout << "Postorder: ";
    cars.postorder(cars.root);
    cout << endl;

    cout << "Inorder: ";
    cars.inorder(cars.root);
    cout << endl;

    cout << "Total Nodes: " << cars.countNodes(cars.root) << endl;
    cout << "Total Price: " << cars.sumPrices(cars.root) << endl;
    cout << "Total Quantity: " << cars.sumQuantity(cars.root) << endl;
    cout << "Tree Height: " << cars.treeHeight(cars.root) << endl;
    cout << "Min Quantity: " << cars.minQuantity(cars.root) << endl;
    cout << "Max Quantity: " << cars.maxQuantity(cars.root) << endl;

    cars.root = cars.deleteNode(cars.root, "Car0051");
    cout << "After deleting Car0051, Inorder: ";
    cars.inorder(cars.root);
    cout << endl;

    for (int i = 0; i < 6; ++i) {
        delete[] data[i];
    }
    delete[] data;

    return 0;
}
