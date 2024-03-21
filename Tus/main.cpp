#include "kNN.hpp"
#include <chrono>

void tc1(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    // dataset.printHead();
    // dataset.printTail();
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

void _tc(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    // dataset.printHead();
    // dataset.printTail();
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    kNN knn(35);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    double test_size = 0.5;
    train_test_split(feature, label, test_size, X_train, X_test, y_train, y_test);

    cout << "k = " << knn.getK() << ", test_size = " << test_size << endl;

    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

void testList(){
    List<List<int>*>* data = new LinkedList<List<int>*>();

    List<int> * LL1 = new LinkedList<int>();
    LL1->push_back(1);
    LL1->push_back(2);
    LL1->push_back(3);
    data->push_front(LL1);

    List<int> * LL2 = new LinkedList<int>();
    LL2->push_back(4);
    LL2->push_back(5);
    LL2->push_back(6);
    data->push_front(LL2);

    List<int> * LL3 = new LinkedList<int>();
    LL3->push_back(7);
    LL3->push_back(8);
    LL3->push_back(9);
    data->push_back(LL3);

    cout << "test push_back, push_front and print: " << endl;
    for (int i = 0; i < data->length(); ++i) {
        data->get(i)->print();
        cout << endl;
    }

    // cout << "test reverse each inner list: " << endl; 
    // for (int i = 0; i < data->length(); i++){
    //     data->get(i)->print();
    //     cout << endl;
    // }

    // cout << "test reverse outer list: " << endl;
    // data->reverse();
    // for (int i = 0; i < data->length(); i++){
    //     data->get(i)->print();
    //     cout << endl;
    // }

    // int colIndex = 1;
    // cout << "test remove in inner lists: " << endl;
    // for (int i = 0; i < data->length(); i++){
    //     data->get(i)->remove(colIndex);
    // }

    // for (int i = 0; i < data->length(); i++){
    //     data->get(i)->print();
    //     cout << endl;
    // }

    // cout << "test remove in outer list: " << endl;
    // data->remove(colIndex);

    // for (int i = 0; i < data->length(); i++){
    //     data->get(i)->print();
    //     cout << endl;
    // }
    // delete data;

    // for (int i = 0; i < data->length(); ++i) {
    //     data->get(i)->print();
    //     cout << endl;
    // }

    // cout << "test moveHeadToTail: " << endl;
    // data->moveHeadToTail();
    // for (int i = 0; i < data->length(); ++i) {
    //     data->get(i)->print();
    //     cout << endl;
    // }

    // cout << "test moveHeadToTail: " << endl;
    // data->moveHeadToTail();
    // for (int i = 0; i < data->length(); ++i) {
    //     data->get(i)->print();
    //     cout << endl;
    // }

    // cout << "test moveHeadToTail: " << endl;
    // data->moveHeadToTail();
    // for (int i = 0; i < data->length(); ++i) {
    //     data->get(i)->print();
    //     cout << endl;
    // }
}

void testDataset(){
    Dataset dataset1;

    dataset1.loadFromCSV("mnist.csv");

    Dataset dataset2(dataset1);

    // cout << dataset2.getData()->length() << endl;

    // cout << "TEST loadFromCSV: " << endl;

    // cout << "------------------------------------------------------------------\n";
    // cout << "dataset1:" << endl;
    // cout << "numCols = " << dataset1.getNumCols() << ", numRows = " << dataset1.getNumRows() << endl;
    // cout << "features->length() = " << dataset1.getFeatures()->length() << endl;
    // cout << "data->length() = " << dataset1.getData()->length() << endl;
    // cout << "------------------------------------------------------------------\n";

    // cout << "TEST COPY CONSTRUCTOR: " << endl;
    // cout << "------------------------------------------------------------------\n";
    // cout << "dataset2:" << endl;
    // cout << "numCols = " << dataset2.getNumCols() << ", numRows = " << dataset2.getNumRows() << endl;
    // cout << "features->length() = " << dataset2.getFeatures()->length() << endl;
    // cout << "data->length() = " << dataset2.getData()->length() << endl;

    // for (int i = 0; i < dataset2.getFeatures()->length(); i++){
    //     if (dataset1.getFeatures()->get(i) != dataset2.getFeatures()->get(i)){
    //         cout << "\nfeatures list of dataset2 is different from dataset1 at: " << i << endl;
    //         break;
    //     }
    // }
    // cout << "\nfeatures list of dataset1 is the same with dataset2\n";

    // for (int i = 0; i < dataset2.getData()->length(); i++){
    //     for (int j = 0; j < dataset2.getData()->get(i)->length(); j++){
    //         if (dataset2.getData()->get(i)->get(j) != dataset1.getData()->get(i)->get(j)){
    //             cout << "\ndata list of dataset2 is different from dataset1 at: (" 
    //                 << i  << ", " << j << ")" << endl;
    //             break;
    //         }
    //     }
    // }
    // cout << "\ndata list of dataset1 is the same with dataset2\n";

    // cout << "TEST drop:" << endl;
    // cout << "====================================================\n";
    // cout << "axis = 0\n";
    // cout << "dataset2 before drop:" << endl;
    // cout << "rows = " << dataset2.getNumRows() << ", cols = " << dataset2.getNumCols() << endl;
    // dataset2.printHead(6, 20);

    // dataset2.drop(0, -1, "");

    // cout << "dataset2 after drop:" << endl;
    // cout << "rows = " << dataset2.getNumRows() << ", cols = " << dataset2.getNumCols() << endl;
    // dataset2.printHead(5, 20);
    // cout << "====================================================\n";

    // cout << "axis = 1\n";

    // string dropColName = "label";
    // cout << "dataset2 before drop column: " << dropColName << endl;
    // cout << "rows = " << dataset2.getNumRows() << ", cols = " << dataset2.getNumCols() << endl;
    // dataset2.printHead();

    // dataset2.drop(1, -1, "hehe");

    // cout << "dataset2 after drop column: " << dropColName << endl;
    // cout << "rows = " << dataset2.getNumRows() << ", cols = " << dataset2.getNumCols() << endl;
    // dataset2.printHead();
    // cout << "====================================================\n";

    // cout << "TEST extract: \n";
    // Dataset label = dataset1.extract(0, -1, 0, 0);
    // cout << "numRows = " << label.getNumRows() << ", numCols = " << label.getNumCols() << endl;
    // cout << "features.length = " << label.getFeatures()->length() << endl;
    // cout << "features[0] = " << label.getFeatures()->get(0) << endl;
    
    // for (int i = 0; i < label.getData()->length(); i++){
    //     for (int j = 0; j < label.getData()->get(i)->length(); j++){
    //         cout << "label.data[" << i << "][" << j << "] = " 
    //             << label.getData()->get(i)->get(j) << endl;
    //     }
    // }

    // cout << "=======================\n";
    
    // Dataset feature = dataset2.extract(0, -1, 1, -1);
    // cout << "numRows = " << feature.getNumRows() 
    //     << ", numCols = " << feature.getNumCols() << endl;
    // cout << "features.length = " << feature.getFeatures()->length() << endl;

    // cout << "test train_test_split:" << endl;

    // Dataset label = dataset1.extract(0, -1, 0, 0);
    // Dataset feature = dataset1.extract(0, -1, 1, -1);
    // Dataset X_train, y_train, X_test, y_test;
    // double test_size = 0.2;
    // train_test_split(feature, label, test_size, X_train, X_test, y_train, y_test);

    // cout << "X_train.shape = (" << X_train.getNumRows() << ", " << X_train.getNumCols()
    //     << ")" << endl;
    // cout << "X_test.shape = (" << X_test.getNumRows() << ", " << X_test.getNumCols()
    //     << ")" << endl;
    // cout << "y_train.shape = (" << y_train.getNumRows() << ", " << y_train.getNumCols()
    //     << ")" << endl;
    // cout << "y_test.shape = (" << y_test.getNumRows() << ", " << y_test.getNumCols()
    //     << ")" << endl;

    
    // y_train.getData()->get(0)->print();

}

void testkNN(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

    // cout << "feature.shape = (" << feature.getNumRows() << ", " 
    //     << feature.getNumCols() << ")\n";
    
    // cout << "X_train.shape = (" << X_train.getNumRows() << ", " 
    //     << X_train.getNumCols() << ")\n";

    // cout << "X_test.shape = (" << X_test.getNumRows() << ", " 
    //     << X_test.getNumCols() << ")\n";

    // cout << "y_train.shape = (" << y_train.getNumRows() << ", " 
    //     << y_train.getNumCols() << ")\n";
    
    // cout << "label.shape = (" << label.getNumRows() << ", " 
    //     << label.getNumCols() << ")\n";

    // cout << "y_test.shape = (" << y_test.getNumRows() << ", " 
    //     << y_test.getNumCols() << ")\n";

    knn.fit(X_train, y_train);

    // cout << "knn.X_train.shape = (" << knn.getX_train().getNumRows()
    //     << ", " << knn.getX_train().getNumCols() << ")\n";

    // cout << "knn.y_train.shape = (" << knn.getY_train().getNumRows()
    //     << ", " << knn.getY_train().getNumCols() << ")\n";

    //     cout << "knn.X_test.shape = (" << X_test.getNumRows()
    //     << ", " << X_test.getNumCols() << ")\n";

    // cout << "knn.y_test.shape = (" << y_test.getNumRows()
    //     << ", " << y_test.getNumCols() << ")\n";

    Dataset y_pred = knn.predict(X_test);

    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

void tc_insert(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int>* row = dataset.getData()->get(0);
    for(int j = 0; j < 1; j++){
        for(int i = 0; i < 5; i++){
            row->insert(0, 1);
        }
        for(int i = 0; i < 5; i++){
            row->remove(0);
        }
    }
    cout << row->length();
}

void tc1004()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int> *row = dataset.getData()->get(0);

    row->push_back(0);
    row->push_back(2);

    cout << row->length() << endl;
    row->print();
}

void tc1006()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int> *row = dataset.getData()->get(0);

    row->push_back(1);
    row->push_back(0);
    row->push_back(0);

    cout << row->length() << endl;
    row->print();
}

void tc1010()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int> *row = dataset.getData()->get(0);

    for (int i = 0; i < 100000; i++)
    {
    row->push_back(2);
    }

    cout << row->length() << endl;
    row->print();
}

