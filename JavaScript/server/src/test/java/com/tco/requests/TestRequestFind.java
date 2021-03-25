package com.tco.requests;

import com.tco.requests.RequestFind;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

public class TestRequestFind {

    private RequestFind find;

    @BeforeEach
    public void createConfigurationForTestCases() {
        find = new RequestFind();
        find.buildResponse();
    }

    @Test
    @DisplayName("Request type is \"find\"")
    public void testType() {
        String type = find.getRequestType();
        assertEquals("find", type);
    }

    @Test
    @DisplayName("Version number is equal to 4")
    public void testVersion() {
        int version = find.getRequestVersion();
        assertEquals(4, version);
    }

    @Test
    @DisplayName("Limit is set to 1")
    public void testLimit() {
        RequestFind limitTest = new RequestFind(1);
        int limit = limitTest.getLimit();
        limitTest.buildResponse();
        assertEquals(1, limit);
    }

    @Test
    @DisplayName("Match is set to Denver")
    public void testMatch() {
        RequestFind matchTest = new RequestFind("Denver");
        String match = matchTest.getMatch();
        matchTest.buildResponse();
        assertEquals(match, "Denver");
    }

    @Test
    @DisplayName("Narrow is set to defaults from config")
    public void testNarrow() {
        HashMap<String, List<String>> filters = new HashMap<>();
        filters.put("type", Arrays.asList("airport", "heliport", "balloonport"));
        filters.put("where", Arrays.asList("Canada", "Mexico", "United States"));
        RequestFind narrowTest = new RequestFind(filters);
        HashMap<String, List<String>> narrow = narrowTest.getNarrow();
        narrowTest.buildResponse();
        assertEquals(narrow, filters);
    }

    @Test
    @DisplayName("Test RequestFind with match and limit")
    public void testMatchLimit() {
        RequestFind matchLimitTest = new RequestFind("Denver", 4);
        String match = matchLimitTest.getMatch();
        matchLimitTest.buildResponse();
        assertEquals(match, "Denver");
    }

    @Test
    @DisplayName("Test RequestFind with match and narrow")
    public void testMatchNarrow() {
        HashMap<String, List<String>> filters = new HashMap<>();
        filters.put("type", Arrays.asList("airport", "heliport", "balloonport"));
        filters.put("where", Arrays.asList("Canada", "Mexico", "United States"));
        RequestFind matchNarrowTest = new RequestFind("Denver", filters);
        String match = matchNarrowTest.getMatch();
        HashMap<String, List<String>> narrow = matchNarrowTest.getNarrow();
        matchNarrowTest.buildResponse();
        assertEquals(match, "Denver");
        assertEquals(narrow, filters);
    }

    @Test
    @DisplayName("Test RequestFind with narrow and limit")
    public void testNarrowLimit() {
        HashMap<String, List<String>> filters = new HashMap<>();
        filters.put("type", Arrays.asList("airport", "heliport", "balloonport"));
        filters.put("where", Arrays.asList("Canada", "Mexico", "United States"));
        RequestFind narrowLimitTest = new RequestFind(filters, 10);
        int limit = narrowLimitTest.getLimit();
        HashMap<String, List<String>> narrow = narrowLimitTest.getNarrow();
        narrowLimitTest.buildResponse();
        assertEquals(limit, 10);
        assertEquals(narrow, filters);
    }

    @Test
    @DisplayName("Test RequestFind with match, narrow and limit")
    public void testMatchNarrowLimit() {
        HashMap<String, List<String>> filters = new HashMap<>();
        filters.put("type", Arrays.asList("airport", "heliport", "balloonport"));
        filters.put("where", Arrays.asList("Canada", "Mexico", "United States"));
        RequestFind matchNarrowLimitTest = new RequestFind("Denver", filters, 10);
        String match = matchNarrowLimitTest.getMatch();
        int limit = matchNarrowLimitTest.getLimit();
        HashMap<String, List<String>> narrow = matchNarrowLimitTest.getNarrow();
        matchNarrowLimitTest.buildResponse();
        assertEquals(match, "Denver");
        assertEquals(limit, 10);
        assertEquals(narrow, filters);
    }

    @Test
    @DisplayName("Test match setter")
    public void testMatchSetter() {
        find.setMatch("Foco");
        String match = find.getMatch();
        assertEquals(match, "Foco");
    }

    @Test
    @DisplayName("Test limit setter")
    public void testLimitSetter() {
        find.setLimit(3);
        int limit = find.getLimit();
        assertEquals(limit, 3);
    }

    @Test
    @DisplayName("Test narrow setter")
    public void testNarrowSetter() {
        HashMap<String, List<String>> filters = new HashMap<>();
        filters.put("type", Arrays.asList("airport", "heliport", "balloonport"));
        filters.put("where", Arrays.asList("Canada", "Mexico", "United States"));
        find.setNarrow(filters);
        HashMap<String, List<String>> narrow = find.getNarrow();
        assertEquals(filters, narrow);
    }

//    @Test
//    @DisplayName("Test Found getter")
//    public void testFoundGetter() {
//        RequestFind matchTest = new RequestFind("Denver", 4);
//        matchTest.buildResponse();
//        assertTrue(matchTest.getFound() > 4);
//    }

//    @Test
//    @DisplayName("Test places getter")
//    public void testPlaces() {
//        find.setMatch("Denver");
//        find.setLimit(3);
//        find.buildResponse();
//        assertEquals(3, find.getPlaces().size());
//    }
}