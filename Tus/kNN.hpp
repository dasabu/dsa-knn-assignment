#include "main.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

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
};

template<typename T>
class Node {
    public:
        T value;
        Node<T>* next;

        Node(T value, Node<T>* next) {
            this->value = value;
            this->next = next;
        }
};

template<typename T>
class LinkedList : public List<T> {
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
    public:
        LinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
            this->size = 0;
        }
        ~LinkedList() {
            if(this->head != nullptr && this->size > 0) this->clear();
        };
        void addFirstNode(Node<T>* newNode) {
            this->head = newNode;
            this->tail = newNode;
        };
        void push_back(T value) {
            Node<T>* newNode = new Node<T>(value, nullptr);

            if(this->head == nullptr || this->size == 0) {
                this->addFirstNode(newNode);
            } else {
                this->tail->next = newNode;
                this->tail = newNode;
            }
            this->size++;
        };
        void push_front(T value) {
            Node<T>* newNode = new Node<T>(value, nullptr);

            if (this->head == nullptr || this->size ==0) {
                this->addFirstNode(newNode);
            } else {
                newNode->next = this->head;
                this->head = newNode;
            }
            this->size++;
        };
        void insert(int index, T value) {
            if(index < 0 || index > this->size) {
                return;
            }

            if(index == size) {
                this->push_back(value);
            } else if(index == 0) {
                this->push_front(value);
            } else {
                Node<T>* newNode = new Node<T>(value,nullptr);
                Node<T>* currentNode = this->head;
                
                for(int i = index; i > 1; i--) {
                    currentNode = currentNode->next;
                }
                newNode->next = currentNode->next;
                currentNode->next = newNode;
                this->size++;
            }
        };
        void remove(int index){
            if(size == 0) return;
            if(index < 0 || index >= this->size) {
                return;
            }
            //size == 1
            if(size == 1) {
                this->head = nullptr;
                this->tail = nullptr;
                this->size--;
                return;
            }
            //head
            if(index == 0) {
                Node<T>* currentNode = this->head;
                this->head = currentNode->next;
                currentNode->next = nullptr;
                delete currentNode;
            } else {
                Node<T>* nodeToRemoved = this->head;
                Node<T>* currentNode = nullptr;
                
                for(int i = index; i > 0; i--) {
                    currentNode = nodeToRemoved;
                    nodeToRemoved = nodeToRemoved->next;
                }
                //tail
                currentNode->next = nodeToRemoved->next;
                if(index == size - 1) {
                    this->tail = currentNode->next;
                }
                nodeToRemoved->next = nullptr;
                delete nodeToRemoved;
            }
            this->size--;
        };
        T& get(int index) const {
            if(index < 0 || index >= this->size) {
                throw std::out_of_range("get(): Out of range");
            }
            Node<T>* currentNode = this->head;
            for(int i = 0; i < index; i++) {
                currentNode = currentNode->next;
            }
            return currentNode->value;
        };
        int length() const {
            return this->size;
        };
        void clear() {
            while(this->size > 0) {
                this->remove(0);
            }
        };
        void print() const {
            Node<T>* currentNode = this->head;

            for(int i = 0; i < size; i++) {
                if(i==0) {
                    cout << currentNode->value;
                } else {
                    cout << " " << currentNode->value;
                }
                currentNode = currentNode->next;
            }
        };
        void reverse() {
            if(this->size > 1) {
                Node<T>* previousNode = nullptr;
                Node<T>* currentNode = this->head;
                Node<T>* nextNode = nullptr;
                bool isTail = true;

                while(currentNode) {
                    nextNode = currentNode->next;
                    currentNode->next = previousNode;
                    previousNode = currentNode;
                    currentNode = nextNode;
                    if(isTail) {
                        this->tail = previousNode;
                        isTail = false;
                    }
                }
                this->head = previousNode;
            }
            else return;
        };
       
};

template<typename T>
class ArrayList : public List<T> {
    private:
        T* list;
        int size;
        int capacity;

