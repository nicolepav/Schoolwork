#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

template <class elemType>
void insertionSort(elemType list[], int length, int FOOindex) 
{
    for (int firstOutOfOrder = FOOindex; firstOutOfOrder < (FOOindex + length); firstOutOfOrder++)
    {
        if (list[firstOutOfOrder] < list[firstOutOfOrder - 1]) 
        {
            elemType temp = list[firstOutOfOrder]; int location = firstOutOfOrder;

            do
            {
                list[location] = list[location - 1]; location--;
            }
            while (location > 0 && list[location - 1] > temp);
            
            list[location] = temp; 
        }
    }
}; //end insertionSort


#endif