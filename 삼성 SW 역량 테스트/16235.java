import java.io.*;
import java.util.*;

public class Main {
	
	static class Tree {
		int r, c, age;

		public Tree(int r, int c, int age) {
			this.r = r;
			this.c = c;
			this.age = age;
		}
	}
	
	private static final int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	private static final int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	private static int N, M, K;
	
	private static int[][] A, nutrient;
	static Queue<Tree> dead;
	static LinkedList<Tree> tree = new LinkedList<>();
	
	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		A = new int[N+1][N+1];
		nutrient = new int[N+1][N+1];
		
	    for(int r=1; r<=N; r++){
	    	st = new StringTokenizer(br.readLine());
	        for(int c=1; c<=N; c++) {
	            A[r][c] = Integer.parseInt(st.nextToken());
	            nutrient[r][c] = 5; // 가장 처음에 양분은 모든 칸에 5만큼 들어있음
	        }
	    }
		
	    for(int i=0; i<M; i++){ // 입력으로 주어지는 나무의 위치는 모두 서로 다름
	    	st = new StringTokenizer(br.readLine());
	    	tree.add(new Tree(
	    			Integer.parseInt(st.nextToken()), // r
	    			Integer.parseInt(st.nextToken()), // c
	    			Integer.parseInt(st.nextToken()) // age
	    			));
	    }
	    while(K-- > 0) year();
	    System.out.println(tree.size());
	}

	private static void year() {
	    
		// 봄
		dead = new LinkedList<>();
		Iterator<Tree> iterator = tree.iterator();
		while(iterator.hasNext()) {
			Tree t = iterator.next();
			int r = t.r;
			int c = t.c;
			int age = t.age;
			
			if(nutrient[r][c] < age) { // 양분을 먹지 못하고 즉시 죽는 나무 
                dead.offer(t); // 죽음
                iterator.remove();
			}
			else {
				nutrient[r][c]-=age; // 자신의 나이만큼 양분을 먹고
				t.age++; //  나이가 1 증가
			}
		}
		
        while (!dead.isEmpty()) {
            Tree t = dead.poll();
            nutrient[t.r][t.c] += t.age / 2;
        }

	    // 가을 - 나무 번식	
	    LinkedList<Tree> newTree = new LinkedList<>();
	    for(Tree t : tree) {
	    	int r = t.r;
	    	int c = t.c;
	    	int age = t.age;
	    	if(age%5==0) {
                for(int d=0; d<8; d++){ // 나무 번식
                    int nr = r+dr[d];
                    int nc = c+dc[d];
                    if(nr<1 || nr>N || nc<1 || nc>N) continue;
                    newTree.add(new Tree(nr, nc, 1)); // 나이가 1인 나무가 생김 
                }
	    	}
	    }
	    tree.addAll(0, newTree);

	    // 겨울 - 양분 추가
	    for(int r=1; r<=N; r++){
	        for(int c=1; c<=N; c++) nutrient[r][c]+=A[r][c];
	    }
		
	}
}