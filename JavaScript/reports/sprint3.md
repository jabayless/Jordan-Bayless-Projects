# Sprint 3 - *t09* - *Revenge of the Sprint*

## Goal
### Build a trip!

## Sprint Leader: 
### *Zachary Wikel*


## Definition of Done

* The version in `server/pom.xml` is `<version>3.0</version>`.
* The Product Increment release for `v3.0` created on GitHub.
* The team's web application is deployed on the production server (`black-bottle.cs.colostate.edu`).
* The design document (`design.md`) is updated.
* The sprint document (`sprint.md`) is updated with scrums, completed metrics, review, and retrospective.


## Policies

### Mobile First Design
* Design for mobile, tablet, laptop, desktop in that order.
* Use ReactStrap and ReactLeaflet for a consistent user experience (no HTML, CSS, style, etc.).

### Clean Code
* Technical Debt Ratio less than 5% (A).
* Minimize code smells and duplication.

### Test Driven Development
* Write tests before code.
* Unit tests are fully automated.
* Code coverage greater than 70%.

### Processes
* Master is never broken. 
* All pull request builds and tests are successful on Travis-CI.
* All dependencies managed using Maven, npm, and WebPack.
* GitHub etiquette is followed always.


## Planned Epics

*Find distance #30:*
The purpose of this epic is for the user to find the distance between points as how Ironman would fly. This would allow the user to specify two points via multiple methods. This would be shown in miles assuming an earth radius of 3959 miles. The great circle distance will be computed using the Vincenty method. The map would then display a line between those two points.

*v3 protocol #34:*
This epic will update the standard object format used by the client and server. This includes adding trip to supported requests in config, adding the trip type, updating the requestVersion to 3, and modifying the find behavior when no match is specified. The user will also be able to see the version and supported types in the footer.

*Build a trip #36:*
The goal of this epic is to allow the user to select a multitude of points and create a trip with them. The user will be able to name, save, and load the trip. The trip will be displayed on the map and will be able to support an unlimited number of destinations. The round-trip distance will be displayed as well as an itinerary containing the leg and cumulative distances. 

## Metrics

| Statistic | # Planned | # Completed |
| --- | ---: | ---: |
| Epics | *3* | *3* |
| Tasks |  *34*   | *34* | 
| Story Points |  *61*  | *61* | 


## Scrums

| Date | Tasks closed  | Tasks in progress | Impediments |
| :--- | :--- | :--- | :--- |
| *10-7-2020* | *sprint planning* | *140, 223, 243, 252, 255* | none | 
| *10-9-2020* | *223, 255, 256* | *138, 140, 243, 252, 272* | New protocol update | 
| *10-12-2020* | *243, 252* | *138, 140, 272, 288, 291* |  | 
| *10-14-2020* | *138, 140, 264, 309* | *263, 246, 251* |  | 
| *10-16-2020* | *138, 140, 249, 251, 263, 264, 295* | *246, 325, 327, 328* |  |
| *10-19-2020* | * * | *246, 257, 258, 259, 325, 327, 328* | Fixing code smells and defects |
| *10-21-2020* | *257, 258, 260, 325, 327, 328* | *246, 254, 259, 348, 358, 361* | |

## Review

### Epics done  
* Find distance #30
* v3 protocol #34
* Build a trip #36

### Epics not done 
* None

### What went well
* Achieved a technical debt ratio less than 5%
* Improved code coverage by over 10%
* Fixed all issues from the previous sprints
* Strengthened team cohesion

### Problems encountered and resolutions
* Sprint occurring during midterms
* Protocol misunderstanding
* Leftover issues from last sprint


## Retrospective

### What we changed this sprint
We came into this sprint with a better understanding of the workload we can manage. For this reason, we improved our planning by taking on less epics but breaking them up into more tasks. This way we could have a more consistent burndown chart without ourselves burning down. We also placed a heavier emphasis on making sure the protocol was followed correctly. This included reading the latest protocol several times and fixing prior code to ensure we were in compliance.  

### What went well
During this sprint we fixed issues we had created for ourselves from previous sprints. There was a steep learning curve that influenced our project direction initially. We made uneducated decisions that ended up creating more work for us in the long run. One example was our Atlas file being over 500 lines long and containing way too many functions. We were able to break that up into multiple files and create a much more maintainable code base. This proved beneficial going into the "Build a trip" epic as the code was easier to understand and more enjoyable to work with. Overall, as a team we put our project in a much better position going forward that will allow us to add future code more efficiently.

### Potential improvements
For the next sprint we could plan our tasks a little bit better. We had improved our task making ability since last sprint, but some tasks still take much more time and effort compared to others. These tasks would be better off broken into two separate issues. We could also prioritize our tasks more efficiently. Some tasks require another specific issue being completed first before that task can be taken on. This would reduce time waiting for that issue to be completed before starting the following task.

### What we will change next time
For the next sprint it would be nice to change the roles we've all fell into. For example, some people have touched only Java backend files while others have only touched JavaScript frontend files. We should reverse the positions as to allow everyone equal chance to work on all aspects of the project. This will not only improve the strength of the team but allow a fresh perspective on what our project needs.
