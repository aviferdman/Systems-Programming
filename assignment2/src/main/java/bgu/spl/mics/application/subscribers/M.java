package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Callback;
import bgu.spl.mics.Event;
import bgu.spl.mics.Future;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.passiveObjects.Agent;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Report;
/*import bgu.spl.mics.application.passiveObjects.Squad;
import bgu.spl.mics.application.publishers.TimeService;
import com.google.gson.internal.$Gson$Preconditions;
import com.sun.jmx.mbeanserver.Repository;*/

import java.util.List;
import java.util.concurrent.TimeUnit;

/**
 * M handles ReadyEvent - fills a report and sends agents to mission.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class M extends Subscriber {

	private Diary d = Diary.getInstance();

	private String id;

	private Report r;

	Callback<TickBroadcast> tickBroadcastCallback = new Callback<TickBroadcast>() {
		@Override
		public void call(TickBroadcast c) {
			setTime(c.getTick());
		}
	};

	private Callback <TerminateBroadcast> terminateBroadcastCallback = new Callback<TerminateBroadcast>() {
		@Override
		public void call(TerminateBroadcast c) {
			getSimplePublisher().sendBroadcast(new FinalTerminateBroadcast());
			terminate();
		}
	};

	public M(String id) {
		super("M");
		this.id = id;
	}


	@Override
	protected void initialize() {

		//register to M's kind of terminate broadcast
		subscribeBroadcast(TerminateBroadcast.class, terminateBroadcastCallback);

		Callback<MissionReceivedEvent> callback = new Callback<MissionReceivedEvent>() {
			public void call(MissionReceivedEvent m) {
				d.inc();
				r=new Report();
				// 1. Check Agents
				Event e = new AgentsAvailableEvent(m.getMI().getSerialAgentsNumbers(),r);
				Future<Boolean> hasAgents = getSimplePublisher().sendEvent(e);
				Boolean b1 = hasAgents.get(m.getMI().getTimeExpired()-m.getMI().getDuration(), TimeUnit.MILLISECONDS);
				if (hasAgents != null) {
					if (b1!=null&&b1) {
						// 2. Check gadget
						Future<Boolean> hasGadgets = getSimplePublisher().sendEvent(new GadgetAvailableEvent(m.getMI().getGadget(),r,getTime()));
						Boolean b2 = hasGadgets.get();
						if (hasGadgets != null) {
							if (b2!=null&&b2&getTime() <= m.getMI().getTimeExpired()) {
								getSimplePublisher().sendEvent(new SendAgentsToMissionEvent(m.getMI().getSerialAgentsNumbers(),m.getMI().getDuration()));
								try {
									//M is doing a mission
									//she *still* get broadcasts and events
									Thread.sleep(m.getMI().getDuration()*100);
								}
								catch (Exception e1){

								}
								//generate a report of the mission
								//d.inc();
								makeReport(m);
							}
							else {
								// 3. Release agents
								Future<List<String>> serials = getSimplePublisher().sendEvent(new ReleaseAgentsEvent(m.getMI().getSerialAgentsNumbers()));
							}
						}
						else {
							// 3. Release agents
							Future<List<String>> serials = getSimplePublisher().sendEvent(new ReleaseAgentsEvent(m.getMI().getSerialAgentsNumbers()));
						}
					}
				}
			}
		};

		//register to mission received event
		subscribeEvent(MissionReceivedEvent.class,callback);

		//register to tick broadcast
		subscribeBroadcast(TickBroadcast.class, tickBroadcastCallback);
	}


	private void makeReport(MissionReceivedEvent m){
		r.setMissionName(m.getMI().getMissionName());
		r.setM(Integer.parseInt(id));
		r.setAgentsSerialNumbersNumber(m.getMI().getSerialAgentsNumbers());
		r.setGadgetName(m.getMI().getGadget());
		r.setTimeIssued(m.getMI().getTimeIssued());
		r.setTimeCreated(getTime());
		d.addReport(r);
	}
}