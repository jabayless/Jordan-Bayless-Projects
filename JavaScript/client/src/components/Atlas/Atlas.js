import React, {Component, createRef} from 'react';
import {Button, Container,} from 'reactstrap';
import {Map, Marker, Polyline, Popup, TileLayer} from 'react-leaflet';
import Control from 'react-leaflet-control';

import icon from 'leaflet/dist/images/marker-icon.png';
import iconShadow from 'leaflet/dist/images/marker-shadow.png';
import homeIcon from '../../../../images/home.png'

import 'leaflet/dist/leaflet.css';
import {isJsonResponseValid, sendServerRequest} from "../../utils/restfulAPI";
import {renderRowAndCol} from "../../utils/format";
import * as distanceSchema from "../../../schemas/ResponseDistance.json";

import NavigationBar from "./NavigationBar";
import GPS from "./GPS";
import {
    PROTOCOL_VERSION,
    EARTH_RADIUS_UNITS_DEFAULT,
    SEARCH_MARKER,
    FIRST_DISTANCE_MARKER,
    SECOND_DISTANCE_MARKER
} from "../../utils/constants";

import {getAddressFromCoordinates} from "./ReverseGeocode";

const MAP_BOUNDS = [[-90, -180], [90, 180]];
const MAP_CENTER_DEFAULT = [40.5734, -105.0865];
const MAP_ZOOM_DEFAULT = 16.9;
const MARKER_ICON = L.icon({iconUrl: icon, shadowUrl: iconShadow, iconAnchor: [12, 40]});
const MAP_LAYER_ATTRIBUTION = "&copy; <a href=&quot;http://osm.org/copyright&quot;>OpenStreetMap</a> contributors";
const MAP_LAYER_URL = "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png";
const MAP_MIN_ZOOM = 1;
const MAP_MAX_ZOOM = 19;
const UNICODE_TRASH_SYMBOL = "\uD83D\uDDD1";
const CURRENT_LOCATION_ICON = L.icon({iconUrl: homeIcon, shadowUrl: iconShadow, iconAnchor: [24, 40]});

export default class Atlas extends Component {

    constructor(props) {
        super(props);
        this.getStringMarkerPosition = this.getStringMarkerPosition.bind(this);
        this.setMarker = this.setMarker.bind(this);
        this.processCenterMap = this.processCenterMap.bind(this);
        this.processSearchResult = this.processSearchResult.bind(this);
        this.resetMap = this.resetMap.bind(this);
        this.processTripResult = this.processTripResult.bind(this);
        this.MapRef = createRef()

        this.state = {
            gpsLocation: null,
            clickMarker: null,
            markers: [null, null, null],
            distanceReadout: 0,
            tripPoints: null,
            currentViewport: {
                center: MAP_CENTER_DEFAULT,
                zoom: MAP_ZOOM_DEFAULT,
            }
        };
    }

    render() {
        return (
            <Container>
                <NavigationBar
                    processSearchResult={this.processSearchResult}
                    distanceReadout={this.state.distanceReadout}
                    processTripResult={this.processTripResult}
                    serverSettings={this.props.serverSettings}
                    createSnackBar={this.props.createSnackBar}
                />
                <br/>
                {this.renderLeafletMap()}
                <br/>
            </Container>
        );
    }

    renderLeafletMap() {
        return (
            renderRowAndCol(
                <Map
                    className={'mapStyle'}
                    boxZoom={false}
                    useFlyTo={true}
                    viewport={this.state.currentViewport}
                    minZoom={MAP_MIN_ZOOM}
                    maxZoom={MAP_MAX_ZOOM}
                    maxBounds={MAP_BOUNDS}
                    onClick={this.setMarker}
                    ref={this.MapRef}
                >
                    <TileLayer url={MAP_LAYER_URL} attribution={MAP_LAYER_ATTRIBUTION}/>
                    <Control position="topright">
                        <GPS
                            currentViewPort={this.state.currentViewport}
                            processCenterMap={this.processCenterMap}
                        />
                    </Control>
                    {this.renderResetButton()}
                    {this.renderMarkersAndLines()}
                </Map>
            )
        );
    }

    renderResetButton() {
        return (
            <Control position="bottomleft">
                <Button outline size="sm" color="primary"
                        onClick={this.resetMap}>{UNICODE_TRASH_SYMBOL}</Button>{' '}
            </Control>
        );
    }

    renderMarkersAndLines() {
        return (
            <div>
                {this.getMarker(this.state.gpsLocation, CURRENT_LOCATION_ICON)}
                {this.getMarker(this.state.clickMarker, MARKER_ICON)}
                {this.getMarker(this.state.markers[SEARCH_MARKER], MARKER_ICON)}
                {this.getMarker(this.state.markers[FIRST_DISTANCE_MARKER], MARKER_ICON)}
                {this.getMarker(this.state.markers[SECOND_DISTANCE_MARKER], MARKER_ICON)}
                {this.renderLine(this.state.markers[FIRST_DISTANCE_MARKER], this.state.markers[SECOND_DISTANCE_MARKER], "red")}
                {this.renderTripMarkers()}
                {this.renderTripLines()}
            </div>
        );
    }

