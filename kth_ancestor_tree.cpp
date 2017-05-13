/**
 * Description: Level Ancestor (Finds the Kth level ancestor of a node in tree using sparse table)
 * Usage: assign, process O(N lg(N)), query O(lg(N))
 * Note: The tree should in form of an array P where P[i] represents parent of i th node.
 * Source: https://github.com/dragonslayerx
 */

class levelAncestor
{
	private:
		vector<size_t> tree;
		vector<vector<size_t> > LA;

	public:
		levelAncestor(){}

		levelAncestor(size_t size){
			assign(size);
		}

		template<class value> levelAncestor(const vector<value> &T){
			assign(T);
		}

		template<class value> void assign(const vector<value> &T){
			clear();
			tree.resize(T.size());
			for(size_t i=0;i<tree.size();i++) tree[i]=T[i];
		}

		void process(){
			size_t lgn=0;
			for(size_t sz=tree.size();sz;sz>>=1,lgn++);

			LA.resize(lgn,vector<size_t>(tree.size()));

			for(size_t j=0;j<LA[0].size();j++)
				LA[0][j]=tree[j];

			for(size_t i=1;i<LA.size();i++)
				for(size_t j=0;j<LA[i].size();j++)
					LA[i][j]=LA[i-1][LA[i-1][j]];
		}

		size_t& operator [](size_t pos){
			return tree[pos];
		}

		size_t query(size_t node,size_t level) const{
			int k=0;
			int current=node;
			for(;level;level>>=1,k++) {
				if(level&1) {
					current=LA[k][current];
				}
			}
			return current;
		}

		size_t size() const{
			return tree.size();
		}

		void clear(){
			tree.clear();
		}

		~levelAncestor(){
			clear();
		}
};
