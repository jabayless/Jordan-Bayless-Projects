package com.tco.requests;

import com.tco.misc.DistanceCalculator;
import java.util.HashMap;

public class RequestDistance extends RequestHeader {

    protected final static Double KM_EARTH_RADIUS = 6371.0;
    protected final static Double MI_EARTH_RADIUS = 3959.0;
    protected final static Double NT_EARTH_RADIUS = 3440.0;

    private HashMap <String,String> place1 = new HashMap<>();
    private HashMap <String,String> place2 = new HashMap<>();

    private long distance;
    private Double earthRadius;

    public RequestDistance(){
        this(KM_EARTH_RADIUS,"0","0","0","0");
    }

    public RequestDistance(Double Radius, String Latitude1, String Longitude1, String Latitude2, String Longitude2){
        this.requestType = "distance";
        this.requestVersion = RequestHeader.CURRENT_SUPPORTED_VERSION;

        place1.put("latitude", Latitude1);
        place1.put("longitude",Longitude1);

        place2.put("latitude", Latitude2);
        place2.put("longitude",Longitude2);
        earthRadius = Radius;
    }

    public void setPlace1(HashMap<String, String> place1) {
        this.place1 = place1;
    }

    public void setPlace2(HashMap<String, String> place2) {
        this.place2 = place2;
    }

    public void setDistance(double distance) {
        this.distance = (long)distance;
    }

    public HashMap<String, String> getPlace1() {
        return place1;
    }

    public HashMap<String, String> getPlace2() {
        return place2;
    }

    public long getDistance() {
        return distance;
    }

    public static double getEarthRadius() {
        return KM_EARTH_RADIUS;
    }

    @Override
    public void buildResponse() {
        DistanceCalculator distanceCalculator = new DistanceCalculator(this.earthRadius);
        distance = (long)Math.round(distanceCalculator.CalculateSurfaceDistance(place1,place2));
    }
}
