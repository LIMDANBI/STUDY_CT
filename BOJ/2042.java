import java.io.*;
import java.util.*;

public class Main {
	
	static StringBuilder sb = new StringBuilder();
	static int N, tree_size=1;
	static long [] tree;
	
	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int M, K;
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		// set tree size
		while(tree_size < N) tree_size <<= 1;
		tree = new long[tree_size << 1];
		
		// set leaf node
		for(int i=tree_size; i<tree_size+N; i++) tree[i] = Long.parseLong(br.readLine());
		
		make_indexed_tree();
		
		int a, b; long c;
		for(int i=0; i<M+K; i++) {
			st = new StringTokenizer(br.readLine());
			a = Integer.parseInt(st.nextToken());
			b = Integer.parseInt(st.nextToken());
			c = Long.parseLong(st.nextToken());
			if(a==1) update(b, c);
			else if(a==2) interval_sum(b, (int)c);
		}
 
		System.out.println(sb.toString());
		br.close();
	}

	private static void update(int idx, long val) {
		idx += (tree_size-1);
		tree[idx] = val;
		while((idx>>=1) > 0) tree[idx] = tree[idx<<1] + tree[idx<<1|1];
	}

	private static void interval_sum(int left, int right) {
		left += (tree_size-1);
		right += (tree_size-1);
		
		long res = 0;
		while(left<=right) {
			if((left & 1) == 1) res+=tree[left]; // right에 있으면 취함
			if((right & 1) == 0) res+=tree[right]; // left에 있으면 취함
			left = (left+1) >> 1;
			right = (right-1) >> 1;
		}
		sb.append(res+"\n");
	}

	private static void make_indexed_tree() {
		for(int i=tree_size-1; i>0; i--) {
			tree[i] = tree[i<<1] + tree[i<<1|1]; // left node + right node
		}
	}
}