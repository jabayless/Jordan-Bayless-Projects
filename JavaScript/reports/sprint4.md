# Sprint 4 - *t09* - *Revenge of the Sprint*

## Goal
### Shorter Trips!
## Sprint Leader
### *Michael Foster*


## Definition of Done

* The version in `server/pom.xml` is `<version>4.0</version>`.
* The Product Increment release for `v4.0` created on GitHub.
* The team's web application is deployed on the production server (`black-bottle.cs.colostate.edu`).
* The design document (`design.md`) is updated.
* The sprint document (`sprint.md`) is updated with scrums, completed metrics, review, and retrospective.


## Policies

### Mobile First Design
* Design for mobile, tablet, laptop, desktop in that order.
* Use ReactStrap and ReactLeaflet for a consistent user experience (no HTML, CSS, style=, etc.).

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
*V4 Protocol:*
This epic will update the protocol version to version 4. This protocol update will include an optional response variable in trip that corresponds to the number of seconds allowed for optimization. It will also include the ability to pass filters into config that can be used in the new narrow element in find, as well as an optional coordinates element that is a string containing coordinates in a format other than decimal degrees. 

*Shorter:*
The goal of this epic will be to give the user the ability to reduce the mileage of their trip while still visiting all places. We will do this by using heuristic optimization on larger trips. We would like the server to always respond in less than a second, therefore we will pass in a response variable to indicate maximum response time. 

*Filter Search:*
After this epic has been implemented, the user will be able to filter their search when they find places. We will do this by using our new filter element in config and narrow in find. 

*User Experience:*
The overall goal of this epic is to enhance the user experience. We want our application to be as simple to use as possible with the least amount of clutter and scrolling. We hope that upon completion of this epic, a brand new user could pick up the application and know how it works without instruction. 

## Metrics

| Statistic | # Planned | # Completed |
| --- | ---: | ---: |
| Epics | *4* | *4* |
| Tasks |  *25*   | *57* | 
| Story Points |  *38*  | *68* | 


## Scrums

| Date | Tasks closed  | Tasks in progress | Impediments |
| :--- | :--- | :--- | :--- |
| *10-28-2020* | ** | *#386, #390, #393, #394, #399, #400* | none | 
| *11-1-2020* | *#399, #400, #393, #404, #401, #394* | *#386, #390, #403, #405, #421, #433* | none |
| *11-4-2020* | *#396, #446, #448* | *#390, #386, #403, #405, #438, #421, #435* | none |
| *11-8-2020* | *#403, #389* |  *#390, #392, #386, #405, #435, #402* | none |
| *11-9-2020* | *#405* |  *#386, #390, #391, #392, #402, #435*| none |
| *11-11-2020* | *#386, #391, #435* |  *#388, #390, #392, #402, #489*| none |

## Review

### Epics done  
* V4 Protocol
* Shorter
* Filer Search
* User Experience

### Epics not done 
* None

### What went well
* Consistently got things done during the sprint
* Communicated well when we had problems
* Reached out to eachother for help
* Came to scrum meetings prepared with any questions/clarifications we had

### Problems encountered and resolutions
* Found a few issues in our API side of things, promptly made defects and fixed them
* Unclear explanations of tasks, ended up talking over and figuring out what was misunderstood
* We began to "Specialize" in Server or Client side, so this sprint we made a point to work on things we had not worked on yet

## Retrospective

### What we changed this sprint
In the past couple of sprints we began specializing in things where some of us would do the server side tasks while others would do client side tasks. This sprint we decided to switch it up and work on things that we had not yet worked on. This resulted in a more wholistic understanding of the entire application itself within the team. This better understanding will help in future sprint planning and tasks. 

### What went well
This sprint we did a great job of chugging away at tasks over time instead of waiting until the last minute to start working on tasks. This resulted in a much lower level of stress all around towards the end of the sprint. Everyone on the team came to scrum meetings prepared with any questions, issues, problems, defects, etc. that they had found since the last meeting. We promptly talked these out as a team and decided the best course of action. Overall we are very happy with how this sprint went.

### Potential improvements
In the next sprint we can improve on the planning side of things. There were times during this sprint where tasks were not clearly communicated from the person who wrote them to the person who was actually doing them. This resulted in a few mixups that we eventually cuaght and fixed. 

### What we will change next time
Next time we will do a better job of planning and maybe even decide wether a task is to be implemented on the server side or client side from the beginning. It would also be useful if we made it a point to talk with whoever created the task that we are working on and make sure that we clearly understand what the intention was behind that task.
