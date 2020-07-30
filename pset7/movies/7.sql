# 排序的方法是先排rating再排title，所以rating要先
SELECT title, rating FROM movies JOIN ratings ON id = movie_id WHERE year = 2010 ORDER BY rating DESC, title ASC;