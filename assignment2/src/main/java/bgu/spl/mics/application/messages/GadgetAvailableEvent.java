package bgu.spl.mics.application.messages;

import bgu.spl.mics.*;
import bgu.spl.mics.application.passiveObjects.Report;

public class GadgetAvailableEvent implements Message, Event {

    private String gadget;

    private Report r;

    private int Qtime;

    public GadgetAvailableEvent(String gadget) {
        this.gadget = gadget;
    }

    public GadgetAvailableEvent(String gadget, Report r, int QTime) {
        this.gadget = gadget;
        this.Qtime = QTime;
        this.r = r;
        r.setQTime(this.Qtime);
    }

    public String getGadget() {
        return this.gadget;
    }

    public int getQTime() {
        return this.Qtime;
    }
}