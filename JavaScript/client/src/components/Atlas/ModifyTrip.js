import React, {Component} from "react";
import {Button, Input, InputGroup, InputGroupAddon, Label} from "reactstrap";

export default class ModifyTrip extends Component {

    constructor(props) {
        super(props);
        this.state = {
            selectedPoint: "",
        }
    }

    render(){
        return (
            <div>
                {this.renderPointEdit()}
            </div>
        );
    }

    InputIsNumber(){
        return !isNaN(parseInt(this.state.selectedPoint));
    }

    ClampInput(number){
        let max = this.props.numPoints-1
        return number <= 0 ? 0 : number >= max ? max : number;
    }

    ParsePointNumber(){
        if (this.InputIsNumber()){
            let pointNum = parseInt(this.state.selectedPoint)
            pointNum = pointNum - 1
            return this.ClampInput(pointNum);
        } else {
            return -1
        }
    }

    removeSelected = () => {
        this.props.doOptimizeToggle(false)
        if (this.props.numPoints > 2){
            let point = this.ParsePointNumber()
            if (point!==-1){
                this.props.tripPoints.splice(point,1)
                this.props.modifyPoints(this.props.tripPoints, this.props.numPoints-1);
            } else {
                //otherwise remove the last point
                this.props.tripPoints.splice(this.props.numPoints-1,1)
                this.props.modifyPoints(this.props.tripPoints, this.props.numPoints-1);
            }
            this.props.submitModify();
        }
    }

    renderButton(callback,Color,text){
        return (
            <InputGroupAddon addonType="append">
                <Button
                    type="search"
                    color={Color}
                    onClick={callback}
                >{text}</Button>
            </InputGroupAddon>
        );
    }

    submitModifications(){
        this.props.modifyPoints(this.props.tripPoints, this.props.numPoints);
        this.props.submitModify();
    }
    setupSwap(){
        this.props.doOptimizeToggle(false)
        return this.ParsePointNumber()
    }
    swapTripPoints(pos1, pos2){
        let temp = this.props.tripPoints[pos2];
        this.props.tripPoints[pos2] = this.props.tripPoints[pos1];
        this.props.tripPoints[pos1] = temp;
    }

    MoveUp = () => {
        let point = this.setupSwap()
        if (point <= this.props.numPoints-2 && point !== -1){
            //uses -2 so that there is a minimum of one extra element on the end (ie cannot swap past end)
            this.swapTripPoints(point,point+1)
        }
        this.submitModifications()
    }

    MoveDown = () => {
        let point = this.setupSwap()
        if (point > 0){
            //uses 0 as to not swap past the end.
            this.swapTripPoints(point,point-1);
        }
        this.submitModifications()
    }

    renderOptimizeBox = () => {
        const handleOptimizeCheck = () => {
            this.props.doOptimizeToggle(!this.props.optimize)
        }
        return (
            <div style={{"marginLeft":20}}>
                <Input
                    type="checkbox"
                    onChange={handleOptimizeCheck}
                    checked={this.props.optimize}
                    value={this.props.optimize}
                />
                <label>Optimize Destinations</label>
            </div>
        );
    }

    renderPointEdit(){
        return (
            <div>
                <Label>Edit Points</Label>
                <InputGroup size="md">
                    <Input id="name"
                           onChange={e => this.setState({selectedPoint: e.target.value})}
                           placeholder="Enter Point Number"
                           value={undefined}/>
                    {this.renderButton(this.removeSelected, "primary", "Remove")}
                    {this.renderButton(this.MoveUp,"secondary","Move Up")}
                    {this.renderButton(this.MoveDown, "secondary", "Move Down")}
                    {this.renderOptimizeBox()}
                </InputGroup>
            </div>
        );
    }
}