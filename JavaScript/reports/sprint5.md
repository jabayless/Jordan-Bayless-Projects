# Sprint 5 - *t09* - *Revenge of the Sprint*

## Goal
### More powerful user tools!

## Sprint Leader
### *Alex King*


## Definition of Done

* The version in `server/pom.xml` is `<version>5.0</version>`.
* The Product Increment release for `v5.0` created on GitHub.
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
*File Formats:* Advanced users may analyze trips with alternative tools, as such we will be providing CSV, KML, and SVG formats to be saved. This will require the introduction of new UI to allow for detecting the user choice. 

*Distance Units:* While we already provide an interface to allow users to change the earth radius, we would like to now add in some default options, as well as allow users to specify their own earth radius with a name for that unit. This should carry between sessions, a good way to accomplish this might be through the use of a cookie given that the protocol does not provide this.

*Modify Trip:* The goal of this epic is to allow the user to modify a trip, such modifications include changing the starting location, reversing the order of the destinations, reordering individual destinations, removing destinations, and adding notes and correcting destination mistakes.

*Place Display:* This epic is designed to provide more information about a place when the user makes a selection, such information may include region, and country. This feature should also provide external links to information about these locations. We will do this by introducing new UI and functionality on the front end to leverage our backend.

*Place Details:* We would like to provide more information for locations through both click and coordinate input. As such we will use reverse geocoding and new UI elements to provide the user this experience. This information should also be included in the trip itinerary tab, as well as the marker used on the map.

## Metrics

| Statistic | # Planned | # Completed |
| --- | ---: | ---: |
| Epics | *5* | *5* |
| Tasks |  *19*   | *55* |
| Story Points |  *27*  | *60* |

We have chosen 5 epics, which should be comfortable for us based on our previous sprints. Though some of the tasks may be somewhat more difficult to implement, we are confident in our abilities based on the skills we have gained in our previous sprints. It should be expected that as issues come up along the way we will likely need to assign more story points and tasks to deal with those issues, though we feel comfortable with the initial estimates we have given on our tasks.

## Scrums

| Date | Tasks closed  | Tasks in progress | Impediments |
| :--- | :--- | :--- | :--- |
| 11-30-2020 | #518, #544, #550 | #526, #525, #519, #514, #513 | none |
| 12-2-2020 | #526, #514, #556 | #516, #525, #519, #528, #513 | none |
| 12-4-2020 | #528, #524, #513, #561, #572, #571, #569, #560, #575, #576, #519, #578, #577, #579, #580, #583, #584, #525, #573, #585, #516, #581 | #521, #574, #582 | none |
| 12-7-2020| #582, #589, #591, #515, #590, #517, #592, #503, #595, #593, #596, #594 | #523, #601, #598, #521, #597 | none |
| 12-9-2020| #523, #601, #598, #521, #597  | #504, #603, #604, #600, #529, #599, #520, #605, #522, #527 | none |

## Review

### Epics done
* File Formats
* Distance Units
* Modify Trip
* Place Display
* Place Details

### Epics not done
* None
### What went well
* Broke down problems better
* Members took initiative on tasks
* Very comfortable reaching out for help and suggestions
* Good scrum attendance

### Problems encountered and resolutions
* Encountered issues updating the modal with the point edits, this got remedied through some extra constructor arguments.
* Since we all had specialized and this sprint largely focused on the client, server-sided team members found some difficulties, we resolved this through good team communication.
* We also had some difficulty with one of the apis client side, but this was remedied with a promise a bit of work.

## Retrospective

### What we changed this sprint
This sprint we had members take charge on specific epics, this allowed us to delegate tasks and get help and suggestions in a smoother manner. Further it makes each epic feel more cohesive. Finally, our performance rate was higher this sprint than ever, we got more epics done than previous sprints. This methodology gave us good direction for each epic.  
### What went well
How we delegated our tasks this sprint lead us to a more cohesive design for each epic. It also allowed us to spend more time in the "zone" as we worked. We all attended sprints specifically to get more design recommendations as we've slowly needed less technical recommendations. We did a much better job having multiple people test each branch before we merged the pull requests as well.
### Potential improvements
One potential improvement would be not having an extended break in the middle of the sprint. While this technically gave us more time to work on the sprint, it was vacation time. This makes it difficult to come back and immediately start swinging for the fences. While we all were happy with how tasks had been delegated this sprint, we could have broken certain tasks up more still.
### What we will change next time
We've already been good about revising our projections and breaking tasks down, in another sprint we would definitely try to grow on this. Having people in the lead on specific epics worked well. The relative sizes of different tasks still shows we have work to do in this area. Perhaps for future sprints that means another round of breaking down tasks as we understand the scope of each task.