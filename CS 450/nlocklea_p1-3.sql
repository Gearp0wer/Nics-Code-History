--Written by Nicholas Locklear
-- G01090642


DROP TABLE BUILDING CASCADE CONSTRAINTS;
DROP TABLE ROOM CASCADE CONSTRAINTS;
DROP TABLE DEPARTMENT CASCADE CONSTRAINTS;
DROP TABLE MAILADDRESS;
DROP TABLE EMPLOYEE;
DROP TABLE MEASUREMENTS;

CREATE TABLE BUILDING (
    buildingName CHAR(20) PRIMARY KEY,
    floorCount INT NOT NULL,
    roomCount INT NOT NULL
);

INSERT  INTO BUILDING 
values ('Innovation', 3, 57);

INSERT  INTO BUILDING 
values ('Johnson', 5, 200);



CREATE TABLE ROOM (
    roomNumber INT NOT NULL,
    buildingName CHAR(20) NOT NULL,
    phoneNumber INT,
    squareFeet INT NOT NULL,
    roomUse char(10) NOT NULL,
    roomUse2 char(10),
    maxCapacity INT,
    CONSTRAINT roomLocation PRIMARY KEY (roomNumber, buildingName),
    FOREIGN KEY (buildingName) REFERENCES BUILDING(buildingName)
);

INSERT  INTO ROOM 
values (2, 'Innovation', 1234567690, 100, 'lab', NULL, NULL);

INSERT  INTO ROOM 
values (4, 'Innovation', 2132435465, 120, 'office', NULL, NULL);

INSERT  INTO ROOM 
values (123, 'Johnson', 8675309, 800, 'office', NULL, NULL);

INSERT  INTO ROOM 
values (21, 'Johnson', 1111111111, 60, 'confrence', NULL, 1000);

INSERT  INTO ROOM 
values (6, 'Innovation', 657885, 100, 'lab', 'office', NULL);



CREATE TABLE DEPARTMENT (
    roomNumber INT NOT NULL,
    buildingName CHAR(50) NOT NULL,
    departmentName CHAR(50) NOT NULL,
    phoneNumber INT,
    webAddress char(50) UNIQUE,
    emailAdress char(50) UNIQUE NOT NULL,
    CONSTRAINT DepartmentName PRIMARY KEY (departmentName)
);

INSERT INTO DEPARTMENT 
values (6,'Innovation', 'Halloween',  4444444444, 'www.GMUhalloween.com', 'halloweendepartment@gmu.edu');

INSERT INTO DEPARTMENT 
values (123, 'Johnson', 'Miscellaneous_Variables', 55555, 'www.GMUmiscellaneousvariables.com', 'miscellaneousvariables@gmu.edu');

INSERT INTO DEPARTMENT 
values (4, 'Innovation', 'Space', 1800, NULL, 'space@gmu.edu');



CREATE TABLE MAILADDRESS(
    departmentName CHAR(50) PRIMARY KEY,
    streetAddress char(20) NOT NULL,
    city char(20) NOT NULL,
    abbrevState char(2) NOT NULL,
    zipCode INT NOT NULL
);

INSERT  INTO MAILADDRESS 
values ('Halloween', '1', 'Fairfax', 'va', 4);

INSERT  INTO MAILADDRESS 
values ('Miscellaneous_Variables', '2', 'Fairfax', 'va', 5);

INSERT  INTO MAILADDRESS 
values ('Space', '3', 'Fairfax', 'va', 6);



CREATE TABLE EMPLOYEE(
    eID INT PRIMARY KEY,
    firstName char(15),
    lastName char(15),
    birthday DATE,
    emailAdress char(50) NOT NULL,
    employeeDepartment CHAR(50) NOT NULL,
    roomNumber INT NOT NULL,
    buildingName CHAR(20) NOT NULL,
    FOREIGN KEY (roomNumber, buildingName) REFERENCES ROOM(roomNumber, buildingName),
    FOREIGN KEY (employeeDepartment) REFERENCES DEPARTMENT(DepartmentName)
);
INSERT  INTO EMPLOYEE 
values (887, 'Michael', 'Myers', NULL, 'mmyers@gmu.edu', 'Halloween', 21, 'Johnson');

INSERT  INTO EMPLOYEE 
values (5050, 'Lewis', 'Skeleton', NULL, 'lskeleton@gmu.edu', 'Halloween', 2, 'Innovation');

