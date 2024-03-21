#include "main.hpp"
#include <typeinfo>

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

unsigned long int makeDistanceWithLabel(int distance, int label);
int getDistance(unsigned long int variable);
int getLabel(unsigned long int variable);

template<typename T>
class Node{
public:
    T value;
    Node<T> * next;
    Node(T value, Node * next){
        this->value = value;
        this->next = next;
    }
};

template<typename T>
class Iterator;

template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    //* Self-defined methods:
    virtual Node<T>* getFirst() const = 0;
    virtual class Iterator<T> begin() = 0;
    virtual class Iterator<T> end() = 0;
};

template<typename T>
class Iterator {
private:
    List<T>* list;
    Node<T>* current;
    int index;
public:
    Iterator(){
        this->list = nullptr;
        this->current = nullptr;
        this->index = -1;
    }
    Iterator(List<T> * list, bool begin){
        this->list = list;
        if (begin){
            if (this->list){
                this->current = this->list->getFirst();
                this->index = 0;
            }
            else {
                this->current = nullptr;
                this->index = -1;
            }
        }
        else {
            this->current = 0;
            if (this->list) this->index = this->list->length();
            else this->index = 0;
        }
    }
    Iterator& operator=(const Iterator& it){
        this->list = it.list;
        this->current = it.current;
        this->index = it.index;

        return *this;
    }
    T& operator*(){
        if (this->current != nullptr) return this->current->value;
        else throw std::out_of_range("get(): Out of range");
    }
    bool operator!=(const Iterator& it){
        return ((this->current != it.current) || (this->index != it.index));
    }
     // Prefix ++ overload
    Iterator &operator++(){
        if (this->current != nullptr){
            if (this->index == -1) this->current = this->list->getFirst();
            else this->current = this->current->next;
            
            this->index++;
            
            return *this;
        }
        else throw std::out_of_range("get(): Out of range");
    }
    List<T> * getList() { return this->list; }
    Node<T> * getCurrent() { return this->current; }
    int getIndex(){ return this->index; }
};

template<typename T>
class LinkedList : public List<T>{
private:
    Node<T> * head;
    Node<T> * tail;
    int size;
public:
    LinkedList(){
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }
    void push_back(T value){
        Node<T> * newNode = new Node<T>(value, nullptr);
        if (this->size == 0 || this->head == nullptr){
            this->head = this->tail = newNode;
        }
        else {
            this->tail->next = newNode;
            this->tail = newNode;
        }
        this->size++;
    }
    void push_front(T value){
        Node<T> * newNode = new Node<T>(value, nullptr);
        if (this->size == 0 || this->head == nullptr){
            this->head = this->tail = newNode;
        }
        else {
            newNode->next = this->head;
            this->head = newNode;
        }
        this->size++;
    }
    void insert(int index, T value){
        if (index < 0 || index >= this->size) return;
        else if (index == 0) {
            this->push_front(value);
        }
        else if (index == this->size - 1) this->push_back(value);
        else { // index > 0 && index < size
            Node<T> * newNode = new Node<T>(value, nullptr);

            Node<T> * prev = this->head;
            for (int i = 0; i < index-1; i++){
                prev = prev->next;
            }
            newNode->next = prev->next;
            prev->next = newNode;
            this->size++;
        }   
    }
    void remove(int index){
        if (this->size == 0 || index < 0 || index >= this->size){
            return;
        }
        else if (this->size == 1){ // head = tail
            delete this->head;
            this->head = this->tail = nullptr;
        }
        else if (index == 0){
            Node<T> * tmp = this->head;
            this->head = tmp->next;
            tmp->next = nullptr;
            delete tmp;
        }
        else if (index == this->size - 1){
            Node<T> * tmp = this->head;
            for (int i = 0; i < index - 1; i++){
                tmp = tmp->next;
            }
            this->tail = tmp;
            tmp = tmp->next;
            tail->next = nullptr;
            delete tmp;
        }
        else {
            Node<T> * curr = this->head;
            Node<T> * prev = nullptr;
            for (int i = 0; i < index; i++){
                prev = curr;
                curr = curr->next;
            }
            prev->next = curr->next;
            curr->next = nullptr;
            delete curr;
        }
        this->size--;
    }
    T& get(int index) const{
        if (index < 0 || index >= this->size){
            throw std::out_of_range("get(): Out of range");
        }
        else {
            Node<T> * tmp = this->head;
            for (int i = 0; i < index; i++){
                tmp = tmp->next;
            }
            return tmp->value;
        }
    }
    int length() const{
        return this->size;
    }
    void clear(){
        while(this->size > 0){
            this->remove(0);
        }
    }
    void print() const{
        Node<T> * tmp = this->head;

        for (int i = 0; i < this->length(); i++){
            if (i == 0) std::cout << tmp->value;
            else std::cout << " " << tmp->value;
            tmp = tmp->next;
        }
    }
    void reverse(){
        if (this->size == 0 || this->size == 1) return;
    
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        Node<T>* next = nullptr;

        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        
        head = prev;
    }
    ~LinkedList(){
        if (this->size > 0 && this->head != nullptr){
            this->clear();
        }
    }
    // * Self-defined method: 
    Node<T>* getFirst() const {
        return this->head;
    }
    void pushWithLimit(int distance, int label, int limit){
        T distanceWithLabel = makeDistanceWithLabel(distance, label);
        if (this->size < limit){
            this->push_back(distanceWithLabel);
        }
        else {
            T maxValue = getDistance(this->get(0));
            int maxIndex = 0;
            for (int k = 1; k < this->size; k++){
                if (getDistance(this->get(k)) > maxValue) {
                    maxValue = getDistance(this->get(k));
                    maxIndex = k;
                }
            }
            if (maxValue > distance) this->get(maxIndex) = distanceWithLabel;
        }
    }
    // * For Iterator
    Iterator<T> begin() { return Iterator<T>(this, true); }
    Iterator<T> end() { return Iterator<T>(this, false); }
};

