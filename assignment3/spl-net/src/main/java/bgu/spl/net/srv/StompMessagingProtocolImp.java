package bgu.spl.net.srv;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.Data.Data;

public class StompMessagingProtocolImp <T> implements StompMessagingProtocol<Frame> {

    private boolean shouldTerminate = false;
    private int connectionId;
    private ConnectionImp<Frame> connections;
    private Data data;

    public StompMessagingProtocolImp (Data data){
        this.data = data;
    }

    @Override
    public void start(int connectionId, ConnectionImp<Frame> connections) {
        this.connectionId = connectionId;
        this.connections = connections;
    }

    @Override
    public void process(Frame message) {
        message.execute(connectionId, connections, this);
    }

    @Override
    public boolean shouldTerminate() {
        return this.shouldTerminate;
    }

    public void setShouldTerminate(boolean shouldTerminate){
        this.shouldTerminate = shouldTerminate;
    }
}
