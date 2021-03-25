import React, {Component} from "react";
import {Alert, Button, Input, InputGroup, InputGroupAddon,} from "reactstrap";
import {Tabs, Tab, ListGroup, Card} from "react-bootstrap";
import {isJsonResponseValid, sendServerRequest} from "../../utils/restfulAPI";
import {PROTOCOL_VERSION} from "../../utils/constants";
import * as findSchema from "../../../schemas/ResponseFind.json";
import PointNote from "./PointNote";

export default class Search extends Component {

    constructor(props) {
        super(props);

        this.state = {
            countryFilter: [],
            typeFilter: [],
            lat: null,
            long: null,
            splitButtonOpen: false,
            errorAlert: {
                alertVisible: false,
                errorMessage: "Error: Something went wrong..."
            },
            searchInput: this.props.searchInput,
            validResponse: false,
            showCard: false,
            config: {},
            test: false,
            test2: "",
            placeInfo:{
                placeName: "",
                placeRegion: "",
                placeCountry: "",
                placeWiki: "",
                placeAltitude: ""
            }
        };
    }

    render() {
        return (
            <div>
                {this.renderSearchBar()}
                {this.renderErrorAlert()}
                {this.renderCard()}
                {this.renderSearchResults()}
            </div>
        );
    }

    renderSearchBar() {
        return (
            <InputGroup size="md">
                <Input
                    className="text-center"
                    placeholder="Enter a location!"
                    value={this.state.searchInput}
                    onChange={e => this.setState({searchInput: e.target.value})}/>
                {this.renderSearchButton()}
            </InputGroup>
        );
    }
    renderSearchButton() {
        return (
            <InputGroupAddon addonType="append">
                <Button
                    type="search"
                    color="primary"
                    onClick={() => this.locationInput(this.state.searchInput)}
                >Search
                </Button>
            </InputGroupAddon>
        );
    }
    renderSearchResults() {
        const RESULTS = "Results";
        const TYPES = "Filter by Type";
        const COUNTRIES = "Filter by Country";
        //when user clicks on filter, the filter state variable is set
        //when set, the result list function will change the result based on the the filters in the
        //filter state variable
        if (this.state.validResponse === true) {
            let typeList = this.filterList(this.props.serverSettings.serverConfig.filters.type, this.state.typeFilter);
            let countryList = this.filterList(this.props.serverSettings.serverConfig.filters.where, this.state.countryFilter);
            return (
                <Tabs defaultActiveKey={RESULTS} justify>
                    <Tab eventKey={RESULTS} title={RESULTS}>
                        {this.renderList(this.resultList())}
                    </Tab>
                    <Tab eventKey={TYPES} title={TYPES}>
                        {this.renderList(typeList)}
                    </Tab>
                    <Tab eventKey={COUNTRIES} title={COUNTRIES}>
                        {this.renderList(countryList)}
                    </Tab>
                </Tabs>
            );
        }
    }

    renderList(items) {
        return (
            <div style={{
                overflowY: 'scroll',
                maxHeight: '150px'
            }}>
                <ListGroup className="col text-center">
                    {items}
                </ListGroup>
            </div>
        );
    }

    resultList() {
        const removeList = (e) => {
            this.setState({validResponse: false});
            let lat = parseFloat(this.state.config.places[e.target.id].latitude);
            let long = parseFloat(this.state.config.places[e.target.id].longitude);
            this.setState({lat: lat, long: long}, this.callProcessResult);
            this.setState({showCard: true});
            this.setState({placeInfo: {
                    placeName: this.state.config.places[e.target.id].name,
                    placeRegion: this.state.config.places[e.target.id].region,
                    placeCountry: this.state.config.places[e.target.id].country,
                    placeWiki: this.state.config.places[e.target.id].url,
                    placeAltitude: this.state.config.places[e.target.id].altitude
                }});
        }

        let resultList = [];
        for (let i = 0; i < this.state.config.places.length; i++) {
            resultList.push(<ListGroup.Item action id={i} key={i} onClick={removeList}>
                    {"#" + (i + 1) + " " + this.state.config.places[i].name + " - " + this.state.config.places[i].region + " - " + this.state.config.places[i].country}
                </ListGroup.Item>
            );
        }
        return resultList;
    }