int getMaxLabel(const LinkedList<unsigned long int> * list);
int EuclideanDistance(List<int> * list1, List<int> * list2);

class Dataset {
private:
    List<List<int>*>* data;
    //You may need to define more
    List<string>* features;
    int numRows;
    int numCols;
public:
    Dataset(){
        this->data = new LinkedList<List<int>*>();
        this->features = new LinkedList<string>();
        this->numRows = 0;
        this->numCols = 0;
    }
    Dataset(List<List<int>*>* data, List<string>* features, int numRows, int numCols){
        this->data = data;
        this->features = features;
        this->numRows = numRows;
        this->numCols = numCols;
    }
    ~Dataset(){
        if (this->features){
            this->features->clear();
            delete this->features;
            this->features = nullptr;
        }

        if (this->data){
            for (int i = 0; i < this->data->length(); i++){
                List<int> * tmp = this->data->get(i);
                if (tmp){
                    tmp->clear();
                    delete tmp;
                }
            }
        }

        // this->data->clear();
        delete this->data;
        this->data = nullptr;
    }
    Dataset(const Dataset& other){
        this->data = new LinkedList<List<int>*>();
        this->features = new LinkedList<string>();
        this->numRows = other.numRows;
        this->numCols = other.numCols;
        
        for (int i = 0; i < other.data->length(); i++){
            List<int> * innerList = new LinkedList<int>();
            List<int> * otherInnerList = other.data->get(i);
            for (int j = 0; j < otherInnerList->length(); j++){
                innerList->push_back(otherInnerList->get(j));
            }
            this->data->push_back(innerList);
        }

        for (int i = 0; i < other.features->length(); i++){
            this->features->push_back(other.features->get(i));
        }
    }
    Dataset& operator=(const Dataset& other) {
        if (this != &other) { // check if this assignment is self-assignment
            this->features->clear();
            for (int i = 0; i < other.features->length(); i++) {
                this->features->push_back(other.features->get(i));
            }

            this->data->clear();
            for (int i = 0; i < other.data->length(); i++) {
                List<int>* newInnerList = new LinkedList<int>();
                for (int j = 0; j < other.data->get(i)->length(); j++) {
                    newInnerList->push_back(other.data->get(i)->get(j));
                }
                this->data->push_back(newInnerList);
            }

            this->numRows = other.numRows;
            this->numCols = other.numCols;
        }
        return *this;
    }
    bool loadFromCSV(const char* fileName){
        ifstream inp;
        inp.open(fileName);

        if (inp.is_open()){
            bool isFeature = true;
            string line;

            while ((getline(inp, line))){
                stringstream ss(line);
                string tok;
                if (isFeature == true){
                    isFeature = false;
                    while(getline(ss, tok, ',')){
                        this->features->push_back(tok);
                    }
                }
                else {
                    List<int> * tmp = new LinkedList<int>();
                    while(getline(ss, tok, ',')){
                        tmp->push_back(stoi(tok));
                    }
                    this->data->push_back(tmp);
                }
            }

            this->numRows = this->data->length();
            this->numCols = this->data->get(0)->length();

            inp.close();

            return true;
        }

        return false;
    }
    void printHead(int nRows = 5, int nCols = 5) const{
        if (nRows > 0 && nCols > 0){
            int rows = (nRows > this->numRows) ? this->numRows : nRows;
            int cols = (nCols > this->numCols) ? this->numCols : nCols;

            for (int j = 0; j < cols; j++){
                if (j == cols - 1) cout << this->features->get(j) << endl;
                else cout << this->features->get(j) << " ";
            }

            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    if (i == rows - 1 && j == cols - 1)cout << this->data->get(i)->get(j);
                    else if (j == cols - 1) cout << this->data->get(i)->get(j) << endl;
                    else cout << this->data->get(i)->get(j) << " ";
                }
            }
        }
    }
    void printTail(int nRows = 5, int nCols = 5) const{
        if (nRows > 0 && nCols > 0){
            int startRow = (this->numRows > nRows) ? (this->numRows - nRows) : 0;
            int startCol = (this->numCols > nCols) ? (this->numCols - nCols) : 0;

            for (int j = startCol; j < this->numCols; j++){
                if (j == this->numCols - 1) cout << this->features->get(j) << endl;
                else cout << this->features->get(j) << " ";
            }

            for (int i = startRow; i < this->numRows; i++){
                for (int j = startCol; j < this->numCols; j++){
                    if (i == this->numRows - 1 && j == this->numCols - 1)cout << this->data->get(i)->get(j);
                    else if (j == this->numCols - 1) cout << this->data->get(i)->get(j) << endl;
                    else cout << this->data->get(i)->get(j) << " ";
                }
            }
        }
    }
    void getShape(int& nRows, int& nCols) const{
        nRows = this->numRows;
        nCols = this->numCols;
    }
    void columns() const{
        this->features->print();
    }
    bool drop(int axis = 0, int index = 0, std::string columns = ""){
        if (axis == 0){ // delete row
            if (index < 0 || index >= this->numRows) return false; // invalid index
            // valid index
            this->data->remove(index);
            this->numRows--;
            return true;
        }
        else if (axis == 1){ // delete column (with name in columns strng)
            // check if column name (columns) is in features list
            int colIndex = -1;
            for (int j = 0; j < this->features->length(); j++){
                if (columns == this->features->get(j)){
                    colIndex = j;
                    break; 
                }
            }
            if (colIndex == -1) return false; // invalid column
            // valid column
            this->features->remove(colIndex);
            for (int i = 0; i < this->numRows; i++){
                this->data->get(i)->remove(colIndex);
            }
            this->numCols--;
            return true;
        }
        return false;
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const{
        if (startRow < 0 || startCol < 0 || endRow < -1 || endCol < -1)
            throw std::out_of_range("get(): Out of range");
        
        if (endRow == -1) endRow = this->numRows - 1;
        if (endCol == -1) endCol = this->numCols - 1;

        if (startRow > endRow || startCol > endCol) throw std::out_of_range("get(): Out of range");

        Dataset newDataset;
        newDataset.setNumRows(endRow - startRow + 1);
        newDataset.setNumCols(endCol - startCol + 1);

        for (int j = startCol; j <= endCol; j++){
            string ele = this->features->get(j);
            newDataset.getFeatures()->push_back(ele);
        }

        for (int i = startRow; i <= endRow; i++){
            List<int> * newInnerList = new LinkedList<int>();
            for (int j = startCol; j <= endCol; j++){
                int ele = this->data->get(i)->get(j);
                newInnerList->push_back(ele);
            }
            newDataset.getData()->push_back(newInnerList);
        }

        return newDataset;
    }
    // * Self-defined methods 
    // & Getter 
    List<List<int>*>* getData() const{ return this->data; }
    List<string>* getFeatures() const{ return this->features; }
    int getNumRows() const{ return this->numRows; }
    int getNumCols() const{ return this->numCols; }
    // & Setter 
    void setData(List<List<int>*> * otherData){ this->data = otherData; }
    void setFeatures(List<string> * otherFeatures){ this->features = otherFeatures; }
    void setNumRows(int numRows){ this->numRows = numRows; }
    void setNumCols(int numCols){ this->numCols = numCols; }
};

