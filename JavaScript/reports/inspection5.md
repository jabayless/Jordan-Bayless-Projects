# Inspection - Team *T09*

| Inspection | Details |
| ----- | ----- |
| Subject | *Server Request Files* |
| Meeting | *Nov 20th at 2:30pm on Microsoft Teams* |
| Checklist | */reports/checklist.md* |

### Roles

| Name | Preparation Time |
| ---- | ---- |
| Alex | 40 minutes |
| Caleb | 46 minutes |
| Jordan | 33 minutes |
| Michael | 42 minutes |
| Zach | 1 hour 9 minutes |

### Problems found

| file:line | problem | hi/med/low | who found | github#  |
| --- | --- | :---: | :---: | --- |
| RequestTrip.java 97 & ProcessTrip.java 29 | could use a constant as a flag insted of -69696969| low | Michael | |
| RequestTrip.java 90 | responseMilliseconds could be set to a constant instead of 100000000| low | Michael | |
| QueryPlaces.java : 80 | High function complexity | low | Zach | |
| RequestTrip.java : 93 | 1000 and 100 should be constants | low | Jordan | |
| RequestTrip.java : 88 | could place local variables at top of function | low | Jordan | |
| RequestDistance.java : 58 | Should use earthRadius and not constant KM_EARTH_RADIUS | low | Alex | 549 |
| RequestDistance.java : 8,9,10 | Constants probably should be offloaded to the client | low | Alex | 551 |
| ProcessTrip.java : 89 | compute distances should use distance table to save time | med | Caleb | 550 |
