package bgu.spl.net.srv.ClientFrames;

import bgu.spl.net.srv.*;

import java.util.List;

public abstract class ClientFrame extends Frame {

    protected ConnectionImp connectionImp;

    public ClientFrame(String title, List<String> headers, String body) {
        super(title, headers, body);
    }

    public void setConnectionImp(ConnectionImp connectionImp) {
        this.connectionImp = connectionImp;
    }

    public ConnectionImp getConnectionImp() {
        return connectionImp;
    }

    public abstract void execute(int connectionId, ConnectionImp<Frame> connections, StompMessagingProtocolImp protocolImp);

    @Override
    public String toString() {
        return null;
    }
}
