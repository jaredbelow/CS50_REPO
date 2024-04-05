-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get the schema for all tables
.schema

-- Find crime scene description
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND year = 2023
AND street = 'Humphrey Street';

-- Find the names & transcript of all interviews taken on day of theft
SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28 AND year = 2023;

-- Narrow selection to just three witnesses by looking for thief in transcript
SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28 AND year = 2023
AND transcript LIKE '%thief%';

-- Check all license plates within 10 minutes of theft per Ruth transcript
SELECT license_plate
FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND year = 2023
AND hour = 10
AND minute >= 15 AND minute <= 25;

-- Find names of people with those license plates exiting the crime scene
SELECT name
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND year = 2023
    AND hour = 10
    AND minute >= 15 AND minute <= 25
)
AND activity = 'exit';

-- Check ATM transactions day of theft in early morning on Legget Street per transcript
SELECT *
FROM atm_transactions
WHERE month = 7 AND day = 28 AND year = 2023
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street';

-- Cross reference account numbers Vs. people_id
SELECT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE month = 7 AND day = 28 AND year = 2023
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street';

-- Check phone logs for calls made less than a minute long per transcript
SELECT name, caller, receiver, duration
FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE month = 7 AND day = 28 AND year = 2023
AND duration < 60;

-- Run phone number against license plate list for people
SELECT *
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE month = 7 AND day = 28 AND year = 2023
AND duration <= 60
AND people.license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND year = 2023
    AND hour = 10
    AND minute >= 15 AND minute <= 20
);

-- Look for earliest flight out of fiftyville
SELECT *
FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.city = 'Fiftyville'
AND flights.day > 28
ORDER BY month, day, hour, minute ASC LIMIT 1;

-- Query to attempt to find the thief
SELECT name
FROM people
WHERE people.phone_number IN (
    SELECT caller
    FROM phone_calls
    JOIN people ON phone_calls.caller = people.phone_number
    WHERE month = 7 AND day = 28 AND year = 2023
    AND duration < 60
)
AND people.license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND year = 2023
    AND hour = 10
    AND minute >= 15 AND minute <= 25
    AND activity = 'exit'
)
AND people.passport_number IN (
    SELECT passport_number
    FROM passengers
    JOIN flights ON passengers.flight_id = flights.id
    WHERE passengers.flight_id IN (
        SELECT flights.id
        FROM flights
        JOIN airports ON flights.origin_airport_id = airports.id
        WHERE airports.city = 'Fiftyville'
        AND flights.day = 28
        ORDER BY month, day, hour, minute ASC
    )
)
AND people.id IN (
    SELECT people.id
    FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE month = 7 AND day = 28 AND year = 2023
    AND transaction_type = 'withdraw'
    AND atm_location = 'Leggett Street'
);

-- Narrow down between Bruce & Diana
-- Using flight id 36 from earliest flights query
SELECT name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = 36
AND people.name IN ('Bruce', 'Diana');

-- Query destination for flight
SELECT city
FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.id = 36;

-- Query for accomplice to Bruce
SELECT name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.caller IN (
    SELECT phone_number
    FROM people
    WHERE name = 'Bruce'
)
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60;



