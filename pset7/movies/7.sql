-- List all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
SELECT movies.title, ratings.rating
FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE movies.year = 2010 AND ratings.rating IS NOT NULL
ORDER BY ratings.rating DESC, movies.title ASC;
