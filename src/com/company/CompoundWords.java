package com.company;
import edu.princeton.cs.algs4.*;
import java.util.ArrayList;
import java.util.HashSet;

import java.util.Collections;

public class CompoundWords {

    public static void main( String[] args ) {
        String[] strArr = { "after", "afterthought", "thought", "therefore", "there", "fore",
                            "before", "be", "cause", "because", "likely" };
        ArrayList< String > strList = new ArrayList< String >();
        for ( int i = 0; i < strArr.length; ++i ) {
            strList.add( strArr[ i ] );
        }

        Collections.sort( strList );
        HashSet< String > hashSet = new HashSet< String >( strList );

        for ( int i = 0; i < strList.size(); ++i ) {
            for ( int j = i + 1; j < strList.size(); ++j ) {
                if ( strList.get( j ).startsWith( strList.get( i ) ) ) {
                    String restOfWord = strList.get( j ).substring( strList.get( i ).length() );

                    if ( hashSet.contains( restOfWord ) ) {
                        StdOut.println( "DEBUG: " + strList.get( j ) );
                    }
                } else {
                    break;
                }
            }
        }
    }
}