INSERT  INTO EMPLOYEE 
values (01090642, 'Nic', 'Locklear', NULL, 'nlocklea@gmu.edu', 'Miscellaneous_Variables', 123, 'Johnson');

INSERT  INTO EMPLOYEE 
values (66, 'Chuckie', 'Cheese', NULL, 'ccheese@gmu.edu', 'Miscellaneous_Variables', 123, 'Johnson');

INSERT  INTO EMPLOYEE 
values (2468, 'Zip', 'Zop', NULL, 'zzop@gmu.edu', 'Space', 4, 'Innovation');



CREATE TABLE MEASUREMENTS(
    roomNumber INT NOT NULL,
    buildingName CHAR(20) NOT NULL,
    timeTaken TIMESTAMP NOT NULL,
    temperature INT,
    semester CHAR(10),
    soundLevel INT,
    lightLevel INT,
    CONSTRAINT timeOfMeasurement PRIMARY KEY (timeTaken),
    FOREIGN KEY (roomNumber, buildingName) REFERENCES ROOM(roomNumber, buildingName)
);

INSERT  INTO MEASUREMENTS 
values (2, 'Innovation','2023-01-01 18:22:21', NULL, NULL, 6, 10);

INSERT  INTO MEASUREMENTS 
values (4, 'Innovation','2023-02-01 23:22:00', 55, NULL, 18, 1);

INSERT  INTO MEASUREMENTS 
values (4, 'Innovation','2022-06-04 22:11:30', 78, NULL, 20, 50);

INSERT  INTO MEASUREMENTS 
values (123, 'Johnson','2023-10-31 23:22:00', 68, NULL, 27, 11);

INSERT  INTO MEASUREMENTS 
values (123, 'Johnson','2023-10-31 22:22:00', 63, NULL, 10, 11);

INSERT  INTO MEASUREMENTS 
values (123, 'Johnson','2023-10-31 21:22:00', 61, NULL, 6, 3);

INSERT  INTO MEASUREMENTS 
values (123, 'Johnson','2023-10-31 20:22:00', 57, NULL, 21, 6);

INSERT  INTO MEASUREMENTS 
values (21, 'Johnson','2023-11-31 06:53:32', 76, NULL, 22, 11);


SELECT DISTINCT DEPARTMENT.departmentName, MAILADDRESS.streetAddress, ROOM.phoneNumber
FROM DEPARTMENT, ROOM, MAILADDRESS
WHERE (DEPARTMENT.departmentName = MAILADDRESS.departmentName) AND (DEPARTMENT.roomNumber = ROOM.roomNumber) AND (DEPARTMENT.buildingName = ROOM.buildingName);

SELECT  buildingName, floorCount
FROM BUILDING
WHERE floorCount<4;

SELECT DISTINCT ROOM.buildingName, ROOM.roomNumber
FROM ROOM
WHERE ( NOT (roomUse = roomUse2) ) AND ((roomUse = 'lab' AND roomUse2 = 'office') OR (roomUse = 'office' AND roomUse2 = 'lab'));

SELECT DISTINCT buildingName, roomCount
FROM BUILDING;

SELECT ROOM.roomNumber, MEASUREMENTS.temperature
FROM  Room, Measurements
WHERE (ROOM.roomNumber = MEASUREMENTS.roomNumber) AND (MEASUREMENTS.buildingName = ROOM.buildingName );

SELECT eID, firstName, lastName
FROM EMPLOYEE
GROUP BY eID, firstName, lastName
HAVING COUNT(emailAdress) = 2;

SELECT ROOM.roomNumber, ROOM.squareFeet
FROM ROOM
LEFT JOIN MEASUREMENTS ON ROOM.roomNumber = MEASUREMENTS.roomNumber AND ROOM.buildingName = MEASUREMENTS.buildingName
WHERE MEASUREMENTS.roomNumber IS NULL;

SELECT MEASUREMENTS.roomNumber, ROOM.phoneNumber
FROM MEASUREMENTS
INNER JOIN ROOM ON MEASUREMENTS.roomNumber = ROOM.roomNumber
WHERE MEASUREMENTS.lightLevel = (
    SELECT MAX(average_light)
    FROM (
        SELECT roomNumber, AVG(lightLevel) AS average_light
        FROM MEASUREMENTS
        GROUP BY roomNumber
    ) AS subquery));


