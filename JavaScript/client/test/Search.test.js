import './jestConfig/enzyme.config.js';

import React from 'react';
import {shallow} from 'enzyme';

import Search from "../src/components/Atlas/Search";

const startProperties = {
    createSnackBar: jest.fn()
};

function testInitialState() {
    const search = shallow(<Search createSnackBar={startProperties.createSnackBar}/>);
    expect(search.state().lat).toEqual(null);
    expect(search.state().long).toEqual(null);
    expect(search.state().validResponse).toEqual(false);
    expect(search.state().errorAlert.alertVisible).toEqual(false);
}

test("Testing state on render", testInitialState);


function testErrorMessage() {
    const search = shallow(<Search createSnackBar={startProperties.createSnackBar}/>);
    let searchInstance = search.instance();
    searchInstance.displayNewErrorMessage("Test");
    expect(search.state().errorAlert.alertVisible).toEqual(true);
    expect(search.state().errorAlert.errorMessage).toEqual("Test");
}

test("Testing error message on change", testErrorMessage);


function testSearchButton() {
    const search = shallow(<Search createSnackBar={startProperties.createSnackBar}/>);
    simulateOnClickEvent(search);
    expect(search.state().test).toEqual(true);
}

test("Testing search button to call the right method", testSearchButton);

function testInputWithCoordinates()
{
    const search = shallow(<Search createSnackBar={startProperties.createSnackBar}/>);
    let searchInstance = search.instance();
    searchInstance.locationInput("40, -105");
    expect(search.state().lat).toEqual(40);
    expect(search.state().long).toEqual(-105);
}

test("Testing location input of 40, -105", testInputWithCoordinates);

function simulateOnClickEvent(reactWrapper) {
    reactWrapper.find('Button').at(0).simulate('click');
    reactWrapper.update();
}