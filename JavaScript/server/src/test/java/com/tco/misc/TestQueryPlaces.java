package com.tco.misc;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import sun.jvm.hotspot.ui.tree.BooleanTreeNodeAdapter;
import sun.jvm.hotspot.utilities.Assert;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class TestQueryPlaces {
    private QueryPlaces testPlaces;

//    @Test
//    @DisplayName("Test Denver Query Limit")
//    public void testDenverLimit() {
//        testPlaces = new QueryPlaces();
//        ArrayList<HashMap<String, String>> testList = testPlaces.placeQuery("Denver", null, 5);
//        assertEquals(5, testList.size());
//    }

//    @Test
//    @DisplayName("Test Random Place Query")
//    public void testRandom() {
//        testPlaces = new QueryPlaces();
//        ArrayList<HashMap<String, String>> testList = testPlaces.placeQuery("", null, 1);
//        assertEquals(1, testList.size());
//    }

//    @Test
//    @DisplayName("Test Multiple Random Place Query")
//    public void testMultipleRandom() {
//        testPlaces = new QueryPlaces();
//        ArrayList<HashMap<String, String>> testList = testPlaces.placeQuery("", null, 10);
//        assertEquals(10, testList.size());
//    }

//    @Test
//    @DisplayName("Test Denver Query Name")
//    public void testDenverName() {
//        testPlaces = new QueryPlaces();
//        ArrayList<HashMap<String, String>> testList = testPlaces.placeQuery("Denver", null, 1);
//        String name = testList.get(0).get("name");
//        String municipality = testList.get(0).get("municipality");
//        boolean containsDenver = false;
//        if (name.contains("Denver") || municipality.contains("Denver")) {
//            containsDenver = true;
//        }
//        assertTrue(containsDenver);
//    }

//    @Test
//    @DisplayName("Test Narrow Query")
//    public void testNarrow() {
//        testPlaces = new QueryPlaces();
//        HashMap<String, List<String>> filters = new HashMap<>();
//        filters.put("type", Arrays.asList("airport", "heliport", "balloonport"));
//        filters.put("where", Arrays.asList("Canada", "Mexico", "United States"));
//        ArrayList<HashMap<String, String>> testList = testPlaces.placeQuery("Denver", filters, 20);
//        assertTrue(testList.size() > 15);
//    }

//    @Test
//    @DisplayName("Test getCountries")
//    public void testGetCountries() {
//        testPlaces = new QueryPlaces();
//        List<String> result = testPlaces.getCountries();
//        assertTrue(result.size() > 200);
//    }

//    @Test
//    @DisplayName("Test getFound")
//    public void testGetFound() {
//        testPlaces = new QueryPlaces();
//        Integer limit = new Integer(10);
//        String match = "Denver";
//
//        int result = testPlaces.getFound(null, null);
//        assertTrue(result == 1);
//
//        result = testPlaces.getFound(null, limit);
//        assertTrue(result == 10);
//
//        testPlaces.placeQuery(match, null, limit);
//        result = testPlaces.getFound(match, limit);
//        assertTrue(result > 10);
//    }
}
