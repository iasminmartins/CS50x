-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description -- To know more from the report, you can access the description, since you have the other informations necessary
FROM crime_scene_reports
WHERE month = 7
AND day = 28
AND year = 2023
AND street = 'Humphrey Street';


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
