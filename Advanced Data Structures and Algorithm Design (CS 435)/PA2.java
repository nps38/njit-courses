import java.util.*;
import java.util.concurrent.ThreadLocalRandom;
import java.time.Clock;

public class PA2 {
    static int COMPCOUNT=0;
   
    static void printArray(int arr[]){
        int n = arr.length;
        for (int i=0; i<n; ++i)
            System.out.print(arr[i] + " ");
        System.out.println();
    }
    
    public static int[] mergeSort(int[] arr){
        int n = arr.length;
        if (n < 2)
            return arr;
        else{
            int[] left = Arrays.copyOfRange(arr,0,n/2);
            int[] right = Arrays.copyOfRange(arr,n/2,n);
            int[] l = mergeSort(left);
            int[] r = mergeSort(right);
            int[] combined = new int[l.length+r.length];
            merge(l, r, combined);
            return combined;
        }
    }
    public static void merge(int[] left, int[] right, int[] combined){
        int i = 0, j = 0, k = 0, m = left.length, n = right.length;
        while (m > i && n > j){ 
            COMPCOUNT++;
            if (left[i] <= right[j]){
               combined[k] = left[i];
                i++;
            }
            else{
               combined[k] = right[j];
                j++;
            }
            k++;
        } 
        while (m > i){
           combined[k] = left[i];
            i++;
            k++;
        }
        while (n > j){
           combined[k] = right[j];
            j++;
            k++;
        }
    }

    public static int[] quickSort(int[] A, int left, int right){
        int temp, l, r, V, k = 0;
        if (left >= right)
           return A;
        k = ThreadLocalRandom.current().nextInt(left, right + 1);
        V = A[k];
        temp = A[left];
        A[left] = A[k];
        A[k] = temp;
        l = left+1;
        r = right;
        
        while (l<=r){
           while (l <= r && A[l] <= V){
              l = l+1;
              COMPCOUNT++;
           }
           while (l <= r && A[r] > V){
              r = r-1;
              COMPCOUNT++;
           }
           if (l<r){
              temp = A[l];
              A[l] = A[r];
              A[r] = temp;
              l = l+1;
              r = r-1;
           }
        }
        temp = A[left];
        A[left] = A[r];
        A[r] = temp;
        quickSort(A, left, r-1);
        quickSort(A, r+1, right);
        return A;
    }

    public static int[] heapsort(int[] arr){
        int n = arr.length;
       // Build heap
        for (int i = n/2 - 1; i >= 0; i--)
            heapify(arr, n, i);
        for (int i = n-1; i >= 0; i--) {
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            heapify(arr, i, 0);
        }
        return arr;
    }
   
