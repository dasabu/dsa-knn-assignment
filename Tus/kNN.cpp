#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test) {
    int numRowX = X.getNumRows();
    int numRowXTest = ceil(numRowX * test_size);
    int numRowXTrain = numRowX - numRowXTest;
    
    int numRowY = y.getNumRows();
    int numRowYTest = ceil(numRowY * test_size);
    int numRowYTrain = numRowY - numRowYTest;

    X_train = X.extract(0, numRowXTrain - 1, 0, -1);
    X_test = X.extract(numRowXTrain, -1, 0, -1);
    y_train = y.extract(0, numRowYTrain - 1, 0, -1);
    y_test = y.extract(numRowYTrain, -1, 0, -1);
};

int calculateEuclindeDistance(List<int>* testImg, List<int>* trainImg) {
    int result = 0;
    for(int i = 0; i < testImg->length(); i++) {
        result +=  pow((testImg->get(i) - trainImg->get(i)),2);
    }
    return result;
}

bool compare(int a, int b) {
    return a/10 > b/10;
}

void bubbleSortDsc(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = n-1; i > 0; i--) {
        swapped = false;
        for (j = n-1; j > n - i - 1; j--) {
            if (arr[j-1] < arr[j]) {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}