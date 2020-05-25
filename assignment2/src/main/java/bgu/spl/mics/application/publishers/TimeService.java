package bgu.spl.mics.application.publishers;

import bgu.spl.mics.Broadcast;
import bgu.spl.mics.MessageBroker;
import bgu.spl.mics.MessageBrokerImpl;
import bgu.spl.mics.Publisher;
import bgu.spl.mics.application.messages.InteligenceTerminate;
import bgu.spl.mics.application.messages.TerminateBroadcast;
import bgu.spl.mics.application.messages.TickBroadcast;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * TimeService is the global system timer There is only one instance of this Publisher.
 * It keeps track of the amount of ticks passed since initialization and notifies
 * all other subscribers about the current time tick using {@link Tick Broadcast}.
 * This class may not hold references for objects which it is not responsible for.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */

public class TimeService extends Publisher {
	private int duration;
	private int counter;
	private Timer timer;

	public TimeService() {
		super("TimeService");
		timer = new Timer();
	}

    public void setDuration(int duration) {
		this.duration = duration;
	}

	public int getDuration() {
		return duration;
	}

	private static class SingletonHolder {
		private static TimeService instance = new TimeService();
	}

	public static TimeService getInstance() {
		return TimeService.SingletonHolder.instance;
	}

	public TimeService(int duration) {
		super("TimeService");
		this.duration = duration;
	}

	@Override
	protected void initialize() {
		this.counter = 0;
		run();
	}

	@Override
	public void run() {
		TimerTask timerTask = new TimerTask() {
			@Override
			public void run() {
				if (counter < duration) {
					//send tick if session is not done
					TickBroadcast b = new TickBroadcast();
					b.setTick(counter);
					counter++;
					getSimplePublisher().sendBroadcast(b);
				}
				else {
					//send terminate kind of broadcasts when the session is over
					TerminateBroadcast b = new TerminateBroadcast();
					InteligenceTerminate b2 = new InteligenceTerminate();
					getSimplePublisher().sendBroadcast(b);
					getSimplePublisher().sendBroadcast(b2);
					counter++;
					timer.cancel();
				}
			}
		};
		timer.scheduleAtFixedRate(timerTask, 0, 100);
	}

	public int getCounter() {
		return counter;
	}
	public void setCounter(int counter) {
		this.counter = counter;
	}
}
