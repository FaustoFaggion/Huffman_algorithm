#include "decoder.h"

static int	tree_hight(node *root)
{
	int	left;
	int	right;

	if (root == NULL)
		return (-1);
	else {
		left = tree_hight(root->left) + 1;
		right = tree_hight(root->right) + 1;
		if (left > right)
			return (left);
		else
			return (right);
	}
}

static char	**dictionary_malloc(int columns)
{
	char	**dic;

	if (columns == 1)
		columns = 2;
	dic = malloc(sizeof(char *) * EXTEND_ASCII_SIZE);
	if (dic == NULL)
		exit(2);
	for (int i = 0; i < EXTEND_ASCII_SIZE; i++)
		dic[i] = ft_calloc(columns, sizeof(char));
	return (dic);
}

static void	generate_dictionary(char **dic, node *root, char *path, int columns)
{
	char	left[columns];
	char	right[columns];

	if (columns == 1){
		strcpy(dic[(int)(root->character)],"0");
		return ;
	}
	if (root->left == NULL && root->right == NULL){
		strcpy(dic[(int)(root->character)],path);
	}
	else {
		strcpy(left, path);
		strcpy(right, path);
		strcat(left, "0");
		strcat(right, "1");
		
		generate_dictionary(dic, root->left, left, columns);
		generate_dictionary(dic, root->right, right, columns);
	}
}

char	**make_dictionary(node *tree)
{
	int		columns;
	char	**dic = NULL;

	columns = tree_hight(tree) + 1;
	dic = dictionary_malloc(columns);
	generate_dictionary(dic, tree, "", columns);
	return (dic);
}