    public:
        ArrayList(int capacity) {
            this->list = new T[capacity];
            this->capacity = capacity;
            this->size = 0;
        }
        ~ArrayList(){
            delete[] list;
        };
        void push_back(T value){
            if(this->size == this->capacity) {
                int newCapacity = ceil(this->capacity*1.5);
                T* newList = new T[newCapacity];
                for (int i = 0; i < this->size;i++) {
                    newList[i] = list[i];
                }
                delete[] list;
                this->capacity = newCapacity;
                this->list = newList;
            }
                this->list[size] = value;
                size++;
        };
        void push_front(T value){
            if(this->size == this->capacity) {
                this->capacity += 1;
                T* newList = new T[this->capacity];
                for (int i = 0; i < this->capacity;i++) {
                    newList[i+1] = list[i];
                }
                this->list = newList;
                delete[] newList;
            }
                this->list[0] = value;
                size++;
        };
        void insert(int index, T value){
            if (index < 0 || index > size) return;
            if (index == size) {
                push_back(value);
                return;
            }
            for (int i = size; i > index; i--) {
                this->list[i] = this->list[i-1];
            }
            this->list[index] = value;
            size++;
            return;
        };
        void remove(int index){
            if (index < 0 || index >= size) return;
            for (int i = index; i < size; i++) {
                this->list[i] = this->list[i+1];
            }
            size--;
            return;
            // list.erase(index-1)
        };
        T& get(int index) const{
            if (index < 0 || index >= size) {
                throw std::out_of_range("get(): Out of range");
            }
            return this->list[index];
        };
        int length() const{
            return this->size;
        };
        void clear() {
            delete[] this->list;
            this->list = new T[5];
            capacity = 5;
            size = 0;
        };
        void print() const{
            bool first = true;
            for(int i = 0; i < size; i++) {
                if(first){
                    first = false;
                    cout << this->get(i);
                } else {
                    cout << " " << this->get(i);
                }
            }
        };
        void reverse(){
            T* newList = new T[size];
            for(int i = 0; i < size; i++) {
                newList[size - (i + 1)] = this->list[i];
            }
            delete[] list;
            this->list = newList;
            delete[] newList;
        };
};

int calculateEuclindeDistance(List<int>* testImg, List<int>* trainImg);
bool compare(int a, int b);
void bubbleSortDsc(int arr[], int n);

