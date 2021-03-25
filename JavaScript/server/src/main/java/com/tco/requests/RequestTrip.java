package com.tco.requests;

import com.tco.misc.BadRequestException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import com.tco.misc.ProcessTrip;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class RequestTrip extends RequestHeader{

    private final transient Logger log = LoggerFactory.getLogger(RequestTrip.class);
    private HashMap<String, String> options = new HashMap<>();
    private ArrayList<HashMap<String, String>> places = new ArrayList<>();
    private ArrayList<Long> distances = new ArrayList<>();
    // Notes?

    public RequestTrip() {
        this.requestType = "trip";
        this.requestVersion = RequestHeader.CURRENT_SUPPORTED_VERSION;
    }

    public RequestTrip(HashMap<String, String> options, ArrayList<HashMap<String, String>> places) {
        this();
        this.options.put("earthRadius", options.get("earthRadius"));
        String[] optionalParameters = {"title", "units", "response"};
        for (String currParam : optionalParameters) {
            String currOption = options.get(currParam);
            if (currOption != null) {
                this.options.put(currParam, options.get(currParam));
            }
        }
        this.places = places;
    }

    public RequestTrip(HashMap<String, String> options, ArrayList<HashMap<String, String>> places, ArrayList<Long> distances) {
        this(options, places);
        this.distances = distances;
    }

    public void setTitle(String title) {
        this.options.put("title", title);
    }

    public void setUnits(String units){
        this.options.put("units", units);
    }

    public void setResponse(String response){
        this.options.put("response", response);
    }

    public void setEarthRadius(double earthRadius) {
        this.options.put("earthRadius", "" + earthRadius);
    }

    public String getTitle() {
        return options.get("title");
    }

    public Double getEarthRadius() {
        return Double.parseDouble(options.get("earthRadius"));
    }

    public String getUnits() {
        return options.get("units");
    }

    public String getResponse() {
        return options.get("response");
    }

    public ArrayList<HashMap<String, String>> getPlaces() {
        return places;
    }

    public HashMap<String, String> getOptions() {
        return options;
    }

    public ArrayList<Long> getDistances() {
        return distances;
    }

    @Override
    public void buildResponse() {
        // Helper file calls
        long responseMilliseconds = 100000000; //27 hours
        if(this.getResponse() != null && !this.getResponse().equals("0.0")){
            double response = Double.parseDouble(this.getResponse());
            responseMilliseconds = (long)((response * 1000) - 100);//-0.1s to play it safe
        }
        ProcessTrip newTrip = new ProcessTrip();
        long[][] distanceTable = newTrip.createDistanceTable(places, Double.parseDouble(options.get("earthRadius")), responseMilliseconds);
        if(distanceTable[places.size() - 1][places.size() -1] != -69696969){
            //if distance table didn't get stopped early, optimize
            int[] route = newTrip.optimizePlaces(distanceTable, places);
            places = newTrip.restructureTrip(route, places);
            distances = newTrip.computeDistancesWTable(distanceTable, route);
        }
        else {
            distances = newTrip.computeDistances(places, Double.parseDouble(options.get("earthRadius")));
        }
        log.trace("buildResponse -> {}", this);
    }
}