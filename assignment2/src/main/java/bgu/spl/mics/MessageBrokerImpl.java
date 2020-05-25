package bgu.spl.mics;

import bgu.spl.mics.application.messages.MissionReceivedEvent;
import bgu.spl.mics.application.messages.TerminateBroadcast;
import bgu.spl.mics.application.passiveObjects.Diary;

import java.util.HashMap;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * The {@link MessageBrokerImpl class is the implementation of the MessageBroker interface.
 * Write your implementation here!
 * Only private fields and methods can be added to this class.
 */
public class MessageBrokerImpl implements MessageBroker {

    private HashMap<Event<?>, Future> futures;//event-future
    private HashMap<Class<? extends Message>, ConcurrentLinkedQueue<Subscriber>> MessageList;//message type-subscribers
    private HashMap<Subscriber, LinkedBlockingQueue<Message>> subscriberQueue;//subscribers-message type
    private Diary d = Diary.getInstance();

    /**
     * Retrieves the single instance of this class.
     */

    //Singleton
    private static class SingletonHolder {
        private static MessageBrokerImpl instance = new MessageBrokerImpl();
    }

    public static MessageBroker getInstance() {
        return SingletonHolder.instance;
    }

    private MessageBrokerImpl() {
        futures = new HashMap<>();
        MessageList = new HashMap<>();
        subscriberQueue = new HashMap<>();
    }

    @Override
    public <T> void subscribeEvent(Class<? extends Event<T>> type, Subscriber m) {
        MessageList.putIfAbsent(type, new ConcurrentLinkedQueue<Subscriber>());
            MessageList.get(type).add(m);
    }

    @Override
    public void subscribeBroadcast(Class<? extends Broadcast> type, Subscriber m) {
        MessageList.putIfAbsent(type, new ConcurrentLinkedQueue<>());
        MessageList.get(type).add(m);
    }

    @Override
    public <T> void complete(Event<T> e, T result) {
        Future f = futures.get(e);
        f.resolve(result);
    }

    @Override
    public void sendBroadcast(Broadcast b) {

        //if the session isn't timeout yet
        if (b.getClass()!= TerminateBroadcast.class) {
            ConcurrentLinkedQueue<Subscriber> q = MessageList.get(b.getClass());
            if (q != null) {
                q.forEach(s -> {
                    if (subscriberQueue.get(s) != null)
                        subscriberQueue.get(s).add(b);
                });
            }
        }

        //if the session timeout yet
        else {
            ConcurrentLinkedQueue<Subscriber> q = MessageList.get(b.getClass());
            if (q != null) {
                q.forEach(s -> {
                    if (subscriberQueue.get(s) != null) {
                        while (!subscriberQueue.get(s).isEmpty()){
                            if(subscriberQueue.get(s).remove() instanceof MissionReceivedEvent)
                                d.inc();
                        }
                        subscriberQueue.get(s).add(b);
                    }
                });
            }
        }
    }

    @Override
    //insert the events in a round robin manner
    public synchronized <T> Future<T> sendEvent(Event<T> e) {
        Future<T> future = new Future<>();
        futures.put(e, future);
        Subscriber s;
        ConcurrentLinkedQueue<Subscriber> q = MessageList.get(e.getClass());
        if (q == null) {
            return null;
        }

        //round robin manner
        synchronized (e.getClass()) {
            s = q.poll();
            if (s==null) {
                return null;
            }
            q.add(s);
        }

        synchronized (s) {
            LinkedBlockingQueue<Message> q2 = subscriberQueue.get(s);
            if (q2 == null) {
                return null;
            }
            q2.add(e);
        }
        return future;
    }

    @Override
    public void register(Subscriber m) {
        subscriberQueue.put(m, new LinkedBlockingQueue<>());
    }

    @Override
    public void unregister(Subscriber m) {
        MessageList.forEach((key, value) -> {
            synchronized (key) {
                value.remove(m);
            }
        });
        LinkedBlockingQueue<Message> q2;
        synchronized (m) {
            q2 = subscriberQueue.remove(m);
        }

        while (q2!=null&&!q2.isEmpty()) {
            Message msg = q2.poll();
            Future<?> f = futures.get(msg);
            if (f != null && f.isDone()) {
                f.resolve(null);
            }
        }
    }

    @Override
    public Message awaitMessage(Subscriber m) throws InterruptedException {
        //the "take" function is blocking
        try {
            LinkedBlockingQueue<Message> l = subscriberQueue.get(m);
            return l.take();
        }
        catch (Exception e){
          e.printStackTrace();
        }
        return null;
    }
}
