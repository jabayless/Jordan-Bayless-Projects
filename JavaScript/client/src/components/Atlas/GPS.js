import React, {Component} from "react";
import {Button} from "reactstrap";

const UNICODE_GPS_SYMBOL = "\uD83D\uDCCD";

const MAP_CENTER_DEFAULT = [40.5734, -105.0865];

export default class GPS extends Component {

    constructor(props) {
        super(props);

        this.setMapToCurrentPosition = this.setMapToCurrentPosition.bind(this);
        this.getPositionSuccessCallback = this.getPositionSuccessCallback.bind(this);

        this.state = {
            latitude: MAP_CENTER_DEFAULT[0],
            longitude: MAP_CENTER_DEFAULT[1]
        }
    }

    componentDidMount() {
        this.setMapToCurrentPosition();
    }


    render() {
        return (
            this.renderCenterButton()
        );
    }

    renderCenterButton() {
        return (
            <div>
                <Button outline size="sm" color="primary"
                        onClick={this.setMapToCurrentPosition}>{UNICODE_GPS_SYMBOL}</Button>{' '}
            </div>
        );
    }

    setMapToCurrentPosition() {
        if (this.geolocationDidMount()) {
            navigator.geolocation.getCurrentPosition(this.getPositionSuccessCallback, this.getPositionErrorCallback, {enableHighAccuracy: true});
        }
    }

    geolocationDidMount() {
        return "geolocation" in navigator;
    }

    getPositionSuccessCallback(position) {
        this.setState({
            latitude: position.coords.latitude,
            longitude: position.coords.longitude
        }, this.centerMap);
    }

    getPositionErrorCallback(error) {
        console.log("Could not get client load position, code: " + error);
    }

    centerMap() {
        this.props.processCenterMap(this.state.latitude, this.state.longitude);
    }

}