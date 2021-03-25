import axios from 'axios';
import Ajv from 'ajv';

export async function sendServerRequest(requestBody, serverPort=getOriginalServerPort()) {
  try { return await axios.post(`${serverPort}/api/${requestBody.requestType}`, JSON.stringify(requestBody)) }
  catch(error) { return null; }
}

export function getOriginalServerPort() {
  const serverProtocol = location.protocol;
  const serverHost = location.hostname;
  const serverPort = location.port;
  const alternatePort = process.env.SERVER_PORT;
  return `${serverProtocol}\/\/${serverHost}:${(!alternatePort ? serverPort : alternatePort)}`;
}

export function isJsonResponseValid(object, schema) {
  let anotherJsonValidator = new Ajv();
  let validate = anotherJsonValidator.compile(schema);
  return validate(object);
}

export function downloadFile(fileText, fileName, fileType) {
  let file = new Blob([fileText], {type: fileType});
  let a = document.createElement('a'),
      url = URL.createObjectURL(file);
  a.href = url;
  a.download = fileName;
  document.body.appendChild(a);
  a.click();
  setTimeout(function() {
    document.body.removeChild(a);
    window.URL.revokeObjectURL(url);
  }, 0);
}