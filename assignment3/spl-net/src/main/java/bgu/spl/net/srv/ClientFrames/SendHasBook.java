package bgu.spl.net.srv.ClientFrames;

import bgu.spl.net.srv.ConnectionImp;
import bgu.spl.net.srv.Data.Data;
import bgu.spl.net.srv.Frame;
import bgu.spl.net.srv.ServerFrames.Message;
import bgu.spl.net.srv.ServerFrames.ServerFrame;
import bgu.spl.net.srv.StompMessagingProtocolImp;
import bgu.spl.net.srv.User;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

public class SendHasBook extends SendFrame {

    public SendHasBook(String title, List<String> headers, String body) {
        super(title, headers, body);
    }

    @Override
    public void execute(int connectionId, ConnectionImp<Frame> connections, StompMessagingProtocolImp protocolImp) {
        Data data = Data.getInstance();
        String title = "MESSAGE";
        List<String> headers = new ArrayList<>();
        String genre = getHeaders().get(0);
        ConcurrentHashMap<User, String> usersToSend = Data.getInstance().getChannel_clients_subId().get(genre);
        if (usersToSend==null) return;
        for (User u : usersToSend.keySet()) {
            Integer connectionToSendId = data.findConnectionByUser(u);
            String sub_id = usersToSend.get(u);
            String message_id = "" + data.getMessageId();
            headers.add(sub_id);
            headers.add(message_id);
            headers.add(genre);
            String body = getBody();
            ServerFrame message = new Message(title, headers, body);
            message.setMy_message_id(data.getMessageId());
            data.incMessageId();
            connections.send(connectionToSendId, message);
        }
    }
}
