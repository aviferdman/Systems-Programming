package bgu.spl.net.srv;

import java.util.List;

public abstract class Frame {

    protected String title;
    protected List<String> headers;
    protected String body;
    protected boolean terminate = false;

    public Frame(String title, List<String> headers, String body) {
        this.title = title;
        this.headers = headers;
        this.body = body;
    }

    public List<String> getHeaders() {
        return headers;
    }

    public String getBody() {
        return body;
    }

    public void setHeaders(List<String> headers) {
        this.headers = headers;
    }

    public void setBody(String body) {
        this.body = body;
    }

    public boolean isTerminate() {
        return terminate;
    }

    public void setTerminate(boolean terminate) {
        this.terminate = terminate;
    }

    public abstract void execute(int connectionId, ConnectionImp<Frame> connections,StompMessagingProtocolImp protocolImp);

    @Override
    public abstract String toString ();
}
