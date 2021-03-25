import React, {Component} from 'react';

import {Container, Row, Col, Button, Card, CardTitle, CardImg, CardBody, CardText, Jumbotron} from 'reactstrap';

import mikeImage from "../../../../team/images/fostermImg400.jpg"
import zachImage from "../../../../team/images/Zach_Wikel.jpg"
import alexImage from "../../../../team/images/alex_profile.jpg"

import {CLIENT_TEAM_NAME} from "../../utils/constants";

const ZACH = {
    name: "Zachary Wikel",
    link: zachImage,
    bio: "Hey, my name is Zachary Wikel but feel free to call me Zach. I’m a senior at\n" +
        "Colorado State University majoring in computer science with a minor in mathematics.\n" +
        "I originally lived in Ohio but moved to Fort Collins after serving six years in the\n" +
        "United States Army. I really enjoy programming and would love to develop software\n" +
        "for the aerospace industry. In my free time you can find me trail running or playing\n" +
        "video games."
}
const ALEX = {
    name: "Alex King",
    link: alexImage,
    bio: "I'm Alex King, I'm 23 and I study Computer Science and Mathematics at CSU. My\n" +
        "current goals mainly center around graduation, and learning as much as I can while\n" +
        "still in school. I am from a military family so I moved around a lot, where I rest\n" +
        "my head is home. In my free time I play guitar!"
}
const JORDAN = {
    name: "Jordan Bayless",
    link: "https://pbs.twimg.com/profile_images/1302770080036478976/ko8IAQm__400x400.jpg",
    bio: "My name is Jordan Bayless, I am 23 years old and study computer science at\n" +
        "CSU. I grew up in Colorado Springs, Colorado. I just finished 6 years of service\n" +
        "with the Army National Guard. I am getting married to my fiance Heather Mohrman in\n" +
        "May of 2021. In my free time I like to lift weights and learn Brazilian Jui Jitsu."
}
const MICHAEL = {
    name: "Michael Foster",
    link: mikeImage,
    bio: "Hi, my name is Michael Foster, I am 20 years old and I am senior Computer\n" +
        "Science major at CSU. I come from a small town by the name of Crook in Northeastern\n" +
        "Colorado. Currently I am working on a few side projects as well as interning at HPE\n" +
        "part-time. My biggest goal right now is to get a side project that I have been\n" +
        "working on off of the ground. Outside of work and school I enjoy hunting, fishing, \n" +
        "wakeboarding, working out, and playing music."
}
const CALEB = {
    name: "Caleb Maranian",
    link: "https://pbs.twimg.com/media/Ehf99UDU0AAyjRR?format=jpg&name=small",
    bio: "My name is Caleb Maranian, I am a 20 year old Computer Science student planning on\n" +
        "double majoring in math. I am the head of the Esports Association here at CSU and I've\n" +
        "played competitively for multiple teams. I have even traveled to Vegas for the finals of\n" +
        "the Mountain West League of Legends Conference. I am the current competitive president\n" +
        "and have guest starred on podcasts and radio shows to talk about my involvement in\n" +
        "Esports."
}

export default class About extends Component {

    render() {
        return (
            <Container id="about">
                <Row>
                    <Col>
                        <h2>{CLIENT_TEAM_NAME}</h2>
                    </Col>
                    <Col id="closeAbout" xs='auto'>
                        <Button color="primary" onClick={this.props.closePage} xs={1}>
                            Close
                        </Button>
                    </Col>
                </Row>
                {this.renderJumbotron()}
                <Row>
                    {this.renderCard(ZACH.name, ZACH.link, ZACH.bio)}
                    {this.renderCard(ALEX.name, ALEX.link, ALEX.bio)}
                    {this.renderCard(JORDAN.name, JORDAN.link, JORDAN.bio)}
                    {this.renderCard(MICHAEL.name, MICHAEL.link, MICHAEL.bio)}
                    {this.renderCard(CALEB.name, CALEB.link, CALEB.bio)}
                </Row>
            </Container>
        )
    }

    renderJumbotron() {
        return (
            <Jumbotron>
                <h1 className="display-5">Mission Statement</h1>
                <hr className="my-2"/>
                <p className="lead">We here at team Revenge of the Sprint are dedicated to creating
                    and optimizing a high quality product. We believe that with hard work and enough
                    time anything is possible. Because of these beliefs we are invested in getting work done
                    efficiently, painlessly, and quickly. We hope that you will enjoy our products and
                    look to our development team as an example of professionalism and hard work.</p>
            </Jumbotron>
        );
    }

    renderCard(name, link, bio) {
        return (
            <Col sm={12} md={6} lg={4}>
                <Card inverse color="primary">
                    <CardImg
                        src={link}
                        alt={name}/>
                    <CardBody className="text-center">
                        <CardTitle tag="h3">{name}</CardTitle>
                        <CardText>{bio}</CardText>
                    </CardBody>
                </Card>
            </Col>
        );
    }
}
