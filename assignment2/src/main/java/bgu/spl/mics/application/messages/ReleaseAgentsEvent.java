package bgu.spl.mics.application.messages;

import bgu.spl.mics.Event;
import bgu.spl.mics.Message;

import java.util.List;

public class ReleaseAgentsEvent implements Event, Message {

    private List<String> serials;

    public ReleaseAgentsEvent(List<String> serials){
        this.serials = serials;
    }

    public List<String> getSerials() {
        return serials;
    }

    public void setSerials(List<String> serials) {
        this.serials = serials;
    }

}
