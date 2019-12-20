package com.company;
import edu.princeton.cs.algs4.*;
import java.io.File;

public class ListingFiles {

    private Queue< File > queue;

    public ListingFiles() {
        queue = new Queue< File >();
    }

    public void printFilesRecursively( File file ) {
        queue.enqueue( file );
        String dirSpace = "";
        String fileSpace = "  ";

        while ( ! queue.isEmpty() ) {
            File folder = queue.dequeue();
            StdOut.println( dirSpace + folder.getName() + "/" );

            if ( queue.isEmpty() ) {
                dirSpace += "  ";
                fileSpace += "  ";
            }

            File[] listOfFiles = folder.listFiles();
            for ( int i = 0; i < listOfFiles.length; ++i ) {
                if ( listOfFiles[ i ].isDirectory() ) {
                    queue.enqueue( listOfFiles[ i ] );
                } else {
                    StdOut.println( fileSpace + listOfFiles[ i ].getName() );
                }
            }
        }
    }

    public static void main( String[] args ) {
        File file = new File( "/Users/phongvcao/Downloads" );
        ListingFiles listingFiles = new ListingFiles();
        listingFiles.printFilesRecursively( file );
    }
}
