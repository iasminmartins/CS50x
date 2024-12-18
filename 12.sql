-- List the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
SELECT title
FROM movies
JOIN stars AS brad_cooper ON movies.id = brad_cooper.movie_id
JOIN stars AS jen_lawrence ON movies.id = jen_lawrence.movie_id
JOIN people AS cooper ON cooper.id = brad_cooper.person_id
JOIN people AS lawrence ON lawrence.id = jen_lawrence.person_id
WHERE cooper.name = 'Bradley Cooper'
AND lawrence.name = 'Jennifer Lawrence';
