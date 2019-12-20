package com.company;
import edu.princeton.cs.algs4.*;
import java.lang.Math;

public class BSTOptCompares< Key extends Comparable< Key >, Value > {

    private class Node {
        private Key key = null;
        private Value value = null;
        private int N = 0;
        private Node left = null;
        private Node right = null;

        public Node( Key key, Value value, int N ) {
            this.key = key;
            this.value = value;
            this.N = N;
        }

        public String toString() {
            String rv = " | " + this.key + " : " + this.value;
            if ( this.left != null ) {
                rv += " ; left : " + this.left.key;
            } else {
                rv += " ; left : null";
            }

            if ( this.right != null ) {
                rv += " ; right : " + this.right.key;
            } else {
                rv += " ; right : null";
            }
            rv += " | ";
            return rv;
        }
    }

    private Node root = null;

    public BSTOptCompares() {
        // Not implemented
    }

    public void put( Key key, Value value ) {
        root = put( root, key, value );
    }

    public Node put( Node x, Key key, Value value ) {
        if ( x == null ) return new Node( key, value, 1 );
        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            x.left = put( x.left, key, value );
        } else if ( cmp > 0 ) {
            x.right = put( x.right, key, value );
        } else {
            x.value = value;
        }
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public int size() {
        return size( root );
    }

    public int size( Node x ) {
        if ( x == null ) {
            return 0;
        } else {
            return x.N;
        }
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int height() {
        return height( root, -1 );
    }

    public int height( Node x, int count ) {
        if ( x == null ) return count;
        int leftHeight = height( x.left, count + 1 );
        int rightHeight = height( x.right, count + 1 );
        return leftHeight < rightHeight ? rightHeight : leftHeight;
    }

    public Value get( Key key ) {
        return get( root, key ).value;
    }

    public Node get( Node x, Key key ) {
        if ( x == null ) return x;
        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return get( x.left, key );
        } else if ( cmp > 0 ) {
            return get( x.right, key );
        } else {
            return x;
        }
    }

    public int rank( Key key ) {
        return rank( root, key );
    }

