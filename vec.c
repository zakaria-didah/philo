#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector
{
	void	*data;
	size_t	size;
	size_t	capacity;
	size_t	element_size;

	void	(*push_back)(struct Vector *, const void *);
	void	(*pop_back)(struct Vector *);
	void	*(*get)(struct Vector *, size_t index);
	void	(*set)(struct Vector *, size_t index, const void *);
	void	(*destroy)(struct Vector *);
}			Vector;

Vector		*vector_new(size_t element_size);

#define INITIAL_CAPACITY 10

static void	vector_push_back(Vector *vec, const void *element)
{
	void	*target;

	if (vec->size >= vec->capacity)
	{
		vec->capacity *= 2;
		vec->data = realloc(vec->data, vec->capacity * vec->element_size);
	}
	target = (char *)vec->data + vec->size * vec->element_size;
	memcpy(target, element, vec->element_size);
	vec->size++;
}

static void	vector_pop_back(Vector *vec)
{
	if (vec->size > 0)
	{
		vec->size--;
	}
}

static void	*vector_get(Vector *vec, size_t index)
{
	if (index >= vec->size)
		return (NULL);
	return ((char *)vec->data + index * vec->element_size);
}

static void	vector_set(Vector *vec, size_t index, const void *element)
{
	void	*target;

	if (index >= vec->size)
		return ;
	target = (char *)vec->data + index * vec->element_size;
	memcpy(target, element, vec->element_size);
}

static void	vector_destroy(Vector *vec)
{
	free(vec->data);
	free(vec);
}

Vector	*vector_new(size_t element_size)
{
	Vector	*vec;

	vec = malloc(sizeof(Vector));
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

int	main(void)
{
	Vector	*v;
	char	*n;
	char	**val;

	v = vector_new(sizeof(char *));
	n = "z0000000000000000000";
	char *z = "11111111111111111";
	v->push_back(v, &n);
	val = (char **)v->get(v, 6);
    if (val)
	    printf("[%s] ", *val);
	v->destroy(v);
	return (0);
}
