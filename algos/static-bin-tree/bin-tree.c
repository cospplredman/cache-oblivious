#include<stdio.h>
#include<stdlib.h>


struct bin_tree{
	int val;
	struct bin_tree* left;
	struct bin_tree* right;
};



struct bin_tree *bin_tree(int val, struct bin_tree* left, struct bin_tree* right){
	struct bin_tree *ret = malloc(sizeof(struct bin_tree));

	*ret = (struct bin_tree){ .val = val, .left = left, .right = right };
	return ret;
}



struct bin_tree *complete_bin_prefix_tree(int layers){
	if(layers == 0){
		return bin_tree(0, NULL, NULL);
	}

	return bin_tree(0, complete_bin_prefix_tree(layers - 1), complete_bin_prefix_tree(layers - 1));
}



struct bin_tree *traverse(int path, int len, struct bin_tree *tr){
	if(len == 0)
		return tr;

	if(path & (1 << len)){
		return traverse(path, len - 1, tr->left);
	}else{
		return traverse(path, len - 1, tr->right);
	}
}


void print_tr(struct bin_tree *tr, int depth){
	if(tr == NULL)
		return;
	for(int i = 0; i < depth; i++)
		printf("  ");
	printf("| %d\n", tr->val);
	print_tr(tr->left, depth + 1);
	print_tr(tr->right, depth + 1);
}


int main(){
	srand(3);
	struct bin_tree *tr = complete_bin_prefix_tree(BITS);

	int sum = 0;
	for(int i = 0; i < SEARCH; i++){
		struct bin_tree *c_tr = traverse(rand() & ((1<<BITS) - 1), BITS, tr);
		c_tr->val += rand();
		sum += c_tr->val;
	}

	printf("%d\n", sum);
}
