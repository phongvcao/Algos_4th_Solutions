package com.company;
import java.text.SimpleDateFormat;
import java.util.Date;
import edu.princeton.cs.algs4.*;
import java.text.DateFormat;

public class ReadDates {
    public static void main( String[] args ) {
        Date[] dates = readDates( "10/23/1992 11/07/1994" );
        for ( int i = 0; i < dates.length; ++i ) {
            SimpleDateFormat df = new SimpleDateFormat( "yyyy.MM.dd" );
            StdOut.println( "DATE: " + df.format( dates[ i ] ) );
        }
    }

    public static Date strToDate( String dateStr ) {
        String[] fields = dateStr.split( "/" );
        StdOut.println( "DEBUG: fields: " + java.util.Arrays.toString( fields ) );
        return new Date( Integer.parseInt( fields[ 2 ] ), Integer.parseInt( fields[ 0 ] ), Integer.parseInt( fields[ 1 ] ) );
    }

    public static Date[] readDates( String line ) {
        String[] dates = line.split( "\\s+" );
        Queue< Date > q = new Queue< Date >();
        DateFormat sdf = new SimpleDateFormat( "MM/dd/yyyy" );

        for ( int i = 0; i < dates.length; ++i ) {
            try {
                q.enqueue( sdf.parse( dates[ i ] ) );
            } catch ( java.text.ParseException e ) {
                // Do nothing
            }
        }

        int N = q.size();
        Date[] a = new Date[ N ];
        for ( int i = 0; i < N; ++i ) {
            a[ i ] = q.dequeue();
        }
        return a;
    }
}
