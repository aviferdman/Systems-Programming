package bgu.spl.mics.application;

import bgu.spl.mics.MessageBroker;
import bgu.spl.mics.MessageBrokerImpl;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Inventory;
import bgu.spl.mics.application.passiveObjects.MissionInfo;
import bgu.spl.mics.application.passiveObjects.Squad;
import bgu.spl.mics.application.publishers.TimeService;
import bgu.spl.mics.application.subscribers.Intelligence;
import bgu.spl.mics.application.subscribers.M;
import bgu.spl.mics.application.subscribers.Moneypenny;
import bgu.spl.mics.application.subscribers.Q;
import com.google.gson.Gson;
import com.google.gson.stream.JsonReader;

import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/** This is the Main class of the application. You should parse the input file,
 * create the different instances of the objects, and run the system.
 * In the end, you should output serialized objects.
 */
public class MI6Runner {
    public static void main(String[] args) {
        // TODO Implement this
        Gson gson = new Gson();
        try {
            int id=0;
            JsonReader reader = new JsonReader(new FileReader(args[0]));
            MyJsonReader j = gson.fromJson(reader, MyJsonReader.class);

            //Load inventory
            Inventory inventory = Inventory.getInstance();
            inventory.load(j.getInventory());

            //Load Squad
            Squad squad = Squad.getInstance();
            squad.load(j.getSquad());

            List<Thread> threads = new ArrayList<>();
            List<Subscriber> ser = new ArrayList<>();

            Services s = j.getServices();

            MessageBroker msg = MessageBrokerImpl.getInstance();

            int numOfM = 0;
            for(int i=0; i<s.getM(); i++){
                ser.add(new M(Integer.toString(++id)));
                numOfM++;
            }
            for(int i=0; i<s.getMoneyPenny(); i++){
                Moneypenny m = new Moneypenny(Integer.toString(++id));
                m.setNumberOfM(numOfM);
                ser.add(m);
            }
            Q q = new Q("newQ");
            q.setNumberOfM(numOfM);
            ser.add(q);

            //loading Missions and Intelligence
            for (int i=0; i<j.getServices().getIntelligence().length; i=i+1){
                Intelligence intelligence = new Intelligence(Integer.toString(++id));
                MissionInfo [] array = j.getServices().getIntelligence()[i].getMissions();
                intelligence.SetMissionInfo(array);
                ser.add(intelligence);
            }

            //define Time service
            TimeService timeService = TimeService.getInstance();
            timeService.setDuration(j.getServices().getTime());

            //wake up all the Threads
            for (Subscriber subscriber : ser) {
                msg.register(subscriber);
            }
            for (Subscriber subscriber : ser) {
                Thread thread = new Thread(subscriber, subscriber.getName());
                threads.add(thread);
                thread.start();
            }
            Thread th = new Thread(timeService);
            threads.add(th);
            th.start();
            for (Thread thread : threads){
                try {
                    thread.join();
                }
                catch (Exception ignored){

                }
            }

            //Output
            inventory.printToFile(args[1]);
            Diary d = Diary.getInstance();
            d.printToFile(args[2]);
        }

        //if the file path illegal
        catch (IOException e){
            System.out.println("File doesn't exist");
        }
    }
}
