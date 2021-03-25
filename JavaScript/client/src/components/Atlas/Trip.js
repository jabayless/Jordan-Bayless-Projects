import React, {Component} from "react";
import {Button, Col, Form, FormGroup, Input, Label, Modal, ModalBody, ModalFooter, ModalHeader, Row} from 'reactstrap';

import Search from "./Search";
import SaveLoad from "./SaveLoad";
import Itinerary from "./Itinerary";
import ModifyTrip from "./ModifyTrip";
import {EARTH_RADIUS_UNITS_DEFAULT, EARTH_RADIUS_UNITS_KM, EARTH_RADIUS_UNITS_NM, PROTOCOL_VERSION} from "../../utils/constants";
import {isJsonResponseValid, sendServerRequest} from "../../utils/restfulAPI";
import * as tripSchema from "../../../schemas/ResponseTrip.json";

export default class Trip extends Component {

    constructor(props) {
        super(props);

        this.state = {
            showUnits: false,
            modal: [false, false],
            tripName: "My Trip",
            selectedUnit: "Miles",
            earthRadius: EARTH_RADIUS_UNITS_DEFAULT.miles,
            doOptimize: true,
            numPoints: 2,
            tripJson: null,
            tripPoints: [[null, null, ""], [null, null, ""]], // [lat, long, name]
            validResponse: false
        }

        this.processTripInput = this.processTripInput.bind(this);
        this.processSaveLoad = this.processSaveLoad.bind(this);
    }

    render() {
        return (
            <Row>
                <Col>
                    {this.renderModal("Info", this.renderInfoInput(), 1)}
                </Col>
                <Col>
                    {this.renderModal("Points", this.renderPointInput(), 2)}
                </Col>
                <Itinerary
                    tripJson={this.state.tripJson}
                    selectedUnit={this.state.selectedUnit}
                />
                <SaveLoad
                    processSaveLoad={this.processSaveLoad}
                    tripJson={this.state.tripJson}
                    tripName={this.state.tripName}
                    createSnackBar={this.props.createSnackBar}
                />
            </Row>
        );
    }

    renderModal(header, content, i) {
        const toggle = () => this.setState({modal: {[i]: !this.state.modal[i]}});
        return (
            <div>
                <Button block color="primary" onClick={toggle}>{header}</Button>
                <Modal isOpen={this.state.modal[i]} toggle={toggle} className="primary">
                    <ModalHeader toggle={toggle}>{header}</ModalHeader>
                    <ModalBody>
                        {content}
                    </ModalBody>
                    <ModalFooter>
                        {this.renderSubmitButton(i)}
                        <Button color="secondary" onClick={toggle}>Cancel</Button>{' '}
                    </ModalFooter>
                </Modal>
            </div>
        );
    }

    renderSubmitButton(i) {
        const submit = () => {
            this.sendTripRequest();
            this.setState({modal: {[i]: !this.state.modal[i]}});
        }
        return (
            <div>
                <Button color="primary" onClick={submit}>Submit</Button>{' '}
            </div>
        );
    }

    renderInfoInput() {
        return (
            <Form>
                <FormGroup>
                    <Label>Trip Name</Label>
                    <Input id="name"
                           onChange={e => this.setState({tripName: e.target.value})}
                           placeholder="My Trip"
                           value={this.state.tripName}/>
                </FormGroup>
                {this.renderInfoUnits()}
            </Form>
        );
    }

    customUnit = () => {
        if (this.state.showUnits) {
            return (
                <div>
                    <FormGroup>
                        <Label>Unit Name</Label>
                        <Input id="Custom Unit Name" placeholder={this.state.selectedUnit}
                               onChange={e => this.setState({selectedUnit: e.target.value})}
                               value={this.state.selectedUnit}/>
                        <Label>Earth Radius</Label>
                        <Input id="radius" onChange={e => this.setState({earthRadius: e.target.value})}
                               value={this.state.earthRadius}/>
                    </FormGroup>
                </div>);
        }
    }

