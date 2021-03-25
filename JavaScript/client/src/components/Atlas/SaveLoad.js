import React, {Component} from "react";
import {Button, Col, Form, FormGroup, Input, Label, Modal, ModalBody, ModalFooter, ModalHeader,} from "reactstrap";
import {renderToString} from 'react-dom/server'

import {downloadFile, isJsonResponseValid} from "../../utils/restfulAPI";
import * as fileSchema from "../../../schemas/TripFile.json";
import {SVGMap} from "../../utils/SVGMap";
import {KMLMap} from "../../utils/KMLMap";

const JSON_EXT = ".json";
const JSON_TYPE = "application/json";
const CSV_EXT = ".csv";
const CSV_TYPE = "text/csv";
const KML_EXT = ".kml";
const KML_TYPE = "application/vnd.google-earth.kml+xml";
const SVG_EXT = ".svg";
const SVG_TYPE = "image/svg+xml";
const WIDTH = 180.0;
const HEIGHT = 90.0;
const RATIO = (512.0 / 180.0);

export default class SaveLoad extends Component {

    constructor(props) {
        super(props);

        this.state = {
            modal: false,
            fileExtension: JSON_EXT
        }

        this.inputOpenFileRef = React.createRef()
        this.FileReader = null;
    }

    render() {
        return (
            <>
                <Col>
                    {this.renderSaveModal()}
                </Col>
                <Col>
                    {this.renderLoadButton()}
                </Col>
            </>
        );
    }

    renderSaveModal() {
        const toggle = () => this.setState({modal: !this.state.modal});
        return (
            <>
                <Button block color="primary" onClick={toggle}>Save</Button>
                <Modal isOpen={this.state.modal} toggle={toggle}>
                    <ModalHeader toggle={toggle}>Save</ModalHeader>
                    <ModalBody>
                        {this.renderSaveOptions()}
                    </ModalBody>
                    <ModalFooter>
                        {this.renderSaveButton()}
                        <Button color="secondary" onClick={toggle}>Cancel</Button>
                    </ModalFooter>
                </Modal>
            </>
        );
    }

    renderSaveOptions() {
        const select = (e) => this.setState({fileExtension: e.target.value});
        return (
            <Form>
                <FormGroup>
                    <Label for="fileSelect">Save Trip As: </Label>
                    <Input type="select" name="select" id="fileSelect" onClick={select}>
                        <option value={JSON_EXT}>JSON</option>
                        <option value={CSV_EXT}>CSV</option>
                        <option value={KML_EXT}>KML</option>
                        <option value={SVG_EXT}>SVG</option>
                    </Input>
                </FormGroup>
            </Form>
        );
    }

    renderSaveButton() {
        const download = () => this.processSaveOption(this.state.fileExtension);
        return (
            <Button color="primary" onClick={download}>Download</Button>
        );
    }

    renderLoadButton() {
        const showOpenFileDlg = () => this.inputOpenFileRef.current.click()
        return (
            <div>
                <input ref={this.inputOpenFileRef} type="file" style={{display: "none"}}
                       onChange={this.FileSelectionChange}/>
                <Button block color="primary" onClick={showOpenFileDlg}>Load</Button>{''}
            </div>
        )
    }

    ProcessFileUploaded = () => {
        let jsonInput = null;
        try {
            jsonInput = JSON.parse(this.FileReader.result)
        } catch (e) {
            this.props.createSnackBar("File is not in JSON format.");
            return;
        }
        let NewState = {}
        if (isJsonResponseValid(jsonInput, fileSchema)) {
            NewState.earthRadius = jsonInput.options.earthRadius
            NewState.tripName = jsonInput.options.title
            NewState.selectedUnit = jsonInput.options.units

            NewState.numPoints = jsonInput.places.length;
            NewState.tripPoints = [[null, null, ""]]
            for (let place = 0; place < NewState.numPoints; place++) {
                let curPlace = jsonInput.places[place]
                NewState.tripPoints[place] = [parseFloat(curPlace.latitude), parseFloat(curPlace.longitude), curPlace.name]
            }
            this.props.processSaveLoad(NewState)
        } else {
            this.props.createSnackBar("File is not in Trip format.");
        }
    }

    FileSelectionChange = event => {
        try {
            this.FileReader = new FileReader()
            this.FileReader.onloadend = this.ProcessFileUploaded
            this.FileReader.readAsText(event.target.files[0])
        } catch (e) {
            this.props.createSnackBar("Could not process file.");
        }
    }

