package bgu.spl.net.srv.ServerFrames;

import java.util.List;

public class Receipt extends ServerFrame{

    public Receipt(String title, List<String> headers, String body) {
        super(title, headers, body);
    }

    @Override
    public String toString() {
        String output = "RECEIPT\n";
        output = output + "receipt-id:"+getHeaders().get(0)+"\n";
        output = output+""+"\n";
        output = output+""+"\n";
        return output;
    }
}
