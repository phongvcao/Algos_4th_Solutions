package com.company;
import edu.princeton.cs.algs4.*;

public class MyRedBlackBST< Key extends Comparable< Key >, Value > {

    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private class Node {
        private Key key = null;
        private Value value = null;
        private int N = 0;
        private Node left = null;
        private Node right = null;
        private boolean color = BLACK;

        public Node( Key key, Value value, int N, boolean color ) {
            this.key = key;
            this.value = value;
            this.N = N;
            this.color = color;
        }

        public String toString() {
            String rv = " | " + this.key + " : " + this.value + " ; size : " + this.N + " ; color : " + this.color;
            if ( this.left != null ) {
                rv += " ; left : " + this.left.key + " ; color : " + this.left.color;
            } else {
                rv += " ; left : null";
            }

            if ( this.right != null ) {
                rv += " ; right : " + this.right.key + " ; color : " + this.right.color;
            } else {
                rv += " ; right : null";
            }
            return rv;
        }
    }

    private Node root = null;

    private boolean isRed( Node x ) {
        if ( x == null ) return false;
        return x.color == RED;
    }

    public MyRedBlackBST() {
        // Not implemented
    }

    public Node rotateLeft( Node h ) {
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = 1 + size( h.left ) + size( h.right );
        return x;
    }

    public Node rotateRight( Node h ) {
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = 1 + size( h.left ) + size( h.right );
        return x;
    }

    public void flipColors( Node h ) {
        h.color = RED;
        h.left.color = BLACK;
        h.right.color = BLACK;
    }

    public void put( Key key, Value value ) {
        root = put( root, key, value );
        root.color = BLACK;
    }

    public Node put( Node h, Key key, Value value ) {
        if ( h == null ) {
            return new Node( key, value, 1, RED );
        }

        int cmp = key.compareTo( h.key );
        if ( cmp < 0 ) {
            h.left = put( h.left, key, value );
        } else if ( cmp > 0 ) {
            h.right = put( h.right, key, value );
        } else {
            h.value = value;
        }

        if ( isRed( h.right ) && ! isRed( h.left ) ) h = rotateLeft( h );
        if ( isRed( h.left ) && isRed( h.left.left ) ) h = rotateRight( h );
        if ( isRed( h.left ) && isRed( h.right ) ) flipColors( h );
        h.N = size( h.left ) + size( h.right ) + 1;
        return h;
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

    /* public void deleteMin() {

    }

    public Node deleteMin( Node x ) {

    }

    public void deleteMax() {

    }

    public Node deleteMax( Node x ) {

    }

    public void delete( Key key ) {

    }

    public Node delete( Node x, Key key ) {

    } */

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
            return select( x.right, k - size - 1 );
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
        String rv = "\nROOT : " + this.root.key + "\n";
        rv += toString( root );
        return rv;
    }

    public String toString( Node x ) {
        if ( x == null ) return "";
        String rv = toString( x.left);
        rv += x.toString();
        rv += toString( x.right);
        return rv;
    }

    public Iterable< Key > keys() {
        return keys( min(), max() );
    }

    public Iterable< Key > keys( Key low, Key high ) {
        Queue< Key > queue = new Queue< Key >();
        if ( low.compareTo( high ) > 0 ) return queue;
        keys( root, queue, low, high );
        return queue;
    }

    public void keys( Node x, Queue< Key > queue, Key low, Key high ) {
        if ( x == null ) return;
        int cmpLow = x.key.compareTo( low );
        int cmpHigh = x.key.compareTo( high );
        if ( cmpLow < 0 ) return;
        if ( cmpHigh < 0 ) return;
        keys( x.left, queue, low, high );
        queue.enqueue( x.key );
        keys( x.right, queue, low, high );
    }

    public static void main( String[] args ) {

    }

 }