class Dataset {
private:
    List<List<int>*>* data;
    List<string>* title;
    int numRows;
    int numCols;
    //You may need to define more
public:
    Dataset() {
        this->data = new LinkedList<List<int>*>();
        this->title = new LinkedList<string>();
        this->numRows = 0;
        this->numCols = 0;
    };
    ~Dataset() {
        if(this->title) {
            delete this->title;
            this->title = nullptr;
        }
        if(this->data) {
            for(int i = 0; i < this->data->length(); i++) {
                List<int>* temp = this->data->get(i);
                if(temp) {
                    delete temp;
                }
            }
        }
        delete data;
        this->data = nullptr;
    };
    Dataset(const Dataset& other) {
        this->data = new LinkedList<List<int>*>();
        this->title = new LinkedList<string>();
        this->numRows = other.numRows;
        this->numCols = other.numCols;
        
        for(int i = 0; i < this->numCols; i++) {
            this->title->push_back(other.title->get(i));
        }

        for(int i = 0; i < this->numRows; i++) {
            List<int> * innerList = new LinkedList<int>();
            List<int> * otherInnerList = other.data->get(i);
            
            for (int j = 0; j < otherInnerList->length(); j++) {
                innerList->push_back(otherInnerList->get(j));
            }
            this->data->push_back(innerList);
        }
    };
    Dataset& operator=(const Dataset& other) {
        if(this != &other) {
            this->numRows = other.numRows;
            this->numCols = other.numCols;

            this->title->clear();
            for(int i = 0; i < this->numCols; i++) {
                this->title->push_back(other.title->get(i));
            }

            this->data->clear();
            for(int i = 0; i < this->numRows; i++) {
                List<int> * innerList = new LinkedList<int>();
                List<int> * otherInnerList = other.data->get(i);
                
                for (int j = 0; j < otherInnerList->length(); j++) {
                    innerList->push_back(otherInnerList->get(j));
                }
                this->data->push_back(innerList);
            }
        }
        return *this;
    };
    bool loadFromCSV(const char* fileName) {
        ifstream file(fileName);
        
        if(file.is_open()) {
            bool isFirstLine = true;
            string line;
            
            while(getline(file, line)) {
                stringstream lineStream(line);
                string token;

                if(isFirstLine) {
                    while(getline(lineStream, token, ',')) {
                        this->title->push_back(token);
                    }
                    isFirstLine = false;
                }
                else {
                    List<int> * temp = new LinkedList<int>();
                    while(getline(lineStream, token, ',')) {
                        temp->push_back(stoi(token));
                    }
                    this->data->push_back(temp);
                }
                
            }
            this->numCols = this->title->length();
            this->numRows = this->data->length();
            
            file.close();
            return true;
        } 
        return false;
    };
    void printHead(int nRows = 5, int nCols = 5) const {
        if(nRows < 0 || nCols < 0) return;
        
        int rows = (nRows>this->numRows) ? this->numRows : nRows;
        int cols = (nCols>this->numCols) ? this->numCols : nCols;
        //col name
        for(int i = 0; i < cols; i++) {
            string value = this->title->get(i);
            if(i == 0) {
                cout << value;
            } else cout << " " << value;
        }
        //data
        for(int i = 0; i < rows; i++) {
            cout << endl;
            for(int j = 0; j < cols; j++) {
                if(j == 0) {
                    cout << this->data->get(i)->get(j);
                } else cout << " " << this->data->get(i)->get(j);
            }
        }
    };
    void printTail(int nRows = 5, int nCols = 5) const {
        if(nRows < 0 || nCols < 0) return;
        
        int startRow = (nRows>this->numRows) ? 0 : this->numRows - nRows;
        int startCol = (nCols>this->numCols) ? 0 : this->numCols - nCols;
        
        //col name
        for(int i = startCol; i < this->numCols; i++) {
            if(i == startCol) {
                cout << this->title->get(i);
            } else cout << " " << this->title->get(i);
        }
        //data
        for(int i = startRow; i < this->numRows; i++) {
            cout << endl;
            for(int j = startCol; j < this->numCols; j++) {
                if(j == startCol) {
                    cout << this->data->get(i)->get(j);
                } else {
                    cout << " " << this->data->get(i)->get(j);
                } 
            }
        }
    };
    void getShape(int& nRows, int& nCols) const {
        nRows = this->numRows;
        nCols = this->numCols;
    };
    void columns() const {
        this->title->print();
    };
    bool drop(int axis = 0, int index = 0, std::string columns = "") {
        if(axis !=0 && axis != 1) {
            return false;
        }
        if(axis == 0) {
            if(index >= this->numRows || index < 0) return false;

            this->data->remove(index);
            this->numRows--;
            return true;
        }
        if(axis == 1) {
            int indexToRemove = -1;
            
            for(int i = 0; i < this->numCols; i++) {
                if(this->title->get(i) == columns) {
                    indexToRemove = i;
                    this->title->remove(indexToRemove);
                    break;
                }
            }

            if(indexToRemove!=-1){
                for(int i = 0; i < this->numRows; i ++) {
                    this->data->get(i)->remove(indexToRemove);
                }
                this->numCols--;
                return true;
            }
            return false;
        }
    };
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const {
        Dataset newDataset;
        if(endRow==-1) endRow = this->numRows - 1;
        if(endCol==-1) endCol = this->numCols - 1;
        newDataset.setNumCols(endCol - startCol + 1);
        newDataset.setNumRows(endRow - startRow + 1);
        
        for(int i = startCol; i <= endCol; i++) {
            newDataset.getTitle()->push_back(this->title->get(i));
        }

        for(int i = startRow; i <= endRow; i++) {
            List<int> * temp = new ArrayList<int>(endCol - startCol + 1);
            // List<int> * temp = new LinkedList<int>();
            for(int j = startCol; j <= endCol; j++) {
                int value = this->data->get(i)->get(j);
                temp->push_back(value);
            }
            newDataset.getData()->push_back(temp);
        }
        return newDataset;
    };
    List<List<int>*>* getData() const {
        return this->data;
    };
    List<string> * getTitle() const {
        return this->title;
    }
    int getNumRows() const {
        return this->numRows;
    };
    void setNumRows(int numRows) {
        this->numRows = numRows;
    };
    int getNumCols() const {
        return this->numCols;
    };
    void setNumCols(int numCols) {
        this->numCols = numCols;
    };

};

