#include "main.hpp"
#include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

struct kDTreeNode
{
    vector<int> data;
    kDTreeNode *left;
    kDTreeNode *right;
    // ! for kNN 
    int label;

    kDTreeNode(vector<int> data, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }

    friend ostream &operator<<(ostream &os, const kDTreeNode &node)
    {
        os << "(";
        for (int i = 0; i < node.data.size(); i++)
        {
            os << node.data[i];
            if (i != node.data.size() - 1)
            {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }
};

// g++ -o main main.cpp kDTree.cpp Dataset.o -I . -std=c++11

void merge(vector<vector<int>>& arr, int axis, int l, int m, int r);
void mergeSort(vector<vector<int>>& arr, int axis, int l, int r);
int distance(const vector<int>& target, const vector<int>& point);
list<int> getMaxLabel(vector<kDTreeNode*> bestList);

class kDTree
{
private:
    int k;
    kDTreeNode *root;

public:
    kDTree(int k = 2){
        this->k = k;
        this->root = nullptr;
        // cout << "This tree has " << k << " dimensions." << endl;
    }
    ~kDTree(){
        clearTree(this->root);
    }
    const kDTree &operator=(const kDTree &other){
        if (this != &other) {
            // if exists before information, delete them first, then copy from other to this
            clearTree(this->root);
            this->root = deepCopyTree(other.root);
        }
        return *this;
    }
    kDTree(const kDTree &other){
        this->root = deepCopyTree(other.root);
    }

    void inorderTraversal() const{
        bool isRoot = false;
        inorderTraversalUtil(this->root, this->root, isRoot);
    }
    void preorderTraversal() const{
        preorderTraversalUtil(this->root, true);
    }
    void postorderTraversal() const{
        postorderTraversalUtil(this->root, true);
    }
    int height() const{
        return heightUtil(this->root);
    }
    int nodeCount() const{
        return nodeCountUtil(this->root);
    }
    int leafCount() const{
        return leafCountUtil(this->root);
    }

    void insert(const vector<int> &point){
        this->root = insertUtil(this->root, point, 0);
    }
    void remove(const vector <int >& point){
        removeUtil(this->root, point, 0);
    } 
    bool search(const vector<int> &point){
        return searchUtil(root, point, 0);
    }
    void buildTree(const vector<vector<int>> &pointList){
        this->root = buildTreeUtil(pointList, 0);
    }
    void nearestNeighbour(const vector<int> &target, kDTreeNode *&best){
        nearestNeighbourUtil(root, target, best, 0);
    }
    void kNearestNeighbour(const vector<int>& target, int k, vector<kDTreeNode*>& bestList) {
        kNearestNeighbourUtil(root, target, k, bestList, 0);
    }

    //! ----------------------- Utils -----------------------
    // % Insert 
    kDTreeNode * insertUtil(kDTreeNode* node, const vector<int>& point, int depth){
        if (node == nullptr) return new kDTreeNode(point);

        int axis = depth % k;

        if (point[axis] < node->data[axis]) node->left = insertUtil(node->left, point, depth + 1);
        else node->right = insertUtil(node->right, point, depth + 1);

        return node;
    }
    // % Build tree 
    kDTreeNode* buildTreeUtil(const vector<vector<int>>& pointList, int depth) {
        if (pointList.empty()) return nullptr;

        int axis = depth % k;

        // Sort along the axis
        vector<vector<int>> sortedPointList = pointList;
        mergeSort(sortedPointList, axis, 0, sortedPointList.size() - 1);
        
        int medianIndex = (sortedPointList.size() - 1) / 2; // Find median point
        vector<int> medianPoint = sortedPointList[medianIndex];

        // Create new node with median point
        kDTreeNode* newNode = new kDTreeNode(medianPoint);

        // Recursively build left and right subtrees
        vector<vector<int>> leftSubTree(sortedPointList.begin(), sortedPointList.begin() + medianIndex);
        vector<vector<int>> rightSubTree(sortedPointList.begin() + medianIndex + 1, sortedPointList.end());
        newNode->left = buildTreeUtil(leftSubTree, depth + 1);
        newNode->right = buildTreeUtil(rightSubTree, depth + 1);

        return newNode;
    }
    // % Search 
    bool searchUtil(kDTreeNode* node, const vector<int>& point, int depth) {
        if (node == nullptr) return false;

        if (point == node->data) return true; // Found

        int axis = depth % k;

        if (point[axis] < node->data[axis]){
            return searchUtil(node->left, point, depth + 1);
        }
        else return searchUtil(node->right, point, depth + 1);
    }
    // % Remove 
    kDTreeNode* findMin(kDTreeNode* node, int dim, int depth) {
        if (node == nullptr) return nullptr; // empty tree

        int axis = depth % k;

        if (axis == dim) {
            if (node->left == nullptr) return node;
            else return findMin(node->left, dim, depth + 1);
        } 
        else {
            kDTreeNode* leftMinNode = findMin(node->left, dim, depth + 1);
            kDTreeNode* rightMinNode = findMin(node->right, dim, depth + 1);
            kDTreeNode* currMinNode = node;

            if (leftMinNode != nullptr && leftMinNode->data[dim] < currMinNode->data[dim]) {
                currMinNode = leftMinNode;
            }
            if (rightMinNode != nullptr && rightMinNode->data[dim] < currMinNode->data[dim]) {
                currMinNode = rightMinNode;
            }

            return currMinNode;
        }
    }
    kDTreeNode* removeUtil(kDTreeNode* node, const vector<int>& point, int depth) {
        if (node == nullptr) return nullptr;

        int currDim = depth % k;

        if (point == node->data) {
            if (node->right == nullptr && node->left == nullptr){ // leaf
                delete node;
                return nullptr;
            }
            else if (node->right != nullptr) {
                kDTreeNode* minNode = findMin(node->right, currDim, depth + 1);
                node->data = minNode->data;
                node->right = removeUtil(node->right, minNode->data, depth + 1);
            } 
            else if (node->left != nullptr) {
                kDTreeNode* minNode = findMin(node->left, currDim, depth + 1);
                node->data = minNode->data;
                node->left = removeUtil(node->left,minNode->data, depth + 1);
            }
        } 
        else if (point[currDim] < node->data[currDim]) {
            node->left = removeUtil(node->left, point, depth + 1);
        } 
        else {
            node->right = removeUtil(node->right, point, depth + 1);
        }

        return node;
    }   
    // * Pre Order 
    void preorderTraversalUtil(const kDTreeNode* node, bool isRoot = false) const {
        if (node != nullptr) {
            if (isRoot) cout << *(node);
            else cout << " " << *(node);
            preorderTraversalUtil(node->left);
            preorderTraversalUtil(node->right); 
        }
    }
    // * In Order 
    void inorderTraversalUtil(const kDTreeNode* root, const kDTreeNode* node, bool & isRight) const {
        if (node != nullptr) {
            inorderTraversalUtil(root, node->left, isRight);
            if (node == root && isRight == false){
                isRight = true;
                cout << *node;
            }
            else if (isRight == false) cout << *node << " ";
            else if (isRight == true) cout << " " << *node;
            inorderTraversalUtil(root, node->right, isRight);
        }
    }
    // * Post Order 
    void postorderTraversalUtil(const kDTreeNode* node, bool isRoot = false) const {
        if (node != nullptr) {
            postorderTraversalUtil(node->left);
            postorderTraversalUtil(node->right); 
            if (isRoot) cout << *(node);
            else cout << *(node) << " ";
        }
    }
    // & Height 
    int heightUtil(const kDTreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        // Recursively calculate the height of the left and right subtrees
        int leftSubTreeHeight = heightUtil(node->left);
        int rightSubTreeHeight = heightUtil(node->right);
        // Return the maximum height plus one (to account for the current node)
        return 1 + max(leftSubTreeHeight, rightSubTreeHeight);
    }
    // & Node Count 
    int nodeCountUtil(const kDTreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        // Recursively count nodes in the left and right subtrees
        int leftSubTreeNodeCount = nodeCountUtil(node->left);
        int rightSubTreeNodeCount = nodeCountUtil(node->right);
        // Return the total count of nodes including the current node
        return 1 + leftSubTreeNodeCount + rightSubTreeNodeCount;
    }
    // & Leaf Count 
    int leafCountUtil(const kDTreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        // If the node is a leaf (both left and right subtrees are nullptr), return 1
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }
        // Recursively count leaf nodes in the left and right subtrees
        int leftSubTreeLeafCount = leafCountUtil(node->left);
        int rightSubTreeLeafCount = leafCountUtil(node->right);
        // Return the total count of leaf nodes
        return leftSubTreeLeafCount + rightSubTreeLeafCount;
    }
    // ! Nearest Neighbor 
    void nearestNeighbourUtil(kDTreeNode* node, const vector<int>& target, 
                            kDTreeNode*& best, int depth){
        if (node == nullptr) return;

        if (best == nullptr || distance(target, node->data) < distance(target, best->data))
            best = node;

        int axis = depth % this->k;

        if (target[axis] < node->data[axis]) {
            nearestNeighbourUtil(node->left, target, best, depth + 1);
        } 
        else {
            nearestNeighbourUtil(node->right, target, best, depth + 1);
        }

        // Check for other side 
        int axisDist = abs(target[axis] - node->data[axis]);
        if (best == nullptr || axisDist * axisDist < distance(target, best->data)) {
            if (target[axis] < node->data[axis]) {
                nearestNeighbourUtil(node->right, target, best, depth + 1);
            } 
            else {
                nearestNeighbourUtil(node->left, target, best, depth + 1);
            }
        }
    }
    // ! K Nearest Neighbor 
    void kNearestNeighbourUtil(kDTreeNode * node, const vector<int>& target, int k, 
                            vector<kDTreeNode*>& bestList, int depth){
        if (node == nullptr) return;
        // cout << "Current node: " << *node << "; "; 
        insertInBestList(node, bestList, k, target);

        int axis = depth % this->k;
        if (target[axis] < node->data[axis]){
            kNearestNeighbourUtil(node->left, target, k, bestList, depth + 1);
        }
        else {
            kNearestNeighbourUtil(node->right, target, k, bestList, depth + 1);
        }

        int axisDist = abs(target[axis] - node->data[axis]);
        if (bestList.size() < k || axisDist < distance(target, bestList.back()->data)){
            if (target[axis] < node->data[axis]){
                kNearestNeighbourUtil(node->right, target, k, bestList, depth + 1);
            }
            else {
                kNearestNeighbourUtil(node->left, target, k, bestList, depth + 1);
            }
        }
    }
    void insertInBestList(kDTreeNode * node, vector<kDTreeNode*>& bestList,
                        int k, const vector<int> & target){
        if (bestList.empty()){
            bestList.push_back(node);
            return;
        }

        if (bestList.size() == 1){
            if (distance(target, node->data) <= distance(target, bestList[0]->data)){
                bestList.insert(bestList.begin(), node);
            }
            else bestList.push_back(node);
            return;
        }
        
        for (vector<kDTreeNode *>::iterator it = bestList.begin(); it != bestList.end(); ++it){
            if (distance(target, node->data) <= distance(target, (*it)->data)){
                bestList.insert(it, node);
                break;
            }
        }

        if (bestList.size() > k){
            bestList.pop_back();
        }
    }
    //! ----------------------- Support Functions -----------------------
    void clearTree(kDTreeNode* node) {
        if (node == nullptr) {
            return;
        }
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
    kDTreeNode* deepCopyTree(kDTreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }
        kDTreeNode* newNode = new kDTreeNode(node->data);
        newNode->left = deepCopyTree(node->left);
        newNode->right = deepCopyTree(node->right);
        return newNode;
    }
    // ! For kNN
    void buildTreeWithLabel(const vector<vector<int>>& pointList){
        this->root = buildTreeWithLabelUtil(pointList, 0);
    }
    kDTreeNode* buildTreeWithLabelUtil(const vector<vector<int>>& pointList, int depth){
        // pointList.shape = (159, 785)
        if (pointList.empty()) return nullptr;

        int axis = depth % this->k; // axis = 0..783

        // Sort along the axis
        vector<vector<int>> sortedPointList = pointList;
        mergeSort(sortedPointList, axis, 0, sortedPointList.size() - 1);
        
        int medianIndex = (sortedPointList.size() - 1) / 2; // Find median point
        vector<int> medianPoint = sortedPointList[medianIndex];

        // Create new node with median point and initial its label
        int label = medianPoint.back();
        medianPoint.pop_back();
        kDTreeNode* newNode = new kDTreeNode(medianPoint);
        newNode->label = label;

        // Recursively build left and right subtrees
        vector<vector<int>> leftSubTree(sortedPointList.begin(), sortedPointList.begin() + medianIndex);
        vector<vector<int>> rightSubTree(sortedPointList.begin() + medianIndex + 1, sortedPointList.end());
        newNode->left = buildTreeWithLabelUtil(leftSubTree, depth + 1);
        newNode->right = buildTreeWithLabelUtil(rightSubTree, depth + 1);

        // << "label: " << newNode->label << ", shape: " << newNode->data.size() << endl;
        return newNode;
    }
};

class kNN
{
private:
    int k;
    kDTree * kdtree;
public:
    kNN(int k = 5)
    {
        this->k = k;
    }
    void fit(Dataset &X_train, Dataset &y_train)
    {
        int numRows, numCols;
        X_train.getShape(numRows, numCols); // (numRows, numCols) = (159, 784)
        // Initial kdtree with 784 dimensions
        this->kdtree = new kDTree(numCols);
        // Clone data from X_train (list<list<int>> format) to vector<vector<int>> format
        vector<vector<int> > trainDataList; // (159, 784)
        for (list<int> innerList : X_train.data){
            vector<int> innerVector;
            for (int ele : innerList){
                innerVector.push_back(ele);
            }
            trainDataList.push_back(innerVector);
        }
        vector<int> trainLabelList; // (159, 1)
        // Clone y_train.data to a vector<int> labelList
        for (list<int> innerLabelList : y_train.data){
            trainLabelList.push_back(innerLabelList.front());
        }
        // With each point in trainDataList, push_back its respectively label 
        for (int i = 0; i < trainDataList.size(); i++){
            trainDataList[i].push_back(trainLabelList[i]);
        }
        // (159 points, each point has 785 dimension)
        // Now each point in trainDataList have 785 elements = 784 features + 1 label in the last position
        // We will build a kdtree with 784 dimensions (ignore the last dimension, which is label of that point)
        this->kdtree->buildTreeWithLabel(trainDataList);
    }
    Dataset predict(Dataset &X_test)
    {
        Dataset y_pred;
        y_pred.columnName.push_back("label");

        // Clone data from X_test.data (list<list<int>> format) to vector<vector<int>> format
        vector<vector<int> > testData;
        for (list<int> innerList : X_test.data){
            vector<int> innerVector;
            for (int ele : innerList){
                innerVector.push_back(ele);
            }
            testData.push_back(innerVector);
        }
        // Result will be stored in this list
        list<list<int>> y_pred_data;
        // Get each target from testData (vector<vector<int>>)
        for (vector<int> target : testData){
            vector<kDTreeNode*> bestList;
            // Find k nearest neighbors for each target and store them in bestList
            this->kdtree->kNearestNeighbour(target, this->k, bestList);
            y_pred_data.push_back(getMaxLabel(bestList));
        }
        y_pred.data = y_pred_data;
        return y_pred;
    }
    double score(const Dataset &y_test, const Dataset &y_pred){
        int correctLabel = 0, totalLabel = y_test.data.size();
        auto it_test = y_test.data.begin();
        auto it_pred = y_pred.data.begin();
        while(it_test != y_test.data.end() && it_pred != y_pred.data.end()){
            if((*it_test).front() == (*it_pred).front()) correctLabel++;
            it_test++; it_pred++;
        }
        double accuracy = 1.0 * correctLabel / totalLabel;
        return accuracy;
    }
};

// Please add more or modify as needed
