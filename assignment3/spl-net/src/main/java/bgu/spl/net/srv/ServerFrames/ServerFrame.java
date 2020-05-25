package bgu.spl.net.srv.ServerFrames;

import bgu.spl.net.srv.ConnectionImp;
import bgu.spl.net.srv.Frame;
import bgu.spl.net.srv.StompMessagingProtocolImp;

import java.util.List;

public abstract class ServerFrame extends Frame {

    private Integer my_message_id;

    public ServerFrame(String title, List<String> headers, String body) {
        super(title, headers, body);
    }

    public void execute(int connectionId, ConnectionImp<Frame> connections, StompMessagingProtocolImp protocolImp){

    }

    public Integer getMy_message_id() {
        return my_message_id;
    }

    public void setMy_message_id(Integer my_message_id) {
        this.my_message_id = my_message_id;
    }
}