class kNN {
private:
    int k;
    Dataset* x_train;
    Dataset* y_train;
    //You may need to define more
public:
    kNN(int k = 5) {
        this->k = k;
        this->x_train = new Dataset();
        this->y_train = new Dataset();
    };
    void fit(const Dataset& X_train, const Dataset& y_train) {
        this->x_train->operator=(X_train);
        this->y_train->operator=(y_train);
    };
    
    Dataset predict(const Dataset& X_test) {
        int numRows = X_test.getNumRows();
        Dataset * predictData = new Dataset();

        for(int i = 0; i < numRows; i++){
            List<int>* tempTestImg = X_test.getData()->get(i);
            int tempNumber = tempTestImg->length();
            int * kMinDistance = new int[this->k];

            for(int j = 0; j < this->x_train->getNumRows(); j++){
                List<int>* tempTrainImg = this->x_train->getData()->get(j);
                int label = this->y_train->getData()->get(j)->get(0);
                int distance = calculateEuclindeDistance(tempTestImg, tempTrainImg)*10 + label;
                if(j < this->k) {
                    kMinDistance[j] = distance;
                } else if(distance < kMinDistance[0]) {
                    int tempIndex = 0;
                    while(tempIndex < this->k-1 && distance < kMinDistance[tempIndex + 1]) {
                        kMinDistance[tempIndex] = kMinDistance[tempIndex + 1];
                        tempIndex++;
                    }
                    kMinDistance[tempIndex] = distance;
                }
                if(j==this->k-1) bubbleSortDsc(kMinDistance, this->k);
            }
            List<int> * listToInsert = new LinkedList<int>();
            int maxCount = 0;
            int eleMaxFreq;
            for(int j = 0; j < 5; j++) {
                int count = 0;
                for (int k =0; k < 5; k++) {
                    if(kMinDistance[j]%10 == kMinDistance[k]%10) {
                        count++;
                    }
                    if(count > maxCount) {
                        maxCount = count;
                        eleMaxFreq = kMinDistance[j]%10;
                    } else if (count == maxCount && eleMaxFreq > kMinDistance[j]%10) {
                        eleMaxFreq = kMinDistance[j]%10;
                    }
                }
                if(maxCount == 5) break;
            }
            listToInsert->push_back(eleMaxFreq);
            predictData->getData()->push_back(listToInsert);
            delete[] kMinDistance;
        }
        predictData->getTitle()->push_back("label");
        predictData->setNumRows(X_test.getNumRows());
        predictData->setNumCols(1);
        return *predictData;
    };
    double score(const Dataset& y_test, const Dataset& y_pred) {
        int total = y_pred.getNumRows();
        int correct = 0;
        for(int i = 0; i < total; i++) {
            int test = y_test.getData()->get(i)->get(0);
            int pred = y_pred.getData()->get(i)->get(0);
            if(test == pred) correct++;
        }
        double res = 1.0*correct/total;
        return res;
    };
    int getK(){ return this->k; }
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

