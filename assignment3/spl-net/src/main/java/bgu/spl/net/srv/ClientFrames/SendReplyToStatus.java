package bgu.spl.net.srv.ClientFrames;

import bgu.spl.net.srv.ConnectionImp;
import bgu.spl.net.srv.Data.Data;
import bgu.spl.net.srv.Frame;
import bgu.spl.net.srv.ServerFrames.Message;
import bgu.spl.net.srv.ServerFrames.ServerFrame;
import bgu.spl.net.srv.StompMessagingProtocolImp;

import java.util.ArrayList;
import java.util.List;

public class SendReplyToStatus extends SendFrame {

    public SendReplyToStatus(String title, List<String> headers, String body) {
        super(title, headers, body);
    }

    @Override
    public void execute(int connectionId, ConnectionImp<Frame> connections, StompMessagingProtocolImp protocolImp) {
        Data data = Data.getInstance();
        String title = "MESSAGE";
        List<String> headers = new ArrayList<>();
        String genre = getHeaders().get(0);
        //send a unique message to all subscribers
        data.getChannel_clients_subId().get(genre).forEach((user, integer) -> {
            Integer connectionToSendId = data.findConnectionByUser(user);
            String sub_id = integer.toString();
            String message_id = ""+data.getMessageId();
            headers.add(sub_id);
            headers.add(message_id);
            headers.add(genre);
            String body = getBody();
            ServerFrame message = new Message(title, headers, body);
            message.setMy_message_id(data.getMessageId());
            data.incMessageId();
            connections.send(connectionToSendId, message);
        });
    }
}
