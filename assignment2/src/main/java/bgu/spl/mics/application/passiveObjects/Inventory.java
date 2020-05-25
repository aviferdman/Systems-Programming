package bgu.spl.mics.application.passiveObjects;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 *  That's where Q holds his gadget (e.g. an explosive pen was used in GoldenEye, a geiger counter in Dr. No, etc).
 * <p>
 * This class must be implemented safely as a thread-safe singleton.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You can add ONLY private fields and methods to this class as you see fit.
 */
public class Inventory {
	private List<String> gadgets;
	/**
	 * Retrieves the single instance of this class.
	 */
	private boolean isMissionOver;
	private static class SingletonHolder {

		private static Inventory instance = new Inventory();
	}
	private Inventory() {
		if (getInstance() == null){
			setGadgets(new ArrayList<>());
			this.isMissionOver = false;
		}
	}

	public void setGadgets(List<String> gadgets) {
		this.gadgets = gadgets;
	}

	public static Inventory getInstance() {
		return SingletonHolder.instance;
	}

	/**
	 * Initializes the inventory. This method adds all the items given to the gadget
	 * inventory.
	 * <p>
	 * @param inventory 	Data structure containing all data necessary for initialization
	 * 						of the inventory.
	 */
	public void load (String[] inventory) {
		for(int i=0; i < inventory.length; i++) {
			gadgets.add(i, inventory[i]);
		}
	}

	/**
	 * acquires a gadget and returns 'true' if it exists.
	 * <p>
	 * @param gadget 		Name of the gadget to check if available
	 * @return 	‘false’ if the gadget is missing, and ‘true’ otherwise
	 */
	public boolean getItem(String gadget){
		synchronized (this) {
			if (this.gadgets.contains(gadget)) {
				gadgets.remove(gadget);
				return true&!isMissionOver;
			}
			return false;
		}
	}

	/**
	 *
	 * <p>
	 * Prints to a file name @filename a serialized object List<String> which is a
	 * list of all the of the gadgeds.
	 * This method is called by the main method in order to generate the output.
	 */
	public void printToFile(String filename){
		Gson gson = new GsonBuilder()
				.create();

		String json = gson.toJson(this.gadgets);

		File myFile = new File(filename);
		try {
			myFile.createNewFile();
		} catch (IOException e) {
			e.printStackTrace();
		}
		FileOutputStream fOut = null;
		try {
			fOut = new FileOutputStream(myFile);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		OutputStreamWriter myOutWriter =new OutputStreamWriter(fOut);
		try {
			myOutWriter.append(json);
		} catch (IOException e) {
			e.printStackTrace();
		}
		try {
			myOutWriter.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		try {
			fOut.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
