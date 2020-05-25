package bgu.spl.mics.application.messages;

import bgu.spl.mics.Event;
import bgu.spl.mics.Message;
import bgu.spl.mics.application.passiveObjects.MissionInfo;

public class MissionReceivedEvent implements Message, Event  {

    private MissionInfo MI;

    public MissionReceivedEvent(MissionInfo MI){
        this.MI = MI;
    }

    public MissionInfo getMI() {
        return MI;
    }

}
