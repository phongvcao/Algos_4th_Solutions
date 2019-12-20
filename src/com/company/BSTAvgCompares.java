package com.company;
import edu.princeton.cs.algs4.*;

public class BSTAvgCompares< Key extends Comparable< Key >, Value > {

    private class Node {
        private Key key = null;
        private Value value = null;
        private int N = 0;
        private Node left = null;
        private Node right = null;
        public int totalCompares = 1;
        public int avgCompares = 0;

        public Node( Key key, Value value, int N, int totalCompares ) {
            this.key = key;
            this.value = value;
            this.N = N;
            this.totalCompares = totalCompares;
        }

        public String toString() {
            String rv = " | " + this.key + " : " + this.value + " ; totalCompares : " + this.totalCompares;
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

    public BSTAvgCompares() {
        // Not implemented
    }

    public void put( Key key, Value value ) {
        root = put( root, key, value, 1 );
    }

    public Node put( Node x, Key key, Value value, int totalCompares ) {
        if ( x == null ) {
            return new Node( key, value, 1, totalCompares );
        }

        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            x.left = put( x.left, key, value, totalCompares + 1 );
        } else if ( cmp > 0 ) {
            x.right = put( x.right, key, value, totalCompares + 1 );
        } else {
            x.value = value;
        }
        x.N = size( x.left ) + size( x.right ) + 1;
        x.totalCompares = countTotalCompares( x.left ) + countTotalCompares( x.right ) + totalCompares;
        x.avgCompares = x.totalCompares / x.N + 1;
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

    public int countTotalCompares() {
        return countTotalCompares( root );
    }

    public int countTotalCompares( Node x ) {
        if ( x == null ) {
            return 0;
        } else {
            return x.totalCompares;
        }
    }

    public void updateTotalCompares() {
        updateTotalCompares( root, 1 );
    }

    public int updateTotalCompares( Node x, int totalCompares ) {
        if ( x == null ) return 0;
        x.totalCompares = updateTotalCompares( x.left, totalCompares + 1 ) +
                updateTotalCompares( x.right, totalCompares + 1 ) +
                totalCompares;
        x.avgCompares = x.totalCompares / x.N + 1;
        return x.totalCompares;
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

    public Key min() {
        return min( root ).key;
    }

    public Node min( Node x ) {
        if ( x == null ) return null;
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
        updateTotalCompares( root, 1 );
    }

    public Node deleteMin( Node x ) {
        if ( x == null ) return x;
        if ( x.left == null ) {
            /* if ( x.right != null ) {
                --x.right.totalCompares;
            } */
            return x.right;
        }
        x.left = deleteMin( x.left );
        x.N = size( x.left ) + size( x.right ) + 1;
        // x.totalCompares = countTotalCompares( x.left ) + countTotalCompares( x.right ) + x.totalCompares;
        return x;
    }

    public void deleteMax() {
        root = deleteMax( root );
        updateTotalCompares( root, 1 );
    }

    public Node deleteMax( Node x ) {
        if ( x == null ) return x;
        if ( x.right == null ) {
            /* if ( x.left != null ) {
                --x.left.totalCompares;
            } */
            return x.left;
        }
        x.right = deleteMax( x.right );
        x.N = size( x.left ) + size( x.right ) + 1;
        // x.totalCompares = countTotalCompares( x.left ) + countTotalCompares( x.right ) + x.totalCompares;
        return x;
    }

    public void delete( Key key ) {
        root = delete( root, key );
        updateTotalCompares( root, 1 );
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
        // x.totalCompares = countTotalCompares( x.left ) + countTotalCompares( x.right ) + totalCompares;
        return x;
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
            return size( x.left ) + rank( x.right, key ) + 1;
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
            return select( x.right, k - 1 - size );
        } else {
            return x;
        }
    }

    public Key floor( Key key ) {
        return floor( root, key ).key;
    }

    public Node floor( Node x, Key key ) {
        if ( x == null ) return x;
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
        return "\nROOT: " + root.key + "\n" + toString( root );
    }

    public String toString( Node x ) {
        if ( x == null ) return "";
        String rv = toString( x.left );
        rv += x.toString();
        rv += toString( x.right );
        return rv;
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
        if ( x == null ) return;
        int cmpLow = x.key.compareTo( low );
        int cmpHigh = x.key.compareTo( high );
        if ( cmpLow < 0 ) return;
        if ( cmpHigh > 0 ) return;
        keys( x.left, queue, low, high );
        queue.enqueue( x.key );
        keys( x.right, queue, low, high );
    }

    public int avgComparesRecursively() {
        return countTotalComparesRecursively( root, 1 ) / size() + 1;
    }

    public int avgComparesNonRecursively() {
        return root.avgCompares;
    }

    public int countTotalComparesRecursively( Node x, int count ) {
        if ( x == null ) return 0;
        int leftCompares = countTotalComparesRecursively( x.left, count + 1 );
        int rightCompares = countTotalComparesRecursively( x.right, count + 1 );
        return count + leftCompares + rightCompares;
    }

    // SELECT METHODS
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

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
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

    public static void main( String[] args ) {
        Integer[] keyArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] valueArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        BSTAvgCompares< Integer, Integer > bst = new BSTAvgCompares< Integer, Integer >();

        for ( int i = 0; i < keyArr.length; ++i ) {
            bst.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst: " + bst.toString() );
        StdOut.println( "DEBUG: bst.totalCompares(): " + bst.countTotalComparesRecursively( bst.root, 1 ) );
        StdOut.println( "DEBUG: bst.avgComparesRecursively(): " + bst.avgComparesRecursively() );
        StdOut.println( "DEBUG: bst.avgCompares() (NON-RECURSIVE): " + bst.root.avgCompares );
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
        StdOut.println( "DEBUG: bst.totalCompares(): " + bst.countTotalComparesRecursively( bst.root, 1 ) );
        StdOut.println( "DEBUG: bst.avgCompares(): " + bst.avgComparesRecursively() );
        StdOut.println( "DEBUG: bst.avgCompares() (NON-RECURSIVE): " + bst.root.avgCompares );
    }
}
