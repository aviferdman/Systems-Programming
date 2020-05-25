package bgu.spl.mics.application.messages;

import bgu.spl.mics.Event;
import bgu.spl.mics.Message;

import java.util.List;


public class SendAgentsToMissionEvent implements Message, Event  {
    private  List<String> serialNumbers;
    private int durantion;


    public SendAgentsToMissionEvent(List<String> serialNumbers, int durantion) {
        this.serialNumbers = serialNumbers;
        this.durantion = durantion;
    }

    public List<String> getSerialNumbers() {
        return serialNumbers;
    }

    public int getDurantion(){
        return this.durantion;
    }
}
