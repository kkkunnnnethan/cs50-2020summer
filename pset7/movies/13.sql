/* In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
    Your query should output a table with a single column for the name of each person.
    There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
    Kevin Bacon himself should not be included in the resulting list. */

/* 這個比較難：
    先將電影跟明星的資料關聯串在一起，然後篩選出有Kevin Bacon演出的電影
    將這些電影的id與傳給只有明星的資料，這樣的話根據那些電影的id就可以篩選出有參與演出這些電影的明星
    最後將與Kevin Bacon同名的明星去掉就是答案 */

SELECT name FROM people WHERE people.id IN 
(SELECT person_id FROM stars WHERE movie_id IN 
    (SELECT movies.id FROM movies JOIN stars ON movies.id = movie_id JOIN people ON people.id = person_id WHERE name = "Kevin Bacon" AND birth = 1958)) 
AND NOT name = "Kevin Bacon";