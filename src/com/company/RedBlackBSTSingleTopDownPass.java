package com.company;
import edu.princeton.cs.algs4.*;
import java.util.ArrayList;
import java.util.HashSet;

public class RedBlackBSTSingleTopDownPass< Key extends Comparable< Key >, Value > {

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
                rv += " ; left : " + this.left.key;
            } else {
                rv += " ; left : null";
            }

            if ( this.right != null ) {
                rv += " ; right : " + this.right.key;
            } else {
                rv += " ; right : null";
            }

            rv += " | \n";
            return rv;
        }

        public int compareTo( Node other ) {
            return this.key.compareTo( other.key );
        }

        public boolean equals( Node other ) {
            return this.key.compareTo( other.key ) == 0;
        }

        public int hashCode() {
            return this.key.hashCode();
        }
    }

    private Node root = null;

    public RedBlackBSTSingleTopDownPass() {
        // Not implemented
    }

    private boolean isRed( Node h ) {
        if ( h == null ) return false;
        return h.color == RED;
    }

    private Node rotateLeft( Node h ) {
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = size( h.left ) + size( h.right ) + 1;
        return x;
    }

    private Node rotateRight( Node h ) {
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = size( h.left ) + size( h.right ) + 1;
        return x;
    }

    private void flipColors( Node h ) {
        h.color = RED;
        h.left.color = BLACK;
        h.right.color = BLACK;
    }

    public void put2( Key key, Value value ) {
        Node ptr = root;
        ArrayList< Node > path = new ArrayList< Node >();
        if ( ptr == null ) {
            root = new Node( key, value, 1, RED );
            return;
        }

        while ( ptr != null ) {
            path.add( ptr );
            if ( isRed( ptr.left ) && isRed( ptr.right ) ) flipColors( ptr );
            int cmp = key.compareTo( ptr.key );
            if ( cmp < 0 ) {
                if ( ptr.left != null ) {
                    ptr = ptr.left;
                } else {
                    ptr.left = new Node( key, value, 1, RED );
                    path.add( ptr.left );
                    break;
                }
            } else if ( cmp > 0 ) {
                if ( ptr.right != null ) {
                    ptr = ptr.right;
                } else {
                    ptr.right = new Node( key, value, 1, RED );
                    path.add( ptr.right );
                    break;
                }
            } else {
                ptr.value = value;
                break;
            }
        }

        for ( int i = path.size() - 1; i >= 0; --i ) {
            // Update size & rotateLeft() & rotateRight
            Node pathPtr = path.get( i );
            pathPtr.N = size( pathPtr.left ) + size( pathPtr.right ) + 1;
            if ( i > 0 ) {
                Node prevPathPtr = path.get( i - 1 );
                // Check whether i was left or right child of i - 1
                if ( prevPathPtr.left != null && prevPathPtr.left.compareTo( pathPtr ) == 0 ) {
                    if ( isRed( prevPathPtr.left.right ) && ! isRed( prevPathPtr.left.left ) ) {
                        prevPathPtr.left = rotateLeft( prevPathPtr.left );
                    }
                    if ( isRed( prevPathPtr.left.left ) && isRed( prevPathPtr.left.left.left ) ) {
                        prevPathPtr.left = rotateRight( prevPathPtr.left );
                    }
                } else if ( prevPathPtr.right != null && prevPathPtr.right.compareTo( pathPtr ) == 0 ) {
                    if ( isRed( prevPathPtr.right.right ) && ! isRed( prevPathPtr.right.left ) ) {
                        prevPathPtr.right = rotateLeft( prevPathPtr.right );
                    }
                    if ( isRed( prevPathPtr.right.left ) && isRed( prevPathPtr.right.left.left ) ) {
                        prevPathPtr.right = rotateRight( prevPathPtr.right );
                    }
                }
            } else {
                if ( root != null && root.compareTo( pathPtr ) == 0 ) {
                    if ( isRed( root.right ) && ! isRed( root.left ) ) {
                        root = rotateLeft( root );
                    }

                    if ( isRed( root.left ) && isRed( root.left.left ) ) {
                        root = rotateRight( root );
                    }
                }
            }
        }

        root.color = BLACK;
    }

    public void put( Key key, Value value ) {
        Node ptr = root;
        ArrayList< Node > path = new ArrayList< Node >();
        if ( ptr == null ) {
            root = new Node( key, value, 1, RED );
            return;
        }

        while ( ptr != null ) {
            path.add( ptr );
            if ( isRed( ptr.left ) && isRed( ptr.right ) ) flipColors( ptr );
            int cmp = key.compareTo( ptr.key );
            if ( cmp < 0 ) {
                if ( ptr.left != null ) {
                    ptr = ptr.left;
                } else {
                    ptr.left = new Node( key, value, 1, RED );
                    path.add( ptr.left );
                    break;
                }
            } else if ( cmp > 0 ) {
                if ( ptr.right != null ) {
                    ptr = ptr.right;
                } else {
                    ptr.right = new Node( key, value, 1, RED );
                    path.add( ptr.right );
                    break;
                }
            } else {
                ptr.value = value;
                break;
            }
        }

        for ( int i = path.size() - 1; i >= 0; --i ) {
            // Update size & rotateLeft() & rotateRight
            Node pathPtr = path.get( i );
            pathPtr.N = size( pathPtr.left ) + size( pathPtr.right ) + 1;
            if ( i > 0 ) {
                Node prevPathPtr = path.get( i - 1 );
                // Check whether i was left or right child of i - 1
                if ( prevPathPtr.left != null && prevPathPtr.left.compareTo( pathPtr ) == 0 ) {
                    if ( isRed( prevPathPtr.left.right ) && ! isRed( prevPathPtr.left.left ) ) {
                        prevPathPtr.left = rotateLeft( prevPathPtr.left );
                    }
                    if ( isRed( prevPathPtr.left.left ) && isRed( prevPathPtr.left.left.left ) ) {
                        prevPathPtr.left = rotateRight( prevPathPtr.left );
                    }
                } else if ( prevPathPtr.right != null && prevPathPtr.right.compareTo( pathPtr ) == 0 ) {
                    if ( isRed( prevPathPtr.right.right ) && ! isRed( prevPathPtr.right.left ) ) {
                        prevPathPtr.right = rotateLeft( prevPathPtr.right );
                    }
                    if ( isRed( prevPathPtr.right.left ) && isRed( prevPathPtr.right.left.left ) ) {
                        prevPathPtr.right = rotateRight( prevPathPtr.right );
                    }
                }
            } else {
                if ( root != null && root.compareTo( pathPtr ) == 0 ) {
                    if ( isRed( root.right ) && ! isRed( root.left ) ) {
                        root = rotateLeft( root );
                    }

                    if ( isRed( root.left ) && isRed( root.left.left ) ) {
                        root = rotateRight( root );
                    }
                }
            }
        }

        root.color = BLACK;
    }

    public String toStringRecursively() {
        String rv = "\nROOT : " + root.key + "\n";
        rv += toStringRecursively( root );
        return rv;
    }

    public String toStringRecursively( Node h ) {
        if ( h == null ) return "";
        String rv = toStringRecursively( h.left );
        rv += h.toString();
        rv += toStringRecursively( h.right );
        return rv;
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
        Node ptr = root;
        Queue< Node > nodesQueue = new Queue< Node >();
        Queue< Integer > depthQueue = new Queue< Integer >();
        nodesQueue.enqueue( ptr );
        depthQueue.enqueue( 0 );
        Integer maxDepth = 0;
        while ( ! nodesQueue.isEmpty() ) {
            ptr = nodesQueue.dequeue();
            Integer ptrDepth = depthQueue.dequeue();
            if ( maxDepth < ptrDepth ) {
                maxDepth = ptrDepth;
            }
            if ( ptr.left != null ) {
                nodesQueue.enqueue( ptr.left );
                depthQueue.enqueue( ptrDepth + 1 );
            }
            if ( ptr.right != null ) {
                nodesQueue.enqueue( ptr.right );
                depthQueue.enqueue( ptrDepth + 1 );
            }
        }
        return maxDepth;
    }

    public String toString() {
        String rv = "\nROOT : " + root.key + "\n";
        Stack< Node > nodesStack = new Stack< Node >();
        HashSet< Node > nodesPrinted = new HashSet< Node >();
        nodesStack.push( root );

        while ( ! nodesStack.isEmpty() ) {
            Node ptr = nodesStack.pop();
            if ( ptr.left == null || nodesPrinted.contains( ptr.left ) ) {
                rv += ptr.toString();
                nodesPrinted.add( ptr );
            } else {
                if ( ptr.right != null && ! nodesPrinted.contains( ptr.right ) ) {
                    nodesStack.push( ptr.right );
                }
                nodesStack.push( ptr );
                nodesStack.push( ptr.left );
            }
        }
        return rv;
    }

    public Value get( Key key ) {
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

    public int rank( Key key ) {
        Node ptr = root;
        int rank = 0;
        while ( ptr != null ) {
            int cmp = key.compareTo( ptr.key );
            if ( cmp < 0 ) {
                ptr = ptr.left;
            } else if ( cmp > 0 ) {
                rank += size( ptr.left );
                ptr = ptr.right;
            } else {
                rank += size( ptr.left );
            }
        }
        return rank;
    }

    public Key select( int k ) {
        Node ptr = root;
        while ( ptr != null ) {
            int size = size( ptr.left );
            if ( k < size ) {
                ptr = ptr.left;
            } else if ( k > size ) {
                ptr = ptr.right;
            } else {
                return ptr.key;
            }
        }
        return null;
    }

    public Key min() {
        Node ptr = root;
        if ( ptr != null ) {
            while ( ptr.left != null ) {
                ptr = ptr.left;
            }
            return ptr.key;
        } else {
            return null;
        }
    }

    public Key max() {
        Node ptr = root;
        if ( ptr != null ) {
            while ( ptr.right != null ) {
                ptr = ptr.right;
            }
            return ptr.key;
        } else {
            return null;
        }
    }

    public Iterable< Key > keys() {
        return keys( min(), max() );
    }

    public Iterable< Key > keys( Key low, Key high ) {
        Node ptr = root;
        Stack< Node > nodesStack = new Stack< Node >();
        HashSet< Node > nodesOutputed = new HashSet< Node >();
        Queue< Key > queue = new Queue< Key >();
        nodesStack.push( root );
        while ( ! nodesStack.isEmpty() ) {
            ptr = nodesStack.pop();

            if ( ptr.left == null || ptr.left.key.compareTo( low ) < 0 || nodesOutputed.contains( ptr.left ) ) {
                queue.enqueue( ptr.key );
                nodesOutputed.add( ptr );
            } else {
                if ( ptr.right != null && ! nodesOutputed.contains( ptr.right ) && ptr.right.key.compareTo( high ) <= 0 ) {
                    nodesStack.push( ptr.right );
                }
                nodesStack.push( ptr );
                nodesStack.push( ptr.left );
            }
        }
        return queue;
    }

    public static void main( String[] args ) {
        String[] keyArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        String[] valueArr = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
        RedBlackBSTSingleTopDownPass< String, String > bst = new RedBlackBSTSingleTopDownPass< String, String >();
        for ( int i = 0; i < keyArr.length; ++i ) {
            bst.put( keyArr[ i ], valueArr[ i ] );
        }

        StdOut.println( "DEBUG: bst.toString(): " + bst.toString() );
        StdOut.println( "DEBUG: bst.toStringRecursively: " + bst.toStringRecursively() );
        StdOut.println( "DEBUG: bst.height(): " + bst.height() );
        StdOut.println( "DEBUG: bst.min(): " + bst.min() );
        StdOut.println( "DEBUG: bst.max(): " + bst.max() );
        StdOut.println( "DEBUG: bst.keys(): " + bst.keys() );
    }
}
