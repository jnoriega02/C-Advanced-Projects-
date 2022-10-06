//
//  merge_sort.cpp
//   241
//
//  Created by Juviny Noriega on 9/15/22.(Partner Mentor Ballazi)
//

#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
///states the correct namespaces to be used


int buildArray(int array[])
{
        int n=0;
        while (cin >> array[n])
        {
                n++;
        }
        return n;
}

//prints the array 
void printArray(int arr[], int size)
{
    int i;
    int count=0;
    for (i=0; i < size; i++)
    {

        cout << setw(8) << arr[i] << " ";
	count++;
        if(count == 10)
        {
             cout <<"\n";
             count = 0;
        }
	else if (count==size)
	{
		cout<<"\n";
	}
   }

}


void merge( int ar[], int temp[], int lPos, int rPos, int rEnd )
{
    int lEnd = rPos - 1,
     tempPos = lPos,
     numElem = rEnd - lPos + 1;
    while (lPos <= lEnd && rPos <= rEnd)
    {
        if (ar[lPos] <= ar[rPos])
        {
            temp[tempPos++] = ar[lPos++];
        }
        else {
                temp[tempPos++] = ar[rPos++];
             }
        }
    while (lPos <= lEnd)
    {
        temp[tempPos++] = ar[lPos++];
    }
    while (rPos <= rEnd)
    {
        temp[tempPos++] = ar[rPos++];
    }
    for (int i = 0; i < numElem; i++, rEnd--)
    {
        ar[rEnd] = temp[rEnd];
    }
}




void mergeSort(int arr[], int temp[], int left, int right)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        mergeSort(arr, temp, left, center);
        mergeSort(arr, temp, center + 1, right);
        merge(arr, temp, left, center + 1, right);

    }
}
void mergeSort(int arr[], int size)
{
    int *tempArray = new int[size];
    mergeSort(arr, tempArray, 0, size - 1);
}


int main()
{
   int arr[1000];
   int n= buildArray(arr);

  //calls the merge sort function
   mergeSort(arr,n);
   printArray(arr,n);
}


