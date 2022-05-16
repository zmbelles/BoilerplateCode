#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

class Node{
private:
    vector<int> subList;
    int children;
    int size;
    int pivot;
    Node* left;
    Node* right;
public:
    void setData(vector<int> v){subList = v;size=v.size();}
    void setLeftChild(Node* n){left = n;}
    void setRightChild(Node* n){right = n;}
    
    vector<int> getData(){return subList;}
    int getPivot(){return pivot;}
    int hasChildren(){return children;}
    int subListSize(){return subList.size();}
    
    free();
};

int digits_in(int number) {
   return int(log10(number) + 1);
}
void RadixSim(){
    ifstream file;
    int choice;
    string custom_file;
    cout << "choose which unsorted file" << endl;
    cout << "________________________________" << endl;
    cout << "1: 100 elements" << endl;
    cout << "2: 1000 elements" << endl;
    cout << "3: 10000 elements" << endl;
    cout << "4: use my own file" << endl;
    cout << "5: exit" << endl;
    
    cin >> choice;
    switch (choice)
    {
    case 1:
        file.open("test1.txt");
        break;
    case 2:
        file.open("test2.txt");
        break;
    case 3:
        file.open("test3.txt");
    case 4:
        cout << "Please make sure your file has been uploaded into Programs\\SortingAlgorithms before continuing" << endl;
        cout << "What is the name of your file + its extension (i.e a text file named test would be test.txt)?" << endl;
        cin >> custom_file;
        file.open(custom_file);
    }
    RadixInt r;
    r.populate(file);
    r.sort();
    r.printSorted();
}
void InsertionSim(){
    ifstream file;
    int choice;
    string custom_file;
    cout << "choose which unsorted file" << endl;
    cout << "________________________________" << endl;
    cout << "1: 100 elements" << endl;
    cout << "2: 1000 elements" << endl;
    cout << "3: 10000 elements" << endl;
    cout << "4: use my own file" << endl;
    cout << "5: exit" << endl;
    
    cin >> choice;
    switch (choice)
    {
    case 1:
        file.open("test1.txt");
        break;
    case 2:
        file.open("test2.txt");
        break;
    case 3:
        file.open("test3.txt");
    case 4:
        cout << "Please make sure your file has been uploaded into Programs\\SortingAlgorithms before continuing" << endl;
        cout << "What is the name of your file + its extension (i.e a text file named test would be test.txt)?" << endl;
        cin >> custom_file;
        file.open(custom_file);
    }
    InsertionSort i;
    i.populate(file);
    i.sort();
    i.printSorted();
}
void QuickSim(){

}
int find_digit(int dim, int num){
    int tmp = int(num/(pow(10,dim)));
    int sol = int(tmp%10);
    return sol;
}

void copy_vector(const vector<int>& copyFrom,vector<int>& copyTo){
    copyTo.erase(copyTo.begin(),copyTo.end());
    for(int i=0;i<copyFrom.size();i++){
        copyTo.push_back(copyFrom[i]);
    }
}
void print_vector(vector<int> v){
        for(int i=0; i<v.size();i++){
            cout << v[i] << " ";
        }
        cout << endl;
}
//to be implimented later
class Hash{
private:
    int used[10007];
public:

};


//abstract base class for all algorithms
class IntSortingAlgs{
protected:
    vector<int> unsortedArray;
    vector<int> sortedArray;
    int size;
    int dimensions;
public:
    virtual void sort() = 0;
    bool populate(istream&);
    void printUnsorted(){
        for(int i=0; i<unsortedArray.size();i++){
            cout << unsortedArray[i] << " ";
        }
        cout << endl;
    }
    void printSorted(){
        for(int i=0;i<sortedArray.size();i++){
            cout << sortedArray[i] << " ";
        }
        cout << endl;
    }
};
bool IntSortingAlgs::populate(istream& file){
    int tmp = 0;
    int dimTmp = 0;
    dimensions = 0;
    size = 0;
    while(!(file.eof())){
        file >> tmp;
        dimTmp = digits_in(tmp);
        if(dimTmp>dimensions){
            dimensions=dimTmp;
        }
        unsortedArray.push_back(tmp);
        size++;
    }
}
/*
////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////              ///////////////////////////////////////////////
///////////////////////////////////  Radix Sort  ///////////////////////////////////////////////
///////////////////////////////////      LSD     ///////////////////////////////////////////////
///////////////////////////////////              ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
Radix Sort for use with equal length lists of integers
Time complexity is based on the number of elements in the unsortedArray (n)
time the number of digits in each number(d)[this would be average number if 
each number had a different number of digits], or, more simply: O(dn)
*/
class RadixInt : public IntSortingAlgs{
private:
    vector<int> bucket;
public:
    void sort();
    void checkThisDim(int);
};

void RadixInt::sort(){
    int tDim = 0;
    //make bucket=unsortedArray
    copy_vector(unsortedArray,bucket);
    //for each dimension
    while(tDim<dimensions){
        checkThisDim(tDim);
        tDim++;
    }
    sortedArray = bucket;
}

void RadixInt::checkThisDim(int dim){
    vector<int> store_dim_sort;
    size;
    int tmp=0;
    //for each possible 0-9
    for(int i=0;i<=9;i++){
        //for all elements in the list
        for(int j=0;j<size;j++){
            //get the specific digit needed for this dimension
            int thisNum = find_digit(dim, bucket[j]);
            cout << thisNum << " " << bucket[j] << endl;
            if(thisNum==i){
                store_dim_sort.push_back(bucket[j]);
            }
        }
        print_vector(store_dim_sort);
    }
    bucket = store_dim_sort;
    print_vector(bucket);
}
///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////                 ////////////////////////////////////////////
/////////////////////////////////  Insertion Sort  ////////////////////////////////////////////
/////////////////////////////////                  ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
class InsertionSort: public IntSortingAlgs{
public:
    void sort();
};
void InsertionSort::sort(){
    bool sorted = false;
    bool first = true;
    int sent;
    int thisElement;
    
    for(int i=0; i<size; i++){
        thisElement = unsortedArray[i];
        sortedArray.push_back(thisElement);
        sent = i;
        while(!first && !sorted){
            if(sortedArray[sent]<sortedArray[sent-1]){
                swap(sortedArray[sent-1], sortedArray[sent]);
                sent--;
            }
            else{
                sorted=true;
            }
        }
        sorted = false;
        first = false;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////                  ///////////////////////////////////////////
//////////////////////////////////    Quick Sort    ///////////////////////////////////////////
//////////////////////////////////                  ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
class QuickSort : public IntSortingAlgs{
public:
    QuickSort();
    void sort();
    Node* head;
    bool sorted;
    void setHead(Node* n){head =n;}
};
void QuickSort::sort(){
    sorted = false;
    head->setData(unsortedArray);
    while(!sorted){
        
    }
}

int main(){
    
    int choice;
    bool testing = true;
    while(testing){
        cout << "Sorting Algorithm Tester v. 1.01" << endl;
        cout << "________________________________" << endl;
        cout << "1: Radix Sort" << endl;
        cout << "2: Insertion Sort" << endl;
        cout << "3: Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            RadixSim();
            break;
        case 2:
            InsertionSim();
            break;
        case 3:
            QuickSim();
            break;
        case 4:
            cout << "Thank you for trying. Please consider Zachary Belles" << endl;
            testing = false;
            break;
        }
    }
    return 0;
}
