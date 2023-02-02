import java.io.*;
import java.util.*;

public class Main {
	
	static class Data implements Comparable<Data>{
		int num, cnt;
		
		public Data(int num, int cnt) {
			this.num = num;
			this.cnt = cnt;
		}

		@Override
		public int compareTo(Data o) {
			if(cnt == o.cnt) return num-o.num; // 숫자 오름 차순 (2)
			else return cnt-o.cnt; // 등장 횟수 오름 차순 (1)
		}
		
	}
	
	static final int MAX = 100;
	static final int INIT = 3;
	
	static int R, C, K;
	static int rnum=0, cnum=0;
	
	static int[] cntArr;
	static int[][] A = new int[MAX][MAX];
	static int[][] copyA = new int[MAX][MAX];


	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		for(int i=0; i<INIT; i++) {
			 st = new StringTokenizer(br.readLine());
			for(int j=0; j<INIT; j++) {
				A[i][j] = Integer.parseInt(st.nextToken());
			}
		} rnum = cnum = INIT;
		 
		// solution
		solution();
	}

	private static void solution() {
	    int ans = 0;
	    while(ans++ <= 100){
	        if(A[R-1][C-1] == K) {
	            ans--;
	            break;
	        }
	        if(rnum >= cnum) row_operation(); // R 연산
	        else col_operation(); // C 연산
	        copy_and_init();
	    }
	    if(ans > 100) System.out.println(-1); // 100초가 지나도 A[r][c] = k가 되지 않으면 -1을 출력
	    else System.out.println(ans); // A[r][c]에 들어있는 값이 k가 되기 위한 연산의 최소 시간  
	}

	private static void copy_and_init() {
	    for(int i=0; i<MAX; i++){
	        for(int j=0; j<MAX; j++) {
	            A[i][j] = copyA[i][j];
	            copyA[i][j] = 0;
	        }
	    }
	}

	private static void row_operation() {
	    int max_cnum = cnum;
	    for(int r=0; r<rnum; r++){

	        PriorityQueue<Data> pq = new PriorityQueue<>();
	        cntArr = new int[MAX+1];
	        for(int c=0; c<cnum; c++) cntArr[A[r][c]]++; // 등장 빈도 count
	        for(int num=1; num<=MAX; num++){ // 1 ≤ k ≤ 100
	            if(cntArr[num] == 0) continue; // 0은 무시
	            pq.add(new Data(num, cntArr[num])); // 숫자, 빈도
	        }

	        max_cnum = Math.max(max_cnum, Math.min(2*pq.size(), MAX)); // max 값 Update

	        int c = 0, cnt, num;
	        while(!pq.isEmpty() && c<MAX){ // 정렬된 값 대입
	            num = pq.peek().num;
	            cnt = pq.peek().cnt; 
	            pq.poll();
	            copyA[r][c++] = num;
	            copyA[r][c++] = cnt;
	        }
	    }

	    cnum = max_cnum; // max 값 반영 (가장 큰 행을 기준으로 모든 행의 크기가 변함)
	}
	
	private static void col_operation() {
	    int max_rnum = rnum;
	    for(int c=0; c<cnum; c++){

	    	PriorityQueue<Data> pq = new PriorityQueue<>();
	        cntArr = new int[MAX+1]; 
	        for(int r=0; r<rnum; r++) cntArr[A[r][c]]++; // 등장 빈도 count
	        for(int num=1; num<=MAX; num++){ // 1 ≤ k ≤ 100
	            if(cntArr[num] == 0) continue; // 0은 무시
	            pq.add(new Data(num, cntArr[num])); // 숫자, 빈도
	        }

	        max_rnum = Math.max(max_rnum, Math.min(2*pq.size(), MAX)); // max 값 Update

	        int r = 0, cnt, num;
	        while(!pq.isEmpty() && r<MAX){ // 정렬된 값 대입
	            num = pq.peek().num;
	            cnt = pq.peek().cnt; 
	            pq.poll();
	            copyA[r++][c] = num;
	            copyA[r++][c] = cnt;
	        }
	    }

	    rnum = max_rnum; // max 값 반영 (가장 큰 열을 기준으로 모든 열의 크기가 변함)
	}
}