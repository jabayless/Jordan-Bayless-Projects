import React, {Component} from "react";
import {Button, Col, Modal, ModalBody, ModalFooter, ModalHeader, Table} from "reactstrap";
import {getAddressFromCoordinates} from "./ReverseGeocode";

export default class Itinerary extends Component {

    constructor(props) {
        super(props);
        this.state = {
            showItinerary: false,
            roundTripDistance: 0,
        }
    }

    render() {
        return (
            <Col>
                {this.renderModal()}
            </Col>
        );
    }

    renderModal() {
        const toggle = () => this.setState({showItinerary: !this.state.showItinerary});
        return (
            <div>
                <Button block color="primary" onClick={toggle}>{"Itinerary"}</Button>
                <Modal isOpen={this.state.showItinerary} toggle={toggle} className="primary">
                    <ModalHeader toggle={toggle}>{"Itinerary"}</ModalHeader>
                    <ModalBody>
                        {this.renderItinerary()}
                    </ModalBody>
                    <ModalFooter>
                        {this.renderReverseButton()}
                        <Button color="secondary" onClick={toggle}>Cancel</Button>{' '}
                    </ModalFooter>
                </Modal>
            </div>
        );
    }

    renderItinerary() {
        return (
            <Table striped>
                <thead>
                <tr>
                    <th>Point</th>
                    <th>Distance to Next Point</th>
                </tr>
                </thead>
                <tbody>
                {this.renderItineraryList()}
                </tbody>
                <thead>
                <tr>
                    <th>Total Distance</th>
                    <th>{this.state.roundTripDistance} {this.props.selectedUnit}</th>
                </tr>
                </thead>
            </Table>
        );
    }

    renderItineraryList() {
        if (this.props.tripJson === null)
            return;
        let itineraryList = [];
        let legDistance = 0;
        let locationName = "";
        let locationAddress = "";
        let latitude = 0;
        let longitude = 0;
        this.state.roundTripDistance = 0;
        for (let i = 0; i < this.props.tripJson.distances.length; i++) {
            latitude = this.props.tripJson.places[i].latitude;
            longitude = this.props.tripJson.places[i].longitude;
            this.state.roundTripDistance += this.props.tripJson.distances[i];
            getAddressFromCoordinates(latitude, longitude).then(result => {
                legDistance = this.props.tripJson.distances[i];
                locationName = this.props.tripJson.places[i].name;
                locationAddress = result;
                itineraryList.push(
                    <tr key={i}>
                        <td>{locationName}{": "}{locationAddress}</td>
                        <td>{legDistance}</td>
                    </tr>);
            });
        }
        return (itineraryList);
    }

    renderReverseButton() {
        if (this.props.tripJson !== null)
            return (
                <div>
                    <Button color="primary" onClick={this.reverseTripPoints}>Reverse Destinations</Button>{' '}
                </div>
            );
    }

    reverseTripPoints = () => {
        //assume {a->b->c->d} or similar
        //then output would be {a->d->c->b}
        let reversedPlaces = this.props.tripJson.places.reverse();
        let firstPlace = this.props.tripJson.places.pop();
        reversedPlaces.unshift(firstPlace);

        let last_to_first = this.props.tripJson.distances.pop();
        let reversedDistances = this.props.tripJson.distances.reverse();
        reversedDistances.unshift(last_to_first);

        this.props.tripJson.distances = reversedDistances;
        this.props.tripJson.places = reversedPlaces;
        this.setState({showItinerary: !this.state.showItinerary});
    }
}