    filterList(filter, state) {
        let tempList = [];
        let color = "";
        const narrow =(e)=> {
            let item = filter[e.target.id];
            let index = state.indexOf(item);
            (index >= 0) ? state.splice(index, 1) : state.push(item);
            this.locationInput(this.state.searchInput);
        }
        for (let i = 0; i < filter.length; i++) {
            (state.includes(filter[i])) ? color = "info" : color = "";
            tempList.push(<ListGroup.Item action id={i} key={i} onClick={narrow} variant = {color}>
                    {filter[i]}
                </ListGroup.Item>);
        }
        return tempList;
    }

    renderErrorAlert() {
        const onDismiss = () => this.setState({errorAlert: {alertVisible: false}});
        return (
            <Alert color="danger" isOpen={this.state.errorAlert.alertVisible} toggle={onDismiss}>
                {this.state.errorAlert.errorMessage}
            </Alert>
        );

    }

    displayNewErrorMessage(message) {
        this.setState({
            errorAlert: {
                alertVisible: true,
                errorMessage: message
            }
        })
    }

    locationInput(searchValue) {
        this.setState({validResponse: false})
        this.setState({test: true})
        this.setState({test2: searchValue})
        let Coordinates = require('coordinate-parser');
        try {
            let cord = new Coordinates(searchValue);
            this.setState({lat: cord.getLatitude(), long: cord.getLongitude()}, this.callProcessResult);
        } catch (err) {
            this.queryFind(searchValue);
        }
    }

    queryFind(place) {
        let body = {
            requestType: "find",
            requestVersion: PROTOCOL_VERSION,
            match: place,
            narrow: {type:this.state.typeFilter, where:this.state.countryFilter}
        }
        if (place === "") {
            body = {
                requestType: "find",
                requestVersion: PROTOCOL_VERSION
            }
        }
        sendServerRequest(body, this.props.serverPort)
            .then(find => {
                if (find) {
                    this.processFindResponse(find.data)
                }
            });
    }

    processFindResponse(response) {
        if (!isJsonResponseValid(response, findSchema)) {
            this.setState({validResponse: false, config: false});
            this.displayNewErrorMessage("Invalid server response");
        } else {
            this.utilizeFindResponse(response);
        }
    }

    utilizeFindResponse(response) {
        if (response.places.length === 0) {
            this.displayNewErrorMessage("No matches found");
            this.setState({countryFilter: [], typeFilter: []});
        } else if (response.places.length === 1) {
            let lat = parseFloat(response.places[0].latitude);
            let long = parseFloat(response.places[0].longitude);
            this.setState({lat: lat, long: long}, this.callProcessResult);
        } else {
            this.setState({validResponse: true, config: response});
        }
    }

    cardWithLink() {
        if(this.state.placeInfo.placeWiki !== undefined)
        {
            return(<Card.Link href={this.state.placeInfo.placeWiki}>Wiki Page</Card.Link>)
        }
    }

    renderCard(){
        if (this.state.showCard) {
            return (
                <Card>
                    <Card.Body>
                        <Card.Title>{this.state.placeInfo.placeName}</Card.Title>
                        <Card.Text>
                            Country: {this.state.placeInfo.placeCountry}<br/>
                            Region: {this.state.placeInfo.placeRegion}<br/>
                            Coordinates: ({this.state.lat},{this.state.long})<br/>
                            Altitude: {this.state.placeInfo.placeAltitude}<br/>
                        </Card.Text>
                        {this.cardWithLink()}
                        <PointNote/>
                    </Card.Body>
                </Card>
            )
        }
    }

    callProcessResult() {
        if (this.props.processSearchResult)
            this.props.processSearchResult(this.state.lat, this.state.long, this.props.i);
        if (this.props.processTripInput)
            this.props.processTripInput(this.state.lat, this.state.long, this.state.searchInput, this.props.i);
    }

}


