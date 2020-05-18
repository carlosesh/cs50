select distinct(name) from people
join stars on people.id = stars.person_id
join movies on movies.id = stars.movie_id
where year = 2004 ORDER BY birth;