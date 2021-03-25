package com.tco.misc;
import com.tco.requests.RequestTrip;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.BeforeEach;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
public class TestProcessTrip {
    private HashMap<String, String> options = new HashMap<>();
    private ArrayList<HashMap<String, String>> places = new ArrayList<>();
    private ArrayList<Long> distances;

    @BeforeEach
    public void createConfigurationForTestCases(){
        options.put("earthRadius", "3959.0");
        options.put("title", "Fun trip");
        HashMap<String, String> place1 = new HashMap<>();
        place1.put("latitude", "39.7");
        place1.put("longitude", "-105.0");
        place1.put("name", "UrMomsHouse");
        HashMap<String, String> place2 = new HashMap<>();
        place2.put("latitude", "40.0");
        place2.put("longitude", "-105.4");
        place2.put("name", "MyHouse");
        places.add(place1);
        places.add(place2);
    }

    @Test
    @DisplayName("Get one distance back")
    public void testNumDistances() {
        RequestTrip trip = new RequestTrip(options, places);
        trip.buildResponse();
        distances = trip.getDistances();
        assertEquals(distances.size(), 2);
    }

    @Test
    @DisplayName("Get correct distance back")
    public void testCorrectDistance() {
        RequestTrip trip = new RequestTrip(options, places);
        trip.buildResponse();
        distances = trip.getDistances();
        assertEquals(distances.get(0), 30);
    }

    @Test
    @DisplayName("Get 3 distances back from 3 places")
    public void testMultiplePlaces() {
        HashMap<String, String> place3 = new HashMap<>();
        place3.put("latitude", "40.0");
        place3.put("longitude", "-105.4");
        place3.put("name", "MyHouse");
        places.add(place3);
        RequestTrip trip = new RequestTrip(options, places);
        trip.buildResponse();
        distances = trip.getDistances();
        assertEquals(distances.size(), 3);
    }

    @Test
    @DisplayName("Create Distance Table")
    public void testDistanceTable() {
        ProcessTrip newTrip = new ProcessTrip();
        long[][] table = newTrip.createDistanceTable(places, Double.parseDouble(options.get("earthRadius")), 1000);
        assertEquals(table[0][0], 0);
        assertEquals(table[0][1], 30);
        assertEquals(table[1][0], 30);
        assertEquals(table[1][1], 0);
    }

    @Test
    @DisplayName("Test 2op algorithm with less then 3 places")
    public void test2opWith3Places() {
        HashMap<String, String> place3 = new HashMap<>();
        place3.put("latitude", "45.2538");
        place3.put("longitude", "-69.4455");
        place3.put("name", "Maine");
        places.add(place3);
        ProcessTrip newTrip = new ProcessTrip();
        long[][] table = newTrip.createDistanceTable(places, Double.parseDouble(options.get("earthRadius")), 1000);
        assertEquals(places.size(), 3);
        int[] tripArray = newTrip.optimizePlaces(table, places);
        assertEquals(tripArray[0], 0);
        assertEquals(tripArray[1], 1);
        assertEquals(tripArray[2], 2);
    }

    @Test
    @DisplayName("Test 2op algorithm")
    public void test2OpAlgorithm() {
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
        ProcessTrip newTrip = new ProcessTrip();
        long[][] table = newTrip.createDistanceTable(places, Double.parseDouble(options.get("earthRadius")), 1000);
        assertEquals(places.size(), 6);
        int[] tripArray = newTrip.optimizePlaces(table, places);
        assertEquals(tripArray[0], 0);
        assertEquals(tripArray[1], 4);
        assertEquals(tripArray[2], 2);
        assertEquals(tripArray[3], 5);
        assertEquals(tripArray[4], 3);
        assertEquals(tripArray[5], 1);
        assertEquals(tripArray[6], 0);
    }

    @Test
    @DisplayName("Test places pre and post optimization")
    public void testRestructurePlaces() {
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
        ProcessTrip newTrip = new ProcessTrip();
        long[][] table = newTrip.createDistanceTable(places, Double.parseDouble(options.get("earthRadius")), 1000);
        int[] tripArray = newTrip.optimizePlaces(table, places);
        ArrayList<HashMap<String, String>> newPlaces = newTrip.restructureTrip(tripArray, places);
        for (int i = 0; i < places.size(); i++) {
            assertEquals(places.get(tripArray[i]), newPlaces.get(i));
        }
    }
}
