import './jestConfig/enzyme.config.js';

import React from 'react';
import {shallow} from 'enzyme';

import SaveLoad from "../src/components/Atlas/SaveLoad";
import {SVGMap} from "../src/utils/SVGMap";
import {KMLMap} from "../src/utils/KMLMap";

const startProperties = {
    createSnackBar: jest.fn()
};


function testInitialState() {
    const SL = shallow(<SaveLoad createSnackBar={startProperties.createSnackBar}/>);
    expect(SL.FileReader).toEqual(undefined);
}

test("Testing state on render", testInitialState);

function testCSVNullTrip() {
    const saveLoad = shallow(<SaveLoad createSnackBar={startProperties.createSnackBar}/>);
    let SL = saveLoad.instance();
    let csv = SL.convertJSONtoCSV(null);
    expect(csv).toEqual("Name,Latitude,Longitude\n");
}

test("Testing CSV with null trip", testCSVNullTrip);

function testCSVTrip() {
    const saveLoad = shallow(<SaveLoad createSnackBar={startProperties.createSnackBar}/>);
    let SL = saveLoad.instance();
    let tripJson = {
        "options": {
            "earthRadius": "3959",
            "units": "nautical miles"
        },
        "places": [
            {
                "latitude": "40",
                "name": "Point A",
                "longitude": "-105"
            },
            {
                "latitude": "41",
                "name": "Point B",
                "longitude": "-106"
            }
        ],
        "distances": [
            87,
            87
        ],
        "requestType": "trip",
        "requestVersion": 4
    };
    let csv = SL.convertJSONtoCSV(tripJson);
    expect(csv).toContain("Point");
}

test("Testing CSV with trip", testCSVTrip);

function testCoordinateConversion() {
    const saveLoad = shallow(<SaveLoad createSnackBar={startProperties.createSnackBar}/>);
    let SL = saveLoad.instance();
    let point = [];
    point.latitude = "69.0";
    point.longitude = "420.0";
    let [x, y] = SL.coordinateToPixel(point);
    expect(x).toBeGreaterThan(1700);
    expect(y).toBeGreaterThan(59);
}

test("Testing coordinate conversion", testCoordinateConversion);

function testSVGNullTrip() {
    const saveLoad = shallow(<SaveLoad createSnackBar={startProperties.createSnackBar}/>);
    let SL = saveLoad.instance();
    let svg = SL.convertJSONtoSVG(null);
    let emptyMap = SVGMap + "</svg>";
    expect(svg).toEqual(emptyMap);
}

test("Testing SVG with null trip", testSVGNullTrip);

function testSVGPointAndLine() {
    const saveLoad = shallow(<SaveLoad createSnackBar={startProperties.createSnackBar}/>);
    let SL = saveLoad.instance();
    let point = [];
    point.latitude = "0.0";
    point.longitude = "0.0";
    let svg = SL.drawPoint(point, 0);
    expect(svg).toEqual("<circle id=\"point 0\" cx=\"512\" cy=\"256\" r=\"2.5\" fill=\"red\" data-reactroot=\"\"></circle>");
    svg = SL.drawLine(point, point, 0);
    expect(svg).toEqual("<line id=\"line 0\" x1=\"512\" y1=\"256\" x2=\"512\" y2=\"256\" stroke=\"gray\" stroke-width=\"2\" data-reactroot=\"\"></line>");
}

test("Testing SVG with one point", testSVGPointAndLine);

function testKMLNullTrip() {
    const saveLoad = shallow(<SaveLoad createSnackBar={startProperties.createSnackBar}/>);
    let SL = saveLoad.instance();
    let kml = SL.convertJSONtoKML(null);
    let emptyMap = KMLMap + "</Document>\n</kml>";
    expect(kml).toEqual(emptyMap);
}

test("Testing KML with null trip", testKMLNullTrip);

function testKMLMarkAndLine() {
    const saveLoad = shallow(<SaveLoad createSnackBar={startProperties.createSnackBar}/>);
    let SL = saveLoad.instance();
    let point = [];
    point.name = "test";
    point.latitude = "0.0";
    point.longitude = "0.0";
    let expectation = "<coordinates>";
    let kml = SL.addMark(point);
    expect(kml).toContain(expectation);
    kml = SL.addLine(point, point);
    expect(kml).toContain(expectation);
}

test("Testing KML with one point", testKMLMarkAndLine);