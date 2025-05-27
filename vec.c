#include "vector.h"

void	*ft_realloc(void *s, size_t size)
{
	void	*new;

	if (!s)
		return (ft_calloc(size, C_ARENA));
	new = ft_calloc(size, C_ARENA);
	ft_memmove(new, s, size);
	free(s);
	return (new);
}

static void	vector_push_back(t_vector *vec, const void *element)
{
	void	*target;

	if (vec->size >= vec->capacity)
	{
		vec->capacity *= 2;
		vec->data = ft_realloc(vec->data, vec->capacity * vec->element_size);
	}
	target = (char *)vec->data + vec->size * vec->element_size;
	ft_memmove(target, element, vec->element_size);
	vec->size++;
}

static void	vector_pop_back(t_vector *vec)
{
	if (vec->size > 0)
	{
		vec->size--;
	}
}

static void	*vector_get(t_vector *vec, size_t index)
{
	if (index >= vec->size)
		return (NULL);
	return ((char *)vec->data + index * vec->element_size);
}

static void	vector_set(t_vector *vec, size_t index, const void *element)
{
	void	*target;

	if (index >= vec->size)
		return ;
	target = (char *)vec->data + index * vec->element_size;
	ft_memmove(target, element, vec->element_size);
}

static void	vector_destroy(t_vector *vec)
{
	free(vec->data);
	free(vec);
}

t_vector	*vector_new(size_t element_size)
{
	t_vector	*vec;

	vec = malloc(sizeof(t_vector));
	vec->data = malloc(INITIAL_CAPACITY * element_size);
	vec->size = 0;
	vec->capacity = INITIAL_CAPACITY;
	vec->element_size = element_size;
	vec->push_back = vector_push_back;
	vec->pop_back = vector_pop_back;
	vec->get = vector_get;
	vec->set = vector_set;
	vec->destroy = vector_destroy;
	return (vec);
}
