#include "scene.h"

/*
Basic linked list for the objects
*/

t_ll_obj	*tll_add_back(t_ll_obj **head_, t_ll_obj *node)
{
	t_ll_obj	*last;

	last = *head_;
	if (!last)
	{
		*head_ = node;
		return (node);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = node;
	return (node);
}

t_ll_obj	*tll_new_node(t_object *object)
{
	t_ll_obj	*node;

	node = our_malloc(sizeof(t_ll_obj));
	node->o = object;
	node->l = NULL;
	node->next = NULL;
	return (node);
}

void	tll_del_node(t_ll_obj **root, t_ll_obj *node_)
{
	t_ll_obj	*prev;
	t_ll_obj	*node;

	if (!node_)
		return ;
	node = *root;
	prev = NULL;
	while (node != node_ && node)
	{
		prev = node;
		node = node->next;
	}
	if (prev)
		prev->next = node->next;
	if (node == *root)
		*root = (*root)->next;
	if (node != NULL)
	{
		;// delete_object(node->object);
	}
	our_free(node);
}

void	tll_del_list(t_ll_obj **root)
{
	t_ll_obj	*node;
	t_ll_obj	*temp;

	if (!root)
		return ;
	node = *root;
	while (node)
	{
		temp = node->next;
		// delete_object(node->object);
		our_free(node);
		node = temp;
	}
	root = NULL;
}
