import React, {Component} from "react";
import Tabs from "react-bootstrap/Tabs";

import Search from "./Search";
import Trip from "./Trip";

import {renderRowAndCol} from "../../utils/format";
import {SEARCH_MARKER, FIRST_DISTANCE_MARKER, SECOND_DISTANCE_MARKER} from "../../utils/constants";

const SEARCH = "Find a Place"
const DISTANCE = "Calculate Distance"
const TRIP = "Build a Trip"

export default class NavigationBar extends Component {

    constructor(props) {
        super(props);
    }

    render() {
        return (
            renderRowAndCol(
                <Tabs defaultActiveKey={TRIP} justify>
                    {this.renderTripTab()}
                    {this.renderSearchTab()}
                    {this.renderDistanceTab()}
                </Tabs>
            )
        );
    }

    renderSearchBar(marker) {
        return (
            <Search
                processSearchResult={this.props.processSearchResult}
                searchInput={""}
                i={marker}
                serverSettings={this.props.serverSettings}
            />
        );
    }

    renderSearchTab() {
        return (
            <NavigationBar eventKey={SEARCH} title={SEARCH}>
                {this.renderSearchBar(SEARCH_MARKER)}
            </NavigationBar>
        );
    }

    renderDistanceTab() {
        return (
            <NavigationBar eventKey={DISTANCE} title={DISTANCE}>
                {this.renderSearchBar(FIRST_DISTANCE_MARKER)}
                <br/>
                {this.renderSearchBar(SECOND_DISTANCE_MARKER)}
                <hr/>
                {this.renderDistanceDisplay()}
            </NavigationBar>
        );
    }

    renderTripTab() {
        return (
            <NavigationBar eventKey={TRIP} title={TRIP}>
                <Trip
                    processTripResult={this.props.processTripResult}
                    serverSettings={this.props.serverSettings}
                    createSnackBar={this.props.createSnackBar}
                />
            </NavigationBar>
        );
    }

    renderDistanceDisplay() {
        return (
            <div className="col text-center">
                Distance: {this.props.distanceReadout} miles
            </div>

        );
    }
}