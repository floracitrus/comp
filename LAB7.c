//Solution: Quicksort with 2 variants

    void quicksort(int a[], int left, int right, int mode) {
    int i;
    // if left is greater than right, we have sorted.
    if (left >= right) {
        return;
    }
    
    // get the partition; partition appropriately; repeat
    if (mode == MT_PIVOT && (right-left) > 1) {
        // if median of three, and we have three numbers to MT
        // swap the middle element to be at r-1
        int mid = (left+right)/2;
        swap(&(a[right-1]), &(a[mid]));
        
        // bubble sort
        if (a[left] > a[right-1]) {
            swap(&(a[right-1]), &(a[left]));
        }
        
        if (a[right-1] > a[right]) {
            swap(&(a[right-1]), &(a[right]));
        }
        if (a[left] > a[right-1]) {
            swap(&(a[right-1]), &(a[left]));
        }
        
        i = partition(a, left+1, right-1);
    } else {
        if (mode == RANDOM_PIVOT) {
            // get random element
            int randNum = rand() / (RAND_MAX / (right-left) + 1);
            swap(&(a[left+randNum]), &(a[right]));
        }
        i = partition(a, left, right);
    }
    // sort the partitions
    // note i is sorted
    quicksort(a, left, i-1, mode);
    quicksort(a, i+1, right, mode);
}

