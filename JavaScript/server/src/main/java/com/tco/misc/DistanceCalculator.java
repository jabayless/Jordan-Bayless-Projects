package com.tco.misc;

import java.util.HashMap;

public class DistanceCalculator {

    private Double Radius;

    public DistanceCalculator(){
        this(1.0); //Defaults to a unit sphere
    }
    public DistanceCalculator(Double radius){
        if (radius < 0){
            radius = 0.0;
        }
        Radius = radius;
    }

    public Double CalculateSurfaceDistance(HashMap<String, String> place1, HashMap<String, String> place2){
        return ConvertToSurfaceDistance(CalculateAngularDistance(place1,place2));
    }

    Double ConvertToSurfaceDistance(Double AngularDistance){
        return AngularDistance * Radius;
    }

    Double CalculateAngularDistance(HashMap<String, String> place1, HashMap<String, String> place2){
        double DeltaLambda = Math.toRadians(Double.parseDouble(place1.get("longitude"))) - Math.toRadians(Double.parseDouble(place2.get("longitude")));
        double Theta0 = Math.toRadians(Double.parseDouble(place1.get("latitude")));
        double Theta1 = Math.toRadians(Double.parseDouble(place2.get("latitude")));
        //Vincenty Formula:
        double A = Math.cos(Theta1) * Math.sin(DeltaLambda);
        double B = Math.cos(Theta0) * Math.sin(Theta1);
        double C = Math.sin(Theta0) * Math.cos(Theta1) * Math.cos(DeltaLambda);

        double D = Math.sin(Theta0) * Math.sin(Theta1);
        double E = Math.cos(Theta0) * Math.cos(Theta1) * Math.cos(DeltaLambda);

        double top = Math.sqrt(Math.pow(A,2) + Math.pow(B - C,2));
        double bottom = D + E;

        return Math.atan2(top,bottom);
    }
}
