package com.tco.requests;

import com.tco.requests.RequestTrip;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.BeforeEach;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestRequestTrip {

    private double earthRadius = 3500;
    private String title = "Test Title";
    private HashMap<String, String> options = new HashMap<>();
    private ArrayList<Long> distances = new ArrayList<Long>();
    private ArrayList<HashMap<String, String>> places = new ArrayList<>();
    private HashMap<String, String> map = new HashMap<>();

    @BeforeEach
    public void createConfigurationForTestCases() {
        distances.add((long) 1);
        distances.add((long) 2);
        distances.add((long) 3);
    }

    @Test
    @DisplayName("Request type is \"trip\"")
    public void testType() {
        RequestTrip test = new RequestTrip();
        String rv = test.getRequestType();
        assertEquals("trip", rv);
    }

    @Test
    @DisplayName("Request version is \"4\"")
    public void testVersion() {
        RequestTrip test = new RequestTrip();
        Integer rv = test.getRequestVersion();
        assertEquals(4, rv);
    }

    @Test
    @DisplayName("Test setting response w/ constructor")
    public void testResponseConstructor() {
        options.put("earthRadius", "" + earthRadius);
        options.put("title", title);
        options.put("response", "69");
        RequestTrip test = new RequestTrip(options, places);
        String response = test.getResponse();
        assertEquals(response, "69");
    }

    @Test
    @DisplayName("Test setting units w/ constructor")
    public void testUnitsConstructor() {
        options.put("earthRadius", "" + earthRadius);
        options.put("units", "miles");
        RequestTrip test = new RequestTrip(options, places);
        String units = test.getUnits();
        assertEquals(units, "miles");
    }

    @Test
    @DisplayName("Earth radius after constructor")
    public void testRadiusConstructor() {
        options.put("earthRadius", "" + earthRadius);
        options.put("title", title);
        RequestTrip test = new RequestTrip(options, places);
        double rv = test.getEarthRadius();
        assertEquals(earthRadius, rv);
    }

    @Test
    @DisplayName("Title after constructor")
    public void testTitleConstructor() {
        options.put("earthRadius", "" + earthRadius);
        options.put("title", title);
        RequestTrip test = new RequestTrip(options, places);
        String rv = test.getTitle();
        assertEquals(title, rv);
    }

    @Test
    @DisplayName("Places after constructor")
    public void testPlaces() {
        options.put("earthRadius", "" + earthRadius);
        options.put("title", title);
        map.put("a", "b");
        map.put("c", "d");
        places.add(map);
        RequestTrip test = new RequestTrip(options, places, distances);
        ArrayList<HashMap<String, String>> rv = test.getPlaces();
        assertEquals(places, rv);
    }

    @Test
    @DisplayName("Distances after constructor")
    public void testDistancesConstructor() {
        options.put("earthRadius", "" + earthRadius);
        options.put("title", title);
        RequestTrip test = new RequestTrip(options, places, distances);
        ArrayList<Long> rv = test.getDistances();
        assertEquals(distances, rv);
    }

    @Test
    @DisplayName("Set earth radius")
    public void testSetRadius() {
        options.put("earthRadius", "" + earthRadius);
        options.put("title", title);
        RequestTrip test = new RequestTrip(options, places);
        double newRadius = 1000;
        test.setEarthRadius(newRadius);
        double rv = test.getEarthRadius();
        assertEquals(newRadius, rv);
    }

    @Test
    @DisplayName("Set title")
    public void testSetTitle() {
        options.put("earthRadius", "" + earthRadius);
        options.put("title", title);
        RequestTrip test = new RequestTrip(options, places);
        String newTitle = "New Title";
        test.setTitle(newTitle);
        String rv = test.getTitle();
        assertEquals(newTitle, rv);
    }
    @Test
    @DisplayName("Test timer")
    public void testTimer() {
        HashMap<String, String> place3 = new HashMap<>();
        place3.put("latitude", "45.2538");
        place3.put("longitude", "-69.4455");
        place3.put("name", "Maine");
        places.add(place3);
        HashMap<String, String> place4 = new HashMap<>();
        place4.put("latitude", "32.7157");
        place4.put("longitude", "-117.1611");
        place4.put("name", "San Diego");
        places.add(place4);
        HashMap<String, String> place5 = new HashMap<>();
        place5.put("latitude", "40.0583");
        place5.put("longitude", "-74.4057");
        place5.put("name", "New Jersey");
        places.add(place5);
        HashMap<String, String> place6 = new HashMap<>();
        place6.put("latitude", "37.7749");
        place6.put("longitude", "-122.4194");
        place6.put("name", "San Francisco");
        places.add(place6);
        for(int i = 0; i < 1000; i++){
            places.add(place6);
            places.add(place5);
            places.add(place4);
            places.add(place3);
        }
        options.put("earthRadius", "" + earthRadius);
        options.put("title", title);
        options.put("response", "1");
        RequestTrip test = new RequestTrip(options, places);
        //takes 2023 ms
        long start = System.currentTimeMillis();
        test.buildResponse();
        long end = System.currentTimeMillis();
        boolean inTime = false;
        if(end - start < 1000){
            inTime = true;
        }
        assertEquals(inTime, true);
    }
    @Test
    @DisplayName("Test response setter")
    public void testSetResponse() {
        options.put("earthRadius", "" + earthRadius);
        options.put("response", "68");
        RequestTrip test = new RequestTrip(options, places);
        String newResponse = "69";
        test.setResponse(newResponse);
        HashMap<String, String> newOptions = test.getOptions();
        assertEquals(newOptions.get("response"), newResponse);
    }

    @Test
    @DisplayName("Test units setter")
    public void testSetUnits() {
        options.put("earthRadius", "" + earthRadius);
        options.put("units", "miles");
        RequestTrip test = new RequestTrip(options, places);
        String newUnits = "kilometers";
        test.setUnits(newUnits);
        HashMap<String, String> newOptions = test.getOptions();
        assertEquals(newOptions.get("units"), newUnits);
    }
}