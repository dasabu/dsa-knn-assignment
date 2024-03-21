#include "kNN.hpp"

// TODO: You can implement methods, functions that support your data structures here.

void train_test_split(Dataset& X, Dataset& y, double test_size, // Input
                    Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test){ // Output
    int numSamples = X.getNumRows(); // 199
    int testStartRow = numSamples - ceil(numSamples * test_size);
    int trainEndRow = testStartRow - 1;

    X_train = X.extract(0, trainEndRow, 0, -1);
    X_test = X.extract(testStartRow, numSamples - 1, 0, -1);
    y_train = y.extract(0, trainEndRow, 0, -1);
    y_test = y.extract(testStartRow, numSamples - 1, 0, -1);
}

int EuclideanDistance(List<int> * list1, List<int> * list2) {  
    // Not using Iterator
    // double dis = 0;
    // for (int i = 0; i < list1->length(); i++){
    //     double diff = list1->get(i) - list2->get(i);
    //     dis += diff * diff;
    // }

    //! Iterator version
    double dis = 0;
    Iterator<int> it1 = list1->begin();
    Iterator<int> it2 = list2->begin();
    for (it1 = list1->begin(), it2 = list2->begin(); it1 != list1->end() && it2 != list2->end(); ++it1, ++it2){
        double diff = (*it1) - (*it2);
        dis += diff * diff;
    }

    return dis;
}

unsigned long int makeDistanceWithLabel(int distance, int label){
    unsigned long int res = 0;
    res |= (distance & 0x1FFFFFFFUL); // distance = 29 high bits
    res |= ((label & 0xFUL) << 29); // shift-left 29 bits and label = 4 low bits
    return res;
}

int getDistance(unsigned long int variable){
    return variable & 0x1FFFFFFFUL;
}

int getLabel(unsigned long int variable){
    return (variable >> 29) & 0xFUL;
}

int getMaxLabel(const LinkedList<unsigned long int> * list){
    int label[10] = {0};
    for (int i = 0; i < list->length(); i++){
        label[getLabel(list->get(i))]++;
    }
    int maxLabelIndex = 0;
    for (int i = 1; i < 10; i++){
        if (label[i] > label[maxLabelIndex]){
            maxLabelIndex = i;
        }
    }
    return maxLabelIndex;
}