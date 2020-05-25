package bgu.spl.net.srv.ServerFrames;

import java.util.List;

public class Error extends ServerFrame {
    public Error(String title, List<String> headers, String body) {
        super(title, headers, body);
    }

    @Override
    public String toString() {
        String output = "ERROR\n";
        output = output + "receipt-id: "+getHeaders().get(0)+"\n";
        //output = output + "message: "+getHeaders().get(1)+"\n";
        output = output+""+"\n";
        output = output+"The message: "+ getBody() +"\n";
        return output;
    }
}
