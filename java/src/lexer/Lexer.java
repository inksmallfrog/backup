package lexer;

import java.io.IOException;
import java.util.Hashtable;

/**
 * Created by inksmallfrog on 16-3-22.
 */
public class Lexer {
    public int line = 1;
    private char peek = ' ';
    private Hashtable words = new Hashtable();
    void reserve(Word t){
        words.put(t.lexeme, t);
    }
    public Lexer(){
        reserve(new Word(Tag.TRUE, "true"));
        reserve(new Word(Tag.FALSE, "false"));
    }
    public Token scan() throws IOException{
        for(;;peek=(char)System.in.read()){
            if(peek == ' ' || peek == '\t'){
                continue;
            }
            else if(peek == '\n'){
                ++line;
            }
            else{
                break;
            }
        }
        if(Character.isDigit(peek)){
            int v = 0;
            do{
                v = v * 10 + Character.digit(peek, 10);
                peek = (char)System.in.read();
            }while(Character.isDigit(peek));
            if(peek == '.'){
                int fcounter = 1;
                peek = (char)System.in.read();
                while (Character.isDigit(peek)){
                    fcounter *= 10;
                    v = v * 10 + Character.digit(peek, 10);
                    peek = (char)System.in.read();
                }
                return new Fnum(Tag.FNUM, v / (fcounter * 1.0f));
            }
            return new Num(v);
        }
        else if(Character.isLetter(peek)){
            StringBuffer b = new StringBuffer();
            do{
                b.append(peek);
                peek = (char)System.in.read();
            }while(Character.isLetterOrDigit(peek));
            String s = b.toString();
            Word w = (Word)words.get(s);
            if(w != null){
                return w;
            }
            w = new Word(Tag.ID, s);
            words.put(s, w);
            return w;
        }
        switch (peek){
            case '/':
                peek = (char) System.in.read();
                switch (peek) {
                    case '/':
                        while (peek != '\n') {
                            peek = (char) System.in.read();
                        }
                        return scan();
                    case '*':
                        while (peek != '/') {
                            do {
                                peek = (char) System.in.read();
                            } while (peek != '*');
                            peek = (char) System.in.read();
                        }
                        peek = ' ';
                        return scan();
                    default:
                        Token t = new Token('/');
                        return t;
                }
            case '<':
                peek = (char)System.in.read();
                if(peek == '='){
                    peek = ' ';
                    return new Token(Tag.LEQ);
                }
                return new Token('<');
            case '>':
                peek = (char)System.in.read();
                if(peek == '='){
                    peek = ' ';
                    return new Token(Tag.BEQ);
                }
                return new Token('>');
            case '=':
                peek = (char)System.in.read();
                if(peek == '='){
                    peek = ' ';
                    return new Token(Tag.EQ);
                }
                return new Token('=');
            case '!':
                peek = (char)System.in.read();
                if(peek == '='){
                    peek = ' ';
                    return new Token(Tag.NEQ);
                }
                return new Token('!');
            case '.':
                int v = 0;
                int fcounter = 1;
                peek = (char)System.in.read();
                while (Character.isDigit(peek)){
                    fcounter *= 10;
                    v = v * 10 + Character.digit(peek, 10);
                    peek = (char)System.in.read();
                }
                return new Fnum(Tag.FNUM, v / (fcounter * 1.0f));
        }

        Token t = new Token(peek);
        peek = ' ';
        return t;
    }
}
