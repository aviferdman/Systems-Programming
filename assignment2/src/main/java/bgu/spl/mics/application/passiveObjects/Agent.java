package bgu.spl.mics.application.passiveObjects;

/**
 * Passive data-object representing a information about an agent in MI6.
 * You must not alter any of the given public methods of this class. 
 * <p>
 * You may add ONLY private fields and methods to this class.
 */
public class Agent {

	/**
	 * Sets the serial number of an agent.
	 */
	private String serialNumber;
	private String name;
	private Boolean isAvailable;

	public void setSerialNumber(String serialNumber) {
		synchronized (this) {
			this.serialNumber = serialNumber;
		}
	}
	public Agent (){
		this.isAvailable = true;
	}

	/**
	 * Retrieves the serial number of an agent.
	 * <p>
	 * @return The serial number of an agent.
	 */
	public String getSerialNumber() {
			return this.serialNumber;
	}

	/**
	 * Sets the name of the agent.
	 */
	public void setName(String name) {
		synchronized (this) {
			this.name = name;
		}
	}

	/**
	 * Retrieves the name of the agent.
	 * <p>
	 * @return the name of the agent.
	 */
	public String getName() {
			return name;
	}

	/**
	 * Retrieves if the agent is available.
	 * <p>
	 * @return if the agent is available.
	 */
	public boolean isAvailable() {
			return isAvailable;
	}

	/**
	 * Acquires an agent.
	 */
	public void acquire(){
		synchronized (this) {
			this.isAvailable = false;
		}
	}

	/**
	 * Releases an agent.
	 */
	public void release(){
		synchronized (this) {
			this.isAvailable = true;
		}
	}
}
