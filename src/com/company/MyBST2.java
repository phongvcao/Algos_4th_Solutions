package com.company;
import edu.princeton.cs.algs4.*;

public class MyBST2< Key extends Comparable< Key >, Value > {

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
    }

    private Node root = null;

    public MyBST2() {

    }

    public void put( Key key, Value value ) {
        root = put( root, key, value );
    }

    public Node put( Node x, Key key, Value value ) {
        if ( x == null ) {
            return new Node( key, value, 1 );
        }

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

    public Value get( Key key ) {
        return get( root, key );
    }

    public Value get( Node x, Key key ) {
        if ( x == null ) {
            return null;
        }

        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return get( x.left, key );
        } else if ( cmp > 0 ) {
            return get( x.right, key );
        } else {
            return x.value;
        }
    }

    public String toString() {
        return "\nROOT: " + root.key + "\n" + toString( root );
    }

    public String toString( Node x ) {
        if ( x == null ) return "";

        String rv = "";
        rv += toString( x.left );
        rv += " | " + x.key + " : " + x.value;
        if ( x.left != null ) {
            rv += " ; left : " + x.left.key;
        } else {
            rv += " ; left : null";
        }

        if ( x.right != null ) {
            rv += " ; right : " + x.right.key;
        } else {
            rv += " ; right : null";
        }

        rv += " | ";
        rv += toString( x.right );
        return rv;
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

    public int height() {
        return height( root, -1 );
    }

    public int height( Node x, int count ) {
        if ( x == null ) return count;
        int leftCount = height( x.left, count + 1 );
        int rightCount = height( x.right, count + 1 );
        return leftCount < rightCount ? rightCount : leftCount;
    }

    public Key min() {
        Node min = min( root );
        if ( min != null ) {
            return min.key;
        }
        return null;
    }

    public Node min( Node x ) {
        if ( x == null ) {
            return x;
        }

        if ( x.left == null ) {
            return x;
        }

        return min( x.left );
    }

    public Key max() {
        Node max = max( root );
        if ( max != null ) {
            return max.key;
        }
        return null;
    }

    public Node max( Node x ) {
        if ( x == null ) {
            return x;
        }

        if ( x.right == null ) {
            return x;
        }
        return max( x.right );
    }

    public Key floor( Key key ) {
        Node floorNode = floor( root, key );
        if ( floorNode == null ) return null;
        return floorNode.key;
    }

    public Node floor( Node x, Key key ) {
        if ( x == null ) return null;
        int cmp = key.compareTo( x.key );
        if ( cmp == 0 ) return x;
        if ( cmp < 0 ) return floor( x.left, key );

        Node t = floor( x.right, key );
        if ( t != null ) return t;
        else return x;
    }

    public Key select( int k ) {
        return select( root, k ).key;
    }

    public Node select( Node x, int k ) {
        if ( x == null ) return null;
        int t = size( x.left );
        if ( t > k ) {
            return select( x.left, k );
        } else if ( t < k ) {
            return select( x.right, k - t - 1 );
        } else {
            return x;
        }
    }

    /* public int rank( Key key ) {

    }

    public int rank( Node x, Key key ) {

    }

    public void deleteMin() {

    }

    public Node deleteMin( Node x ) {

    }

    public void delete( Key key ) {

    }

    public Node delete( Node x, Key key ) {

    }

    public Iterable< Key > keys() {

    }

    public Iterable< Key > keys( Key low, Key high ) {

    }

    private void keys( Node x, Queue< Key > queue, Key low, Key high ) {

    } */

    public static Comparable selectElement( Comparable[] a, int k ) {
        int low = 0;
        int high = a.length - 1;

        while ( low < high ) {
            int j = partition( a, low, high );
            if ( j == k ) return a[ k ];
            else if ( j > k ) high = j - 1;
            else if ( j < k ) low = j + 1;
        }
        return a[ k ];
    }

    public static int partition( Comparable[] a, int low, int high ) {
        int i = low;
        int j = high + 1;
        Comparable pivot = a[ low ];

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( i >= j ) break;
            exchange( a, i, j );
        }
        exchange( a, low, j );
        return j;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void main( String[] args ) {
        Integer[] keyArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] valueArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MyBST2< Integer, Integer > bst = new MyBST2< Integer, Integer >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            bst.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst: " + bst.toString() );
        StdOut.println( "DEBUG: bst.height(): " + bst.height() );
        StdOut.println( "DEBUG: bst.min(): " + bst.min() );
        StdOut.println( "DEBUG: bst.max(): " + bst.max() );
    }
}
