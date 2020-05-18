select title from people
join stars on people.id = stars.person_id
join movies on movies.id = stars.movie_id
join ratings on ratings.movie_id = movies.id
where name = "Chadwick Boseman" ORDER BY rating DESC
limit 5;