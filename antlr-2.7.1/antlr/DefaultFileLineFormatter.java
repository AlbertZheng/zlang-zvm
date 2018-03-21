package antlr;

/* ANTLR Translator Generator
 * Project led by Terence Parr at http://www.jGuru.com
 * Software rights: http://www.antlr.org/RIGHTS.html
 *
 * $Id: //depot/code/org.antlr/release/antlr-2.7.1/antlr/DefaultFileLineFormatter.java#1 $
 */

public class DefaultFileLineFormatter extends FileLineFormatter {
    public String getFormatString(String fileName, int line) {
	if ( fileName != null ) {
	    return fileName+":"+line+": ";
	}
	else {
	    return "line "+line+": ";
	}
    }
};
