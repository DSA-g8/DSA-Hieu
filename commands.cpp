#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include "DataGenerator.h"
#include "algorithms.h"

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;

//Declare global time variable for calculating execution time
high_resolution_clock::time_point START_TIME;
high_resolution_clock::time_point END_TIME;

int* readDataFromFile(string input_file, int &size) {
    ifstream fi(input_file);
    if (!fi.is_open()) {
        cerr << "Can't open file" << endl;
    }

    string s, num;
    getline(fi, s);
    size = stoi(s);
    int *array = new int[size];

    getline(fi, s);
    stringstream ss(s);
    for (int i = 0; i < size; i++) {
        getline(ss, num, ' ');
        array[i] = stoi(num);
    }

    fi.close();

    return array;
}

void writeToOutputFile(string output_file, int *array, int size) {
    ofstream fo(output_file);
    for (int i = 0; i < size; i++) {
        fo << array[i] << " ";
    }
    fo.close();
}

void writeToInputFile(string input_file, int array[], int size) {
    ofstream fo(input_file);
    fo << size << endl;
    for (int i = 0; i < size; i++) {
        fo << array[i] << " ";
    }
    fo.close();
}

double selectAlgorithmWithTime(string algorithm_name, int *array, int size) {
    duration<double, milli> exec_time;

    if (algorithm_name == "selection-sort") {
        //selection sort
    }
    else if (algorithm_name == "insertion-sort") {
        //insertion sort
    }
    else if (algorithm_name == "bubble-sort") {
        //bubble sort
    }
    else if (algorithm_name == "heap-sort") {
        //heap sort
    }
    else if (algorithm_name == "merge-sort") {
        START_TIME = high_resolution_clock::now();
        mergeSortWithTime(array, 0, size - 1);
        END_TIME = high_resolution_clock::now();
        exec_time = END_TIME - START_TIME;
    }
    else if (algorithm_name == "quick-sort") {
        //quick sort
    }
    else {
        //radix sort
    }

    return exec_time.count();
}

void selectAlgorithmWithComparison(string algorithm_name, int *array, int size, int &comparison) {
    if (algorithm_name == "selection-sort") {
        //selection sort
    }
    else if (algorithm_name == "insertion-sort") {
        //insertion sort
    }
    else if (algorithm_name == "bubble-sort") {
        //bubble sort
    }
    else if (algorithm_name == "heap-sort") {
        //heap sort
    }
    else if (algorithm_name == "merge-sort") {
        mergeSortWithComparison(array, 0, size - 1, comparison);
    }
    else if (algorithm_name == "quick-sort") {
        //quick sort
    }
    else {
        //radix sort
    }
}

//Command 1 ------------------------------------------------------------------------
void runCommand1(string algorithm_name, string input_file, string output_param) {
    int comparisons_count = 0;
    double time = 0;
    int size = 0;
    int *array = readDataFromFile(input_file, size);

    //Display necessary informations
    cout << "Input file: " << input_file << endl;
    cout << "Input size: " << size << endl;
    cout << "------------------------" << endl;

    //Implement the algorithms
    if (output_param == "-time") {
        time = selectAlgorithmWithTime(algorithm_name, array, size);

        cout << "Running time: " << time << " (ms)"  << endl;
    }
    else if (output_param == "-comp") {
        selectAlgorithmWithComparison(algorithm_name, array, size, comparisons_count);
        cout << "Comparisons: " << comparisons_count << endl;
    }
    else {
        time = selectAlgorithmWithTime(algorithm_name, array, size);
        selectAlgorithmWithComparison(algorithm_name, array, size, comparisons_count);

        cout << "Running time: " << time << " (ms)" << endl;
        cout << "Comparisons: " << comparisons_count << endl;
    }
    
    //Write the sorted array to file
    writeToOutputFile("output.txt", array, size);
    
    delete []array;
}

//Command 2 ----------------------------------------------------------------------------------------
void runCommand2(string algorithm_name, int size, string input_order, string output_param) {
    double time = 0;
    int comparisons_count = 0;
    int array[size];
    int FLAG_ORDER;
    string order;

    if (input_order == "-rand") {
        FLAG_ORDER = 0;
        order = "Random";
    }
    else if (input_order == "-sorted") {
        FLAG_ORDER = 1;
        order = "Sorted";
    }
    else if (input_order == "-rev") {
        FLAG_ORDER = 2;
        order = "Reverse";
    }
    else {
        FLAG_ORDER = 3;
        order = "Nearly sorted";
    }

    //Display necessary informations
    cout << "Input size: " << size << endl;
    cout << "Input order " << order << endl;
    cout << "------------------------" << endl;

    //Generate data
    GenerateData(array, size, FLAG_ORDER);
    writeToInputFile("input.txt", array, size);

    //Implement the algorithm here
    if (output_param == "-time") {
        time = selectAlgorithmWithTime(algorithm_name, array, size);
        cout << "Running time: " << time << " (ms)"  << endl;
    }
    else if (output_param == "-comp") {
        selectAlgorithmWithComparison(algorithm_name, array, size, comparisons_count);
        cout << "Comparisons: " << comparisons_count << endl;
    }
    else {
        time = selectAlgorithmWithTime(algorithm_name, array, size);
        selectAlgorithmWithComparison(algorithm_name, array, size, comparisons_count);

        cout << "Running time: " << time << " (ms)" << endl;
        cout << "Comparisons: " << comparisons_count << endl;
    }

    //Write sorted array to output file
    writeToOutputFile("output.txt", array, size);    
}