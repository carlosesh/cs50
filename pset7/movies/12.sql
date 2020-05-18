select title from people
join stars on people.id = stars.person_id
join movies on movies.id = stars.movie_id
where name in ("Johnny Depp","Helena Bonham Carter")
group by title
having count(movies.id) > 1;