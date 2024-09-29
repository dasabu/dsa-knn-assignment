#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
void merge(vector<vector<int>>& arr, int axis, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<vector<int>> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i][axis] <= R[j][axis]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<vector<int>>& arr, int axis, int l, int r) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, axis, l, m);
    mergeSort(arr, axis, m + 1, r);
    merge(arr, axis, l, m, r);
}

// target: dim=784 (testData), point: dim=785 (trainData)
int distance(const vector<int>& target, const vector<int>& point){
    int dis = 0, dim = target.size();
    for (int i = 0; i < dim; ++i) {
        dis += (target[i] - point[i]) * (target[i] - point[i]);
    }
    return dis;
}

list<int> getMaxLabel(vector<kDTreeNode*> bestList){
    int label[10] = {0};
    for (int i = 0; i < bestList.size(); ++i){
        label[bestList[i]->label]++;
    }
    int maxLabelIndex = 0;
    for (int i = 0; i < 10; i++){
        if (label[i] > label[maxLabelIndex]) maxLabelIndex = i;
    }

    list<int> res;
    res.push_back(maxLabelIndex);
    return res;
}