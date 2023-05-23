#include <iostream>
using namespace std;

// Function to print an array
void printArray(int arr[], int n) {
  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";
  cout << endl;
}

bool SMALLER(int A[], int i, int j){
    if (A[i] < A[j])
    	return true;
    else
    	return false;
}

void insertionSort(int arr[], int n){
	int COMPCOUNT = 0;
    int i, j, temp;
    for (i=1; i<n; i++){
        temp = arr[i];
        j=i;
        COMPCOUNT++;
        while (j>0 && arr[j-1] > temp){
        	if (SMALLER(arr, j-1, j) == true)
        		COMPCOUNT++;
            arr[j] = arr[j-1];
            j = j-1;
        }
        arr[j] = temp;
    }
	cout << "Number of key-comparisons: ";
	cout << COMPCOUNT << endl;
}

int main(){
	//SMALL SIZE ARRAY
    int n32 = 32;

    //n=32 worst-case
    int worst32[] = {32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    cout << "Worst-case: n=32\ninput array = ";
    printArray(worst32, n32);
    insertionSort(worst32, n32);
    cout << "output array = ";
    printArray(worst32, n32);
    cout << endl;
    
    //n=32 best-case
    int best32[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
    cout << "Best-case: n=32\ninput array = ";
    printArray(best32, n32);
    insertionSort(best32, n32);
    cout << "output array = ";
    printArray(best32, n32);
    cout << endl;

    //n=32 average-case
    int avg32[32];
    for (int r=0; r<32; r++)
        avg32[r] = rand();
    cout << "Average-case: n=32\ninput array = ";
    printArray(avg32, n32);
    insertionSort(avg32, n32);
    cout << "output array = ";
    printArray(avg32, n32);
    cout << endl;
    
    //INCREASING ARRAY SIZES: n = 100
    int n100 = 100;
    int worst100[100]; //worst-case
    for (int k1=0; k1<100; k1++)
    	worst100[k1] = 100-k1;
    cout << "Worst-case: n=100" << endl;
    insertionSort(worst100, n100);
    cout << endl;
    
    int best100[100]; //best-case
    for (int k2=0; k2<100; k2++)
    	best100[k2] = k2+1;
    cout << "Best-case: n=100" << endl;
    insertionSort(best100, n100);
    cout << endl;
    
    int avg100[100]; //average-case
    for (int k3=0; k3<100; k3++)
    	avg100[k3] = rand();
    cout << "Average-case: n=100" << endl;
    insertionSort(avg100, n100);
    cout << endl;
    
    
    //INCREASING ARRAY SIZES: n = 1000
    int n1000 = 1000;
    int worst1000[1000]; //worst-case
    for (int l1=0; l1<1000; l1++)
    	worst1000[l1] = 1000-l1;
    cout << "Worst-case: n=1000" << endl;
    insertionSort(worst1000, n1000);
    cout << endl;
    
    int best1000[1000]; //best-case
    for (int l2=0; l2<1000; l2++)
    	best1000[l2] = l2+1;
    cout << "Best-case: n=1000" << endl;
    insertionSort(best1000, n1000);
    cout << endl;
    
    int avg1000[1000]; //average-case
    for (int l3=0; l3<1000; l3++)
    	avg1000[l3] = rand();
    cout << "Average-case: n=1000" << endl;
    insertionSort(avg1000, n1000);
    cout << endl;
    
    
    //INCREASING ARRAY SIZES: n = 10000
    int n10000 = 10000;
    int worst10000[10000]; //worst-case
    for (int m1=0; m1<10000; m1++)
    	worst10000[m1] = 10000-m1;
    cout << "Worst-case: n=10000" << endl;
    insertionSort(worst10000, n10000);
    cout << endl;
    
    int best10000[10000]; //best-case
    for (int m2=0; m2<10000; m2++)
    	best10000[m2] = m2+1;
    cout << "Best-case: n=10000" << endl;
    insertionSort(best10000, n10000);
    cout << endl;
    
    int avg10000[10000]; //average-case
    for (int m3=0; m3<10000; m3++)
    	avg10000[m3] = rand();
    cout << "Average-case: n=10000" << endl;
    insertionSort(avg10000, n10000);
    cout << endl;
}