package bgu.spl.mics.application.passiveObjects;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

//import sun.text.resources.CollationData;

/**
 * Passive object representing the diary where all reports are stored.
 * <p>
 * This class must be implemented safely as a thread-safe singleton.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You can add ONLY private fields and methods to this class as you see fit.
 */
public class Diary {

	private List<Report> reports;
	private AtomicInteger total;
	private static Diary instance = null;

	synchronized public static Diary getInstance() {
		if (instance == null) {
			instance = new Diary();
		}
		return instance;
	}

	private Diary(){
		this.reports = new ArrayList<>();
		total = new AtomicInteger(0);
	}
	/**
	 * Retrieves the single instance of this class.
	 */

	public List<Report> getReports() {
		synchronized (reports) {
			return reports;
		}
	}

	/**
	 * adds a report to the diary
	 * @param reportToAdd - the report to add
	 */
	public void addReport(Report reportToAdd){
		synchronized (reports) {
			this.reports.add(reportToAdd);
		}
	}

	/**
	 *
	 * <p>
	 * Prints to a file name @filename a serialized object List<Report> which is a
	 * List of all the reports in the diary.
	 * This method is called by the main method in order to generate the output.
	 */
	public void printToFile(String filename){
		Gson gson = new GsonBuilder()
				.setPrettyPrinting()
				.create();

		String json = gson.toJson(this);
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

	/**
	 * Gets the total number of received missions (executed / aborted) be all the M-instances.
	 * @return the total number of received missions (executed / aborted) be all the M-instances.
	 */
	public int getTotal(){
		synchronized (this) {
			return total.get();
		}
	}

	public int inc()
	{
		return this.total.incrementAndGet();
	}
}
