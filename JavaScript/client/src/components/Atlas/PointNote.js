import React, {Component} from "react";
import {Button, Input, InputGroup} from "reactstrap";
import{Card} from "react-bootstrap";
export default class PointNote extends Component {

    constructor(props) {
        super(props);
        this.state = {
            showNote: false,
            note: "",
        }
    }

    render(){
        return (
            <div>
                {this.renderNoteCard()}
            </div>
        )
    }

    toggle(){
        this.setState({showNote: !this.state.showNote})
    }

    renderToggle(){
        let text = "Add Note"
        if (this.state.showNote){
            text = "Close"
        }
        return (
            <div>
                <Button
                    type="search"
                    color="primary"
                    style={{float: "right"}}
                    onClick={() => this.toggle()}>
                    {text}
                </Button>
            </div>
        )
    }

    setNote = (note) =>{
        this.setState({note: note.target.value})
    }

    renderNoteBox(){
        return(
            <div>
                <InputGroup size="md">
                    <Input id="name"
                           onChange={e => this.setNote(e)}
                           placeholder="Enter Notes"
                           value={undefined}/>
                </InputGroup>
            </div>
        );
    }

    renderNote(){
        if (this.state.note !== ""){
            return (
                <Card>
                    <div>
                        {this.state.note}
                    </div>
                </Card>
            );
        }
    }

    renderNoteCard(){
        if (this.state.showNote) {
            return (
                <div>
                    {this.renderNote()}
                    {this.renderNoteBox()}
                    {this.renderToggle()}
                </div>
            )
        } else {
            return (
                <div>
                    {this.renderNote()}
                    {this.renderToggle()}
                </div>
            )
        }
    }
}