package com.company;
import edu.princeton.cs.algs4.*;

public class SequentialBinarySearchSTCaching {

    public static class SequentialSearchSTCaching< Key extends Comparable< Key >, Value > {

        private class Node {
            Key key = null;
            Value value = null;
            Node next = null;

            public String toString() {
                return " | " + this.key + " : " + this.value + " | ";
            }
        }

        private Node head = null;
        private int N = 0;
        private Node mostRecentlyAccessed = null;

        public SequentialSearchSTCaching() {
            // Not implemented
        }

        public void put( Key key, Value value ) {
            if ( mostRecentlyAccessed != null && key.compareTo( mostRecentlyAccessed.key ) == 0 ) {
                mostRecentlyAccessed.value = value;
                return;
            }

            Node ptr = head;
            Node beforePtr = null;
            while ( ptr != null ) {
                if ( ptr.key.compareTo( key ) == 0 ) {
                    ptr.value = value;
                    mostRecentlyAccessed = ptr;
                    return;
                }
                beforePtr = ptr;
                ptr = ptr.next;
            }

            Node newNode = new Node();
            newNode.key = key;
            newNode.value = value;
            if ( beforePtr != null ) {
                if ( ptr == null ) {
                    beforePtr.next = newNode;
                }
            } else {
                head = newNode;
            }
            mostRecentlyAccessed = newNode;
            ++N;
        }

        public boolean contains( Key key ) {
            return get( key ) != null;
        }

        public int size() {
            return N;
        }

        public boolean isEmpty() {
            return size() == 0;
        }

        public Value get( Key key ) {
            if ( mostRecentlyAccessed != null && key.compareTo( mostRecentlyAccessed.key ) == 0 ) {
                return mostRecentlyAccessed.value;
            }

            Node ptr = head;
            while ( ptr != null ) {
                if ( ptr.key.compareTo( key ) == 0 ) {
                    mostRecentlyAccessed = ptr;
                    return ptr.value;
                }
                ptr = ptr.next;
            }
            return null;
        }

        public void delete( Key key ) {
            Node ptr = head;
            Node beforePtr = head;
            while ( ptr != null ) {
                if ( ptr.key.compareTo( key ) == 0 ) {
                    mostRecentlyAccessed = beforePtr;
                    break;
                }
                beforePtr = ptr;
                ptr = ptr.next;
            }

            if ( beforePtr != null ) {
                if ( ptr != null ) {
                    mostRecentlyAccessed = beforePtr;
                    beforePtr.next = ptr.next;
                }
            }
        }

        public void deleteMax() {
            delete( max() );
        }

        public void deleteMin() {
            delete( min() );
        }

        public int rank( Key key ) {
            int rankCount = 0;
            Node ptr = head;
            while ( ptr != null ) {
                if ( ptr.key.compareTo( key ) < 0 ) {
                    ++rankCount;
                }
            }
            return rankCount;
        }

        public Iterable< Key > keys( Key low, Key high ) {
            Queue< Key > q = new Queue< Key >();
            if ( low.compareTo( high ) > 0 ) return q;
            Node ptr = head;
            while ( ptr != null ) {
                if ( ptr.key.compareTo( low ) >= 0 && ptr.key.compareTo( high ) <= 0 ) {
                    q.enqueue( ptr.key );
                }
                ptr = ptr.next;
            }
            return q;
        }

        public Iterable< Key > keys() {
            return keys( min(), max() );
        }

        public Key min() {
            Node ptr = head;
            Node min = null;
            while ( ptr != null ) {
                if ( min == null || ptr.key.compareTo( min.key ) < 0 ) {
                    min = ptr;
                }
                ptr = ptr.next;
            }
            mostRecentlyAccessed = min;
            return min.key;
        }

        public Key max() {
            Node ptr = head;
            Node max = null;
            while ( ptr != null ) {
                if ( max == null || ptr.key.compareTo( max.key ) > 0 ) {
                    max = ptr;
                }
                ptr = ptr.next;
            }
            mostRecentlyAccessed = max;
            return max.key;
        }

