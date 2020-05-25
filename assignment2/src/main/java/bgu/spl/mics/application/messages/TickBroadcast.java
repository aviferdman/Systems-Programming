package bgu.spl.mics.application.messages;


import bgu.spl.mics.*;
public class TickBroadcast implements Message, Broadcast {

    private int tick;
    public int getTick() {
        return tick;
    }
    public void setTick(int tick) {
        this.tick = tick;
    }
}