    public int rank( Node x, Key key ) {
        if ( x == null ) return 0;
        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return rank( x.left, key );
        } else if ( cmp > 0 ) {
            return rank( x.right, key ) + size( x.left ) + 1;
        } else {
            return size( x.left );
        }
    }

    public Key select( int k ) {
        return select( root, k ).key;
    }

    public Node select( Node x, int k ) {
        if ( x == null ) return x;
        int size = size( x.left );
        if ( k < size ) {
            return select( x.left, k );
        } else if ( k > size ) {
            return select( x.right, k - size - 1 );
        } else {
            return x;
        }
    }

    public void delete( Key key ) {
        root = delete( root, key );
    }

    public Node delete( Node x, Key key ) {
        if ( x == null ) return x;
        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            x.left = delete( x.left, key );
        } else if ( cmp > 0 ) {
            x.right = delete( x.right, key );
        } else {
            if ( x.right == null ) return x.left;
            if ( x.left == null ) return x.right;
            Node temp = x;
            x = min( temp.right );
            x.right = deleteMin( temp.right );
            x.left = temp.left;
        }
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public Key min() {
        return min( root ).key;
    }

    public Node min( Node x ) {
        if ( x == null ) return x;
        if ( x.left == null ) return x;
        return min( x.left );
    }

    public Key max() {
        return max( root ).key;
    }

    public Node max( Node x ) {
        if ( x == null ) return x;
        if ( x.right == null ) return x;
        return max( x.right );
    }

    public void deleteMin() {
        root = deleteMin( root );
    }

    public Node deleteMin( Node x ) {
        if ( x == null ) return null;
        if ( x.left == null ) return x.right;
        x.left = deleteMin( x.left );
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public void deleteMax() {
        root = deleteMax( root );
    }

    public Node deleteMax( Node x ) {
        if ( x == null ) return null;
        if ( x.right == null ) return x.left;
        x.right = deleteMax( x.right );
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public Iterable< Key > keys() {
        return keys( min(), max() );
    }

    public Iterable< Key > keys( Key low, Key high ) {
        Queue< Key > q = new Queue< Key >();
        if ( low.compareTo( high ) > 0 ) return q;
        keys( root, q, low, high );
        return q;
    }

    public void keys( Node x, Queue< Key > queue, Key low, Key high ) {
        if ( low.compareTo( high ) > 0 ) return;
        if ( x == null ) return;
        int cmpLow = x.key.compareTo( low );
        int cmpHigh = x.key.compareTo( high );
        if ( cmpLow < 0 ) return;
        if ( cmpHigh > 0 ) return;
        keys( x.left, queue, low, high );
        queue.enqueue( x.key );
        keys( x.right, queue, low, high );
    }

    public Key floor( Key key ) {
        return floor( root, key ).key;
    }

    public Node floor( Node x, Key key ) {
        if ( x == null ) return null;
        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return floor( x.left, key );
        } else if ( cmp == 0 ) {
            return x;
        }

        Node temp = floor( x.right, key );
        if ( temp != null ) {
            return temp;
        }
        return x;
    }

    public Key ceiling( Key key ) {
        return ceiling( root, key ).key;
    }

    public Node ceiling( Node x, Key key ) {
        if ( x == null ) return x;
        int cmp = key.compareTo( x.key );
        if ( cmp > 0 ) {
            return ceiling( x.right, key );
        } else if ( cmp == 0 ) {
            return x;
        }

        Node temp = ceiling( x.left, key );
        if ( temp != null ) {
            return temp;
        }
        return x;
    }

    public String toString() {
        return toString( root );
    }

    public String toString( Node x ) {
        if ( x == null ) return "";
        String rv = "\nROOT : " + root.key + "\n";
        rv += toString( x.left );
        rv += x.toString();
        rv += toString( x.right );
        return rv;
    }

    public static int optCompares( int N ) {
        if ( N == 0 ) {
            return 0;
        }

        int totalCompares = 0;
        int heightMinus1 = (int) ( Math.log( N ) / Math.log( 2 ) );
        int numberOfNodesBeforeLastLevel = 0;

        for ( int i = 1; i <= heightMinus1; ++i ) {
            totalCompares += i * Math.pow( 2, i - 1 );
            numberOfNodesBeforeLastLevel += Math.pow( 2, i - 1 );
        }

        int nodesInLastLevel = N - numberOfNodesBeforeLastLevel;
        totalCompares += nodesInLastLevel * ( heightMinus1 + 1 );

        int numberOfComparesRequiredByRandomSearchHit = ( totalCompares / N ) + 1;
        return numberOfComparesRequiredByRandomSearchHit;
    }

    public static Comparable select( Comparable[] a, int k ) {
        int low = 0;
        int high = a.length - 1;

        while ( low <= high ) {
            int j = partition( a, low, high );
            if ( k < j ) {
                high = j - 1;
            } else if ( k > j ) {
                low = j + 1;
            } else {
                return a[ k ];
            }
        }
        return a[ k ];
    }

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static int partition( Comparable[] a, int low, int high ) {
        int i = low;
        int j = high + 1;
        Comparable pivot = a[ low ];

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --i ] ) ) if ( j == low ) break;

            if ( i >= j ) break;
            exchange( a, i, j );
        }
        exchange( a, low, j );
        return j;
    }

    public static void main( String[] args ) {
        Integer[] keyArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] valueArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        BSTOptCompares< Integer, Integer > bst = new BSTOptCompares< Integer, Integer >();

        for ( int i = 0; i < keyArr.length; ++i ) {
            bst.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst: " + bst.toString() );
        StdOut.println( "DEBUG: bst.size(): " + bst.size() );
        StdOut.println( "DEBUG: bst.height(): " + bst.height() );
        StdOut.println( "DEBUG: bst.isEmpty(): " + bst.isEmpty() );
        StdOut.println( "DEBUG: bst.get( 9 ): " + bst.get( 9 ) );
        StdOut.println( "DEBUG: bst.min(): " + bst.min() );
        StdOut.println( "DEBUG: bst.max(): " + bst.max() );
        bst.deleteMin();
        StdOut.println( "DEBUG: bst.deleteMin(): " + bst.min() );
        StdOut.println( "DEBUG: bst (AFTER deleteMin()): " + bst.toString() );
        bst.deleteMax();
        StdOut.println( "DEBUG: bst.deleteMax(): " + bst.max() );
        StdOut.println( "DEBUG: bst (AFTER deleteMax()): " + bst.toString() );
        bst.delete( 10 );
        StdOut.println( "DEBUG: bst.delete( 10 ): " + bst.toString() );
        StdOut.println( "DEBUG: bst.rank( 4 ): " + bst.rank( 4 ) );
        StdOut.println( "DEBUG: bst.select( 4 ): " + bst.select( 4 ) );
        StdOut.println( "DEBUG: bst.floor( 4 ): " + bst.floor( 4 ) );
        StdOut.println( "DEBUG: bst.ceiling( 4 ): " + bst.ceiling( 4 ) );
        StdOut.println( "DEBUG: bst.keys(): " + bst.keys() );
        StdOut.println( "DEBUG: optCompares(): " + bst.optCompares( 15 ) );
    }
}