        public String toString() {
            String rv = "{ ";
            Node ptr = head;

            while ( ptr != null ) {
                rv += ptr.key + ", ";
                ptr = ptr.next;
            }

            rv += "}";
            if ( mostRecentlyAccessed != null ) {
                rv += " ; mostRecentlyAccessed : " + mostRecentlyAccessed.key.toString();
            } else {
                rv += " ; mostRecentlyAccessed : null";
            }
            return rv;
        }
    }

    public static class BinarySearchSTCaching< Key extends Comparable< Key >, Value > {

        private Key[] keys;
        private Value[] values;
        private int N = 0;
        private int mostRecentlyAccessed = -1;

        public BinarySearchSTCaching( int cap ) {
            keys = ( Key[] )new Comparable[ cap ];
            values = ( Value[] )new Object[ cap ];
        }

        public void put( Key key, Value value ) {
            int i = rank( key );
            if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
                values[ i ] = value;
                return;
            }

            for ( int j = N; j > i; --j ) {
                keys[ j ] = keys[ j - 1 ];
                values[ j ] = values[ j - 1 ];
            }
            keys[ i ] = key;
            values[ i ] = value;
            mostRecentlyAccessed = i;
            ++N;
        }

        public int size() {
            return N;
        }

        public boolean isEmpty() {
            return size() == 0;
        }

        public boolean contains( Key key ) {
            return get( key ) != null;
        }

        public Value get( Key key ) {
            int i = rank( key );
            if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
                mostRecentlyAccessed = i;
                return values[ i ];
            }
            return null;
        }

        public int rank( Key key ) {
            int low = 0;
            int high = N - 1;
            while ( low <= high ) {
                int mid = low + ( high - low ) / 2;
                int cmp = key.compareTo( keys[ mid ] );
                if ( cmp < 0 ) {
                    high = mid - 1;
                } else if ( cmp > 0 ) {
                    low = mid + 1;
                } else {
                    return mid;
                }
            }
            return low;
        }

        public void delete( Key key ) {
            int i = rank( key );
            if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
                for ( int j = N - 1; j >= i; --j ) {
                    keys[ j ] = keys[ j + 1 ];
                    values[ j ] = values[ j + 1 ];
                }

                if ( mostRecentlyAccessed <= N && mostRecentlyAccessed >= i ) {
                    --mostRecentlyAccessed;
                }
            }
        }

        public void deleteMin() {
            delete( min() );
        }

        public void deleteMax() {
            delete( max() );
        }

        public Key min() {
            mostRecentlyAccessed = 0;
            return keys[ 0 ];
        }

        public Key max() {
            mostRecentlyAccessed = N - 1;
            return keys[ N - 1 ];
        }

        public String toString() {
            return "\nkeys : " + java.util.Arrays.toString( keys ) + "\nvalues : " + java.util.Arrays.toString( values ) + "\nmostRecentlyAccessed : " + mostRecentlyAccessed + "\nkeys[ mostRecentlyAccessed ] : " + keys[ mostRecentlyAccessed ];
        }
    }

    public static void main( String[] args ) {
        Integer[] strArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        // SequentialSearchSTCaching
        SequentialBinarySearchSTCaching.SequentialSearchSTCaching< Integer, Integer > st =
                new SequentialBinarySearchSTCaching.SequentialSearchSTCaching< Integer, Integer >();
        for ( int i = 0; i < strArr.length; ++i ) {
            st.put( strArr[ i ], intArr[ i ] );
        }

        StdOut.println( "DEBUG: st: " + st.toString() );
        StdOut.println( "DEBUG: st: " + st.get( 10 ) );
        StdOut.println( "DEBUG: st.mostRecentlyAccessed: " + st.mostRecentlyAccessed.toString() );

        // BinarySearchSTCaching
        SequentialBinarySearchSTCaching.BinarySearchSTCaching< Integer, Integer > st1 =
                new SequentialBinarySearchSTCaching.BinarySearchSTCaching< Integer, Integer >( strArr.length );
        for ( int i = 0; i < strArr.length; ++i ) {
            st1.put( strArr[ i ], intArr[ i ] );
        }

        StdOut.println( "DEBUG: st1: " + st1.toString() );
        StdOut.println( "DEBUG: st1: " + st1.get( 10 ) );
        StdOut.println( "DEBUG: st1.mostRecentlyAccessed: " + st.mostRecentlyAccessed.toString() );
    }
}
