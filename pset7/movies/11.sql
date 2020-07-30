SELECT title, rating FROM movies JOIN ratings ON id = movie_id 
WHERE id IN (SELECT movie_id FROM stars JOIN people ON person_id = id WHERE name = "Chadwick Boseman") 
ORDER BY rating DESC LIMIT 5;