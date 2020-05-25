package bgu.spl.mics.application;

import bgu.spl.mics.application.passiveObjects.Agent;

public class MyJsonReader {
    private String [] inventory;
    private Agent[] squad;
    private Services services;

    public void setInventory(String[] inventory) {
        this.inventory = inventory;
    }

    public void setSquad(Agent[] squad) {
        this.squad = squad;
    }

    public void setServices(Services services) {
        this.services = services;
    }

    public String[] getInventory() {
        return inventory;
    }

    public Agent[] getSquad() {
        return squad;
    }

    public Services getServices() {
        return services;
    }
}