void tc1047()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int> *row = dataset.getData()->get(0);

    row->remove(-1);

    cout << row->length();
}

void tc1048()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int> *row = dataset.getData()->get(0);

    row->insert(0, 1);
    row->remove(-6);

    cout << row->length();
}

void tc1158()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    Dataset dataset_extract = dataset.extract(0, -2, 0, -1);
    Dataset dataset_extract2 = Dataset(dataset_extract);
    dataset_extract2.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc1155()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    Dataset dataset_extract = dataset.extract();
    dataset_extract.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc1156()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    Dataset dataset_extract = dataset.extract(0, -1, 0, -1);
    dataset_extract.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc1157()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    Dataset dataset_extract = dataset.extract(0, 0, 0, -1);
    dataset_extract.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc_knn_p(int k, int size_X){
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    kNN knn = kNN(k);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, size_X, 1, -1);
    Dataset label = dataset.extract(0, size_X, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);

    cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(10, 10);
    cout << endl;
}

void tc_knn_score(int k, int size_X){
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    kNN knn = kNN(k);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, size_X, 1, -1);
    Dataset label = dataset.extract(0, size_X, 0, 0);

    // ! DA 
    // cout << "feature.shape = (" << feature.getNumRows() << ", "<< feature.getNumCols() << ")\n"
    //     << "label.shape = (" << label.getNumRows() << ", " << label.getNumCols() << ")\n";
    // !
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

    // ! DA 
    // cout << "X_train.shape = (" << X_train.getNumRows() << ", "<< X_train.getNumCols() << ")\n"
    //     << "y_train.shape = (" << y_train.getNumRows() << ", " << y_train.getNumCols() << ")\n"
    //     << "X_test.shape = (" << X_test.getNumRows() << ", " << X_test.getNumCols() << ")\n"
    //     << "y_test.shape = (" << y_test.getNumRows() << ", " << y_test.getNumCols() << ")\n";
    // !

    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

