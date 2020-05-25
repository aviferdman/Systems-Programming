package bgu.spl.net.srv.Data;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.User;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class Data {

    private ConcurrentHashMap<String, ConcurrentHashMap<User,String>> channel_clients_subId;
    private ConcurrentHashMap<Integer,User> connectionId_users;
    private ConcurrentHashMap<Integer, ConnectionHandler> connectionId_connectionHandler;
    private AtomicInteger messageId;
    private static Data instance = null;

    private Data(){
        this.channel_clients_subId = new ConcurrentHashMap<>();
        this.connectionId_users = new ConcurrentHashMap<>();
        this.connectionId_connectionHandler = new ConcurrentHashMap<>();
        this.messageId = new AtomicInteger(0);
    }

    //getters
    public static Data getInstance (){
        if (instance == null){
            instance = new Data();
        }
        return instance;
    }

    public ConcurrentHashMap<String, ConcurrentHashMap<User, String>> getChannel_clients_subId() {
        return channel_clients_subId;
    }

    public ConcurrentHashMap<Integer, ConnectionHandler> getConnectionId_connectionHandler() {
        return connectionId_connectionHandler;
    }

    public ConcurrentHashMap<String, ConcurrentHashMap<User,String>> getChannel_clients() {
        return channel_clients_subId;
    }

    public ConcurrentHashMap<Integer,User> getUsers() {
        return connectionId_users;
    }

    public Integer getMessageId() {
        return messageId.get();
    }

    public List<User> getSubscribersOfChannel(String channel) {
        ArrayList list = new ArrayList();
        channel_clients_subId.get(channel).forEach((i,k)->list.add(i));
        return list;
    }

    //setters
    public void setMessageId(Integer messageId) {
        this.messageId.set(messageId);
    }

    public void setChannel_clients(ConcurrentHashMap<String, ConcurrentHashMap<User,String>> channel_clients_subId) {
        this.channel_clients_subId = channel_clients_subId;
    }

    public void setUsers(ConcurrentHashMap<Integer, User> users) {
        this.connectionId_users = users;
    }

    public void setChannel_clients_id(ConcurrentHashMap<String, ConcurrentHashMap<User, String>> channel_clients_subId) {
        this.channel_clients_subId = channel_clients_subId;
    }

    public void setConnectionId_connectionHandler(ConcurrentHashMap<Integer, ConnectionHandler> connectionId_connectionHandler) {
        this.connectionId_connectionHandler = connectionId_connectionHandler;
    }

    //methods on data base
    public void incMessageId(){
        messageId.incrementAndGet();
    }

    //check if user exists
    public boolean isExist (User user){
        boolean output = false;
        for (User u : this.connectionId_users.values()) {
            if (u.getHost().equals(user.getHost())
                    & u.getClientId().equals(user.getClientId())) {
                output = true;
                break;
            }
        }
        return output;
    }

    public void addConnectionIfNotExists (Integer id, ConnectionHandler connectionHandler){
        if (!this.connectionId_connectionHandler.containsKey(id)) {
            this.connectionId_connectionHandler.put(id, connectionHandler);
        }
    }

    public void disconnect_connectionId(int connectionId) {
        User user = connectionId_users.get(connectionId);
        ConcurrentHashMap <User, String> toRempveFrom = new ConcurrentHashMap<>();
        if (user!=null){
            user.setLogin(false);
            for (String genre : this.channel_clients_subId.keySet()) {
                toRempveFrom = channel_clients_subId.get(genre);
                break;
            }
            toRempveFrom.remove(user);
        }
    }

    public void addUserIfNotExists (int connection_id, User user){
        //the hash map of the id and the connection handler is already updated (int the connection handler)
        if(isExist(user)){
            int key = KeyOfUser(user);
            connectionId_users.remove(key);
        }
        connectionId_users.putIfAbsent(connection_id, user);
    }

    //finds the key of the user
    private int KeyOfUser(User user) {
        for (int i : connectionId_users.keySet()) {
            if (connectionId_users.get(i).getClientId().equals(user.getClientId())){
                return i;
            }
        }
        return 0;
    }

    public User getUser (String userName) {
        for (User u : this.connectionId_users.values()) {
            if (u.getClientId().equals(userName)) {
                return u;
            }
        }
        return null;
    }

    public void unsubscribe (String genre, User user){
        User toRemove = null;
        if (channel_clients_subId.containsKey(genre)) {
            for (User u : channel_clients_subId.get(genre).keySet()) {
                if (u.getClientId().equals(user.getClientId())) {
                    toRemove = u;
                    break;
                }
            }
            assert toRemove != null;
            channel_clients_subId.get(genre).remove(toRemove);
            if (channel_clients_subId.get(genre).isEmpty()){
                channel_clients_subId.remove(genre);
            }
        }
    }

    public void subscribe (String subId, String genre, User user){
        if (!channel_clients_subId.containsKey(genre)) {
            channel_clients_subId.put(genre, new ConcurrentHashMap<>());
        }
        channel_clients_subId.get(genre).put(user, subId);
    }

    public int getConnectionOfUser(User user) {
        for (Integer connection_of_user : this.connectionId_users.keySet()) {
            if (connectionId_users.get(connection_of_user) == user) {
                return connection_of_user;
            }
        }
        return -1;
    }

    public Integer findConnectionByUser(User u) {
        for (int ret : getUsers().keySet()) {
            if (getUsers().get(ret) == u) {
                return ret;
            }
        }
        return -1;
    }

    public String getGenre (int connectionId, String subId){
        User u = connectionId_users.get(connectionId);
        for (String genre : channel_clients_subId.keySet()) {
            if (channel_clients_subId.get(genre).containsKey(u) && channel_clients_subId.get(genre).get(u).equals(subId)) {
                return genre;
            }
        }
        return null;
    }
}