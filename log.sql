-- Keep a log of any SQL queries you execute as you solve the mystery

-- To know more from the report, you can access the description
SELECT description
FROM crime_scene_reports
WHERE month = 7
    AND day = 28
    AND year = 2023
    AND street = 'Humphrey Street';

-- To see the witnesses interviews and also their names
SELECT name, transcript
FROM interviews
WHERE month = 7
    AND year = 2023
    AND day = 28
    AND transcript LIKE '%bakery%';

-- To start fresh
DROP TABLE IF EXISTS suspects;

-- Create table with suspects
CREATE TABLE suspects (
    id INTEGER,
    person_id INTEGER,
    phone_number TEXT,
    passport_number INTEGER,
    PRIMARY KEY(id)
);

-- Insert suspects into suspects table
INSERT INTO suspects (person_id)
    SELECT people.id
    FROM bakery_security_logs
    JOIN people ON bakery_security_logs.license_plate = people.license_plate
    WHERE bakery_security_logs.year = 2023
        AND bakery_security_logs.month = 7
        AND bakery_security_logs.day = 28
        AND bakery_security_logs.hour = 10
        AND bakery_security_logs.minute BETWEEN 15 AND 25
    GROUP BY people.id;

-- Update phone_number of suspects
UPDATE suspects
SET phone_number = (
    SELECT phone_number
    FROM people
    WHERE people.id = suspects.person_id
);

-- Update suspects' passport_number
UPDATE suspects
SET passport_number = (
    SELECT passport_number
    FROM people
    WHERE people.id = suspects.person_id
);

-- Check to see if the suspects are stored with attributes
SELECT * FROM suspects;

-- Delete from suspects anyone not associated with this type of transaction
DELETE FROM suspects
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

-- Just checking, 4 remaining suspects
SELECT * FROM suspects;

-- Remove from suspects number those who don't appear as caller
DELETE FROM suspects
WHERE phone_number NOT IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND duration < 60
);

-- Check remaining suspects (2)
SELECT * FROM suspects;

-- Delete passenger who aren't on the earliest flight of the 29th
DELETE FROM suspects
WHERE passport_number NOT IN (
    SELECT passengers.passport_number
    FROM passengers
    JOIN flights ON passengers.flight_id = flights.id
    WHERE flights.year = 2023
        AND flights.month = 7
        AND flights.day = 29
        AND flights.hour = (
            SELECT MIN(flights.hour)
            FROM flights
            WHERE flights.year = 2023
                AND flights.month = 7
                AND flights.day = 29
        )
);

-- This is the thief!! The last remaining suspect
SELECT * FROM suspects;

 -- Show information on the thief
SELECT id, name, phone_number, passport_number, 'THIEF' AS role
FROM people
WHERE id = (SELECT person_id FROM suspects);

-- Because of that, now I can identify the accomplice: the one the suspect called
SELECT id, name, phone_number, 'ACCOMPLICE' AS role
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

-- To find out the destination airport
SELECT flights.destination_airport_id
FROM flights
JOIN passengers ON flights.id = passengers.flight_id
WHERE flights.year = 2023
    AND flights.month = 7
    AND flights.day = 29
    AND passengers.passport_number = 5773159633;

-- To find out city suspect escaped to
SELECT city
FROM airports
WHERE id IN (
    SELECT destination_airport_id
    FROM flights
    WHERE destination_airport_id = 4
);
