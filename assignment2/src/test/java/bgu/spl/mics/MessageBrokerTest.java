package bgu.spl.mics;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class MessageBrokerTest {

    private Subscriber s1;
    private Subscriber s2;
    SomeEvent e;
    SomeBroadcast b;
    SomeCallback c;

    MessageBroker msg  = MessageBrokerImpl.getInstance(); // Get / Create singleton object

    @BeforeEach
    public void setUp(){
        s1 = new Subscriber("Avi") {
            @Override
            protected void initialize() {

            }
        };
        s2 = new Subscriber("Benny") {
            @Override
            protected void initialize() {

            }
        };
        e = new SomeEvent();
        c = new SomeCallback();
        b = new SomeBroadcast();
    }

    @Test
    public void test(){
        TestUnregisterSubscribers();
        RegisterSubscriberAndGetMessage();
        RegisterSecondSubscriber();
        SubscribeBothSubscribers();
        UnregisterFirstSubscriber();
        CheckBroadcastAgain();
        checkBothUnregisteredSubscribers();
        TestGetInstance();
    }

    //Test unregister Subscribers
    private void TestUnregisterSubscribers () {
        assertThrows(IllegalStateException.class, () -> msg.awaitMessage(s1));
        assertThrows(IllegalStateException.class, () -> msg.awaitMessage(s2));
    }

    //Test register Subscribers and messages
    private void RegisterSubscriberAndGetMessage() {
        msg.register(s1);
        msg.subscribeEvent(e.getClass(), s1);

        Future<Integer> future = msg.sendEvent(e);

        try {
            assertEquals(e, msg.awaitMessage(s1));
        } catch (Exception e) {
            fail();
        }
    }

    private void RegisterSecondSubscriber() {
        msg.register(s2);
    }

    //Test two Subscribe 2 Subscribers To Broadcast And Get Message
    private void SubscribeBothSubscribers()
    {
        msg.subscribeBroadcast(b.getClass(), s1);
        msg.subscribeBroadcast(b.getClass(), s2);

        msg.sendBroadcast(b);

        try{
            assertEquals(b, msg.awaitMessage(s1));
            assertEquals(b, msg.awaitMessage(s2));
        }
        catch (Exception e){
            fail();
        }
    }

    //Test unregister subscriber
    private void UnregisterFirstSubscriber()
    {
        msg.unregister(s1);
    }

    //Test
    private void CheckBroadcastAgain()
    {
        msg.sendBroadcast(b);
        try{
            //s2 still get messages
            assertEquals(b, msg.awaitMessage(s2));
        }
        catch (Exception e){
            fail();
        }
        //exception expected
        assertThrows(IllegalStateException.class, () -> msg.awaitMessage(s1));
    }

    //Test unregister both subscribers
    private void checkBothUnregisteredSubscribers(){
        msg.unregister(s2);
        //exceptions expected
        assertThrows(IllegalStateException.class, () -> msg.awaitMessage(s1));
        assertThrows(IllegalStateException.class, () -> msg.awaitMessage(s2));
    }

    //Test Singleton
    private void TestGetInstance() {
        try {
            MessageBroker msg2 = MessageBrokerImpl.getInstance();
            assertNotNull(msg2);
            assertEquals(msg,msg2);
        }
        catch (Exception e){
            fail();
        }

    }
}
