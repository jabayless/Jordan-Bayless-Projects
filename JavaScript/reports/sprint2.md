# Sprint 2 - 09 - t09 Revenge of the Sprint

## Goal
### Show me the distance
* This sprint, we will calculate distances on our map between points, update our version 2 protocol with current information. The user will aslo be allowed to search for places by name. The user should also be able to look up a place by latitude and longitude.

## Sprint Leader: 
### *Caleb Maranian*

## Definition of Done

* The version in `server/pom.xml` is `<version>2.0</version>`.
* The Product Increment release for `v2.0` created on GitHub.
* The team's web application is deployed on the production server (`black-bottle.cs.colostate.edu`).
* The design document (`design.md`) is updated.
* The sprint document (`sprint.md`) is updated with scrums, completed metrics, review, and retrospective.

## Policies

### Mobile First Design
* Design for mobile, tablet, laptop, desktop in that order.
* Use ReactStrap for a consistent user experience (no HTML, CSS, style, etc.).

### Clean Code
* Code Climate maintainability of A or B.
* Minimize code smells and duplication.

### Test Driven Development
* Write tests before code.
* Unit tests are fully automated.

### Processes
* Master is never broken. 
* All pull request builds and tests for Master are successful on Travis-CI.
* All dependencies managed using Maven, npm, and WebPack.
* GitHub etiquette is followed always.


## Planned Epics

*Introduction:*
Sprint 2 will be conducted from September 15th through October 1st. During this period four epics are planned to be completed. These epics are: v2 protocol, where is, find distance, and find places. This comes to a total of 17 tasks and 29 story points for the duration of the sprint. These epics are detailed below.

*Where is: #5*
This epic will allow the user to input a lat/long grid coordinate, which will be parsed into variables. These variables, once checked by a function for proper input, will then be used to create a marker icon on the map at the indicated grid coordinate. 

*V2 protocol: #29:*
The goal of this epic is to update the standard object format that our clients
and server will use. There will be an addition of two protocol JSON objects: distance, and type,
as well as adding supportedRequests to the config JSON object.

*Find distance: #30:*
The purpose of this epic is for the user to find the distance between points as how Ironman would fly. 
This would allow the user to specify two points via multiple methods. This would be shown in miles 
assuming an earth radius of 3959 miles. The great circle distance will be computed using the Vincenty method. 
The map would then display a line between those two points.

*Find places: #31:*
For this epic the user must be able to find places around the globe. The user must
be able to find these places by their names. A shortlist must also appear while
trying to search for a place and the user should be able to select a result from the 
shortlist to search.


## Metrics

| Statistic | # Planned | # Completed |
| --- | ---: | ---: |
| Epics | 5,29,30,31 | *count* |
| Tasks |  17 tasks   | *count* | 
| Story Points |  29  | *sum* | 


## Scrums

| Date | Tasks closed  | Tasks in progress | Impediments |
| :--- | :--- | :--- | :--- |
| *9-15-2020* | *none* | *none* | sprint plan to be completed | 
| *9-16-2020* | *none* | *128, 130, 131, 123* | *none* |
| *9-18-2020* | *none* | *128, 130, 131, 123* | Architecture Familiarization |
| *9-21-2020* | *177,176* | *126, 128, 130* | Learning call hierarchy |
| *9-23-2020* | *173, 180, 183, 184, 188, 189, 192* | *126, 127, 132, 133 140, 141, 187* | *none* |
| *9-25-2020* | *204, 202, 199, 197, 195* | *187, 141, 140, 135, 133, 127* | *none* |
| *9-28-2020* | *187* | *127, 140, 141, 133, 207* | *none* |
| *9-30-2020* | *208, 210, 211, 213, 212, 214, 207, 215, 127, 216, 218, 219, 133, 220, 225, 224, 221* | *140, 141, 134, 135* | *none* |

## Review

### Epics done  
5,29,30 (Where is, V2 protocol, find places)

### Epics not done 
31 (Find distance)

### What went well
3/4 of the epics were done, which involved lots of work. We effectively split tasks based on our individual team strong suits. We did not break master and followed our github etiquite well.

### Problems encountered and resolutions
One problem our team encountered is that we slightly over estimated the number of epics we could complete this sprint. However, now we are just better at estimating the amount of work we are capable of in the future. 

## Retrospective

### What we changed this sprint
####Server
We added code to process three different requests, config, distance and find. 
####Client
We used the json format and sent out valid requests and got responses from the server that were displayed on our web page. 

### What went well
We worked well as a team and evenly divided the work amongst all team mates and now have expertise in our respective parts of the website we built. 

### Potential improvements
Next sprint, during scrums, going over how to use the code we wrote would help future development. We could do this through cross training eachother so that we all are up do date on how our code works.

### What we will change next time
Next time, we will slightly reduce the number of epics we will alot to ourselves to comlete for the sprint from 4-5 to 3-4. 
