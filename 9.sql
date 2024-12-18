-- List the names of all people who starred in a movie released in 2004, ordered by birth year.
SELECT DISTINCT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.year = 2004
ORDER BY people.birth;

-- Or, instead of using distinct:
-- GROUP BY people.name  -- after line 6
-- ORDER BY people.birth;
