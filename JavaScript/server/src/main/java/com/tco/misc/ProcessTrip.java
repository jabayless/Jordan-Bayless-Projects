package com.tco.misc;
import com.tco.misc.DistanceCalculator;
import java.util.ArrayList;
import java.util.HashMap;

public class ProcessTrip{

    private HashMap<String, String> getLocations(HashMap<String, String> place){
        HashMap<String, String> retPlace = new HashMap<>();
        retPlace.put("latitude", place.get("latitude"));
        retPlace.put("longitude", place.get("longitude"));
        return retPlace;
    }

    public long[][] createDistanceTable(ArrayList<HashMap<String, String>> places, Double earthRadius, long response)
    {
        long start = System.currentTimeMillis();
        DistanceCalculator distanceCalculator = new DistanceCalculator(earthRadius);
        long[][] table = new long[places.size()][places.size()];
        HashMap<String, String> place1;
        HashMap<String, String> place2;
        for (int i = 0; i < places.size(); i++) {
            for (int j = i + 1; j < places.size(); j++) {
                place1 = getLocations(places.get(i));
                place2 = getLocations(places.get(j));
                table[i][j] = (Math.round(distanceCalculator.CalculateSurfaceDistance(place1, place2)));
                table[j][i] = table[i][j];
                if(System.currentTimeMillis() - start > response){
                    table[places.size()-1][places.size()-1] = -69696969;//indicate failure
                    break;
                }
            }
            if(System.currentTimeMillis() - start > response){break;}
        }
        return table;
    }

    public int[] optimizePlaces(long[][] distanceTable, ArrayList<HashMap<String, String>> places) {
        int[] route = new int[places.size()+1];
        for (int routeDestination = 0; routeDestination < places.size(); routeDestination++)
        {
            route[routeDestination] = routeDestination;
        }
        route[places.size()] = 0;
        boolean improvement = true;
        int n = places.size();
        if (n <= 3) {
            improvement = false;
        }
        while (improvement) {
            improvement = false;
            for (int i = 0; i <= n - 3; i++) {  // assert n>4
                for (int k = i + 2; k <= n - 1; k++) {
                    long delta = dis(route, i, k, distanceTable);
                    if (delta < 0) { //improvement?
                        twoOptReverse(route, i + 1, k);
                        improvement = true;
                    }
                }
            }
        }
        return route;
    }

    public long dis(int[] route, int x, int y, long[][] table){
        return -table[route[x]][route[x+1]]-table[route[y]][route[y+1]]+
                table[route[x]][route[y]]+table[route[x+1]][route[y+1]];
    }

    private void twoOptReverse(int[] route, int i1, int k) {
        while(i1 < k) {
            int temp = route[i1];
            route[i1] = route[k];
            route[k] = temp;
            i1++;
            k--;
        }
    }

    public ArrayList<HashMap<String, String>> restructureTrip(int[] route, ArrayList<HashMap<String, String>> places){
        ArrayList<HashMap<String, String>> newPlaces = new ArrayList<>();
        for (int i = 0; i< places.size(); i++)
        {
            newPlaces.add(places.get(route[i]));
        }
        return newPlaces;
    }

    public ArrayList<Long> computeDistances(ArrayList<HashMap<String, String>> places, Double earthRadius){
        DistanceCalculator distanceCalculator = new DistanceCalculator(earthRadius);
        ArrayList<Long> distances = new ArrayList<>();
        for(int i = 0; i < places.size(); i++){
            HashMap<String, String> place1 = getLocations(places.get(i));
            HashMap<String, String> place2 = getPlace2(places, i);
            distances.add(Math.round(distanceCalculator.CalculateSurfaceDistance(place1, place2)));
        }
        return distances;
    }

    public ArrayList<Long> computeDistancesWTable(long[][] table, int[] route){
        ArrayList<Long> distances = new ArrayList<>();
        for(int i = 0; i < route.length - 1; i++){
            distances.add(table[route[i]][route[i+1]]);
        }
        return distances;
    }

    public HashMap<String, String> getPlace2(ArrayList<HashMap<String, String>> places, int i){
        //logic to compare last place with first
        HashMap<String, String> place2;
        if(i == places.size() - 1){
            place2 = getLocations(places.get(0));
        }
        else{
            place2 = getLocations(places.get(i+1));
        }
        return place2;
    }
}