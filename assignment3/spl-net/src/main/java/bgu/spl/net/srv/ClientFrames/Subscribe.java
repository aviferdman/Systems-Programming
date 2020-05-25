package bgu.spl.net.srv.ClientFrames;

import bgu.spl.net.srv.*;
import bgu.spl.net.srv.Data.Data;
import bgu.spl.net.srv.ServerFrames.Receipt;
import bgu.spl.net.srv.ServerFrames.ServerFrame;

import java.util.ArrayList;
import java.util.List;

public class Subscribe extends ClientFrame {

    public Subscribe(String title, List<String> headers, String body) {
        super(title, headers, body);
    }

    @Override
    public void execute(int connectionId, ConnectionImp<Frame> connections,StompMessagingProtocolImp protocolImp) {
        String genre = getHeaders().get(0);
        Data data = Data.getInstance();
        String receipt_id = getHeaders().get(2);
        String title = "RECEIPT";
        List<String> headers = new ArrayList<>();
        headers.add(receipt_id);
        String body = "";
        ServerFrame frame = new Receipt(title, headers, body);
        frame.setMy_message_id(data.getMessageId());
        data.incMessageId();
        User user = data.getUsers().get(connectionId);
        String subId = getHeaders().get(1);
        data.subscribe(subId, genre, user);
        connections.getConnecctionHandlerById(connectionId).send(frame);
    }
}




