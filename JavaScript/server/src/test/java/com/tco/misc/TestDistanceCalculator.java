package com.tco.misc;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import java.util.HashMap;

public class TestDistanceCalculator {

    private void test(HashMap<String, String> place1, HashMap<String, String> place2,Double radius, Double expected) {
        DistanceCalculator dc = new DistanceCalculator(radius);
        assertEquals(expected, Math.floor(dc.CalculateSurfaceDistance(place1,place2)));
    }

    @Test
    @DisplayName("DistanceCalculator accuracy in KM")
    public void testColoradoKM(){

        HashMap<String, String> place1 = new HashMap<>();
        HashMap<String, String> place2 = new HashMap<>();

        place2.put("longitude","-109");
        place2.put("latitude","41");

        place1.put("longitude","-102");
        place1.put("latitude","37");

        test(place1,place2,6371d,750d);
    }

    @Test
    @DisplayName("DistanceCalculator accuracy in Miles")
    public void testColoradoDave(){

        HashMap<String, String> place1 = new HashMap<>();
        HashMap<String, String> place2 = new HashMap<>();

        place2.put("longitude","-109");
        place2.put("latitude","41");

        place1.put("longitude","-102");
        place1.put("latitude","37");

        test(place1,place2,3959d,466d);
    }

    @Test
    @DisplayName("DistanceCalculator Edge Case 0 Radius")
    public void testZeroRadius(){
        HashMap<String, String> place1 = new HashMap<>();
        HashMap<String, String> place2 = new HashMap<>();

        place2.put("longitude","-109");
        place2.put("latitude","41");

        place1.put("longitude","-102");
        place1.put("latitude","37");

        test(place1,place2,0d,0d);
    }

    @Test
    @DisplayName("DistanceCalculator Edge Case Negative Radius")
    public void testNegRadius(){
        HashMap<String, String> place1 = new HashMap<>();
        HashMap<String, String> place2 = new HashMap<>();

        place2.put("longitude","-109");
        place2.put("latitude","41");

        place1.put("longitude","-102");
        place1.put("latitude","37");

        test(place1,place2,-10d,0d);
    }

}
