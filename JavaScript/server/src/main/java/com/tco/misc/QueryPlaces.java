package com.tco.misc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class QueryPlaces {

    private String useTunnel = System.getenv("CS314_USE_DATABASE_TUNNEL");
    // Note that if the variable isn't defined, System.getenv will return null
    private String dburl;
    private String isTravis = System.getenv("TRAVIS");
    ArrayList<HashMap<String, String>> resultList = new ArrayList<>();
    // shared user with read-only access
    private String username = "cs314-db";
    private String password = "eiK5liet1uej";
    private int found = 0;

    private String COUNTRY = "SELECT DISTINCT name FROM country ORDER BY name;";
    private String SELECT = "SELECT DISTINCT world.name, world.latitude, world.longitude, world.id, world.altitude, world.municipality, world.type,  country.name as country, region.name as region, world.wikipedia_link ";
    private String JOIN = "FROM (world INNER JOIN region ON world.iso_region = region.id INNER JOIN country ON world.iso_country = country.id) WHERE ";

    public QueryPlaces(){
        getDB_URL();
    }

    private void getDB_URL() {
        if (isTravis != null && isTravis.equals("true")) {
            dburl = "jdbc:mysql://127.0.0.1/cs314";
            username = "root";
            password = null;
        } else if (useTunnel != null && useTunnel.equals("true")) {
            dburl = "jdbc:mysql://127.0.0.1:56247/cs314";
        } else {
            dburl = "jdbc:mysql://faure.cs.colostate.edu/cs314";
        }
    }

    private String generateQuery(String match, HashMap<String, List<String>> narrow) {
        String QUERY;
        String MATCH = "(country.name LIKE '%" + match + "%' OR region.name LIKE '%" + match + "%' OR world.name LIKE '%" + match + "%' OR world.municipality LIKE '%" + match + "%') ORDER BY world.name;";
        if (match == null) {
            QUERY = "SELECT DISTINCT name, latitude, longitude, id, altitude, municipality, type, iso_region as region, iso_country as country, wikipedia_link FROM world ORDER BY RAND();";
        } else if (narrow != null) {
            List<String> type = narrow.get("type");
            List<String> where = narrow.get("where");
            String TYPE = generateNarrowQuery(type, "world.type");
            String WHERE = generateNarrowQuery(where, "country.name");
            QUERY = (SELECT + JOIN + TYPE + WHERE + MATCH);
        } else {
            QUERY = (SELECT + JOIN + MATCH);
        }
        return QUERY;
    }

    private String generateNarrowQuery(List<String> filters, String columnName) {
        if (filters == null || filters.isEmpty())
            return "";
        String tempQuery = "(";
        for (int i = 0; i < filters.size(); i++) {
            if (i != 0)
                tempQuery += " OR ";
            tempQuery += (columnName + " LIKE '%" + filters.get(i) + "%'");
        }
        tempQuery += ") AND ";
        return tempQuery;
    }

    public ArrayList<HashMap<String, String>> placeQuery(String match, HashMap<String, List<String>> narrow, Integer limit) {
        String QUERY = generateQuery(match, narrow);
        try (Connection conn = DriverManager.getConnection(dburl, username, password);
             Statement query = conn.createStatement();
             ResultSet results = query.executeQuery(QUERY)) {
            while (results.next() && found < limit.intValue()) {
                HashMap<String, String> currPlace = new HashMap<>();
                currPlace.put("name", results.getString("name"));
                currPlace.put("latitude", results.getString("latitude"));
                currPlace.put("longitude", results.getString("longitude"));
                currPlace.put("id", results.getString("id"));
                currPlace.put("altitude", results.getString("altitude"));
                currPlace.put("municipality", results.getString("municipality"));
                currPlace.put("type", results.getString("type"));
                currPlace.put("region", results.getString("region"));
                currPlace.put("country", results.getString("country"));
                currPlace.put("url", results.getString("wikipedia_link"));
                resultList.add(currPlace);
                found++;
            }
            while (results.next()) found++;
        } catch (Exception e) {
            System.err.println("Exception: " + e.getMessage());
        }
        return resultList;
    }

    public List<String> getCountries() {
        List<String> countries = new ArrayList<>();
        try (Connection conn = DriverManager.getConnection(dburl, username, password);
             Statement query = conn.createStatement();
             ResultSet results = query.executeQuery(COUNTRY)) {
            while (results.next()) {
                countries.add(results.getString("name"));
            }
        } catch (Exception e) {
            System.err.println("Exception: " + e.getMessage());
        }
        return countries;
    }

    public int getFound(String match, Integer limit) {
        if (match == null && limit == null)
            return 1;
        else if (match == null)
            return limit.intValue();
        else
            return found;
    }

}