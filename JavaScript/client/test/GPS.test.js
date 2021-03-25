import './jestConfig/enzyme.config.js';

import React from 'react';
import {mount, shallow} from 'enzyme';

import GPS from "../src/components/Atlas/GPS";

const startProperties = {
    createSnackBar: jest.fn()
};


function testInitialState() {

    const gps = shallow(<GPS createSnackBar={startProperties.createSnackBar}/>);

    let actualLat = gps.state().latitude;
    let actualLong = gps.state().longitude;

    expect(actualLat).toEqual(40.5734);
    expect(actualLong).toEqual(-105.0865);
}

test("Testing state on render", testInitialState);