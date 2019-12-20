package com.company;
import edu.princeton.cs.algs4.*;
import java.util.ArrayList;

public class BSTThreeArrays< Key extends Comparable< Key >, Value > {

    private Key[] keys;
    private Value[] values;
    private int[] sizes;
    private int[] leftLinks;
    private int[] rightLinks;

    public BSTThreeArrays( int cap ) {
        keys = ( Key[] )new Comparable[ cap ];
        values = ( Value[] )new Object[ cap ];
        sizes = new int[ cap ];
        leftLinks = new int[ cap ];
        rightLinks = new int[ cap ];

        for ( int i = 0; i < cap; ++i ) {
            sizes[ i ] = 0;
            leftLinks[ i ] = -1;
            rightLinks[ i ] = -1;
        }
    }

    public void put( Key key, Value value ) {
        // Find exact place to put key, value into
        // Root is keys[ 0 ]
        int j = 0;
        ArrayList< Integer > path = new ArrayList< Integer >();
        while ( true ) {
            if ( keys[ j ] == null ) {
                break;
            }

            int cmp = key.compareTo( keys[ j ] );
            path.add( j );
            if ( cmp < 0 ) {
                if ( leftLinks[ j ] != -1 ) {
                    j = leftLinks[ j ];
                } else {
                    leftLinks[ j ] = sizes[ 0 ];
                    break;
                }
            } else if ( cmp > 0 ) {
                if ( rightLinks[ j ] != -1 ) {
                    j = rightLinks[ j ];
                } else {
                    rightLinks[ j ] = sizes[ 0 ];
                    break;
                }
            } else {
                values[ j ] = value;
                return;
            }
        }

        keys[ sizes[ 0 ] ] = key;
        values[ sizes[ 0 ] ] = value;
        sizes[ sizes[ 0 ] ] = 1;
        leftLinks[ sizes[ 0 ] ] = -1;
        rightLinks[ sizes[ 0 ] ] = -1;
        for ( int i = 0; i < path.size(); ++i ) {
            ++sizes[ path.get( i ) ];
        }
    }

    public Value get( Key key ) {
        int j = 0;
        while ( true ) {
            if ( keys[ j ] == null ) {
                break;
            }

            int cmp = key.compareTo( keys[ j ] );
            if ( cmp < 0 ) {
                j = leftLinks[ j ];
            } else if ( cmp > 0 ) {
                j = rightLinks[ j ];
            } else {
                return values[ j ];
            }
        }
        return null;
    }

