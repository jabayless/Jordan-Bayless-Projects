import {Col, Row} from "reactstrap";
import React from "react";

export function renderRowAndCol(renderItem) {
    return (
        <Row>
            <Col sm={12} md={{size: 10, offset: 1}}>
                {renderItem}
            </Col>
        </Row>
    );
}