class kNN {
private:
    int k;
    //You may need to define more
    Dataset X_train;
    Dataset y_train;
public:
    kNN(int k = 5){ this->k = k; }
    void fit(const Dataset& X_train, const Dataset& y_train){
        this->X_train = X_train;
        this->y_train = y_train;

        if (this->k > X_train.getNumRows()) throw std::out_of_range("get(): Out of range");
    }
    Dataset predict(const Dataset& X_test)
    {
        List<string> * pred_features = new LinkedList<string>();
        pred_features->push_back("label");

        List<List<int>*> * pred_list = new LinkedList<List<int>*>();

        //! Iterator version
        Iterator<List<int>*> it_X_test, it_X_train, it_y_train;
        for (it_X_test = X_test.getData()->begin(); it_X_test != X_test.getData()->end(); ++it_X_test){
            LinkedList<unsigned long int> * distances = new LinkedList<unsigned long int>();
            for (it_X_train = this->X_train.getData()->begin(), it_y_train = this->y_train.getData()->begin();
                it_X_train != X_train.getData()->end() && it_y_train != y_train.getData()->end();
                ++it_X_train, ++it_y_train){
                int dis = EuclideanDistance(*it_X_test, *it_X_train);
                distances->pushWithLimit(dis, (*it_y_train)->get(0), this->k);
            }
            List<int> * tmp = new LinkedList<int>();
            tmp->push_back(getMaxLabel(distances));
            pred_list->push_back(tmp);

            delete distances;
        }

        //! Not using Iterator
        // for (int i = 0; i < X_test.getNumRows(); i++){
        //     LinkedList<unsigned long int> * distances = new LinkedList<unsigned long int>();
        //     for (int j = 0; j < this->X_train.getNumRows(); j++){
        //         int dis = EuclideanDistance(X_test.getData()->get(i), this->X_train.getData()->get(j));
        //         distances->pushWithLimit(dis, this->y_train.getData()->get(j)->get(0), this->k);
        //     }
        //     List<int> * tmp = new LinkedList<int>();
        //     tmp->push_back(getMaxLabel(distances));
        //     pred_list->push_back(tmp);

        //     delete distances;
        // }

        return Dataset(pred_list, pred_features, X_test.getNumRows(), 1);
    }
    double score(const Dataset& y_test, const Dataset& y_pred) {
        int correctLabel = 0, totalLabel = y_test.getNumRows();
        //! Iterator version
        Iterator<List<int>*> it_y_test, it_y_pred;
        for (it_y_pred = y_pred.getData()->begin(), it_y_test = y_test.getData()->begin();
            it_y_pred != y_pred.getData()->end() && it_y_test != y_test.getData()->end();
            ++it_y_pred, ++it_y_test){
            if ((*it_y_pred)->get(0) == (*it_y_test)->get(0)) correctLabel++;
        }

        //! Not using Iterator
        // for (int i = 0; i < totalLabel; i++){
        //     if (y_pred.getData()->get(i)->get(0) == y_test.getData()->get(i)->get(0)){
        //         correctLabel++;
        //     }
        // }
        double accuracy = 1.0 * correctLabel / totalLabel;
        return accuracy;
    }

    // * Self-defined methods: 
    // & Getter 
    int getK(){ return this->k; }
    Dataset getX_train(){ return this->X_train; }
    Dataset getY_train(){ return this->y_train; }
};

void train_test_split(Dataset& X, Dataset& y, double test_size, // Input
                    Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);