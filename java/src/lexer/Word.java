package lexer;

/**
 * Created by inksmallfrog on 16-3-22.
 */
public class Word extends Token {
    public final String lexeme;
    public Word(int t, String s){
        super(t);
        lexeme = s;
    }
}
