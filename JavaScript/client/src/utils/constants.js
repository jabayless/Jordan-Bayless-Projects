import ulog from "ulog";

function setLogLevelIfDefault() {
    const urlString = window.location.search;
    const urlParams = new URLSearchParams(urlString);
    if(!urlParams.has("log")) {
        ulog.level = ulog.ERROR
    }
}

setLogLevelIfDefault();

export const LOG = ulog("App");

export const CLIENT_TEAM_NAME = "T09 Revenge of the Sprint";

export const EARTH_RADIUS_UNITS_DEFAULT = {"miles": 3959.0};
export const EARTH_RADIUS_UNITS_KM = 6371.0;
export const EARTH_RADIUS_UNITS_NM = 3440.0;

export const PROTOCOL_VERSION = 4;

export const SEARCH_MARKER = 0;
export const FIRST_DISTANCE_MARKER = 1;
export const SECOND_DISTANCE_MARKER = 2;

export const HTTP_OK = 200;
export const HTTP_BAD_REQUEST = 400;
export const HTTP_INTERNAL_SERVER_ERROR = 500;
export const HERE_API_KEY = "DMBwBGOaJw1G219ZumcZxD7sC0R1FsQK5oUglIBeaow";