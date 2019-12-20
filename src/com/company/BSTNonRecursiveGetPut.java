package com.company;
import edu.princeton.cs.algs4.*;
import java.util.ArrayList;

public class BSTNonRecursiveGetPut< Key extends Comparable< Key >, Value > {

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

    public void putNonRecursive( Key key, Value value ) {
        Node ptr = root;

        if ( ptr == null ) {
            root = new Node( key, value, 1 );
            return;
        }

        ArrayList< Node > path = new ArrayList< Node >();
        boolean nodeAdded = true;
        while ( ptr != null ) {
            path.add( ptr );
            int cmp = key.compareTo( ptr.key );
            if ( cmp < 0 ) {
                if ( ptr.left != null ) {
                    ptr = ptr.left;
                } else {
                    ptr.left = new Node( key, value, 1 );
                }
            } else if ( cmp > 0 ) {
                if ( ptr.right != null ) {
                    ptr = ptr.right;
                } else {
                    ptr.right = new Node( key, value, 1 );
                }
            } else {
                ptr.value = value;
                nodeAdded = false;
                break;
            }
        }

        if ( nodeAdded ) {
            for ( int i = 0; i < path.size(); ++i ) {
                Node eleNode = path.get( i );
                eleNode.N = size( eleNode.left ) + size( eleNode.right ) + 1;
            }
        }
    }

    public Value getNonRecursive( Key key ) {
        Node ptr = root;
        while ( ptr != null ) {
            int cmp = key.compareTo( ptr.key );
            if ( cmp < 0 ) {
                ptr = ptr.left;
            } else if ( cmp > 0 ) {
                ptr = ptr.right;
            } else {
                return ptr.value;
            }
        }
        return null;
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
        if ( x.left == null ) return x.right;
        x.left = deleteMin( x.left );
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public void deleteMax() {
        root = deleteMax( root );
    }

    public Node deleteMax( Node x ) {
        if ( x == null ) return x;
        if ( x.right == null ) return x.left;
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
            x.right = deleteMin( temp.right );
            x.left = temp.left;
        }
        x.N = size( x.left ) + size( x.right ) + 1;
        return x;
    }

    public String toString() {
        String rv = "\nROOT : " + root.key + "\n";
        rv += toString( root );
        return rv;
    }

    public String toString( Node x ) {
        if ( x == null ) return "";
        String rv = toString( x.left );
        rv += x.toString();
        rv += toString( x.right );
        return rv;
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
        if ( cmpHigh > 0 ) return;
        keys( x.left, queue, low, high );
        queue.enqueue( x.key );
        keys( x.right, queue, low, high );
    }

    public static void main( String[] args ) {
        Integer[] keyArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] valueArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        BSTNonRecursiveGetPut< Integer, Integer > bst = new BSTNonRecursiveGetPut< Integer, Integer >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            // bst.put( keyArr[ i ], valueArr[ i ] );
            bst.putNonRecursive( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst: " + bst.toString() );
        StdOut.println( "DEBUG: bst.get(): " + bst.get( 4 ) );
        StdOut.println( "DEBUG: bst.getNonRecursive(): " + bst.getNonRecursive( 4 ) );
    }
}
