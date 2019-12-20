package com.company;
import edu.princeton.cs.algs4.*;

public class MyBST7< Key extends Comparable< Key >, Value > {

    private class Node {
        private Key key = null;
        private Value value = null;
        private int N = 0 ;
        private Node left = null;
        private Node right = null;

        public Node( Key key, Value value, int N ) {
            this.key = key;
            this.value = value;
            this.N = N;
        }

        public String toString() {
            String rv = "";
            rv += " | " + key + " : " + value;
            if ( this.left != null ) {
                rv += " ; left : " + this.left;
            } else {
                rv += " ; left : null";
            }

            if ( this.right != null ) {
                rv += " ; right : " + this.right;
            } else {
                rv += " ; right : null";
            }

            return rv;
        }
    }

    private Node root = null;

    public MyBST7() {
        // Not implemented
    }

    public void put( Key key, Value value ) {
        root = put( root, key, value );
    }

    public Node put( Node x, Key key, Value value ) {
        if ( x == null ) return x;
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

    public String toString() {
        return toString( root );
    }

    public String toString( Node x ) {
        String rv = toString( x.left );
        rv += x.toString();
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
        int leftHeight = height( x.left, count + 1 );
        int rightHeight = height( x.right, count + 1 );
        return leftHeight < rightHeight ? rightHeight : leftHeight;
    }

    public boolean isEmpty() {
        return size() == 0;
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
        if ( x == null ) return x;
        if ( x.left == null ) {
            return x.right;
        }
        x.left = deleteMin( x.left );
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public void deleteMax() {
        root = deleteMax( root );
    }

    public Node deleteMax( Node x ) {
        if ( x == null ) return x;
        if ( x.right == null ) {
            return x.left;
        }
        x.right = deleteMax( x.right );
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
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
            x.right = deleteMin( temp );
            x.left = temp.left;
        }
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
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
            return rank( x.right, key ) + 1 + size( x.left );
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

        Node temp = floor( x.left, key );
        if ( temp != null ) {
            return temp;
        }
        return x;
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

    }
}
