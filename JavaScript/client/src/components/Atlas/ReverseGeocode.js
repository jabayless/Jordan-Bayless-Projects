import React from "react";
import {HERE_API_KEY} from "../../utils/constants";

export function getAddressFromCoordinates(latitude, longitude) {
    return new Promise((resolve) => {
        const url = `https://reverse.geocoder.ls.hereapi.com/6.2/reversegeocode.json?apiKey=${HERE_API_KEY}&mode=retrieveAddresses&prox=${latitude},${longitude}`
        fetch(url)
            .then(res => res.json())
            .then((resJson) => {
                if (resJson && resJson.Response) {
                    resolve(resJson.Response.View[0].Result[0].Location.Address.Label)
                } else {
                    resolve()
                }
            })
            .catch((e) => {
                console.log('Error in getAddressFromCoordinates', e)
                resolve()
            })
    })
}