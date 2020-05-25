package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Callback;
import bgu.spl.mics.Future;
import bgu.spl.mics.Publisher;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.passiveObjects.MissionInfo;

import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Comparator;

/**
 * A Publisher only.
 * Holds a list of Info objects and sends them
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class Intelligence extends Subscriber {

	//need to be here a field called load, and have a getter (for the json reader)

	private int missionId;
	private String id;
	private MissionInfo [] missionInfo;
	private Callback <TerminateBroadcast> terminateBroadcastCallback = c -> terminate();

	private Callback <InteligenceTerminate> inteligenceTerminate = c -> terminate();

	public Intelligence(String id) {
		super("Intelligence");
		this.id = id;
		this.missionId = 0;
		this.missionInfo = new MissionInfo[0];
	}

	private Callback<TickBroadcast> tickBroadcastCallback = new Callback<TickBroadcast>() {
		@Override
		public void call(TickBroadcast c) {
			int tick = c.getTick();
			setTime(tick);
			int timeIssued = missionInfo[missionId].getTimeIssued();
			if (timeIssued==getTime()&&missionId<missionInfo.length) {
				getSimplePublisher().sendEvent(new MissionReceivedEvent(missionInfo[missionId]));
				missionId++;
			}
		}
	};

	public void SetMissionInfo (MissionInfo [] missionInfos){
		this.missionInfo = missionInfos;
	}

	@Override
	protected void initialize() {

		//sort the missions by their beginnings time
		Arrays.sort(missionInfo, Comparator.comparingInt(MissionInfo::getTimeIssued));

		//register to tick broadcast
		subscribeBroadcast(TickBroadcast.class, tickBroadcastCallback);

		//register to its unique terminate broadcast
		subscribeBroadcast(InteligenceTerminate.class, inteligenceTerminate);
	}
}