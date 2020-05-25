package bgu.spl.net.srv;

import bgu.spl.net.srv.Data.Data;

import java.util.List;

public class ConnectionImp <T> implements Connections <T> {

    public ConnectionImp (){
        //this.connectionId_connectionHandler = Data.getInstance().getConnectionId_connectionHandler();
    }

    public void addClientToConnection (int client_connection_Id, ConnectionHandler connectionHandler){
        Data.getInstance().getConnectionId_connectionHandler().putIfAbsent(client_connection_Id, connectionHandler);
    }

    @Override
    //Sends a message T to client represented by the given connectionId
    public boolean send(int connectionId, T msg) {
        ConnectionHandler connectionHandler = Data.getInstance().getConnectionId_connectionHandler().get(connectionId);
        try {
            synchronized (connectionHandler) {
                connectionHandler.send(msg);
            }
            return true;
        }
        catch (Exception e){
            return false;
        }
    }

    @Override
    //Sends a message T to clients subscribed to channel
    public void send(String channel, T msg) {
        List<User> clients= Data.getInstance().getSubscribersOfChannel(channel);
        for (User client : clients) {
            int connection = Data.getInstance().getConnectionOfUser(client);
            send(connection, msg);
        }
    }

    @Override
    //Removes an active client connectionId from the maps
    public void disconnect(int connectionId) {
        //remove from all the maps but remember the user and password
        Data.getInstance().disconnect_connectionId(connectionId);
        Data.getInstance().getConnectionId_connectionHandler().remove(connectionId);
    }

    public ConnectionHandler getConnecctionHandlerById (int id){
        ConnectionHandler c= Data.getInstance().getConnectionId_connectionHandler().get(id);
        return c;
    }
}
