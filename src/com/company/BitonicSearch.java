package com.company;
import edu.princeton.cs.algs4.*;

public class BitonicSearch {

    public static int findMaximumEleIndex( int[] intArr, int low, int high, int count ) {
        if ( high - low <= 1 ) {
            int maxEleIndex = intArr[ low ] < intArr[ high ] ? high : low;
            return maxEleIndex;
        }

        int maxEleIndex;

        int mid = ( low + high ) / 2;
        if ( ( intArr[ mid - 1 ] < intArr[ mid ] ) && ( intArr[ mid ] < intArr[ mid + 1 ] ) ) {
            // If both go up, recurse on right
            maxEleIndex = findMaximumEleIndex( intArr, mid, high, count + 1 );

            if ( intArr[ maxEleIndex ] < intArr[ mid ] ) {
                maxEleIndex = mid;
            }
        } else if ( ( intArr[ mid ] > intArr[ mid + 1 ] ) && ( intArr[ mid - 1 ] > intArr[ mid ] ) ) {
            // If both go down, recurse on left
            maxEleIndex = findMaximumEleIndex( intArr, low, mid, count + 1 );

            if ( intArr[ maxEleIndex ] < intArr[ mid ] ) {
                maxEleIndex = mid;
            }
        } else {
            // Else, recurse on left then on right
            int maxLeftEleIndex = findMaximumEleIndex( intArr, low, mid, count + 1 );
            int maxRightEleIndex = findMaximumEleIndex( intArr, mid, high, count + 1 );

            maxEleIndex = intArr[ maxLeftEleIndex ] < intArr[ maxRightEleIndex ] ? maxRightEleIndex : maxLeftEleIndex;

            if ( intArr[ maxEleIndex ] < intArr[ mid ] ) {
                maxEleIndex = mid;
            }
        }

        return maxEleIndex;
    }

    public static int binarySearch( int[] intArr, int value, int low, int high, boolean ascending ) {
        int valueIndex = -1;

        while ( high - 1 > low ) {
            int mid = ( low + high ) / 2;

            if ( intArr[ mid ] == value ) {
                valueIndex = mid;
                break;
            } else if ( intArr[ mid ] < value ) {
                if ( ascending ) {
                    low = mid;
                } else {
                    high = mid;
                }
            } else if ( intArr[ mid ] > value ) {
                if ( ascending ) {
                    high = mid;
                } else {
                    low = mid;
                }
            }

            // StdOut.println( "DEBUG: low: " + low + "; high: " + high );
        }

        return valueIndex;
    }

    public static int bitonicSearch3LogN( int[] intArr, int value ) {
        int maxEleIndex = findMaximumEleIndex( intArr, 0, intArr.length - 1, 0 );

        int valueIndex = binarySearch( intArr, value, 0, maxEleIndex, true );

        if ( valueIndex == -1 ) {
            valueIndex = binarySearch( intArr, value, maxEleIndex, intArr.length - 1, false );
        }

        return valueIndex;
    }

    public static int bitonicSearch2LogN( int[] intArr, int value, int low, int high ) {
        int mid = ( low + high ) / 2;
        int valueIndex = -1;

        StdOut.println( "DEBUG: value: " + value + "; low: " + low + "; high: " + high + "; mid: " + mid + "; midVal: " + intArr[ mid ] );

        if ( high - low <= 1 ) {
            return -1;
        }

        if ( intArr[ mid ] == value ) {
            valueIndex = mid;
        } else {
            if ( intArr[ mid ] < value ) {
                // Middle element smaller than desired value
                if ( intArr[ mid ] < intArr[ mid + 1 ] ) {
                    // Max is on the right => recurse on the left
                    valueIndex = bitonicSearch2LogN( intArr, value, low, mid );
                } else {
                    // Max is on the left => recurse on the right
                    valueIndex = bitonicSearch2LogN( intArr, value, mid, high );
                }
            } else {
                // Middle element larger than desired value
                // Ascending binarySearch on the left, descending binarySearch on the right
                valueIndex = binarySearch( intArr, value, low, mid, true );

                if ( valueIndex == -1 ) {
                    valueIndex = binarySearch( intArr, value, mid, high, false );
                }
            }
        }

        return valueIndex;
    }

    public static void main( String[] args ) {
        //               0, 1, 2, 3, 4, 5, 6, 7, 8
        // int[] intArr = { 1, 3, 5, 9, 8, 7, 6, 2, 0 };

        // StdOut.println( "DEBUG: " + bitonicSearch3LogN( intArr, 9 ) );
        // StdOut.println( "DEBUG: " + bitonicSearch3LogN( intArr, 10 ) );

        // DEBUG
        // StdOut.println( "DEBUG: " + findMaximumEleIndex( intArr, 0, intArr.length - 1, 0 ) );
        // StdOut.println( "DEBUG: " + findMaximumEleIndex( intArr, 0, intArr.length - 1, 0 ) );
        // END OF DEBUG

        // int[] intArr1 = { 1, 3, 5, 7, 9, 11, 12, 15, 16, 20, 21 };
        // int[] intArr1 = { 21, 20, 16, 15, 12, 11, 11, 9, 7, 5, 3, 1 };

        // StdOut.println( "DEBUG: " + binarySearch( intArr1, 16, true ) );
        // StdOut.println( "DEBUG: " + binarySearch( intArr1, 16, false ) );

        int[] intArr = { 0, 2, 4, 6, 8, 10, 12, 14, 15, 13, 11, 9, 7, 5, 3, 1 };

        /* StdOut.println( "DEBUG: bitonicSearch3LogN: " + bitonicSearch3LogN( intArr, 8 ) );
        StdOut.println( "DEBUG: bitonicSearch3LogN: " + bitonicSearch3LogN( intArr, 16 ) ); */
        StdOut.println( "DEBUG: bitonicSearch2LogN: " + bitonicSearch2LogN( intArr, 6, 0, intArr.length - 1 ) );
    }
}
