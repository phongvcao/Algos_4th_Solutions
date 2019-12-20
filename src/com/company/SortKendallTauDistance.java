package com.company;
import edu.princeton.cs.algs4.*;
import java.util.HashMap;

public class SortKendallTauDistance {

    private static class Element implements Comparable< Element > {

        public Comparable value = null;
        public Integer index = -1;

        public Element( Comparable value, Integer index ) {
            this.value = value;
            this.index = index;
        }

        public int compareTo( Element other ) {
            return this.index.compareTo( other.index );
        }

        public String toString() {
            return this.value + " : " + this.index;
        }
    }

    public static boolean less( Element a, Element b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Element[] a, int i, int j ) {
        Element temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static int insertionSort( Element[] eleArr ) {
        int distance = 0;

        for ( int i = 1; i < eleArr.length; ++i ) {
            for ( int j = i; j > 0 && less( eleArr[ j ], eleArr[ j - 1 ] ); --j ) {
                exchange( eleArr, j, j - 1 );
                ++distance;
            }
        }

        return distance;
    }

    public static int mergeSort( Element[] eleArr ) {
        Element[] aux = new Element[ eleArr.length ];
        return mergeSort( eleArr, aux, 0, eleArr.length - 1 );
    }

    public static int mergeSort( Element[] eleArr, Element[] aux, int low, int high ) {
        if ( low >= high ) return 0;

        int mid = ( low + high ) / 2;
        int distance = 0;
        distance += mergeSort( eleArr, aux, low, mid );
        distance += mergeSort( eleArr, aux, mid + 1, high );
        distance += merge( eleArr, aux, low, mid, high );
        return distance;
    }

    public static int merge( Element[] eleArr, Element[] aux, int low, int mid, int high ) {
        for ( int k = low; k <= high; ++k ) {
            aux[ k ] = eleArr[ k ];
        }

        int i = low;
        int j = mid + 1;
        int distance = 0;

        for ( int k = low; k <= high; ++k ) {
            if ( i > mid ) {
                eleArr[ k ] = aux[ j++ ];
            } else if ( j > high ) {
                eleArr[ k ] = aux[ i++ ];
            } else if ( less( aux[ j ], aux[ i ] ) ) {
                if ( j - mid - 1 <= i - low ) {
                    StdOut.println( "DEBUG: Swapping: " + eleArr[ i ].index + " with: " + eleArr[ j ].index );
                    ++distance;
                }

                eleArr[ k ] = aux[ j++ ];
            } else {
                eleArr[ k ] = aux[ i++ ];
            }
        }
        return distance;
    }

    public static int getKendallTau( Comparable[] a, Comparable[] b ) {
        HashMap< Comparable, Integer > aEleHashMap = new HashMap< Comparable, Integer >();
        Element[] bEleArr = new Element[ b.length ];

        for ( int i = 0; i < a.length; ++i ) {
            aEleHashMap.put( a[ i ], i );
        }

        for ( int i = 0; i < b.length; ++i ) {
            bEleArr[ i ] = new Element( b[ i ], aEleHashMap.get( b[ i ] ) );
        }

        // return insertionSort( bEleArr );
        return mergeSort( bEleArr );
    }

    public static void main( String[] args ) {
        Integer[] aArray = { 0, 3, 1, 6, 2, 5, 4 };
        Integer[] bArray = { 1, 0, 3, 6, 4, 2, 5 };

        StdOut.println( "DEBUG: Kendall Tau distance: " + getKendallTau( aArray, bArray ) );
    }
}
