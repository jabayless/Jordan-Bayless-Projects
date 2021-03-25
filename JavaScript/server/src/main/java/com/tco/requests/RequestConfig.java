package com.tco.requests;

import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

import com.tco.misc.QueryPlaces;
import com.tco.misc.BadRequestException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class RequestConfig extends RequestHeader {

    private final transient Logger log = LoggerFactory.getLogger(RequestConfig.class);
    private String serverName;
    private List<String> supportedRequests;
    private HashMap<String, List<String>> filters = new HashMap<>();

    public RequestConfig() {
        this.requestType = "config";
        this.requestVersion = RequestHeader.CURRENT_SUPPORTED_VERSION;
        this.serverName = "t09 Revenge of the Sprint";
        this.supportedRequests = Arrays.asList("config", "distance", "find", "trip");
        this.filters.put("type", Arrays.asList("airport", "heliport", "balloonport"));
    }

    public String getServerName() {
        return serverName;
    }

    public List<String> getRequestTypes() {
        return supportedRequests;
    }

    public HashMap<String, List<String>> getFilters() {
        return filters;
    }

    @Override
    public void buildResponse() {
        QueryPlaces results = new QueryPlaces();
        this.filters.put("where", results.getCountries());
        log.trace("buildResponse -> {}", this);
    }

}