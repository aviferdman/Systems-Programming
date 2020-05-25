package bgu.spl.mics.application.passiveObjects;

import java.util.ArrayList;
import java.util.List;

/**
 * Passive data-object representing a delivery vehicle of the store.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You may add ONLY private fields and methods to this class.
 */
public class Report {
	/**
	 * Retrieves the mission name.
	 */
	private String missionName ="";
	private int M;
	private int Moneypenny;
	private List<String> agentsSerialNumbersNumber;
	private List<String> agentsNames;
	private String gadgetName;
	private Integer qTime=0;
	private Integer timeIssued=0;
	private Integer timeCreated=0;

	/**
	 * Sets the mission name.
	 */
	public Report (){
		this.agentsSerialNumbersNumber = new ArrayList<>();
		this.agentsNames = new ArrayList<>();
	}
	public void setMissionName(String missionName) {
		synchronized (this.missionName){
			this.missionName = missionName;
		}
	}

	/**
	 * Retrieves the M's id.
	 */
	public int getM() {
		return M;
	}

	/**
	 * Sets the M's id.
	 */
	public void setM(int m) {
		this.M = m;
	}

	/**
	 * Retrieves the Moneypenny's id.
	 */
	public int getMoneypenny() {
		return this.Moneypenny;
	}

	/**
	 * Sets the Moneypenny's id.
	 */
	public void setMoneypenny(int moneypenny) {
		this.Moneypenny = moneypenny;
	}

	/**
	 * Retrieves the serial numbers of the agents.
	 * <p>
	 * @return The serial numbers of the agents.
	 */
	public List<String> getAgentsSerialNumbersNumber() {
		return this.agentsSerialNumbersNumber;
	}

	/**
	 * Sets the serial numbers of the agents.
	 */
	public void setAgentsSerialNumbersNumber(List<String> agentsSerialNumbersNumber) {
		this.agentsSerialNumbersNumber = agentsSerialNumbersNumber;
	}

	/**
	 * Retrieves the agents names.
	 * <p>
	 * @return The agents names.
	 */
	public List<String> getAgentsNames() {
		synchronized (this.agentsSerialNumbersNumber){
			return new ArrayList<>(this.agentsSerialNumbersNumber);
		}
	}

	/**
	 * Sets the agents names.
	 */
	public void setAgentsNames(List<String> agentsNames) {
		synchronized (this.agentsNames){
			List<String> names = new ArrayList<>();
			this.agentsNames.addAll(agentsNames);
		}
	}

	/**
	 * Retrieves the name of the gadget.
	 * <p>
	 * @return the name of the gadget.
	 */
	public String getGadgetName() {
		synchronized (gadgetName){
			return gadgetName;
		}
	}

	/**
	 * Sets the name of the gadget.
	 */
	public void setGadgetName(String gadgetName) {
		synchronized (gadgetName){
			this.gadgetName = gadgetName;
		}
	}

	/**
	 * Retrieves the time-tick in which Q Received the GadgetAvailableEvent for that mission.
	 */
	public int getQTime() {
		synchronized (qTime){
			return qTime;
		}
	}

	/**
	 * Sets the time-tick in which Q Received the GadgetAvailableEvent for that mission.
	 */
	public void setQTime(int qTime) {
		synchronized (this.qTime){
			this.qTime = qTime;
		}
	}

	/**
	 * Retrieves the time when the mission was sent by an Intelligence Publisher.
	 */
	public int getTimeIssued() {
		synchronized (timeIssued){
			return timeIssued;
		}
	}

	/**
	 * Sets the time when the mission was sent by an Intelligence Publisher.
	 */
	public void setTimeIssued(int timeIssued) {
		synchronized (this.timeIssued){
			this.timeIssued = timeIssued;
		}
	}

	/**
	 * Retrieves the time-tick when the report has been created.
	 */
	public int getTimeCreated() {
		synchronized (this.timeCreated){
			return timeCreated;
		}
	}

	/**
	 * Sets the time-tick when the report has been created.
	 */
	public void setTimeCreated(int timeCreated) {
		synchronized (this.timeCreated){
			this.timeCreated = timeCreated;
		}
	}
}
