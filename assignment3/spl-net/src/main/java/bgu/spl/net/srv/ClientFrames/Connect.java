package bgu.spl.net.srv.ClientFrames;

import bgu.spl.net.srv.*;
import bgu.spl.net.srv.Data.Data;
import bgu.spl.net.srv.ServerFrames.Connected;
import bgu.spl.net.srv.ServerFrames.Error;
import bgu.spl.net.srv.ServerFrames.ServerFrame;

import java.util.ArrayList;
import java.util.List;

public class Connect extends ClientFrame{

    public Connect(String title, List<String> headers, String body) {
        super(title, headers, body);
    }

    @Override
    public void execute(int connectionId, ConnectionImp<Frame> connections,StompMessagingProtocolImp protocolImp) {

        Data data = Data.getInstance();
        String version = getHeaders().get(0);
        String host = getHeaders().get(1);
        String userName = getHeaders().get(2);
        String password = getHeaders().get(3);
        User user = new User(userName,password,false,version,host);
        if (data.isExist(user)
        && (user.getPassword().equals(data.getUser(user.getClientId()).getPassword())
        &!data.getUser(user.getClientId()).isLogin())) {//the user exists, the password correct and the user isn't login
            user = data.getUser(user.getClientId());
            user.setLogin(true);
            String title = "CONNECTED";
            List<String> headers = new ArrayList<>();
            headers.add(user.getAccept_version());
            String body = "";
            ServerFrame frame = new Connected(title, headers, body);
            frame.setMy_message_id(data.getMessageId());
            data.incMessageId();
            data.addUserIfNotExists(connectionId, user);
            connections.getConnecctionHandlerById(connectionId).send(frame);
        }
        else if (!data.isExist(user)){ //create new user because the user isn't exists yet
            user.setLogin(true);
            String title = "CONNECTED";
            List<String> headers = new ArrayList<>();
            headers.add(user.getAccept_version());
            String body = "";
            Frame frame = new Connected(title, headers, body);
            data.addUserIfNotExists(connectionId, user);
            connections.getConnecctionHandlerById(connectionId).send(frame);
        }
        else if(!user.getPassword().equals(data.getUser(user.getClientId()).getPassword())){ //the password isn't correct
            String title = "ERROR";
            List<String> headers = new ArrayList<>();
            headers.add("Login Error");
            String body = "Wrong Password";
            ServerFrame frame = new Error(title, headers, body);
            frame.setMy_message_id(data.getMessageId());
            data.incMessageId();
            connections.getConnecctionHandlerById(connectionId).send(frame);
            protocolImp.setShouldTerminate(true);
        }
        else if (data.getUser(user.getClientId()).isLogin()){ //the user isn't login
            String title = "ERROR";
            List<String> headers = new ArrayList<>();
            headers.add("Login Error");
            String body = "User already logged in";
            ServerFrame frame = new Error(title, headers, body);
            frame.setMy_message_id(data.getMessageId());
            data.incMessageId();
            connections.getConnecctionHandlerById(connectionId).send(frame);
            protocolImp.setShouldTerminate(true);
        }
    }
}
