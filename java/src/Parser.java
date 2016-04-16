import java.io.IOException;

/**
 * Created by inksmallfrog on 16-3-22.
 */
public class Parser {
    static int look_ahead;
    public Parser() throws IOException{
        look_ahead = System.in.read();
    }
    public void expr() throws IOException{
        term();
        while(true){
            if(look_ahead == '+'){
                match('+');
                term();
                System.out.write((char)look_ahead);
            }
            else if(look_ahead == '-'){
                match('-');
                term();
                System.out.write((char)look_ahead);
            }
            else{
                return;
            }
        }
    }
    private void term() throws IOException{
        if(Character.isDigit(look_ahead)){
            System.out.write((char)look_ahead);
            match(look_ahead);
        }
        else throw new Error("Not a expr");
    }
    private void match(int t) throws IOException{
        if(look_ahead == t){
            look_ahead = System.in.read();
        }
        else throw new Error("Not a expr");
    }

    public static void main(String[] args) throws IOException{
        Parser parser = new Parser();
        parser.expr();
        System.out.write('\n');
    }
}
