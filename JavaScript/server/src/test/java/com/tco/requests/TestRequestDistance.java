package com.tco.requests;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;
import com.tco.requests.RequestDistance;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestRequestDistance {
    private RequestDistance distance;

    public void createDistanceForTestCases(){
        distance = new RequestDistance();
        distance.buildResponse();
    }

    @Test
    @DisplayName("Check distance is correct")
    public void testColoradoDiagonal(){
        RequestDistance distance = new RequestDistance(3959d,"41","-109","37","-102");
        distance.buildResponse();
        assertEquals(466d,distance.getDistance());
    }

    @Test
    @DisplayName("Request type is \"Distance\"")
    public void testType() {
        createDistanceForTestCases();
        String type = distance.getRequestType();
        assertEquals("distance", type);
    }

    @Test
    @DisplayName("Version number is equal to 4")
    public void testVersion() {
        createDistanceForTestCases();
        int version = distance.getRequestVersion();
        assertEquals(4, version);
    }
    @Test
    @DisplayName("Won't return negative distances")
    public void testNegativeDistance(){
        RequestDistance distance = new RequestDistance(6371099980d,"40.6","-105.1","-33.9","151.2");
        distance.buildResponse();
        assertEquals(13433891190L,distance.getDistance());
    }
}
