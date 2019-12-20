package com.company;
import edu.princeton.cs.algs4.*;

public class MaxPQExplicitLinks< Key extends Comparable< Key > > {

    private class Node {
        Key value = null;
        Node parent = null;
        Node childLeft = null;
        Node childRight = null;
        int size = 0;
    }

    private Node head = null;
    private int N = 0;

    public MaxPQExplicitLinks() {
        // Not implemented
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public boolean less( Key a, Key b ) {
        return a.compareTo( b ) == -1;
    }

    public String toString( Node node ) {
        String str = "";
        if ( node != null ) {
            str += node.value + ", ";
        } else {
            return "";
        }

        // DEBUG
        StdOut.print( "DEBUG: node.value: " + node.value );
        if ( node.childLeft != null ) {
            StdOut.print( "; node.childLeft.value: " + node.childLeft.value );
            StdOut.print( "; node.childLeft.parent: " + node.childLeft.parent.value );
        }
        if ( node.childRight != null ) {
            StdOut.print( "; node.childRight.value: " + node.childRight.value );
            StdOut.print( "; node.childRight.parent: " + node.childRight.parent.value );
        }
        StdOut.println( "\n============" );
        // END OF DEBUG

        return str + toString( node.childLeft ) + toString( node.childRight );
    }

    public String toString() {
        String rv = "";
        Node ptr = head;

        rv += toString( head );

        rv = "{ " + rv + " }";
        return rv;
    }

    public String toStringDelMax() {
        String rv = "{ ";


        while ( ! isEmpty() ) {
            StdOut.println( "DEBUG: BEFORE DELMAX" );
            rv += delMax() + ", ";
            StdOut.println( "DEBUG: AFTER DELMAX" );
        }


        rv += "}";
        return rv;
    }

    public void insert( Key k ) {
        Node newNode = new Node();
        newNode.value = k;

        if ( head == null ) {
            head = newNode;
        } else {
            // Find the right node
            Node root = new Node();
            Node smallestRoot = getSmallerRoot( head, root );
            if ( smallestRoot.childLeft == null ) {
                smallestRoot.childLeft = newNode;
            } else if ( smallestRoot.childRight == null ) {
                smallestRoot.childRight = newNode;
            }
            newNode.parent = smallestRoot;
            /* Node ptr = head;
            while ( ptr != null ) {
                if ( ptr.childLeft == null ) {
                    ptr.childLeft = newNode;
                    break;
                } else if ( ptr.childRight == null ) {
                    ptr.childRight = newNode;
                    break;
                } else {
                    if ( ptr.childLeft.size < ptr.childRight.size ) {
                        ptr = ptr.childLeft;
                    } else {
                        ptr = ptr.childRight;
                    }
                    ++ptr.size;
                }
            } */
            /* // Insert at the end
            if ( tail.childLeft == null ) {
                tail.childLeft = newNode;
            } else {
                tail.childRight = newNode;
                tail = tail.childLeft;
            }
            newNode.parent = tail; */
        }
        swim( newNode );
        ++N;
    }

    public Node getSmallerRoot( Node root, Node result ) {
        if ( root.childLeft == null ) {
            ++result.size;
            return root;
        } else if ( root.childRight == null ) {
            ++result.size;
            return root;
        } else {
            Node leftResult = new Node();
            Node rootLeft = getSmallerRoot( root.childLeft, leftResult );
            Node rightResult = new Node();
            Node rootRight = getSmallerRoot( root.childRight, rightResult );

            result.size = leftResult.size < rightResult.size ? leftResult.size + 1 : rightResult.size + 1;
            return leftResult.size < rightResult.size ? rootLeft : rootRight;
        }
    }

    public Key max() {
        return head.value;
    }

    public boolean equal( Key a, Key b ) {
        return a.compareTo( b ) == 0;
    }

    public Node getDeepestLeaf( Node root, Node result ) {
        Node leafLeft = null;
        Node leafRight = null;
        Node leftResult = new Node();
        Node rightResult = new Node();
        if ( root.childLeft != null ) {
            return getDeepestLeaf( root.childLeft, leftResult );
        } else if ( root.childRight != null ) {
            return getDeepestLeaf( root.childRight, rightResult );
        } else {
            return root;
        }
    }

    public Key delMax() {
        Key max = head.value;
        Node root = new Node();
        Node smallestRoot = getDeepestLeaf( head, root );
        if ( ( smallestRoot.childLeft == null ) && ( smallestRoot.childRight == null ) ) {
            exchange( smallestRoot, head );

            if ( ( smallestRoot.parent.childLeft != null ) && ( equal( smallestRoot.parent.childLeft.value, smallestRoot.value ) ) ) {
                smallestRoot.parent.childLeft = null;
            } else if ( ( smallestRoot.parent.childRight != null ) && ( equal( smallestRoot.parent.childRight.value, smallestRoot.value ) ) ) {
                smallestRoot.parent.childRight = null;
            }
        } else if ( smallestRoot.childRight == null ) {
            exchange( smallestRoot.childLeft, head );
            smallestRoot.childLeft = null;
        } else if ( smallestRoot.childLeft == null ) {
            exchange( smallestRoot.childRight, head );
            smallestRoot.childRight = null;
        } else {
            exchange( smallestRoot.childRight, head );
            smallestRoot.childRight = null;
        }
        sink( head );
        --N;
        return max;
    }

    public void exchange( Node node1, Node node2 ) {
        Key temp = node1.value;
        node1.value = node2.value;
        node2.value = temp;
    }

    public void swim( Node node ) {
        while ( ( node.parent != null ) && ( less( node.parent.value, node.value ) ) ) {
            StdOut.println( "DEBUG: Swapping parent: " + node.parent.value + " with child: " + node.value );
            exchange( node.parent, node );
            node = node.parent;
        }
    }

    public void sink( Node node ) {
        StdOut.println( "DEBUG: Sinking: " + node.value );

        while ( node != null ) {
            Node nodeToSwap = null;
            if ( ( node.childLeft != null ) && ( node.childRight != null ) ) {
                nodeToSwap = node.childLeft;
                if ( less( nodeToSwap.value, node.childRight.value ) ) {
                    nodeToSwap = node.childRight;
                }
            } else if ( node.childLeft != null ) {
                nodeToSwap = node.childLeft;
            } else if ( node.childRight != null ) {
                nodeToSwap = node.childRight;
            } else {
                nodeToSwap = null;
            }
            if ( nodeToSwap == null ) return;
            if ( ! less( node.value, nodeToSwap.value ) ) return;
            exchange( node, nodeToSwap );
            node = nodeToSwap;
        }
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MaxPQExplicitLinks< Integer > maxPQ = new MaxPQExplicitLinks< Integer >();

        for ( int i = 0; i < intArr.length; ++i ) {
            maxPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: maxPQ (BEFORE): " + maxPQ.toString() );
        StdOut.println( "DEBUG: maxPQ (AFTER): " + maxPQ.toStringDelMax() );

    }
}