void tc1205(){
    tc_knn_score(10, 10);
}

void tc1208(){
    tc_knn_score(10, -1);
}

void tc1184(){
    tc_knn_p(2, -1);
}

void tc1187(){
    tc_knn_p(3, 100);
}

void testIterator(){
    List<List<int>*>* data = new LinkedList<List<int>*>();

    List<int> * LL1 = new LinkedList<int>();
    LL1->push_back(1);
    LL1->push_back(2);
    LL1->push_back(3);
    data->push_front(LL1);

    List<int> * LL2 = new LinkedList<int>();
    LL2->push_back(4);
    LL2->push_back(5);
    LL2->push_back(6);
    data->push_front(LL2);

    List<int> * LL3 = new LinkedList<int>();
    LL3->push_back(7);
    LL3->push_back(8);
    LL3->push_back(9);
    data->push_back(LL3);

    cout << "Print Normally:\n";
    for (int i = 0; i < data->length(); i++){
        data->print();
        cout << endl;
    }
    cout << endl;

    // Iterator<List<int>*> it;
    // for (it = data->begin(); it != data->end(); ++it){
    //     List<int> * currList = *it;
    //     Iterator<int> ite;
    //     for (ite = currList->begin(); ite != currList->end(); ++ite){
    //         cout << *ite << " ";
    //     }
    //     cout << endl;
    // }
    // int cnt = 0;

    // while(){
    //     List<int>* currList = it.get_current();
    //     currList->print();
    //     cout << endl;
    //     it.move();
    // }
    // cout << "index: " << outerIterator.getIndex() << endl;
    // outerIterator.getList()->print();
    // Duyệt qua danh sách các danh sách
    // while (outerIterator != nullptr) {
    //     // Lấy danh sách hiện tại từ Iterator
    //     List<int> * currentList = outerIterator.get_current();
        
    //     // // Sử dụng một Iterator mới để duyệt qua danh sách hiện tại
    //     // Iterator<int>* innerIterator = currentList->begin();

    //     // // In ra các phần tử của danh sách hiện tại
    //     // while (innerIterator != nullptr) {
    //     //     std::cout << innerIterator->get() << " ";
    //     //     innerIterator->move();
    //     // }
        
    //     currentList->print();

    //     // Di chuyển đến danh sách tiếp theo
    //     outerIterator.move();
    //     break;
    // }


    // for (auto outerIT = data->begin(); outerIT != data->end(); ++outerIT) {
    //     cout << "List " << outerIT.getIndex() << ": ";
    //     (*outerIT)->print();
    //     cout << endl;
    // }

    // auto it = data->begin();
    // cout << "List " << it.getIndex() << ": ";
    // (*it)->print();
    // ++it;

    // cout << "\nList " << it.getIndex() << ": ";
    // (*it)->print();
    // ++it;

    // cout << "\nList " << it.getIndex() << ": ";
    // (*it)->print();
    // ++it;
    


    // auto it = LL1->begin();
    // if (it.isValid()) {
    //     cout << "it is valid\n";
    //     cout << *it << " ";
    //     ++it;
    //     cout << *it << " ";
    //     it.reset();
    //     cout << *it << " ";
    // } 
    // else {
    //     cout << "huhu";
    // }

    // Giải phóng bộ nhớ
    delete data;
}

int main() {
    auto start = std::chrono::steady_clock::now();
    tc1();
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // In ra thời gian chạy
    cout << "-----------------------------\nTime: " << duration << " ms." << endl;

    return 0;
}