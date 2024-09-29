#include "main.hpp"
// #include "Dataset.hpp"
#include "kDTree.hpp"
// #include <algorithm>
// #include <queue>
void tc1()
{
    kDTree tree(2);
    tree.insert({5, 6});
    // tree.preorderTraversal();
    // cout << "\n";
    tree.insert({2, 2});
    // tree.preorderTraversal();
    // cout << "\n";
    tree.insert({7, 3});
    // tree.preorderTraversal();
    // cout << "\n";
    tree.insert({2, 8});
    // tree.preorderTraversal();
    // cout << "\n";
    tree.insert({8, 7});
    // tree.preorderTraversal();
    // cout << "\n";
    tree.insert({8, 1});
    // tree.preorderTraversal();
    // cout << "\n";
    tree.insert({9, 4});
    // tree.preorderTraversal();
    // cout << "\n";
    tree.insert({3, 5});
    // tree.preorderTraversal();
    // cout << "\n";
    tree.inorderTraversal();
}

void tc2()
{
    kDTree tree(2);
    tree.insert({5, 6});
    tree.insert({2, 2});
    tree.insert({7, 3});
    tree.insert({2, 8});
    tree.insert({8, 7});
    tree.insert({8, 1});
    tree.insert({9, 4});
    tree.insert({3, 5});
    tree.insert({9, 2});
    tree.preorderTraversal();
}

void tc3()
{
    kDTree tree(2);
    vector<vector<int>> pointList = {{5, 6}, {2, 2}, {7, 3}, {2, 8}, {8, 7}, {8, 1}, {9, 4}, {3, 5}};
    tree.buildTree(pointList);
    tree.preorderTraversal();
}

void tc4()
{
    kDTree tree(2);
    vector<vector<int>> pointList = {{5, 6}, {2, 2}, {7, 3}, {2, 8}, {8, 7}, {8, 1}, {9, 4}, {3, 5}};
    tree.buildTree(pointList);
    cout << tree.search({2, 2}) << endl;
    cout << tree.search({9, 3}) << endl;
}

void tc5()
{
    kDTree tree(2);
    tree.insert({5, 6});
    tree.insert({2, 2});
    tree.insert({7, 3});
    tree.insert({2, 8});
    tree.insert({8, 1});
    tree.insert({3, 5});
    tree.insert({9, 2});
    tree.remove({7, 3});
    tree.preorderTraversal();
}

void tc6()
{
    kDTree tree(2);
    tree.insert({5, 6});
    tree.insert({2, 2});
    tree.insert({7, 3});
    tree.insert({2, 8});
    tree.insert({3, 5});
    tree.insert({8, 2});
    tree.insert({8, 7});
    tree.insert({9, 2});
    tree.insert({9, 5});
    kDTreeNode *best = nullptr;
    tree.nearestNeighbour({9, 3}, best);
    cout << "Nearest neighbour of (9, 3) is " << *best << endl;
}

void tc7()
{
    kDTree tree(2);
    tree.insert({5, 6});
    tree.insert({2, 2});
    tree.insert({7, 3});
    tree.insert({2, 8});
    tree.insert({3, 5});
    tree.insert({8, 2});
    tree.insert({8, 7});
    tree.insert({9, 2});
    tree.insert({9, 5});
    vector<kDTreeNode *> bestList;
    tree.kNearestNeighbour({9, 3}, 5, bestList);
    cout << "5 Nearest neighbour of (9, 3) are: ";
    for (auto node : bestList)
    {
        cout << *node << " ";
    }
}

void tc8()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);

    std::cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    std::cout << endl;
    std::cout << "y_test" << endl;
    y_test.printHead(10, 10);
    std::cout << endl;
}

void tc9()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;

    kNN knn(30);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    std::cout << "Accuracy: " << accuracy << endl;
}

// void testBuildTreeWithLabel()
// {
//     kDTree tree(3);
//     vector<vector<int>> pointList = {{5, 6, 9}, {2, 2, 5}, {7, 3, 6}, {2, 8, 3}, 
//                                     {8, 7, 1}, {8, 1, 9}, {9, 4, 3}, {3, 5, 4}};
//     tree.buildTree(pointList);
//     tree.preorderTraversal();
// }


// test 1 node in tree
void tc00(){
    kDTree tree(2);
    tree.insert({1,2});
    cout << "pre order:";
    tree.preorderTraversal();
    cout << "in order:";
    tree.inorderTraversal();
    cout << "post order:";
    tree.postorderTraversal();
}

void tc01(){
    kDTree tree(2);
    tree.insert({1,2});
    tree.insert({3,5});
    tree.insert({5,7});
    tree.insert({0,-1});
    cout << "pre order:";
    tree.preorderTraversal();
    cout << "in order:";
    tree.inorderTraversal();
    cout << "post order:";
    tree.postorderTraversal();
}

// test opearator =
void tc02()
{
    kDTree tree(2);
    tree.insert({5, 6});
    tree.insert({2, 2});
    tree.insert({7, 3});
    tree.insert({2, 8});
    tree.insert({8, 7});
    tree.insert({8, 1});
    tree.insert({9, 4});
    tree.insert({3, 5});
    tree.insert({9, 2});

    kDTree tree2 = tree;
    cout << "tree: ";
    tree.preorderTraversal();
    cout << "\ntree2: "; 
    tree2.preorderTraversal();
}

// test copy constructor
void tc03(){
    kDTree tree(2);
    tree.insert({5, 6});
    tree.insert({2, 2});
    tree.insert({7, 3});
    tree.insert({2, 8});
    tree.insert({8, 7});
    tree.insert({8, 1});
    tree.insert({9, 4});
    tree.insert({3, 5});
    tree.insert({9, 2});

    kDTree tree2(tree);
    cout << "tree: ";
    tree.preorderTraversal();
    cout << "\ntree2: "; 
    tree2.preorderTraversal();
}

// test clear():
void tc04(){
    kDTree * tree = new kDTree(2);
    tree->insert({5, 6});
    tree->insert({2, 2});
    tree->insert({7, 3});
    tree->insert({2, 8});
    tree->insert({8, 7});
    tree->insert({8, 1});
    tree->insert({9, 4});
    tree->insert({3, 5});
    tree->insert({9, 2});

    tree->preorderTraversal();
    delete tree;
    if (tree) cout << "\nDelete!";
    else cout << "\nNot delete!";
}


int main(int argc, const char *argv[])
{
    // testBuildTreeWithLabel();
    // cout << endl;
    // tc3();
    tc5();
    return 0;
}