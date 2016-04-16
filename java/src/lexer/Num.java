package lexer;

/**
 * Created by inksmallfrog on 16-3-22.
 */
public class Num extends Token{
    private final int value;
    public Num(int t){
        super(Tag.NUM);
        value = t;
    }
}
