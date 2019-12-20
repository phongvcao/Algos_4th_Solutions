package com.company;
import edu.princeton.cs.algs4.*;

public class MyRedBlackBST1< Key extends Comparable< Key >, Value > {

    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private class Node {
        private Key key = null;
        private Value value = null;
        private int N = 0;
        private Node left = null;
        private Node right = null;
        private boolean color = RED;

        public Node( Key key, Value value, int N, boolean color ) {
            this.key = key;
            this.value = value;
            this.N = N;
            this.color = color;
        }

        public String toString() {
            String rv = " | " + this.key + " : " + this.value + " ; size : " + this.N + " ; color : " + this.color;
            if ( this.left != null ) {
                rv += " ; left : " + this.left.key + " ; left.color : " + this.left.color;
            } else {
                rv += " ; left : null";
            }

            if ( this.right != null ) {
                rv += " ; right : " + this.right.key + " ; right.color : " + this.right.color;
            } else {
                rv += " ; right : null";
            }
            rv += " | ";
            return rv;
        }
    }

    private Node root = null;

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

    public Node rotateLeft( Node h ) {
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = size( h.left ) + size( h.right ) + 1;
        return x;
    }

    public Node rotateRight( Node h ) {
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = size( h.left ) + size( h.right ) + 1;
        return x;
    }

    private boolean isRed( Node h ) {
        if ( h == null ) return false;
        return h.color == RED;
    }

    public void flipColors( Node h ) {
        h.color = RED;
        h.left.color = BLACK;
        h.right.color = BLACK;
    }

    public Value get( Key key ) {
        return get( root, key ).value;
    }

    public Node get( Node h, Key key ) {
        if ( h == null ) return h;
        int cmp = key.compareTo( h.key );
        if ( cmp < 0 ) {
            return get( h.left, key );
        } else if ( cmp > 0 ) {
            return get( h.right, key );
        } else {
            return h;
        }
    }

    public Key min() {
        return min( root ).key;
    }

    public Node min( Node h ) {
        if ( h == null ) return h;
        if ( h.left == null ) return h;
        return min( h.left );
    }

    public Key max() {
        return max( root ).key;
    }

    public Node max( Node h ) {
        if ( h == null ) return h;
        if ( h.right == null ) return h;
        return max( h.right );
    }

    public int rank( Key key ) {
        return rank( root, key );
    }

    public int rank( Node h, Key key ) {
        if ( h == null ) return 0;
        int cmp = key.compareTo( h.key );
        if ( cmp < 0 ) {
            return rank( h.left, key );
        } else if ( cmp > 0 ) {
            return rank( h.right, key ) + 1 + size( h.left );
        } else {
            return size( h.left );
        }
    }

    public Key select( int k ) {
        return select( root, k ).key;
    }

    public Node select( Node h, int k ) {
        if ( h == null ) return h;
        int size = size( h.left );
        if ( k < size ) {
            return select( h.left, k );
        } else if ( k > size ) {
            return select( h.right, k - size - 1 );
        } else {
            return h;
        }
    }

    public int size() {
        return size( root );
    }

    public int size( Node h ) {
        if ( h == null ) {
            return 0;
        } else {
            return h.N;
        }
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int height() {
        return height( root, -1 );
    }

    public int height( Node h, int count ) {
        if ( h == null ) return count;
        int leftHeight = height( h.left, count + 1 );
        int rightHeight = height( h.right, count + 1 );
        return leftHeight < rightHeight ? rightHeight : leftHeight;
    }

    public String toString() {
        String rv = "\nROOT : " + root.key + "\n";
        rv += toString( root );
        return rv;
    }

    public String toString( Node h ) {
        if ( h == null ) return "";
        String rv = toString( h.left );
        rv += h.toString();
        rv += toString( h.right );
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

    public void keys( Node h, Queue< Key > queue, Key low, Key high ) {
        if ( h == null ) return;
        int cmpLow = h.key.compareTo( low );
        int cmpHigh = h.key.compareTo( high );
        if ( cmpLow < 0 ) return;
        if ( cmpHigh > 0 ) return;
        keys( h.left, queue, low, high );
        queue.enqueue( h.key );
        keys( h.right, queue, low, high );
    }

    /* public void deleteMin() {

    }

    public Node deleteMin( Node h ) {

    }

    public void deleteMax() {

    }

    public Node deleteMax( Node h ) {

    }

    public void delete( Key key ) {

    }

    public Node delete( Node h, Key key ) {

    } */

    public static void main( String[] args ) {

    }
}
