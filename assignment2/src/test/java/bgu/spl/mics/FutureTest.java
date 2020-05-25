package bgu.spl.mics;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.concurrent.TimeUnit;

import static org.junit.jupiter.api.Assertions.*;

public class FutureTest {
    private Future <String> future1;
    private Future <Integer> future2;
    private String s;
    private Integer i;
    @BeforeEach
    public void setUp(){

        future1 = new Future<>();
        future2 = new Future<>();
        s="returned value";
        i=10;

    }

    @Test
    public void test(){
        //TODO: change this test and add more tests :)
        testResolve();
        testGetWithTimeout();
        testGetWithoutTimeout();
        testIsDone();
    }

    //Test if future is done
    private void testIsDone() {
        assertFalse(future1.isDone());
        assertFalse(future2.isDone());
        future1.resolve(s);
        assertFalse(future2.isDone());
        assertTrue(future1.isDone());
        future2.resolve(i);
        assertTrue(future2.isDone());
    }

    //test the get method without timeout - can block
    private void testGetWithoutTimeout() {
        try {
            future1.resolve(s);
            future2.resolve(i);
            assertNotNull(future1.get());
            assertNotNull(future2.get());
            assertEquals(s,future1.get());
            assertEquals(i,future2.get());
        }catch (Exception e){
            fail();
        }
    }

    //test the get method with timeout - doesn't block
    private void testGetWithTimeout() {
        try {
            /*Callable<String> sleep1000 = () -> {
                Thread.sleep(1000);
                return s;
            };

            Callable<Integer> sleep4000 = () -> {
                Thread.sleep(4000);
                return i;
            };

            future1.get(3000, TimeUnit.MILLISECONDS);
            future1.resolve(sleep1000.call());

            future2.get(3000, TimeUnit.MILLISECONDS);
            future2.resolve(sleep4000.call());

            assertEquals(s, future1.get());
            assertTrue(future1.isDone());

            assertNull(future2.get());
            assertFalse(future2.isDone());*/
            future1.resolve(s);
            future2.resolve(i);
            assertNotNull(future1.get(300, TimeUnit.MILLISECONDS));
            assertNotNull(future2.get(400, TimeUnit.MILLISECONDS));
            assertEquals(s,future1.get(300, TimeUnit.MILLISECONDS));
            assertEquals(i,future2.get(400, TimeUnit.MILLISECONDS));
        }

        catch (Exception e){
            fail();
        }
    }

    //Test resolve returned value
    private void testResolve() {
        try {
            assertFalse(future1.isDone());
            future1.resolve(s);
            assertNotNull(future1.get());
            assertEquals(s, future1.get());
            assertTrue(future1.isDone());
        }
        catch (Exception e){
            fail();
        }
    }
}