    static void heapify(int arr[], int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
   
        if (left < n && arr[left] > arr[largest]){
            largest = left;
            COMPCOUNT++;
        }
        if (right < n && arr[right] > arr[largest]){
            largest = right;
            COMPCOUNT++;
        }
        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;
            heapify(arr, n, largest);
        }
    }
    public static void main(String[] args){
        int temp = 0;
        Random rand = new Random();
        int[] random1 = new int[32];
        int[] random2 = new int[32];
        int[] random3 = new int[32];
        for (int r=0; r<32; r++){
            temp = rand.nextInt(32);
            random1[r] = temp;
            random2[r] = temp;
            random3[r] = temp;
        }    
        // MERGESORT n = 32
        System.out.println("MERGESORT n = 32: ");

        // 1. Sorted - Mergesort
        int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
        System.out.println("\nSorted input array = ");
        printArray(sorted);

        long startTime = System.nanoTime();
        sorted = mergeSort(sorted);
        long endTime = System.nanoTime();
        long duration = (endTime - startTime);

        System.out.println("output array = ");
        printArray(sorted);
        System.out.println("COMPCOUNT: " + COMPCOUNT);
        System.out.println("CLOCK: " + (duration) + "ns");

        // 2. Reversely sorted - Mergesort
        COMPCOUNT = 0;
        int reverse1[] = {32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        System.out.println("\nReversely sorted input array = ");
        printArray(reverse1);

        startTime = System.nanoTime();
        reverse1 = mergeSort(reverse1);
        endTime = System.nanoTime();
        duration = (endTime - startTime);

        System.out.println("output array = ");
        printArray(reverse1);
        System.out.println("COMPCOUNT: " + COMPCOUNT);
        System.out.println("CLOCK: " + (duration) + "ns");

        // 3. Randomly generated - Mergesort
        COMPCOUNT = 0;
        System.out.println("\nRandom input array = ");
        printArray(random1);

        startTime = System.nanoTime();
        random1 = mergeSort(random1);
        endTime = System.nanoTime();
        duration = (endTime - startTime);

        System.out.println("output array = ");
        printArray(random1);
        System.out.println("COMPCOUNT: "+ COMPCOUNT);
        System.out.println("CLOCK: " + (duration) + "ns");
        
        System.out.println("____________________________________________________________________________________________");
        
        // QUICKSORT n = 32
        System.out.println("\nQUICKSORT n = 32: ");
        
        // 1. Sorted - quicksort
        COMPCOUNT = 0;
        System.out.println("\nSorted input array = ");
        printArray(sorted);

        startTime = System.nanoTime();
        sorted = quickSort(sorted, 0, sorted.length-1);
        endTime = System.nanoTime();
        duration = (endTime - startTime);

        System.out.println("output array = ");
        printArray(sorted);
        System.out.println("COMPCOUNT: "+ COMPCOUNT);
        System.out.println("CLOCK: " + (duration) + "ns");

        // 2. Reversely sorted - quicksort
        COMPCOUNT = 0;
        int reverse2[] = {32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        System.out.println("\nReversely sorted input array = ");
        printArray(reverse2);
        
        startTime = System.nanoTime();
        reverse2 = quickSort(reverse2, 0, reverse2.length-1);
        endTime = System.nanoTime();
        duration = (endTime - startTime);

        System.out.println("output array = ");
        printArray(reverse2);
        System.out.println("COMPCOUNT: "+ COMPCOUNT);
        System.out.println("CLOCK: " + (duration) + "ns");

        // 3. Randomly generated - quicksort
        COMPCOUNT = 0;
        System.out.println("\nRandom input array = ");
        printArray(random2);

        startTime = System.nanoTime();
        random2 = quickSort(random2, 0, sorted.length-1);
        endTime = System.nanoTime();
        duration = (endTime - startTime);

        System.out.println("output array = ");
        printArray(random2);
        System.out.println("COMPCOUNT: "+ COMPCOUNT);
        System.out.println("CLOCK: " + (duration) + "ns");
      
        System.out.println("____________________________________________________________________________________________");

        // SMALL ARRAY SIZE n = 32
        System.out.println("\nHEAPSORT n =32: ");
    
        // 1. Sorted - heapsort
        COMPCOUNT = 0;
        System.out.println("\nSorted input array = ");
        printArray(sorted);

        startTime = System.nanoTime();
        sorted = heapsort(sorted);
        endTime = System.nanoTime();
        duration = (endTime - startTime);

        System.out.println("output array = ");
        printArray(sorted);
        System.out.println("COMPCOUNT: "+ COMPCOUNT);
        System.out.println("CLOCK: " + (duration) + "ns");
    
        // 2. Reversely sorted - heapsort
        COMPCOUNT = 0;
        int reverse3[] = {32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        System.out.println("\nReversely sorted input array = ");
        printArray(reverse3);

        startTime = System.nanoTime();
        reverse3 = heapsort(reverse3);
        endTime = System.nanoTime();
        duration = (endTime - startTime);

        System.out.println("output array = ");
        printArray(reverse3);
        System.out.println("COMPCOUNT: "+ COMPCOUNT);
        System.out.println("CLOCK: " + (duration) + "ns");
    
        // 3. Randomly generated - heapsort
        COMPCOUNT = 0;
        System.out.println("\nRandom input array = ");
        printArray(random3);

        startTime = System.nanoTime();
        random3 = heapsort(random3);
        endTime = System.nanoTime();
        duration = (endTime - startTime);

        System.out.println("output array = ");
        printArray(random3);
        System.out.println("COMPCOUNT: "+ COMPCOUNT);
        System.out.println("CLOCK: " + (duration) + "ns");

        System.out.println("____________________________________________________________________________________________");

        //LARGE ARRAY SIZES
        System.out.println("LARGE ARRAY SIZES");
        int[] random1024a = new int[1024];
        int[] random1024b = new int[1024];
        int[] random1024c = new int[1024];
        for (int k1=0; k1<1024; k1++){
           temp = rand.nextInt(1024);
           random1024a[k1] = temp;
           random1024b[k1] = temp;
           random1024c[k1] = temp;
        }
        COMPCOUNT = 0;
        startTime = System.nanoTime();
        random1024a = mergeSort(random1024a);
        endTime = System.nanoTime();
        duration = (endTime - startTime);
        System.out.println("\nMergesort n=1024:    COMPCOUNT: " + COMPCOUNT + "    CLOCK: " + (duration) + "ns");
        
        COMPCOUNT = 0;
        startTime = System.nanoTime();
        quickSort(random1024b, 0, random1024b.length-1);
        endTime = System.nanoTime();
        duration = (endTime - startTime);
        System.out.println("\nQuicksort n=1024:    COMPCOUNT: " + COMPCOUNT + "    CLOCK: " + (duration) + "ns");
        
        COMPCOUNT = 0;
        startTime = System.nanoTime();
        heapsort(random1024c);
        endTime = System.nanoTime();
        duration = (endTime - startTime);
        System.out.println("\nHeapsort n=1024:    COMPCOUNT: " + COMPCOUNT + "    CLOCK: " + (duration) + "ns");
        
        System.out.println("____________________________________________________________________________________________");
        int[] random32768a = new int[32768];
        int[] random32768b = new int[32768];
        int[] random32768c = new int[32768];
        for (int k2=0; k2<32768; k2++){
           temp = rand.nextInt(32768);
           random32768a[k2] = temp;
           random32768b[k2] = temp;
           random32768c[k2] = temp;
        }

        COMPCOUNT = 0;
        startTime = System.nanoTime();
        random32768a = mergeSort(random32768a);
        endTime = System.nanoTime();
        duration = (endTime - startTime);
        System.out.println("\nMergesort n=32768:    COMPCOUNT: " + COMPCOUNT + "    CLOCK: " + (duration) + "ns");
        
        COMPCOUNT = 0;
        startTime = System.nanoTime();
        quickSort(random32768b, 0, random32768b.length-1);
        endTime = System.nanoTime();
        duration = (endTime - startTime);
        System.out.println("\nQuicksort n=32768:    COMPCOUNT: " + COMPCOUNT + "    CLOCK: " + (duration) + "ns");
        
        COMPCOUNT = 0;
        startTime = System.nanoTime();
        heapsort(random32768c);
        endTime = System.nanoTime();
        duration = (endTime - startTime);
        System.out.println("\nHeapsort n=32768:    COMPCOUNT: " + COMPCOUNT + "    CLOCK: " + (duration) + "ns");
        
        System.out.println("____________________________________________________________________________________________");
        int[] random1048576a = new int[1048576];
        int[] random1048576b = new int[1048576];
        int[] random1048576c = new int[1048576];
        for (int k3=0; k3<1048576; k3++){
           temp = rand.nextInt(1048576);
           random1048576a[k3] = temp;
           random1048576b[k3] = temp;
           random1048576c[k3] = temp;
        }

        COMPCOUNT = 0;
        startTime = System.nanoTime();
        random1048576a = mergeSort(random1048576a);
        endTime = System.nanoTime();
        duration = (endTime - startTime);
        System.out.println("\nMergesort n=1048576:    COMPCOUNT: " + COMPCOUNT + "    CLOCK: " + (duration) + "ns");
        
        COMPCOUNT = 0;
        startTime = System.nanoTime();
        quickSort(random1048576b, 0, random1048576b.length-1);
        endTime = System.nanoTime();
        duration = (endTime - startTime);
        System.out.println("\nQuicksort n=1048576:    COMPCOUNT: " + COMPCOUNT + "    CLOCK: " + (duration) + "ns");
        
        COMPCOUNT = 0;
        startTime = System.nanoTime();
        heapsort(random1048576c);
        endTime = System.nanoTime();
        duration = (endTime - startTime);
        System.out.println("\nHeapsort n=1048576:     COMPCOUNT: " + COMPCOUNT + "    CLOCK: " + (duration) + "ns");
    }
}
