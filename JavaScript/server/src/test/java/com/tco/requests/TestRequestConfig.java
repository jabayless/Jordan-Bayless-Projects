package com.tco.requests;

import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

import com.tco.requests.RequestConfig;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestRequestConfig {

    private RequestConfig conf;

    @BeforeEach
    public void createConfigurationForTestCases() {
        conf = new RequestConfig();
        conf.buildResponse();
    }

    @Test
    @DisplayName("Request type is \"config\"")
    public void testType() {
        String type = conf.getRequestType();
        assertEquals("config", type);
    }

    @Test
    @DisplayName("Version number is equal to 4")
    public void testVersion() {
        int version = conf.getRequestVersion();
        assertEquals(4, version);
    }

    @Test
    @DisplayName("Team name is t09 Revenge of the Sprint")
    public void testServerName() {
        String name = conf.getServerName();
        assertEquals("t09 Revenge of the Sprint", name);
    }

    @Test
    @DisplayName("Test the request types")
    public void testRequestTypes() {
        List<String> types = conf.getRequestTypes();
        assertEquals(Arrays.asList("config", "distance", "find", "trip"), types);
    }

//    @Test
//    @DisplayName("Test the filter types")
//    public void testRequestFilters() {
//        HashMap<String, List<String>> filters = conf.getFilters();
//        List<String> type = filters.get("type");
//        List<String> where = filters.get("where");
//        assertEquals(Arrays.asList("airport", "heliport", "balloonport"), type);
//        assertEquals(true, where.contains("United States"));
//    }
}