    public int size() {
        return sizes[ 0 ];
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int height() {
        return height( 0, -1 );
    }

    public int height( int x, int count ) {
        if ( x == -1 ) return count;
        int leftHeight = height( leftLinks[ x ], count + 1 );
        int rightHeight = height( rightLinks[ x ], count + 1 );
        return leftHeight < rightHeight ? rightHeight : leftHeight;
    }

    public String toStringRaw() {
        String rv = "\nkeys : " + java.util.Arrays.toString( keys );

        rv += "\nleftKeys : { ";
        for ( int i = 0; i < sizes[ 0 ]; ++i ) {
            if ( leftLinks[ i ] == -1 ) {
                break;
            }
            rv += keys[ leftLinks[ i ] ] + ", ";
        }
        rv += "}";

        rv += "\nrightKeys : { ";
        for ( int i = 0; i < sizes [ 0 ]; ++i ) {
            if ( rightLinks[ i ] == -1 ) {
                break;
            }
            rv += keys[ rightLinks[ i ] ] + ", ";
        }
        rv += "}";

        rv += "\nvalues : " + java.util.Arrays.toString( values );
        rv += "\nsizes : " + java.util.Arrays.toString( sizes );
        rv += "\nleftLinks : " + java.util.Arrays.toString( leftLinks );
        rv += "\nrightLinks : " + java.util.Arrays.toString( rightLinks );
        rv += "\n";
        return rv;
    }

    public Key min() {
        int x = 0;
        while ( leftLinks[ x ] != -1 ) {
            x = leftLinks[ x ];
        }
        return keys[ x ];
    }

    public int min( int x ) {
        if ( x == -1 ) return x;
        if ( leftLinks[ x ] == -1 ) return x;
        return min( leftLinks[ x ] );
    }

    public Key max() {
        int x = 0;
        while ( rightLinks[ x ] != -1 ) {
            x = rightLinks[ x ];
        }
        return keys[ x ];
    }

    public void deleteMin() {
        int x = 0;
        int parent = 0;
        while ( leftLinks[ x ] != -1 ) {
            --sizes[ x ];
            parent = x;
            x = leftLinks[ x ];
        }

        keys[ x ] = null;
        values[ x ] = null;
        if ( rightLinks[ x ] != -1 ) {
            leftLinks[ parent ] = rightLinks[ x ];
        } else {
            leftLinks[ parent ] = -1;
        }
    }

    public int size( int x ) {
        if ( x == -1 ) {
            return 0;
        } else {
            return sizes[ x ];
        }
    }

    public int deleteMin( int x ) {
        if ( x == -1 ) return x;
        if ( leftLinks[ x ] == -1 ) return rightLinks[ x ];
        leftLinks[ x ] = deleteMin( leftLinks[ x ] );
        sizes[ x ] = size( leftLinks[ x ] ) + size( rightLinks[ x ] ) + 1;
        return x;
    }

    public void deleteMax() {
        int x = 0;
        int parent = 0;
        while ( rightLinks[ x ] != -1 ) {
            --sizes[ x ];
            parent = x;
            x = rightLinks[ x ];
        }

        keys[ x ] = null;
        values[ x ] = null;
        if ( leftLinks[ x ] != -1 ) {
            rightLinks[ parent ] = leftLinks[ x ];
        } else {
            rightLinks[ parent ] = -1;
        }
    }

    public int rank( Key key ) {
        return rank( 0, key );
    }

    public int rank( int x, Key key ) {
        if ( x == - 1 ) return 0;
        int cmp = key.compareTo( keys[ x ] );
        if ( cmp < 0 ) {
            return rank( leftLinks[ x ], key );
        } else if ( cmp > 0 ) {
            return rank( rightLinks[ x ], key ) + 1 + sizes[ leftLinks[ x ] ];
        } else {
            return sizes[ leftLinks[ x ] ];
        }
    }

    public Key select( int k ) {
        return select( 0, k );
    }

    public Key select( int x, int k ) {
        if ( x == - 1 ) return null;
        int size = sizes[ leftLinks[ x ] ];
        if ( k < size ) {
            return select( leftLinks[ x ], k );
        } else if ( k > size ) {
            return select( rightLinks[ x ], k - size - 1 );
        } else {
            return keys[ k ];
        }
    }

    public Key floor( Key key ) {
        int floorIdx = floor( 0, key );
        if ( floorIdx == -1 ) {
            return null;
        } else {
            return keys[ floorIdx ];
        }
    }

    public int floor( int x, Key key ) {
        if ( x == -1 ) return x;
        int cmp = key.compareTo( keys[ x ] );
        if ( cmp < 0 ) {
            return floor( leftLinks[ x ], key );
        } else if ( cmp == 0 ) {
            return x;
        }

        int temp = floor( rightLinks[ x ], key );
        if ( temp != -1 ) {
            return temp;
        }
        return x;
    }

    public Key ceiling( Key key ) {
        int ceilingIdx = ceiling( 0, key );
        if ( ceilingIdx == -1 ) {
            return null;
        } else {
            return keys[ ceilingIdx ];
        }
    }

    public int ceiling( int x, Key key ) {
        if ( x == -1 ) return x;
        int cmp = key.compareTo( keys[ x ] );
        if ( cmp > 0 ) {
            return ceiling( rightLinks[ x ], key );
        } else if ( cmp == 0 ) {
            return x;
        }

        int temp = ceiling( leftLinks[ x ], key );
        if ( temp != -1 ) {
            return temp;
        }
        return x;
    }

    public Iterable< Key > keys() {
        return keys( min(), max() );
    }

    public Iterable< Key > keys( Key low, Key high ) {
        Queue< Key > queue = new Queue< Key >();
        if ( low.compareTo( high ) > 0 ) return queue;
        keys( 0, queue, low, high );
        return queue;
    }

    public void keys( int x, Queue< Key > queue, Key low, Key high ) {
        if ( x == -1 ) return;
        int cmpLow = keys[ x ].compareTo( low );
        int cmpHigh = keys[ x ].compareTo( high );
        if ( cmpLow < 0 ) return;
        if ( cmpHigh > 0 ) return;
        keys( leftLinks[ x ], queue, low, high );
        queue.enqueue( keys[ x ] );
        keys( rightLinks[ x ], queue, low, high );
    }

    public void delete( Key key ) {
        int root = delete( 0, key );
    }

    public int delete( int x, Key key ) {
        if ( x == -1 ) return x;
        int cmp = key.compareTo( keys[ x ] );
        if ( cmp < 0 ) {
            leftLinks[ x ] = delete( leftLinks[ x ], key );
        } else if ( cmp > 0 ) {
            rightLinks[ x ] = delete( rightLinks[ x ], key );
        } else {
            if ( rightLinks[ x ] == -1 ) return leftLinks[ x ];
            if ( leftLinks[ x ] == -1 ) return rightLinks[ x ];

            int temp = x;
            x = min( rightLinks[ temp ] );
            rightLinks[ x ] = deleteMin( rightLinks[ temp ] );
            leftLinks[ x ] = leftLinks[ temp ];

            if ( temp == 0 ) {
                keys[ temp ] = keys[ x ];
                values [ temp ] = values[ x ];
                sizes[ temp ] = sizes[ x ];
                leftLinks[ temp ] = leftLinks[ x ];
                rightLinks[ temp ] = rightLinks[ x ];
            } else {
                keys[ temp ] = null;
                values[ temp ] = null;
                leftLinks[ temp ] = -1;
                rightLinks[ temp ] = -1;
                sizes[ temp ] = 0;
            }
        }
        sizes[ x ] = size( leftLinks[ x ] ) + size( rightLinks[ x ] ) + 1;
        return x;
    }

    public static void main( String[] args ) {
        Integer[] keyArr = { 7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14 };
        Integer[] valueArr = { 7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14 };
        BSTThreeArrays< Integer, Integer > bst = new BSTThreeArrays< Integer, Integer >( keyArr.length );

        for ( int i = 0; i < keyArr.length; ++i ) {
            bst.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst: " + bst.toStringRaw() );
        bst.delete( 7 );
        StdOut.println( "DEBUG: bst.delete( root ): " + bst.toStringRaw() );
        bst.delete( 5 );
        StdOut.println( "DEBUG: bst.delete( 5 ): " + bst.toStringRaw() );
        /* StdOut.println( "DEBUG: bst.get( 4 ): " + bst.get( 4 ) );
        StdOut.println( "DEBUG: bst.height(): " + bst.height() );
        StdOut.println( "DEBUG: bst.min(): " + bst.min() );
        StdOut.println( "DEBUG: bst.max(): " + bst.max() );
        StdOut.println( "DEBUG: bst.rank( 5 ): " + bst.rank( 5 ) );
        StdOut.println( "DEBUG: bst.floor( 5 ): " + bst.rank( 5 ) );
        StdOut.println( "DEBUG: bst.keys(): " + bst.keys() );
        bst.deleteMin();
        bst.deleteMin();
        StdOut.println( "DEBUG: bst.deleteMin(): " + bst.toStringRaw() );
        StdOut.println( "DEBUG: bst.deleteMin(): " + bst.min() );
        bst.deleteMax();
        bst.deleteMax();
        StdOut.println( "DEBUG: bst.deleteMax(): " + bst.toStringRaw() );
        StdOut.println( "DEBUG: bst.deleteMax(): " + bst.max() );
        StdOut.println( "DEBUG: bst.keys(): " + bst.keys() ); */
    }
}
