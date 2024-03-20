import numpy as np
import csv
import time
import math

def printInfo(array):
    print(array)
    print(f"shape = {array.shape}")

def loadfromCSV(fileName):
    data_array = []

    with open(fileName, mode='r') as file:
        reader = csv.reader(file)
        next(reader)  # Ignore the first row
        for row in reader:
            row_array = np.array(row)
            data_array.append(row_array)

    data = np.array(data_array, dtype=int)
    return data

def extract(array, startRow, endRow, startCol, endCol):
    if endRow == -1: endRow = array.shape[0]
    if endCol == -1: endCol = array.shape[1]
        
    subarray = array[startRow:endRow, startCol:endCol]
    return subarray

def train_test_split(X, y, test_size):
    test_samples = X.shape[0] - math.ceil(test_size * X.shape[0])
    
    X_train, X_test = X[:test_samples], X[test_samples:]
    y_train, y_test = y[:test_samples], y[test_samples:]
    
    return X_train, X_test, y_train, y_test

def predict_v1(X_train, y_train, X_test): # faster
    
    X_test_squared = np.sum(X_test**2, axis=1, keepdims=True)
    
    X_train_squared = np.sum(X_train**2, axis=1, keepdims=True)
    
    inner_product = np.dot(X_test, X_train.T)
    
    # ||a - b||^2 = ||a||^2 + ||b||^2.T - 2 * np.dot(a,b)
    distances = X_test_squared + X_train_squared.T - 2 * inner_product
    
    # distances = np.sqrt(distances)
    
    return distances

def predict_v2(X_train, y_train, X_test):
    distances = []
    # calculate Euclidean distance of each sample in X_test to each sample in X_train
    for test_sample in X_test:
        distances_to_train_samples = []
        for train_sample in X_train:
            distance = np.sqrt(np.sum((test_sample - train_sample) ** 2))
            distances_to_train_samples.append(distance)
        distances.append(distances_to_train_samples)
    return np.array(distances)

def main():
    data = loadfromCSV("mnist.csv")
    
    label = extract(data, 0, -1, 0, 1) # X
    feature = extract(data, 0, -1, 1, -1) # y
    
    X_train, X_test, y_train, y_test = train_test_split(feature, label, 0.2)

    # print(f'{X_train.shape = }')
    # print(f'{X_test.shape = }')
    # print(f'{y_train.shape = }')
    # print(f'{y_test.shape = }')
    
    distances_v1 = predict_v1(X_train, y_train, X_test)
    
    print(distances_v1[0][0])
    
    first_row = distances_v1[0, :]

    print(first_row[np.argsort(first_row)[:5]])

    
    


if __name__ == "__main__":
    main()


