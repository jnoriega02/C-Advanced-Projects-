#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;



int buildArray(int array[])
{
        int n=0;
        while (cin >> array[n])
        {
                n++;
        }
        return n;
}


void printArray(int arr[], int size)
{
    int i, count;
    for (i=0; i < size; i++)
    {
        count++;
        cout << setw(8) << arr[i] << " ";

        if(count == 10)
        {
             cout << endl;
             count = 0;
        }
	else if (count==size)
	{
		cout<<endl;
	}
    }
}

int partition(int set[],int start, int end)
{
	int pivotIndex,mid;
	int pivotValue,temp;
	
	mid=(start+end)/2;
	
	temp=set[start];
	set[start]=set[mid];
	set[mid]=temp;
	
	pivotIndex = start;
	pivotValue = set [start];
	
	for (int scan=start+1;scan <=end;scan++)
	{
		if (set[scan]<pivotValue)
		{
			pivotIndex++;
			temp=set[pivotIndex];
			set[pivotIndex]=set[scan];
			set[scan]=temp;

		}		
	}
	
	temp=set[start];
	set[start]=set[pivotIndex];
	set[pivotIndex]=temp;
	
	return pivotIndex;
}

void quicksort (int list [], int first, int last)
{
	int pivotPosition;
	if (first < last)
	{
		pivotPosition=partition(list,first,last);
		quicksort(list,first, pivotPosition-1);
		quicksort(list,pivotPosition+1,last);
	}
	
}


int main()
{
   int arr[1000];
   int n= buildArray(arr);

  
   quicksort(arr,0,n-1);
   printArray(arr,n);
}


