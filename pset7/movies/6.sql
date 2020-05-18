select AVG(rating) as rating 
from movies join ratings on movies.id = ratings.movie_id
where year = 2012;