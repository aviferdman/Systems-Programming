package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Callback;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.passiveObjects.Squad;

/**
 * Only this type of Subscriber can access the squad.
 * Three are several Moneypenny-instances - each of them holds a unique serial number that will later be printed on the report.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class Moneypenny extends Subscriber {

	private Squad s = Squad.getInstance();
	private int numberOfM = 0;
	private String id;

	private Callback<TickBroadcast> tickBroadcastCallback = c -> setTime(c.getTick());
	private Callback <TerminateBroadcast> shouldTerminate = c -> terminate();
	private Callback <FinalTerminateBroadcast> finalTerminateBroadcast = c -> {
		setNumberOfM(getNumberOfM()-1);
		if (getNumberOfM() == 0) {
			terminate();
		}
	};

	public Moneypenny(String id) {
		super("MoneyPenny");
		this.id = id;
	}

	public int getNumberOfM() {
		return numberOfM;
	}

	public void setNumberOfM(int numberOfM) {
		this.numberOfM = numberOfM;
	}

	@Override
	protected void initialize() {

		//register to tick broadcast
		subscribeBroadcast(TickBroadcast.class, tickBroadcastCallback);

		//register to it's unique terminate broadcast
		subscribeBroadcast(FinalTerminateBroadcast.class, finalTerminateBroadcast);

		Callback<AgentsAvailableEvent> callback = agentsAvailableEvent -> {
			agentsAvailableEvent.getR().setMoneypenny(Integer.parseInt(id));
			agentsAvailableEvent.getR().setAgentsNames(s.getAgentsNames(agentsAvailableEvent.getAgents()));
			if (s.getAgents(agentsAvailableEvent.getAgents())) {
				complete(agentsAvailableEvent, true);
			} else {
				complete(agentsAvailableEvent, false);
			}
		};

		Callback<SendAgentsToMissionEvent> callback2 = sendAgentsEvent -> s.sendAgents(sendAgentsEvent.getSerialNumbers(), sendAgentsEvent.getDurantion());

		Callback<ReleaseAgentsEvent> callback3 = releaseAgentsEvent -> s.releaseAgents(releaseAgentsEvent.getSerials());

		//register to agents available event
		subscribeEvent(AgentsAvailableEvent.class,callback);

		//register to send agents to mission event
		subscribeEvent(SendAgentsToMissionEvent.class,callback2);

		//register to release agents event
		subscribeEvent(ReleaseAgentsEvent.class,callback3);
	}
}
