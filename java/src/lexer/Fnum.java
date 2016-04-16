package lexer;

/**
 * Created by inksmallfrog on 16-3-22.
 */
public class Fnum extends Token {
    private final float value;
    public Fnum(int t, float f){
        super(t);
        value = f;
    }
}
