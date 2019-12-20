package com.company;
import edu.princeton.cs.algs4.*;

public class MyBST< Key extends Comparable< Key >, Value > {

    private class Node {
        public Key key = null;
        public Value value = null;
        public Node left = null;
        public Node right = null;
        public int N = 0;

        public Node( Key key, Value value, int N ) {
            this.key = key;
            this.value = value;
            this.N = N;
        }
    }

    private Node root;

    public MyBST() {

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

    public Value get( Key key ) {
        return get( root, key );
    }

    public Value get( Node x, Key key ) {
        if ( x == null ) return null;
        int cmp = key.compareTo( x.key );
        if ( cmp < 0 ) {
            return get( x.left, key );
        } else if ( cmp > 0 ) {
            return get( x.right, key );
        } else {
            return x.value;
        }
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

    public static void main( String[] args ) {

    }
}
