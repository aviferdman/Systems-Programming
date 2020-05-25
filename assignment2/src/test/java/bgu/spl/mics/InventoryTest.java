package bgu.spl.mics;

import bgu.spl.mics.application.passiveObjects.Inventory;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.FileReader;
import java.io.Reader;
import java.util.Iterator;

import static org.junit.jupiter.api.Assertions.*;

public class InventoryTest {
    Inventory inventory;
    String[] s = new String[5];

    @BeforeEach
    public void setUp(){
        Inventory inv = Inventory.getInstance();
        for (int i=0; i<5; i=i+1){
            s[i] = "gadget"+i;
        }
    }

    @Test
    public void test(){
        TestLoadAndGet();
        TestAllItemsRemoved();
        TestPrintToJsonFile();
    }

    //Test load and get the to and from the inventory
    private void TestLoadAndGet(){
        for (int i=0;i<5;i++) {
            assertFalse(inventory.getItem("gadget"+i));
        }
        inventory.load(s);
        for (int i=0;i<5;i++) {
            assertTrue(inventory.getItem("gadget"+i));
        }
    }

    //Text removed Items after the function Get
    private void TestAllItemsRemoved() {
        for (int i=0;i<5;i++) {
            assertFalse(inventory.getItem("gadget"+i));
        }
    }

    //Test printing the inventory to files
    private void TestPrintToJsonFile() {
        inventory.load(s);
        String jsonFileName = "inventoryOutputFile.json";
        inventory.printToFile(jsonFileName); // Activate function

        JSONParser parser = new JSONParser();

        try
        {
            Reader reader = new FileReader(jsonFileName);
            assertNotNull(reader); // File should exist

            Object o = parser.parse(reader);
            JSONObject jsonObject = (JSONObject) o;

            JSONArray Gadgets = (JSONArray) jsonObject.get("Inventory");

            Iterator<String> it = Gadgets.iterator();
            while (it.hasNext())
            {
                assertTrue(inventory.getItem(it.next())); // Item should be in the file as it in the inventory
            }

            reader.close();
        } catch(Exception e) {
            fail();
        }
    }
}
