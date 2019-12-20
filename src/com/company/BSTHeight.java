package com.company;
import edu.princeton.cs.algs4.*;

public class BSTHeight< Key extends Comparable< Key >, Value > {

    private class Node {
        private Key key = null;
        private Value value = null;
        private int N = 0;
        private Node left = null;
        private Node right = null;
        private int height = 0;

        public Node( Key key, Value value, int N, int height ) {
            this.key = key;
            this.value = value;
            this.N = N;
            this.height = height;
        }
    }

    private Node root = null;

    public BSTHeight() {

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
        return height( root );
    }

    public int height( Node x ) {
        if ( x == null ) {
            return 0;
        } else {
            return x.height;
        }
    }

    public void put( Key key, Value value ) {
        root = put( root, key, value );
    }

    public Node put( Node x, Key key, Value value ) {
        if ( x == null ) {
            return new Node( key, value, 1, 1 );
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
        x.height = ( height( x.left ) < height( x.right ) ) ? height( x.right ) : height( x.left ) + 1;
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

    public int heightRecursively() {
        return heightRecursively( root, -1 );
    }

    public int heightRecursively( Node x, int count ) {
        if ( x == null ) return count;

        int leftHeight = heightRecursively( x.left, count + 1 );
        int rightHeight = heightRecursively( x.right, count + 1 );
        return leftHeight < rightHeight ? rightHeight : leftHeight;
    }

    public String toString() {
        return "\nROOT: " + root.key + "\n" + toString( root );
    }

    public String toString( Node x ) {
        if ( x == null ) return "";
        String rv = "";
        rv += toString( x.left );
        rv += " | " + x.key + " : " + x.value + " ; height : " + x.height;

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

    public static void main( String[] args ) {
        Integer[] keyArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] valueArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        BSTHeight< Integer, Integer > bst = new BSTHeight< Integer, Integer >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            bst.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst: " + bst.toString() );
        StdOut.println( "DEBUG: bst.height(): " + bst.heightRecursively() );
        StdOut.println( "DEBUG: bst.height(): " + bst.height() );
    }
}
