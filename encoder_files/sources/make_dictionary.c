#include "encoder.h"

static void	free_dic(char ***dic) {

	int	i;

	i = 0;
	while ((*dic)[i] != NULL)
	{
		free((*dic)[i]);
		i++;
	}
	free(*dic);
}

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

static char	**dictionary_malloc(int columns, t_data *data)
{
	char	**dic;

	if (columns == 1)
		columns = 2;
	dic = malloc(sizeof(char *) * EXTEND_ASCII_SIZE);
	if (dic == NULL){
		delete_tree(data->tree);
		exit(2);
	}
	for (int i = 0; i < 256; i++){
		dic[i] = ft_calloc(columns, sizeof(char));
		if (dic[i] == NULL)
			free_dic(&dic);
	}
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

char	**make_dictionary(t_data *data)
{
	int		columns;
	char	**dic = NULL;

	columns = tree_hight(data->tree) + 1;
	dic = dictionary_malloc(columns, data);
	generate_dictionary(dic, data->tree, "", columns);
	return (dic);
}