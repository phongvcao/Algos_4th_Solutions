package com.company;
import edu.princeton.cs.algs4.*;
import java.util.HashMap;
import java.util.ArrayList;

public class SortForceStability {

    private static class Element implements Comparable< Element > {
        public Comparable value = null;
        public Integer index = -1;

        public Element( Comparable value, int index ) {
            this.value = value;
            this.index = index;
        }

        public int compareTo( Element other ) {
            if ( this.value.compareTo( other.value ) != 0 ) {
                return this.value.compareTo( other.value );
            }

            return this.index.compareTo( other.index );
        }
    }

    public static Element[] oldEleArray;

    public static boolean check( Comparable[] a ) {
        // This method invokes sort() and checks whether:
        // 1. After Sort: All elements are still in the Array
        // 2. The Array is in sorted order
        // 3. The Array is stable

        HashMap< Comparable, ArrayList< Comparable > > eleStabilityMap = new HashMap< Comparable, ArrayList< Comparable > >();
        HashMap< Comparable, Integer > eleCountMap = new HashMap< Comparable, Integer >();

        // Comparable[] oldArray = new Comparable[ a.length ];
        for ( int i = 0; i < a.length; ++i ) {
            if ( eleStabilityMap.containsKey( a[ i ] ) ) {
                ArrayList< Comparable > eleList = eleStabilityMap.get( a[ i ] );
                eleList.add( eleList.size(), a[ i ] );
                eleStabilityMap.put( a[ i ], eleList );
                eleCountMap.put( a[ i ], eleCountMap.get( a[ i ] ) + 1 );
            } else {
                ArrayList< Comparable > eleList = new ArrayList< Comparable >();
                eleList.add( a[ i ] );
                eleStabilityMap.put( a[ i ], eleList );
                eleCountMap.put( a[ i ], 1 );
            }
        }

        wrappedSort( a );

        // Check if all elements are intact & they're in sorted order & they still refers to same object
        for ( int i = 0; i < a.length - 1; ++i ) {
            // Check if they're in sorted order
            if ( a[ i ].compareTo( a[ i + 1 ] ) == 1 ) {
                return false;
            }

            // Check stability
            if ( eleStabilityMap.get( a[ i ] ).size() >= 1 ) {
                ArrayList< Comparable > eleList = eleStabilityMap.get( a[ i ] );
                if ( eleList.get( 0 ) != a[ i ] ) {
                    return false;
                } else {
                    eleList.remove( 0 );
                    eleStabilityMap.put( a[ i ], eleList );
                }
            }

            // The array is in order so far & stable
            // Now check if elements are intact
            if ( ( ! eleCountMap.containsKey( a[ i ] ) ) || ( eleCountMap.get( a[ i ] ) <= 0 ) ) {
                return false;
            } else {
                eleCountMap.put( a[ i ], eleCountMap.get( a[ i ] ) - 1 );

                if ( eleCountMap.get( a[ i ] ) == 0 ) {
                    eleCountMap.remove( a[ i ] );
                }
            }
        }

        // Check last element;
        if ( eleStabilityMap.get( a[ a.length - 1 ] ).size() >= 1 ) {
            ArrayList< Comparable > eleList = eleStabilityMap.get( a[ a.length - 1 ] );
            if ( eleList.get( 0 ) != a[ a.length - 1 ] ) {
                return false;
            } else {
                eleList.remove( 0 );
                eleStabilityMap.put( a[ a.length - 1 ], eleList );
            }
        }

        if ( eleCountMap.get( a[ a.length - 1 ] ) <= 0 ) {
            return false;
        } else {
            eleCountMap.put( a[ a.length - 1 ], eleCountMap.get( a[ a.length - 1 ] ) - 1 );

            if ( eleCountMap.get( a[ a.length - 1 ] ) == 0 ) {
                eleCountMap.remove( a[ a.length - 1 ] );
            }
        }

        if ( eleCountMap.size() > 0 ) {
            return false;
        }

        return true;
    }

    public static void wrappedSort( Comparable[] a ) {
        Element[] eleArr = backupArrayIndex( a );

        // java.util.Arrays.sort( a );
        MyQuickSort3.sort( a );

        restoreArrayIndex( a, eleArr );
    }

    public static Element[] backupArrayIndex( Comparable[] a ) {
        Element[] eleArr = new Element[ a.length ];
        for ( int i = 0; i < a.length; ++i ) {
            eleArr[ i ] = new Element( a[ i ], i );
        }
        return eleArr;
    }

    public static void restoreArrayIndex( Comparable[] a, Element[] eleArr ) {
        java.util.Arrays.sort( eleArr );
        for ( int i = 0; i < a.length; ++i ) {
            a[ i ] = eleArr[ i ].value;
        }
    }

    public static void main( String[] args ) {
        int[] intArr = { 14, 12, 12, 12, 12, 10, 80, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] intObjArr = new Integer[ intArr.length ];

        for ( int i = 0; i < intArr.length; ++i ) {
            intObjArr[ i ] = new Integer( intArr[ i ] );
        }

        StdOut.println( "DEBUG: check(): " + check( intObjArr ) );
    }
}
