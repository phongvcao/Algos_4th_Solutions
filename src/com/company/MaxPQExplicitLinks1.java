package com.company;
import edu.princeton.cs.algs4.*;
import java.lang.Math;

public class MaxPQExplicitLinks1< Key extends Comparable< Key > > {

    private class Node {
        public Key value = null;
        public Node parent = null;
        public Node childLeft = null;
        public Node childRight = null;
    }

    private Node head = null;
    private int N = 0;

    public MaxPQExplicitLinks1() {
        // Not implemented
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public String toStringValue( Node node ) {
        return node == null ? "null" : "" + node.value;
    }

    public String toString( Node node ) {
        if ( node == null ) {
            return "null";
        }

        return "\n | parent : " + toStringValue( node ) + " : left : " + toStringValue( node.childLeft ) + "; right: " + toStringValue( node.childRight ) +
                "\n | " + toString( node.childLeft ) + "\n | " + toString( node.childRight );
    }

    public String toString() {
        return toString( head );
    }

    public String toStringDelMax() {
        String rv = "{ ";

        while ( ! isEmpty() ) {
            rv += delMax() + " , ";
            // rv += "\n" + toString() + "\n";
        }

        rv += "}";
        return rv;
    }

    public void insert( Key k ) {
        ++N;
        int[] pathToNode = getPathToNode( N );

        StdOut.println( "DEBUG: pathToNode( " + N + " ) is: " + java.util.Arrays.toString( pathToNode ) );

        Node node = getNodeFromPath( pathToNode );

        if ( node == null ) {
            StdOut.println( "DEBUG: node.value: " + node );
        } else {
            StdOut.println( "DEBUG: node.value: " + node.value );
        }

        Node newNode = new Node();
        newNode.value = k;

        if ( node == null ) {
            head = newNode;
        } else {
            if ( node.childLeft == null ) {
                node.childLeft = newNode;
            } else if ( node.childRight == null ) {
                node.childRight = newNode;
            }
            newNode.parent = node;
            swim( N );
        }

        StdOut.println( "DEBUG: inserted: " + k );
    }

    public boolean less( Node a, Node b ) {
        return a.value.compareTo( b.value ) == -1;
    }

    public void exchange( Node a, Node b ) {
        if ( ( a == null ) || ( b == null ) ) {
            return;
        }

        Key temp = a.value;
        a.value = b.value;
        b.value = temp;
    }

    public void swim( int k ) {
        Node parent = getNodeFromPath( getPathToNode( k ) );

        if ( parent.childRight == null ) {
            // Swim childLeft
            Node ptr = parent.childLeft;
            while ( ptr != null && less( ptr.parent, ptr ) ) {
                exchange( ptr.parent, ptr );
                ptr = ptr.parent;
            }
        } else {
            // Swim childRight
            Node ptr = parent.childRight;
            while ( ptr != null && less( ptr.parent, ptr ) ) {
                exchange( ptr.parent, ptr );
                ptr = ptr.parent;
            }
        }

        StdOut.println( "DEBUG: Swimming: " + getNodeFromPath( getPathToNode( k ) ).value );
    }

    public Key delMax() {
        Key max = head.value;
        Node leafParent = getNodeFromPath( getPathToNode( N ) );
        if ( leafParent.childRight != null ) {
            exchange( head, leafParent.childRight );
            leafParent.childRight = null;
        } else {
            exchange( head, leafParent.childLeft );
            leafParent.childLeft = null;
        }
        sink( 1 );
        --N;
        return max;
    }

    public void sink( int k ) {
        Node parent = getNodeFromPath( getPathToNode( k ) );
        Node ptr = null;

        if ( parent == null ) {
            // This is head
            ptr = parent;
        } else {
            // This is not head
            if ( parent.childRight != null ) {
                ptr = parent.childRight;
            } else {
                ptr = parent.childLeft;
            }
        }

        while ( ptr != null ) {
            Node largestChildPtr = parent.childLeft;

            if ( largestChildPtr == null ) {
                return;
            } else if ( parent.childRight != null ) {
                if ( less( largestChildPtr, parent.childRight ) ) {
                    largestChildPtr = parent.childRight;
                }

                if ( less( parent, largestChildPtr ) ) {
                    exchange( parent, largestChildPtr );
                }
            }
            parent = largestChildPtr;
        }
    }

    public Key max() {
        return head.value;
    }

    public int[] getPathToNode( int nodeIdx ) {
        /* // DEBUG
        N = nodeIdx + 1;
        // END OF DEBUG */
        int[] path = new int[ (int)( Math.log( N ) / Math.log( 2 ) ) + 1 ];
        for ( int i = 0; i < path.length; ++i ) {
            path[ i ] = -1;
        }

        while ( nodeIdx > 0 ) {
            path[ (int)( Math.log( nodeIdx ) / Math.log( 2 ) ) ] = nodeIdx / 2;
            nodeIdx /= 2;
        }
        return path;
    }

    public Node getNodeFromPath( int[] path ) {
        Node ptr = head;
        for ( int i = 2; i < path.length && path[ i ] > -1; ++i ) {
            if ( path[ i ] % 2 == 0 ) {
                ptr = ptr.childLeft;
            } else {
                ptr = ptr.childRight;
            }
        }
        return ptr;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MaxPQExplicitLinks1< Integer > maxPQ = new MaxPQExplicitLinks1< Integer >();

        for ( int i = 0; i < intArr.length; ++i ) {
            maxPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: maxPQ (BEFORE): " + maxPQ.toString() );
        StdOut.println( "DEBUG: maxPQ (AFTER): " + maxPQ.toStringDelMax() );

        /* // DEBUG
        StdOut.println( "DEBUG: getPathToNode: " + java.util.Arrays.toString( maxPQ.getPathToNode( 10 ) ) );
        StdOut.println( "DEBUG: getPathToNode: " + java.util.Arrays.toString( maxPQ.getPathToNode( 9 ) ) );
        StdOut.println( "DEBUG: getPathToNode: " + java.util.Arrays.toString( maxPQ.getPathToNode( 8 ) ) );
        StdOut.println( "DEBUG: getPathToNode: " + java.util.Arrays.toString( maxPQ.getPathToNode( 7 ) ) );
        StdOut.println( "DEBUG: getPathToNode: " + java.util.Arrays.toString( maxPQ.getPathToNode( 6 ) ) );
        // END OF DEBUG */
    }
}
