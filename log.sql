-- Keep a log of any SQL queries you execute as you solve the mystery.

.schema -- to see what are the tables and its attributes

SELECT description -- To know more from the report, you can access the description, since you have the other informations necessary
FROM crime_scene_reports
WHERE month = 7
AND day = 28
AND year = 2023
AND street = 'Humphrey Street';

.read log.sql -- to be able to read the description

SELECT name, transcript -- to see the witnesses interviews and also their names
FROM interviews
WHERE month = 7
AND year = 2023
AND day = 28
AND transcript LIKE '%bakery%';

DROP TABLE IF EXISTS suspects; -- To start fresh

CREATE TABLE suspects ( -- create table with suspects, to store id of people at parking lot
    id INTEGER,
    person_id INTEGER,
    phone_number TEXT,
    passport_number INTEGER,
    PRIMARY KEY(id)
);

INSERT INTO suspects (person_id)
    SELECT people.id
    FROM bakery_security_logs
    JOIN people ON bakery_security_logs.license_plate = people.license_plate
    WHERE bakery_security_logs.year = 2023
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute > 15
    AND bakery_security_logs.minute <= 25
    GROUP BY people.id;

UPDATE suspects -- Update phone_number of suspects
SET phone_number = (
    SELECT phone_number
    FROM people
    WHERE people.id = suspects.person_id
);

UPDATE suspects -- Update suspects' passport_number
SET passport_number = (
    SELECT passport_number
    FROM people
    WHERE people.id = suspects.person_id
);

SELECT * FROM suspects; -- Check to see if the suspects are stored with attributes

DELETE FROM suspects -- Remove NULL values, just to be safe
WHERE phone_number IS NULL OR passport_number IS NULL;

DELETE FROM suspects -- Delete from suspects whomever is not associated with this type of transaction
WHERE person_id NOT IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
);

SELECT * FROM suspects; -- Just checking, 4 remaining

DELETE FROM suspects -- Remove from suspects number that doesn't appear as caller
WHERE phone_number NOT IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
);

SELECT * FROM suspects; -- Check remaining suspects (2)

SELECT passengers.passport_number
FROM passengers
JOIN flights ON passengers.flight_id = flights.id
WHERE (flights.hour > 10 OR (flights.hour = 10 AND flights.minute > 15));

-- Get flight info from suspects and delete who didnt take a flight after 10h15
DELETE FROM suspects
WHERE passport_number NOT IN (
    SELECT passengers.passport_number
    FROM passengers
    JOIN flights ON passengers.flight_id = flights.id
    WHERE (flights.hour > 10 OR (flights.hour = 10 AND flights.minute > 15))
    AND flights.year = 2023
    AND flights.month = 7
    AND flights.day = 28
);

SELECT * FROM suspects; -- Now I know that the thief is person with passport_number 3592750733, as it is the only one with flight after the theft

SELECT id, name, phone_number, passport_number, 'THIEF' AS role -- This is the thief - DIANA!
FROM people
WHERE id = (SELECT person_id FROM suspects);

-- Because of that, now I can identify the accomplice: PHILIP! The one she called.
SELECT id, name, phone_number, passport_number, 'ACCOMPLICE' AS role
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller IN (SELECT phone_number FROM suspects)
);


SELECT * from passengers
WHERE passport_number = 3592750733;

SELECT * FROM flights
JOIN passengers ON flights.id = passengers.flight_id
WHERE passengers.passport_number = 3592750733;

SELECT flights.origin_airport_id, flights.destination_airport_id
FROM flights
JOIN passengers ON flights.id = passengers.flight_id
WHERE flights.year = 2023
AND flights.month = 7
AND flights.day = 28
AND (flights.hour > 10 OR (flights.hour = 10 AND flights.minute > 15))
AND passengers.passport_number = 3592750733;

SELECT * FROM airports;
