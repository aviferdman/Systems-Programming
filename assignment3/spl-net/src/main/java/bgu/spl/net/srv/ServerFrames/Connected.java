package bgu.spl.net.srv.ServerFrames;

import java.util.List;

public class Connected extends ServerFrame{

    public Connected(String title, List<String> headers, String body) {
        super(title, headers, body);
    }

    @Override
    public String toString() {
        String output = "CONNECTED\n";
        output = output + "version:"+getHeaders().get(0)+"\n";
        output = output+""+"\n";
        output = output+""+"\n";
        return output;
    }
}
