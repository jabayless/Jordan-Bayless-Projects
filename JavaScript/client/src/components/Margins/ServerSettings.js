import React, {Component} from "react";
import {Button, Col, Input, Modal, ModalBody, ModalFooter, ModalHeader, Row} from "reactstrap";

import {sendServerRequest, isJsonResponseValid} from "../../utils/restfulAPI";

import * as configSchema from "../../../schemas/ResponseConfig";

export default class ServerSettings extends Component {

    constructor(props) {
        super(props);

        this.state = {
            inputText: this.props.serverSettings.serverPort,
            validServer: null,
            config: {}
        };

        this.saveInputText = this.state.inputText;
    }

    render() {
        return (
            <div>
                <Modal isOpen={this.props.isOpen} toggle={() => this.props.toggleOpen()}>
                    <ModalHeader toggle={() => this.props.toggleOpen()}>Server Connection</ModalHeader>
                    {this.renderSettings(this.getCurrentServerInfo())}
                    {this.renderActions()}
                </Modal>
            </div>
        );
    }

    renderSettings(currentServerInfo) {
        return (
            <ModalBody>
                {this.renderRowAndCol("Name: ", currentServerInfo[0])}
                {this.renderRowAndCol("URL: ", this.renderInputField())}
                {this.renderRowAndCol("Version: ", currentServerInfo[1])}
                {this.renderRowAndCol("Requests: ", currentServerInfo[2])}
            </ModalBody>
        );
    }

    renderRowAndCol(text, obj) {
        return (
            <Row className="m-2">
                <Col xs={2}>
                    {text}
                </Col>
                <Col xs={10}>
                    {obj}
                </Col>
            </Row>
        );
    }

    renderInputField() {
        let valid = this.state.validServer === null ? false : this.state.validServer;
        let notValid = this.state.validServer === null ? false : !this.state.validServer;
        return (
            <Input onChange={(e) => this.updateInput(e.target.value)}
                   value={this.state.inputText}
                   placeholder={this.props.serverPort}
                   valid={valid}
                   invalid={notValid}
            />
        );
    }

    renderActions() {
        return (
            <ModalFooter>
                <Button color="primary" onClick={() => this.resetServerSettingsState()}>Cancel</Button>
                <Button color="primary" onClick={() => {
                    this.props.processServerConfigSuccess(this.state.config, this.state.inputText);
                    this.resetServerSettingsState(this.state.inputText);
                }} disabled={!this.state.validServer}>
                    Save
                </Button>
            </ModalFooter>
        );
    }

    getCurrentServerInfo() {
        let currentServerInfo = this.props.serverSettings.serverConfig && this.state.validServer === null ?
            [this.props.serverSettings.serverConfig.serverName,
                this.props.serverSettings.serverConfig.requestVersion,
                this.props.serverSettings.serverConfig.supportedRequests] : ["", "", ""];

        if (this.state.config && Object.keys(this.state.config).length > 0) {
            currentServerInfo[0] = this.state.config.serverName;
            currentServerInfo[1] = this.state.config.requestVersion;
            currentServerInfo[2] = this.state.config.supportedRequests;
        }

        currentServerInfo[2] = this.serverRequestToString(currentServerInfo[2]);

        return currentServerInfo;
    }

    serverRequestToString(serverRequests) {
        if (!serverRequests)
            return serverRequests;

        let requestsString = serverRequests[0];
        for (let i = 1; i < serverRequests.length; i++)
            requestsString += " " + serverRequests[i];
        return requestsString;
    }

    updateInput(value) {
        this.setState({inputText: value}, () => {
            if (this.shouldAttemptConfigRequest(value)) {
                sendServerRequest({requestType: "config", requestVersion: 1}, value)
                    .then(config => {
                        if (config) {
                            this.processConfigResponse(config.data)
                        } else {
                            this.setState({validServer: true, config: config});
                        }
                    });
            } else {
                this.setState({validServer: false, config: {}});
            }
        });
    }

    shouldAttemptConfigRequest(resource) {
        const urlRegex = /https?:\/\/.+/;
        return resource.match(urlRegex) !== null && resource.length > 15;
    }

    processConfigResponse(config) {
        if (!isJsonResponseValid(config, configSchema)) {
            this.setState({validServer: false, config: false});
        } else {
            this.setState({validServer: true, config: config});
        }
    }

    resetServerSettingsState(inputText = this.saveInputText) {
        this.props.toggleOpen();
        this.setState({
            inputText: inputText,
            validServer: null,
            config: false
        });
    }
}