    renderInfoUnits() {
        const updateRadius = (e) => {
                this.setState({earthRadius: e.target.value});
                if (parseFloat(e.target.value) === EARTH_RADIUS_UNITS_KM) {
                    this.setState({selectedUnit: "Kilometers"});
                } else if (parseFloat(e.target.value) === EARTH_RADIUS_UNITS_DEFAULT.miles) {
                    this.setState({selectedUnit: "Miles"});
                } else if (parseFloat(e.target.value) === EARTH_RADIUS_UNITS_NM) {
                    this.setState({selectedUnit: "Nautical Miles"});}}
        const toggle = () => {this.setState({showUnits: !this.state.showUnits});}
        return (
            <FormGroup>
                <Label>Units</Label>
                <div>
                    <Button color="primary" onClick={toggle}>Custom Unit</Button>{' '}
                    {this.customUnit()}
                    <Button color="primary" optionname="kilometers" value={EARTH_RADIUS_UNITS_KM}
                            onClick={updateRadius}>Kilometers</Button>{' '}
                    <Button color="primary" optionname="miles" value={EARTH_RADIUS_UNITS_DEFAULT.miles}
                            onClick={updateRadius}>Miles</Button>{' '}
                    <Button color="primary" optionname="nautical miles" value={EARTH_RADIUS_UNITS_NM}
                            onClick={updateRadius}>Nautical Miles</Button>{' '}
                    <p>Current Unit: {this.state.selectedUnit}</p>
                </div>
            </FormGroup>
        );
    }

    doOptimizeToggle = (value) => {
        this.setState({doOptimize: value})
    }
    submitModify = () => {
        this.setState({modal: {[0]: !this.state.modal[0]}});
        this.sendTripRequest();
    }
    modifyPoints = (points,num) => {
        this.setState({numPoints: num, tripPoints: points});
    }

    renderPointInput() {
        const increment = () => {
            this.setState({numPoints: this.state.numPoints + 1});
            this.state.tripPoints.push([null, null, ""]);
        }
        let searchList = [];
        for (let i = 0; i < this.state.numPoints; i++) {
            searchList.push(<div key={i}>Point #{i + 1}<Search processTripInput={this.processTripInput}
                                                               tripPoints={this.state.tripPoints}
                                                               searchInput={this.state.tripPoints[i][2]} i={i}
                                                               serverSettings={this.props.serverSettings}/><br/>
            </div>);
        }
        return (
            <div>
                {searchList}
                <Button color="primary" onClick={increment} style={{float: "right"}}>Add Point</Button>{' '}
                <ModifyTrip
                    doOptimizeToggle={this.doOptimizeToggle}
                    submitModify={this.submitModify}
                    numPoints={this.state.numPoints}
                    tripPoints={this.state.tripPoints}
                    optimize={this.state.doOptimize}
                    modifyPoints={this.modifyPoints}/>
            </div>
        );
    }


    processTripInput(lat, long, name, i) {
        this.state.tripPoints[i] = [lat, long, name];
    }

    processSaveLoad(NewState) {
        this.setState(NewState);
        this.sendTripRequest();
    }

    sendTripRequest() {
        let jsonPlaces = this.convertPointsToJSON();
        let responseTime = "1"
        if (!this.state.doOptimize){
            responseTime = "0"
        }
        let body = {
            requestType: "trip",
            requestVersion: PROTOCOL_VERSION,
            options: {
                "earthRadius": String(this.state.earthRadius),
                "title": this.state.tripName,
                "response": responseTime,
                "units": this.state.selectedUnit
            },
            places: jsonPlaces
        }
        sendServerRequest(body, this.props.serverPort)
            .then(trip => {
                if (trip) {
                    this.processTripResponse(trip.data)
                } else {
                    this.setState({validResponse: false});
                }
            });
    }

    convertPointsToJSON() {
        let jsonPlaces = []
        for (let i = 0; i < this.state.tripPoints.length; i++) {
            if (this.state.tripPoints[i][0] !== null)
                jsonPlaces.push({
                    "latitude": this.state.tripPoints[i][0].toString(),
                    "longitude": this.state.tripPoints[i][1].toString(),
                    "name": this.state.tripPoints[i][2]
                },)
        }
        return jsonPlaces
    }

    processTripResponse(response) {
        if (!isJsonResponseValid(response, tripSchema)) {
            this.setState({validResponse: false});
        } else {
            this.setState({validResponse: true, tripJson: response});
            this.props.processTripResult(response.places);
        }
    }
}