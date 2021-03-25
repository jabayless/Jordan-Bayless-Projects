import './jestConfig/enzyme.config.js';

import React from 'react';
import {shallow} from 'enzyme';
import {EARTH_RADIUS_UNITS_NM, EARTH_RADIUS_UNITS_DEFAULT, EARTH_RADIUS_UNITS_KM} from '../../client/src/utils/constants'

import Trip from "../src/components/Atlas/Trip";

const startProperties = {
    createSnackBar: jest.fn()
};

function testInitialState() {
    const trip = shallow(<Trip createSnackBar={startProperties.createSnackBar}/>);
    expect(trip.state().earthRadius).toEqual(EARTH_RADIUS_UNITS_DEFAULT.miles);
    expect(trip.state().validResponse).toEqual(false);
}

test("Testing state on render", testInitialState);


function processTripInput() {
    const trip = shallow(<Trip createSnackBar={startProperties.createSnackBar}/>);
    let tripInstance = trip.instance();
    expect(trip.state().tripPoints[0]).toEqual([null, null, ""]);
    tripInstance.processTripInput(40, -105, "Place", 0);
    expect(trip.state().tripPoints[0]).toEqual([40, -105, "Place"]);
}

test("Testing trip input", processTripInput);

/*function processTripResponse() {
    const trip = shallow(<Trip createSnackBar={startProperties.createSnackBar}/>);
    let tripInstance = trip.instance();
    let testResponse = {
        requestType: "trip",
        requestVersion: PROTOCOL_VERSION,
        options: {
            earthRadius: "3959"
        },
        places: [
            {
                latitude: "40",
                longitude: "-105",
                name: "A"
            },
            {
                latitude: "41",
                longitude: "-106",
                name: "B"
            }
        ],
        distances: [
            87
        ]
    }
    expect(trip.state().validResponse).toEqual(false);
    tripInstance.processTripResponse(null);
    expect(trip.state().validResponse).toEqual(false);
    tripInstance.processTripResponse(testResponse);
    expect(trip.state().validResponse).toEqual(true);
}

test("Testing trip response", processTripResponse);*/

function testConvertPoints() {
    const trip = shallow(<Trip createSnackBar={startProperties.createSnackBar}/>);
    let tripInstance = trip.instance();

    let result = tripInstance.convertPointsToJSON();
    expect(result).toEqual([]);

    tripInstance.setState({tripPoints: [[40, -105, "A"], [41, -106, "B"]]})
    result = tripInstance.convertPointsToJSON();
    expect(result).toEqual([{
        latitude: "40",
        longitude: "-105",
        name: "A"
    },
        {
            latitude: "41",
            longitude: "-106",
            name: "B"
        }
    ]);
}

test("Testing points to json", testConvertPoints);