    processSaveOption(fileExtension) {
        let fileContents = "";
        let fileType = "";
        switch (fileExtension) {
            case JSON_EXT:
                fileContents = JSON.stringify(this.props.tripJson);
                fileType = JSON_TYPE;
                break;
            case CSV_EXT:
                fileContents = this.convertJSONtoCSV(this.props.tripJson);
                fileType = CSV_TYPE;
                break;
            case KML_EXT:
                fileContents = this.convertJSONtoKML(this.props.tripJson);
                fileType = KML_TYPE;
                break;
            case SVG_EXT:
                fileContents = this.convertJSONtoSVG(this.props.tripJson);
                fileType = SVG_TYPE;
                break;
        }
        downloadFile(fileContents, this.props.tripName + fileExtension, fileType);
    }

    convertJSONtoCSV(tripJson) {
        let csv = "Name,Latitude,Longitude\n";
        if (tripJson !== null) {
            // convert json and grab list of places
            let json = JSON.stringify(tripJson);
            json = JSON.parse(json);
            json = Object.values(json);
            json = json[1];
            for (let i = 0; i < json.length; i++) {
                let values = Object.values(json[i]); // grab line
                [values[0], values[1]] = [values[1], values[0]]; // swap element 0 and 1
                values[0] = '\"' + values[0] + '\"'; // add quotes to name
                csv += values.join(',') + '\n'; // make string and add to file
            }
        }
        return csv;
    }

    convertJSONtoSVG(tripJson) {
        let svg = SVGMap;
        if (tripJson !== null) {
            let tripLength = tripJson.places.length - 1;
            for (let i = 0; i < tripLength; i++) {
                svg += this.drawPoint(tripJson.places[i], i);
                svg += this.drawLine(tripJson.places[i], tripJson.places[i + 1], i);
            }
            svg += this.drawPoint(tripJson.places[tripLength], tripLength);
            svg += this.drawLine(tripJson.places[tripLength], tripJson.places[0], tripLength);
        }
        svg += "</svg>";
        return svg;
    }

    coordinateToPixel(point) {
        let x = (parseFloat(point.longitude) + WIDTH) * RATIO;
        let y = (parseFloat(point.latitude) - HEIGHT) * (-1) * RATIO;
        return [x, y];
    }

    drawPoint(point, i) {
        let id = "point " + i;
        let [x, y] = this.coordinateToPixel(point);
        return renderToString(<circle id={id} cx={x} cy={y} r="2.5" fill="red"/>);
    }

    drawLine(point1, point2, i) {
        let id = "line " + i;
        let [x1, y1] = this.coordinateToPixel(point1);
        let [x2, y2] = this.coordinateToPixel(point2);
        return renderToString(<line id={id} x1={x1} y1={y1} x2={x2} y2={y2} stroke="gray" strokeWidth="2"/>);
    }

    convertJSONtoKML(tripJson) {
        let kml = KMLMap;
        if (tripJson !== null) {
            let tripLength = tripJson.places.length - 1;
            for (let i = 0; i < tripLength; i++) {
                kml += this.addMark(tripJson.places[i]);
                kml += this.addLine(tripJson.places[i], tripJson.places[i + 1]);
            }
            kml += this.addMark(tripJson.places[tripLength]);
            kml += this.addLine(tripJson.places[tripLength], tripJson.places[0]);
        }
        kml += "</Document>\n</kml>";
        return kml;
    }

    addLine(place1, place2) {
        let x1 = (parseFloat(place1.longitude));
        let y1 = (parseFloat(place1.latitude));
        let x2 = (parseFloat(place2.longitude));
        let y2 = (parseFloat(place2.latitude));
        let line = "\t<Placemark>\n\t\t<styleUrl>#line</styleUrl>\n\t\t<LineString>\n";
        line += `\t\t\t<coordinates> ${x1},${y1},0
                    ${x2},${y2},0 </coordinates>\n`;
        line += "\t\t</LineString>\n\t</Placemark>\n";
        return line;
    }

    addMark(place) {
        let name = place.name;
        name = name.replace('&', 'and'); // & character creates parsing errors
        let x = (parseFloat(place.longitude));
        let y = (parseFloat(place.latitude));
        let mark = "\t<Placemark>\n";
        mark += `\t\t<name>${name}</name>\n`;
        mark += "\t\t<styleUrl>#icon</styleUrl>\n\t\t<Point>\n";
        mark += `\t\t\t<coordinates> ${x},${y},0 </coordinates>\n`;
        mark += "\t\t</Point>\n\t</Placemark>\n";
        return mark;
    }
}