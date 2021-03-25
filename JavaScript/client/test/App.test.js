import './jestConfig/enzyme.config.js';

import React from 'react';
import {shallow} from 'enzyme';
import { SnackbarProvider} from 'notistack';

import App, {HookCaller} from '../src/components/App';

const startProperties = {
    createSnackBar: jest.fn()
};

function testInitialAppState() {

    const app = shallow(<App createSnackBar={startProperties.createSnackBar}/>);
    let appInstance = app.instance()
    expect(appInstance.render()).toEqual(
        <SnackbarProvider
            maxSnack={3} preventDuplicate={true}>
            <HookCaller/>
        </SnackbarProvider>);
}

test("Testing App's Initial State", testInitialAppState);