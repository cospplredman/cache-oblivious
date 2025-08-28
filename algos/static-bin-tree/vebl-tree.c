#include<stdio.h>
#include<stdlib.h>

struct bin_tree{
	int val;
	struct bin_tree* left;
	struct bin_tree* right;
};


int total_nodes = 0;
struct bin_tree *bin_tree(int val, struct bin_tree* left, struct bin_tree* right){
	struct bin_tree *ret = malloc(sizeof(struct bin_tree));
	total_nodes++;

	*ret = (struct bin_tree){ .val = val, .left = left, .right = right };
	return ret;
}



struct bin_tree *complete_bin_prefix_tree(int layers){
	if(layers == 0){
		return bin_tree(0, NULL, NULL);
	}

	return bin_tree(0, complete_bin_prefix_tree(layers - 1), complete_bin_prefix_tree(layers - 1));
}

struct bin_tree *vebl_layout_1(struct bin_tree* tr, int height, int seek, struct bin_tree *buf, struct bin_tree *buf_start){
	if(seek != 0){
		struct bin_tree* cur = vebl_layout_1(tr->left, height, seek - 1, buf, buf_start);
		return vebl_layout_1(tr->right, height, seek - 1, cur, buf_start);
	}else{
		if(height == 1){
			buf->val = 0;
			tr->val = buf - buf_start;
			buf->left = tr->left;
			buf->right = tr->right;
			return buf + 1;
		}
		struct bin_tree *cur = vebl_layout_1(tr, height/2, 0, buf, buf_start);

		int th = height - height/2;
		return vebl_layout_1(tr, th, height / 2, cur, buf_start);
	}
}

void vebl_layout_2(struct bin_tree* tr, struct bin_tree* buf){
	tr->val = 0;
	if(tr->left != NULL){
		tr->left = buf + tr->left->val;
		vebl_layout_2(tr->left, buf);
	}

	if(tr->right != NULL){
		tr->right = buf + tr->right->val;
		vebl_layout_2(tr->right, buf);
	}
}


struct bin_tree *vebl_layout(struct bin_tree *tr, int height, struct bin_tree *buf){
	vebl_layout_1(tr, height + 1, 0, buf, buf);
	vebl_layout_2(buf + tr->val, buf);

	return buf;
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
	struct bin_tree *buf = malloc(sizeof(struct bin_tree)*((1<<(BITS + 1))-1));

	struct bin_tree *vebl_layout_tr = vebl_layout(tr, BITS, buf);

	int sum = 0;
	for(int i = 0; i < SEARCH; i++){
		struct bin_tree *c_tr = traverse(rand() & ((1<<BITS) - 1), BITS, vebl_layout_tr);
		c_tr->val += rand();
		sum += c_tr->val;
	}

	printf("%d\n", sum);
}
