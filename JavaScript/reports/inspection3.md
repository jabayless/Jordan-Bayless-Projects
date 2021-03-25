# Inspection - Team *T09* 
 
| Inspection | Details |
| ----- | ----- |
| Subject | *Misc server side files* |
| Meeting | *Nov 2nd at 2:30 PM on Microsoft Teams* |
| Checklist | */reports/checklist.md* |

### Roles

| Name | Preparation Time |
| ---- | ---- |
| Alex | 48 minutes |
| Caleb | 52 minutes |
| Jordan | 47 minutes |
| Michael | 50 minutes |
| Zach | 1 hour 9 minutes |

### Problems found

| file:line | problem | hi/med/low | who found | github#  |
| --- | --- | :---: | :---: | --- |
| TestRequestDistance.java : 34 | Server version is not a constant | low | Zach |  |
| TestRequestDistance.java : 16 | No specific tests of getters/setters | low | Jordan |  |
| TestMicroServer.java: 0 | No tests written in this file | med | Jordan | 435 | 
| TestRequestTrip.java | Could use BeforeEach to reduce code | low | Michael | | 
| Trip.js: 34 | numpoints is an unecessary variable. just use tripPoints.length instead | low | Caleb |  |
| Trip.js: 33 | earthRadius is an unecessary variable. just use the constant declared in constants.js | low | Caleb |  |
| QueryPlaces.java : 71 | i could be changed to be more descriptive | low | Alex | |
| TestDistanceCalculator.java | Could use an edge case test for 0 earth radius | med | Alex | 438 |
