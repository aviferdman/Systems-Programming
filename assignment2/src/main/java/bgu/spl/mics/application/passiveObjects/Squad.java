package bgu.spl.mics.application.passiveObjects;
import java.util.*;

/**
 * Passive data-object representing a information about an agent in MI6.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You may add ONLY private fields and methods to this class.
 */
public class Squad {

	private final Map<String, Agent> agents = new HashMap<>();
	private static Squad instance = null;

	/**
	 * Retrieves the single instance of this class.
	 */
	synchronized public static Squad getInstance() {
		if (instance == null){
			instance = new Squad();
		}
		return instance;
	}

	/**
	 * Initializes the squad. This method adds all the agents to the squad.
	 * <p>
	 * @param agents 	Data structure containing all data necessary for initialization
	 * 						of the squad.
	 */

	//load an array of agents to the squad
	public void load (Agent[] agents) {
		for (Agent agent : agents) {
			this.agents.put(agent.getSerialNumber(), agent);
		}
	}

	/**
	 * Releases agents.
	 */
	//releases agents from the squad
	public void releaseAgents(List<String> serials) {
		synchronized (agents) {
			String agentid;
			for (String serial : serials) {
				agentid = serial;
				//if agents exists, release him
				if (this.agents.containsKey(agentid)) {
					this.agents.get(agentid).release();
				}
			}
		}
	}

	/**
	 * simulates executing a mission by calling sleep.
	 * @param time   milliseconds to sleep
	 */
	//send agents to missions demonstrate it by sleeping
	public void sendAgents(List<String> serials, int time) {
			try {
				Thread.sleep(time*100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			releaseAgents(serials);
	}

	/**
	 * acquires an agent, i.e. holds the agent until the caller is done with it
	 * @param serials   the serial numbers of the agents
	 * @return ‘false’ if an agent of serialNumber ‘serial’ is missing, and ‘true’ otherwise
	 */


	public boolean getAgents(List<String> serials) {
		//if there is an agent which is'nt exists return false
		for (String serial : serials) {
			if (!agents.containsKey(serial))
				return false;
		}

		// waiting them to be available
		for (String serial : serials) {
			while (!agents.get(serial).isAvailable()) {
				try {
					//going to sleep for one Tick
					//check the availability after a tick
					Thread.sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				//changes the agent so need to be synchronized
				synchronized (agents.get(serial)) {
					agents.get(serial).acquire();
				}
			}
		}
		return true;
	}
	/**
	 * gets the agents names
	 * @param serials the serial numbers of the agents
	 * @return a list of the names of the agents with the specified serials.
	 */

	//get
	public List<String> getAgentsNames(List<String> serials){
		List<String> names = new LinkedList<>();
		for (String serial : serials) {
			if (agents.containsKey(serial)) {
				names.add(this.agents.get(serial).getName());
			}
		}
		return names;
	}
}
