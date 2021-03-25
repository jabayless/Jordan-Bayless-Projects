package com.tco.requests;

import com.tco.misc.BadRequestException;
import com.tco.misc.QueryPlaces;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class RequestFind extends RequestHeader {

    private final transient Logger log = LoggerFactory.getLogger(RequestFind.class);
    private String match;
    private HashMap<String, List<String>> narrow;
    private Integer limit;
    private int found;
    private List<HashMap<String, String>> places = new ArrayList<>();

    public RequestFind() {
        this.requestType = "find";
        this.requestVersion = RequestHeader.CURRENT_SUPPORTED_VERSION;
    }

    public RequestFind(String match) {
        this();
        this.match = match;
    }

    public RequestFind(HashMap<String, List<String>> narrow) {
        this();
        this.narrow = narrow;
    }

    public RequestFind(Integer limit) {
        this();
        this.limit = limit;
    }

    public RequestFind(String match, HashMap<String, List<String>> narrow) {
        this();
        this.match = match;
        this.narrow = narrow;
    }

    public RequestFind(String match, Integer limit) {
        this();
        this.match = match;
        this.limit = limit;
    }

    public RequestFind(HashMap<String, List<String>> narrow, Integer limit) {
        this();
        this.narrow = narrow;
        this.limit = limit;
    }

    public RequestFind(String match, HashMap<String, List<String>> narrow, Integer limit) {
        this();
        this.match = match;
        this.narrow = narrow;
        this.limit = limit;
    }

    public void setMatch(String match) {
        this.match = match;
    }

    public void setLimit(Integer limit) {
        this.limit = limit;
    }

    public void setNarrow(HashMap<String, List<String>> narrow) {
        this.narrow = narrow;
    }

    public String getMatch() {
        return match;
    }

    public Integer getLimit() {
        return limit;
    }

    public HashMap<String, List<String>> getNarrow() {
        return narrow;
    }

    public int getFound() {
        return found;
    }

    public List<HashMap<String, String>> getPlaces() {
        return places;
    }

    @Override
    public void buildResponse() {
        QueryPlaces results = new QueryPlaces();
        if (limit == null && match == null)
            places = results.placeQuery(match, narrow, 1);
        else if (limit == null)
            places = results.placeQuery(match, narrow, 100);
        else
            places = results.placeQuery(match, narrow, limit);
        found = results.getFound(match, limit);
        log.trace("buildResponse -> {}", this);
    }
}