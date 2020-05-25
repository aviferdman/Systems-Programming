package bgu.spl.mics.application;

import bgu.spl.mics.application.passiveObjects.MissionInfo;

public class JsonReaderMission {
    private MissionInfo[] missions;

    public MissionInfo[] getMissions() {
        return missions;
    }

    public void setMissions(MissionInfo[] missions) {
        this.missions = missions;
    }
}
