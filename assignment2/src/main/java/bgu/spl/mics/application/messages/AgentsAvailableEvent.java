package bgu.spl.mics.application.messages;

import bgu.spl.mics.*;
import bgu.spl.mics.application.passiveObjects.*;

import java.util.LinkedList;
import java.util.List;

public class AgentsAvailableEvent implements Message, Event {

    private List<String> agentsSerials;
    private List<String> agentsNames;
    private Report r;

    public AgentsAvailableEvent(List<String> agents ) {
        this.agentsSerials = agents;
    }

    public AgentsAvailableEvent(List<String> agents, Report r) {
        this.agentsSerials = agents;
        this.agentsNames = new LinkedList<>();
        this.r = r;
        r.setAgentsNames(this.agentsNames);
    }

    public List<String> getAgents() {
        return this.agentsSerials;
    }

    public List<String> getNames() {
        return this.agentsNames;
    }

    public void setNames(List<String> names) {
        this.agentsNames = names;
    }

    public Report getR() {
        return this.r;
    }
}
