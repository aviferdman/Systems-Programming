package bgu.spl.net.srv;

public class User {
    private String clientId;
    private String password;
    private boolean login;
    private String accept_version;
    private String host;

    public String getClientId() {
        return clientId;
    }

    public User(String clientId, String password, boolean login, String accept_version, String host) {
        this.clientId = clientId;
        this.password = password;
        this.login = login;
        this.accept_version = accept_version;
        this.host = host;
    }

    //getter
    public String getPassword() {
        return password;
    }

    public boolean isLogin() {
        return login;
    }

    public String getAccept_version() {
        return accept_version;
    }

    public String getHost() {
        return host;
    }

    //setter
    public void setClientId(String clientId) {
        this.clientId = clientId;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setLogin(boolean login) {
        this.login = login;
    }

    public void setAccept_version(String accept_version) {
        this.accept_version = accept_version;
    }

    public void setHost(String host) {
        this.host = host;
    }
}
