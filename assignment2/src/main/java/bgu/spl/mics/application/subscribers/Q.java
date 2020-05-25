package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Callback;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.passiveObjects.Inventory;

/**
 * Q is the only Subscriber\Publisher that has access to the {@link bgu.spl.mics.application.passiveObjects.Inventory}.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class Q extends Subscriber {

	private Inventory i = Inventory.getInstance();
	private String id;
	private int numberOfM;
	private boolean isMissionOver = false;
	private Callback <TickBroadcast> tickBroadcastCallback = c -> setTime(c.getTick());
	private Callback <TerminateBroadcast> shouldTerminate = c -> {
		isMissionOver = true;
	};
	private Callback <FinalTerminateBroadcast> finalTerminateBroadcast = c -> {
		setNumberOfM(getNumberOfM()-1);
		if (getNumberOfM() == 0) {
			terminate();
		}
	};

	public int getNumberOfM() {
		return numberOfM;
	}

	public Q(String id) {
		super("Q");
		this.id = id;
	}

	public void setNumberOfM(int numberOfM) {
		this.numberOfM = numberOfM;
	}

	protected void initialize() {

		//tells the inventory that the session is done
		subscribeBroadcast(TerminateBroadcast.class, (shouldTerminate));

		//register to tick broadcast
		subscribeBroadcast(TickBroadcast.class, tickBroadcastCallback);

		//register to its unique terminate broadcast
		subscribeBroadcast(FinalTerminateBroadcast.class, finalTerminateBroadcast);

		Callback<GadgetAvailableEvent> callback = g -> {
			if (i.getItem(g.getGadget())) {
				//the gadget is available
				//let the M know if the session over and if so, returns that the gadget is unavailable
				complete(g, !isMissionOver);
			}
			else {
				complete(g, false);
			}
		};

		//register to gadget available event
		subscribeEvent(GadgetAvailableEvent.class,callback);
	}
}