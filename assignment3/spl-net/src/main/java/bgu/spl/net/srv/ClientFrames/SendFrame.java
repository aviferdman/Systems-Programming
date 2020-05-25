package bgu.spl.net.srv.ClientFrames;

import bgu.spl.net.srv.ConnectionImp;
import bgu.spl.net.srv.Frame;
import bgu.spl.net.srv.StompMessagingProtocolImp;

import java.util.List;

public abstract class SendFrame extends ClientFrame {

    public SendFrame(String title, List<String> headers, String body) {
        super(title, headers, body);
    }

    public abstract void execute(int connectionId, ConnectionImp<Frame> connections, StompMessagingProtocolImp protocolImp);
}
