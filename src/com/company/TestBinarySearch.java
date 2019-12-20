package com.company;
import edu.princeton.cs.algs4.*;

public class TestBinarySearch {

    public static class BinarySearchST< Key extends Comparable< Key >, Value > {

        private Key[] keys;
        private Value[] values;
        private int N = 0;

        public BinarySearchST( int cap ) {
            keys = ( Key[] )new Comparable[ cap ];
            values = ( Value[] )new Object[ cap ];
        }

        public void put( Key key, Value value ) {
            int i = rank( key );
            if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
                values[ i ] = value;
                return;
            }

            for ( int j = N; j > i; --j ) {
                keys[ j ] = keys[ j - 1 ];
                values[ j ] = values[ j - 1 ];
            }
            keys[ i ] = key;
            values[ i ] = value;
            ++N;
        }

        public int size() {
            return N;
        }

        public boolean isEmpty() {
            return size() == 0;
        }

        public int rank( Key key ) {
            int low = 0;
            int high = N - 1;
            while ( low <= high ) {
                int mid = low + ( high - low ) / 2;
                int cmp = key.compareTo( keys[ mid ] );
                if ( cmp < 0 ) {
                    high = mid - 1;
                } else if ( cmp > 0 ) {
                    low = mid + 1;
                } else {
                    return mid;
                }
            }
            return low;
        }

        public Iterable< Key > keys( Key low, Key high ) {
            Queue< Key > q = new Queue< Key >();
            if ( low.compareTo( high ) > 0 ) return q;
            int lowRank = rank( low );
            int highRank = rank( high );
            for ( int i = lowRank; i <= highRank; ++i ) {
                q.enqueue( keys[ i ] );
            }
            return q;
        }

        public Iterable< Key > keys() {
            return keys( min(), max() );
        }

        public Key max() {
            return keys[ N - 1 ];
        }

        public Key min() {
            return keys[ 0 ];
        }

        public void deleteMin() {
            delete( min() );
        }

        public void deleteMax() {
            delete( max() );
        }

        public void delete( Key key ) {
            int i = rank( key );
            if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
                for ( int j = i + 1; j < N; ++j ) {
                    keys[ j - 1 ] = keys[ j ];
                    values[ j - 1 ] = values[ j ];
                }
                keys[ N - 1 ] = null;
                values[ N - 1 ] = null;
                --N;
            }
        }

        public Key floor( Key key ) {
            int i = rank( key );
            if ( i < N && key.compareTo( keys[ i ] ) == 0 ) return keys[ i ];
            else return keys[ i - 1 ];
        }

        public Key ceiling( Key key ) {
            int i = rank( key );
            if ( i < N && key.compareTo( keys[ i ] ) == 0 ) return keys[ i ];
            return null;
        }

        public Value get( Key key ) {
            int i = rank( key );
            if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
                return values[ i ];
            }
            return null;
        }

        public boolean contains( Key key ) {
            return get( key ) != null;
        }

        public Key select( int k ) {
            return keys[ k ];
        }

        public String toString() {
            return "\nkeys : " + java.util.Arrays.toString( keys ) + "\nvalues : " + java.util.Arrays.toString( values );
        }
    }

    public static void main( String[] args ) {
        Integer[] strArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        TestBinarySearch.BinarySearchST< Integer, Integer > st = new TestBinarySearch.BinarySearchST< Integer, Integer >( intArr.length );
        for ( int i = 0; i < intArr.length; ++i ) {
            st.put( strArr[ i ], intArr[ i ] );
        }

        StdOut.println( "DEBUG: st: " + st.toString() );
        StdOut.println( "DEBUG: st.min(): " + st.min() );
        StdOut.println( "DEBUG: st.max(): " + st.max() );
        StdOut.println( "DEBUG: st.floor( 8 ): " + st.floor( 8 ) );
        StdOut.println( "DEBUG: st.ceiling( 8 ): " + st.ceiling( 8 ) );
        StdOut.println( "DEBUG: st.floor( 15 ): " + st.floor( 15 ) );
        StdOut.println( "DEBUG: st.ceiling( 15 ): " + st.ceiling( 15 ) );
        StdOut.println( "DEBUG: st.rank( 12 ): " + st.rank( 12 ) );
        st.deleteMin();
        StdOut.println( "DEBUG: st.deleteMin(): " + st.toString() );
        st.deleteMax();
        StdOut.println( "DEBUG: st.deleteMax(): " + st.toString() );
        StdOut.println( "DEBUG: st.keys(): " + st.keys() );
        StdOut.println( "DEBUG: st.keys( 2, 10 ): " + st.keys( 2, 10 ).toString() );

    }
}
