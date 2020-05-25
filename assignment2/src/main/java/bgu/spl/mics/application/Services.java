package bgu.spl.mics.application;

public class Services {
    private int M;
    private int Moneypenny;
    private JsonReaderMission [] intelligence;
    private int time;

    public int getM() {
        return M;
    }

    public int getMoneyPenny() {
        return Moneypenny;
    }

    public JsonReaderMission[] getIntelligence() {
        return intelligence;
    }

    public int getTime() {
        return time;
    }

    public void setM(int M) {
        this.M = M;
    }

    public void setMoneyPenny(int moneyPenny) {
        this.Moneypenny = moneyPenny;
    }

    public void setIntelligence(JsonReaderMission[] intelligence) {
        this.intelligence = intelligence;
    }

    public void setTime(int time) {
        this.time = time;
    }
}