    renderLine(Point1, Point2, color) {
        if (Point1 && Point2) {
            return (
                <Polyline positions={[Point1, Point2]} color={color}/>
            );
        }
    }

    renderTripMarkers() {
        if (Array.isArray(this.state.tripPoints)) {
            let tripMarkers = []
            for (let i = 0; i < this.state.tripPoints.length; i++) {
                let tempMarker = new MouseEvent("");
                tempMarker.lat = this.state.tripPoints[i][0];
                tempMarker.lng = this.state.tripPoints[i][1];
                tripMarkers.push(<div key={i}>{this.getMarker(tempMarker, MARKER_ICON)}</div>);
            }
            return tripMarkers;
        }
    }

    newBounds(trip) {
        if (Array.isArray(trip)) {
            const map = this.MapRef.current.leafletElement;
            map.fitBounds(trip)
        }
    }

    renderTripLines() {
        if (Array.isArray(this.state.tripPoints)) {
            let tripLines = []
            let length = this.state.tripPoints.length
            for (let i = 0; i < length - 1; i++)
                tripLines.push(<div
                    key={i}>{this.renderLine(this.state.tripPoints[i], this.state.tripPoints[i + 1], "blue")}</div>);
            if (this.state.tripPoints.length > 2)
                tripLines.push(<div
                    key={length - 1}>{this.renderLine(this.state.tripPoints[length - 1], this.state.tripPoints[0], "blue")}</div>);
            return tripLines;
        }
    }

    setMarker(mapClickInfo) {
        this.setState({clickMarker: mapClickInfo.latlng});
    }

    getMarker(markerState, markerType) {
        const initMarker = ref => {
            if (ref) {
                ref.leafletElement
            }
        };

        if (markerState) {
            let markerText = this.getStringMarkerPosition(markerState).split('\n').map(i => {
                return <p>{i}</p>
            });
            return (
                <Marker ref={initMarker} position={markerState} icon={markerType}>
                    <Popup offset={[0, -18]}
                           className="font-weight-bold">{markerText}</Popup>
                </Marker>
            );
        }
    }

    getStringMarkerPosition(markerState) {
        let address = markerState.address;
        if(address === undefined){
            const reverse = require('reverse-geocode')
            let currAddress = reverse.lookup(markerState.lat, markerState.lng, 'us')
            address = "\n" + currAddress.city + ", " + currAddress.state;
        }
        else{
            address = "\n" + markerState.address;
        }
        return markerState.lat.toFixed(3) + ', ' + markerState.lng.toFixed(3) +
                address;
    }

    distanceRequest(place1, place2) {
        if (!place1 || !place2) {
            return;
        }
        sendServerRequest({
            requestType: "distance",
            requestVersion: PROTOCOL_VERSION,
            place1: {"latitude": place1.lat.toString(), "longitude": place1.lng.toString()},
            place2: {"latitude": place2.lat.toString(), "longitude": place2.lng.toString()},
            earthRadius: EARTH_RADIUS_UNITS_DEFAULT.miles,
        }, this.props.serverPort)
            .then(distance => {
                if (distance) {
                    this.processDistanceResponse(distance.data);
                } else {
                    console.log("No response from server.");
                }
            });
    }

    processDistanceResponse(distance) {
        if (isJsonResponseValid(distance, distanceSchema)) {
            //set distance instance variable
            this.setState({distanceReadout: distance.distance});
        } else {
            console.log("Not Valid response");
        }
    }

    processCenterMap(lat, long) {
        this.state.gpsLocation = new MouseEvent("");
        this.state.gpsLocation.lat = lat;
        this.state.gpsLocation.lng = long;
        getAddressFromCoordinates(lat, long).then(result => {
            this.state.gpsLocation.address = result;
            this.setState({
                currentViewport: {
                    center: [lat, long],
                    zoom: MAP_ZOOM_DEFAULT
                }
            });
        });
    }

    processSearchResult(lat, long, i) {
        this.state.markers[i] = new MouseEvent("");
        this.state.markers[i].lat = lat;
        this.state.markers[i].lng = long;
        getAddressFromCoordinates(lat, long).then(result => {
            this.state.markers[i].address = result;
        });
        this.setState({
            currentViewport: {
                center: [lat, long],
                zoom: this.state.currentViewport.zoom
            }
        });
        this.distanceRequest(this.state.markers[FIRST_DISTANCE_MARKER], this.state.markers[SECOND_DISTANCE_MARKER]);
    }

    processTripResult(tripResults) {
        let tempTrip = [];
        for (let i = 0; i < tripResults.length; i++) {
            tempTrip.push([parseFloat(tripResults[i].latitude), parseFloat(tripResults[i].longitude)]);
        }
        this.setState({
            tripPoints: tempTrip
        });
        this.newBounds(tempTrip)
    }

    resetMap() {
        this.setState({
            clickMarker: null,
            markers: [null, null, null],
            distanceReadout: 0,
            tripPoints: null
        })
    }
}
