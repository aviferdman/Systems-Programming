package bgu.spl.net.srv.ServerFrames;

import java.util.List;

public class Message extends ServerFrame{

    public Message(String title, List<String> headers, String body) {
        super(title, headers, body);
    }

    @Override
    public String toString() {
        String output = "MESSAGE\n";
        output = output + "subscription:"+getHeaders().get(0)+"\n";
        output = output + "Message-id:"+getHeaders().get(1)+"\n";
        output = output + "destination:"+getHeaders().get(2)+"\n";
        output = output+""+"\n";
        output = output+ getBody() +"\n";
        return output;
    }

}
