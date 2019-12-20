package com.company;
import edu.princeton.cs.algs4.*;

public class ArraySTSelfOrganizingSearch< Key extends Comparable< Key >, Value > {

    private Key[] keys;
    private Value[] values;
    private int N = 0;

    public ArraySTSelfOrganizingSearch( int cap ) {
        keys = ( Key[] )new Comparable[ cap ];
        values = ( Value[] )new Object[ cap ];
    }

    public void put( Key key, Value value ) {
        for ( int i = 0; i < N; ++i ) {
            if ( key.compareTo( keys[ i ] ) == 0 ) {
                values[ i ] = value;
                return;
            }
        }
        keys[ N ] = key;
        values[ N ] = value;
        ++N;
    }

    public int rank( Key key ) {
        int rankCount = 0;
        for ( int i = 0; i < N; ++i ) {
            if ( key.compareTo( keys[ i ] ) > 0 ) {
                ++rankCount;
            }
        }
        return N;
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public boolean contains( Key key ) {
        return get( key ) != null;
    }

    public Value get( Key key ) {
        for ( int i = 0; i < N; ++i ) {
            if ( key.compareTo( keys[ i ] ) == 0 ) {
                Value rv = values[ i ];
                for ( int j = i; j >= 1; --j ) {
                    keys[ j ] = keys[ j - 1 ];
                    values[ j ] = values[ j - 1 ];
                }
                keys[ 0 ] = key;
                values[ 0 ] = rv;
                return rv;
            }
        }
        return null;
    }

    private void exchange( int i, int j ) {
        Key tempKey = keys[ i ];
        keys[ i ] = keys[ j ];
        keys[ j ] = tempKey;

        Value tempValue = values[ i ];
        values[ i ] = values[ j ];
        values[ j ] = tempValue;
    }

    public String toString() {
        return "\nkeys : " + java.util.Arrays.toString( keys ) + "\nvalues : " + java.util.Arrays.toString( values );
    }

    public Iterable< Key > keys( Key low, Key high ) {
        Queue< Key > q = new Queue< Key >();
        if ( low.compareTo( high ) > 0 ) return q;
        for ( int i = 0; i < N; ++i ) {
            if ( low.compareTo( keys[ i ] ) <= 0 && high.compareTo( keys[ i ] ) >= 0 ) {
                q.enqueue( keys[ i ] );
            }
        }
        return q;
    }

    public Iterable< Key > keys() {
        return keys( min(), max() );
    }

    public Key min() {
        Key min = null;
        for ( int i = 0; i < N; ++i ) {
            if ( min == null || keys[ i ].compareTo( min ) < 0 ) {
                min = keys[ i ];
            }
        }
        return min;
    }

    public Key max() {
        Key max = null;
        for ( int i = 0; i < N; ++i ) {
            if ( max == null || keys[ i ].compareTo( max ) > 0 ) {
                max = keys[ i ];
            }
        }
        return max;
    }

    public void delete( Key key ) {
        for ( int i = 0; i < N; ++i ) {
            if ( key.compareTo( keys[ i ] ) == 0 ) {
                keys[ i ] = null;
                values[ i ] = null;
                --N;
                return;
            }
        }
    }

    public void deleteMin() {
        delete( min() );
    }

    public void deleteMax() {
        delete( max() );
    }

    public static void main( String[] args ) {
        Integer[] strArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        ArraySTSelfOrganizingSearch< Integer, Integer > st = new ArraySTSelfOrganizingSearch< Integer, Integer >( intArr.length );
        for ( int i = 0; i < intArr.length; ++i ) {
            st.put( strArr[ i ], intArr[ i ] );
        }

        StdOut.println( "DEBUG: st: " + st.toString() );
        StdOut.println( "DEBUG: st.get( 14 ): " + st.get( 13 ) );
        StdOut.println( "DEBUG: st: " + st.toString() );
    }
}
