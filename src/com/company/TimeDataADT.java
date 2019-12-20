package com.company;
import edu.princeton.cs.algs4.*;

public class TimeDataADT {

    private static class Time implements Comparable< Time > {
        private int hours = 0;
        private int minutes = 0;
        private int seconds = 0;
        private String time = null;

        public Time( String timeStr ) {
            String[] strArr = timeStr.split( ":" );
            this.hours = Integer.parseInt( strArr[ 0 ] );
            this.minutes = Integer.parseInt( strArr[ 1 ] );
            this.seconds = Integer.parseInt( strArr[ 2 ] );
            this.time = timeStr;
        }

        public int compareTo( Time other ) {
            if ( this.hours < other.hours ) {
                return -1;
            } else if ( this.hours > other.hours ) {
                return 1;
            }

            if ( this.minutes < other.minutes ) {
                return -1;
            } else if ( this.minutes > other.minutes ) {
                return 1;
            }

            if ( this.seconds < other.seconds ) {
                return -1;
            } else if ( this.seconds > other.seconds ) {
                return 1;
            }

            return 0;
        }

        public String toString() {
            return this.time;
        }
    }

    private static class Event {
        public String place = null;

        public Event( String place ) {
            this.place = place;
        }

        public String toString() {
            return this.place;
        }
    }

    private static class EventBinarySearchST< Key extends Comparable< Key >, Value > {

        private Key[] keys;
        private Value[] values;
        private int N = 0;

        public EventBinarySearchST( int cap ) {
            keys = ( Key[] )new Comparable[ cap ];
            values = ( Value[] )new Object[ cap ];
        }

        public void put( Key key, Value value ) {
            int i = rank( key );
            if ( i < N && keys[ i ].compareTo( key ) == 0 ) {
                values[ i ] = value;
            } else {
                for ( int j = N; j > i; --j ) {
                    keys[ j ] = keys[ j - 1 ];
                    values[ j ] = values[ j - 1 ];
                }
                keys[ i ] = key;
                values[ i ] = value;
            }
            ++N;
        }

        public boolean contains( Key key ) {
            return get( key ) != null;
        }

        public int rank( Key key ) {
            int low = 0;
            int high = N - 1;
            while ( low <= high ) {
                int mid = low + ( high - low ) / 2;
                if ( less( key, keys[ mid ] ) ) {
                    high = mid - 1;
                } else if ( less( keys[ mid ], key ) ) {
                    low = mid + 1;
                } else {
                    return mid;
                }
            }
            return low;
        }

        public Value get( Key key ) {
            int i = rank( key );
            if ( keys[ i ].compareTo( key ) == 0 ) {
                return values[ i ];
            }
            return null;
        }

        private boolean less( Comparable a, Comparable b ) {
            return a.compareTo( b ) == -1;
        }

        public int size() {
            return N;
        }

        public boolean isEmpty() {
            return size() == 0;
        }

        public String toString() {
            return "\nkeys : " + java.util.Arrays.toString( keys ) + "\nvalues : " + java.util.Arrays.toString( values );
        }
    }

    public static void main( String[] args ) {
        String[] strArr = { "09:37:44", "09:36:14", "09:35:21", "09:25:52", "09:22:54", "09:22:43", "09:21:05",
                            "09:19:46", "09:19:32", "09:14:25", "09:10:25", "09:10:11", "09:03:13", "09:01:10",
                            "09:00:59", "09:00:13", "09:00:03", "09:00:00" };
        String[] citiesArr = { "09:37:44", "09:36:14", "09:35:21", "09:25:52", "09:22:54", "09:22:43", "09:21:05",
                "09:19:46", "09:19:32", "09:14:25", "09:10:25", "09:10:11", "09:03:13", "09:01:10",
                "09:00:59", "09:00:13", "09:00:03", "09:00:00" };
        /* String[] citiesArr = { "Chicago", "Houston", "Chicago", "Seattle", "Seattle", "Phoenix", "Chicago", "Chicago",
                               "Chicago", "Seattle", "Seattle", "Chicago", "Chicago", "Seattle", "Phoenix", "Houston",
                               "Phoenix", "Chicago" }; */
        EventBinarySearchST< Time, Event > eventBSST = new EventBinarySearchST< Time, Event >( strArr.length );

        for ( int i = 0; i < strArr.length; ++i ) {
            eventBSST.put( new Time( strArr[ i ] ), new Event( citiesArr[ i ] ) );
        }

        StdOut.println( "DEBUG: eventBSST: " + eventBSST.toString() );
    }
}
