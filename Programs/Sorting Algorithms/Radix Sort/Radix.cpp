#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;
int find_digit(int dim, int num){
    int tmp = int(num/(pow(10,dim)));
    int sol = int(tmp%10);
    return sol;
}

void copy_vector(const vector<int>& copyFrom,vector<int>& copyTo){
    for(int i=0;i<copyFrom.size();i++){
        copyTo.push_back(copyFrom[i]);
    }
}
void printVector(vector<int> v){
        for(int i=0; i<v.size();i++){
            cout << v[i] << " ";
        }
        cout << endl;
    }
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

/*
pre: an open file
post: unsorted array is populated with file contents
assumptions: all integers, each integer is stored in its own line
*/
bool IntSortingAlgs::populate(istream& file){
    int tmp = 0;
    int dimTmp = 0;
    size = 0;
    while(!(file.eof())){
        file >> tmp;
        unsortedArray.push_back(tmp);
        size++;
    }
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/*
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
    vector<int> checkThisDim(int);
};

void RadixInt::sort(){
    int tDim = dimensions;
    //make bucket=unsortedArray
    copy_vector(unsortedArray,bucket);
    while(tDim!=0){
        checkThisDim(tDim);
        tDim--;
    }
}

vector<int> RadixInt::checkThisDim(int){
    for(int i=0;i<9;i++){
        
        for(int j=0;j<size;j++){
            //get the specific digit needed for this dimension
            int thisNum = find_digit(i, bucket[j]);
            cout << "thisNum: " << thisNum << endl;
            if(thisNum==i){
                bucket.push_back(bucket[j]);
            }
        }
    }
    return bucket;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
int main(){
    ifstream file;
    file.open("test1.txt");
    RadixInt r;
    r.populate(file);
    r.printUnsorted();
    r.sort();
    return 0;
}