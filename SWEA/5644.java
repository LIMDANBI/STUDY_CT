import java.io.*;
import java.util.*;

public class Solution {
	
	static BufferedReader br = null;
	static StringBuilder sb = new StringBuilder();
	
	static final int dy[] = { 0, -1, 0, 1, 0 }; // 이동x 상 우 하 좌
	static final int dx[] = { 0, 0, 1, 0, -1 };
	
	static int M, A;
	static int[][] bc;
	static int[] pathA, pathB; 
	
	public static void main(String[] args) throws Exception {
		br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
	    for(int t=1; t<=T; t++){
	    	input();
	    	sb.append("#"+t+" "+solution()+"\n");
	    }
	    System.out.println(sb.toString());
	}
	
	static void input() throws Exception {
		StringTokenizer st = new StringTokenizer(br.readLine());
		M = Integer.parseInt(st.nextToken()); // 총 이동 시간
		A = Integer.parseInt(st.nextToken()); // BC의 개수
		pathA = new int[M]; 
		pathB = new int[M];
		bc = new int[A][4];
		
		st = new StringTokenizer(br.readLine()); // 사용자 A의 이동 정보
		for (int i = 0; i < M; i++) pathA[i] = Integer.parseInt(st.nextToken());
		
		st = new StringTokenizer(br.readLine()); // 사용자 B의 이동 정보
		for (int i = 0; i < M; i++) pathB[i] = Integer.parseInt(st.nextToken());
		
		for (int i = 0; i < A; i++) { // BC의 정보
			st = new StringTokenizer(br.readLine()); // 좌표(X, Y), 충전 범위(C), 처리량(P)
			bc[i][1] = Integer.parseInt(st.nextToken()); // y
			bc[i][0] = Integer.parseInt(st.nextToken()); // x
			bc[i][2] = Integer.parseInt(st.nextToken()); // c
			bc[i][3] = Integer.parseInt(st.nextToken()); // p
		}
	}
	
	static int[] get_possible_charge(int y, int x){
		int[] res = new int[A];
		int idx = 0;
	    for(int i=0; i<A; i++){
	        if(Math.abs(y-bc[i][0])+Math.abs(x-bc[i][1]) <= bc[i][2]) res[idx++] = i;
	    } return Arrays.copyOf(res, idx);
	}

	static int solution(){ 
	    int ans = 0;
	    int ay=1, ax=1, by=10, bx=10;

	    for(int i=-1; i<M; i++){ // 사용자는 초기 위치(0초)부터 충전할 수 있음 
	        
	        if(0<=i){ 
	            int da = pathA[i]; ay+=dy[da]; ax+=dx[da]; // a 이동
	            int db = pathB[i]; by+=dy[db]; bx+=dx[db]; // b 이동
	        }

	        if(ay==by && ax==bx){ // 두 사용자의 위치가 같은 경우 
	            int[] pab = get_possible_charge(ay, ax);
	            if(pab.length == 0) continue; // 0개
	            else if(pab.length==1) ans+=bc[pab[0]][3]; // 1개
	            else{ // 2개 이상
	                PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
	                for(int a=0; a<pab.length; a++) pq.offer(bc[pab[a]][3]);
	                ans+=pq.peek(); pq.poll(); // first
	                ans+=pq.peek(); // second
	            }
	        }
	        else{ // 위치가 다른 경우

	            int[] pa = get_possible_charge(ay, ax); // a 충전
	            int[] pb = get_possible_charge(by, bx); // b 충전

	            // 최대가 되는 조합을 찾음
	            PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
	            for(int a=0; a<pa.length; a++) pq.offer(bc[pa[a]][3]);
	            for(int b=0; b<pb.length; b++) pq.offer(bc[pb[b]][3]);
	            for(int a=0; a<pa.length; a++) {
	                for(int b=0; b<pb.length; b++){
	                    if(pa[a]!=pb[b]) pq.offer(bc[pa[a]][3]+bc[pb[b]][3]);
	                }
	            }
	            if(!pq.isEmpty()) ans+=pq.poll();
	        }
	    } 
	    return ans;
	}
}