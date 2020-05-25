package bgu.spl.mics;

import bgu.spl.mics.application.passiveObjects.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assertions.fail;

public class SquadTest {
    private Squad s;
    private Agent[] agents;
    private Agent a;
    private Agent b;
    private List<String> serials;

    @BeforeEach
    public void setUp(){

        s = Squad.getInstance();
        agents = new Agent[2];
        a = new Agent ();
        b = new Agent ();

        a.setName("James Bond");
        a.setSerialNumber("007");
        agents[0] = a;

        b.setName("Alec Trevelyan");
        b.setSerialNumber("006");
        agents[1] = b;

        serials = new ArrayList<>();
        serials.add("007");

    }

    @Test
    public void test(){

        TestLoad();
        TestGetAgents();
        TestReleaseAgents();
        TestGetAgentsName();
        TestSendAgents();
        TestGetInstance();

    }
    //Test get agents Names
    private void TestGetAgentsName() {
        try {
            List<String> names = s.getAgentsNames(serials);
            int i = 0;
            for (String name : names) {
                assertEquals(name, agents[i].getName());
                i = i + 1;
            }
        }
        catch (Exception e){
            fail();
        }
    }

    //Test get agents
    private void TestGetAgents() {
        try {
            List<String> serials2 = new ArrayList<>();
            serials2.add("007");
            serials2.add("000");
            assertTrue(s.getAgents(serials));
            assertFalse(s.getAgents(serials2));
        }
        catch (Exception e){
            fail();
        }
    }

    //Test Singelton
    private void TestGetInstance() {
        try {
            List<String> serials2 = new ArrayList<>();
            serials2.add("007");
            serials2.add("006");
            Squad s2 = Squad.getInstance();
            assertNotNull(s2);
            assertEquals(s,s2);
            assertEquals(s.getAgents(serials2), s2.getAgents(serials2));
            assertEquals(s.getAgents(serials), s2.getAgents(serials));
            assertEquals(s.getAgentsNames(serials).get(0),s2.getAgentsNames(serials).get(0));
        }
        catch (Exception e){
            fail();
        }

    }

    //Test send available Agent to a mission
    private void TestSendAgents() {
        try {
            if (s.getAgents(serials)) {
                assertTrue(a.isAvailable());
                s.sendAgents(serials, 3000);
                Thread.sleep(3000);
                assertTrue(a.isAvailable());
            }
        } catch (Exception e) {
            fail();
        }
    }

    //Test releasing agents
    private void TestReleaseAgents() {
        try {
            List<String> serials2 = new ArrayList<>();
            serials2.add("007");
            serials2.add("006");
            s.releaseAgents(serials2);
            assertTrue(a.isAvailable());
            assertTrue(b.isAvailable());
        }
        catch (Exception e){
            fail();
        }
    }

    //Test loading agents
    public void TestLoad(){
        try {
            List<String> serials2 = new ArrayList<>();
            serials2.add("007");
            serials2.add("006");
            s.load(agents);
            assertEquals(2, s.getAgentsNames(serials2).size());
            assertEquals(a.getName(), s.getAgentsNames(serials2).get(0));
            assertEquals(b.getName(), s.getAgentsNames(serials2).get(1));
        }
        catch (Exception e){
            fail();
        }
    }

}
