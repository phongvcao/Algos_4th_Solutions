package com.company;
import edu.princeton.cs.algs4.*;
import java.util.ArrayList;

public class SortAndDedupString {

    // Use mergeSort & remove duplicates during the merge step
    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void sort( Comparable[] a, Comparable[] aux, int low, int high ) {
        if ( low >= high ) return;
        int mid = ( low + high ) / 2;

        sort( a, aux, low, mid );
        sort( a, aux, mid + 1, high );
        merge( a, aux, low, mid, high );
    }

    public static void merge( Comparable[] a, Comparable[] aux, int low, int mid, int high ) {
        int i = low;
        int j = mid + 1;
        for ( int k = low; k <= high; ++k ) {
            aux[ k ] = a[ k ];
        }

        int k = low;
        while ( k <= high ) {
            if ( i > mid ) {
                a[ k++ ] = aux[ j++ ];
            } else if ( j > high ) {
                a[ k++ ] = aux[ i++ ];
            } else {
                if ( aux[ i ].compareTo( aux[ j ] ) == -1 ) {
                    a[ k++ ] = aux[ i++ ];
                } else if ( aux[ j ].compareTo( aux[ i ] ) == -1 ) {
                    a[ k++ ] = aux[ j++ ];
                } else {
                    a[ k++ ] = aux[ j++ ];
                }
            }
        }
    }

    public static Integer[] dedup( Integer[] a ) {
        Integer[] aux = new Integer[ a.length ];
        sort( a, aux, 0, a.length - 1 );

        int i = 0;
        ArrayList< Integer > newArrayList = new ArrayList< Integer>();
        while ( i < a.length ) {
            if ( newArrayList.isEmpty() || a[ i ].compareTo( newArrayList.get( newArrayList.size() - 1 ) ) != 0 ) {
                newArrayList.add( a[ i ] );
            }
            ++i;
        }

        Integer[] newArray = new Integer[ newArrayList.size() ];
        for ( int k = 0; k < newArray.length; ++k ) {
            newArray[ k ] = newArrayList.get( k );
        }
        return newArray;
    }

    public static String toString( Integer[] a ) {
        String rv = "{ ";

        for ( int i = 0; i < a.length; ++i ) {
            if ( a[ i ] != null ) {
                rv += a[ i ] + ", ";
            }
        }

        rv += "}";
        return rv;
    }


    public static void main( String[] args ) {
        // String[] strArr = { "14", "12", "10", "08", "06", "04", "02", "00", "02", "02", "01", "03", "05", "07", "09", "11", "13" };
        Integer[] intArr = { 16, 14, 12, 10, 8, 6, 2, 2, 2, 2, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        // DEBUG
        Integer[] deduppedArr = dedup( intArr );
        StdOut.println( "DEBUG: intArr (AFTER): " + toString( intArr ) );
        StdOut.println( "DEBUG: deduppedArr (AFTER): " + toString( deduppedArr ) );
        // END OF DEBUG
    }
}
