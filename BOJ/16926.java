import java.io.*;
import java.util.*;

public class Main {
	
	static StringBuilder sb = new StringBuilder();
	static int N, M, R;
	
	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		// input
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());
		int[][] arr = new int[N][M];
		
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<M; j++) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		// rotate array
		while(R-- > 0) rotate(arr);
		
		
		// output
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				sb.append(arr[i][j] + " ");
			} sb.append("\n");
		}
		System.out.println(sb.toString());
		
	}

	static void rotate(int[][] arr) {
		int y=0, x=0, mid = Math.min(N,M)/2;
		
		while(y < mid) {
			int tmp = arr[y][x];
			for(int col=x; col<M-x-1; col++) arr[y][col] = arr[y][col+1]; // 상
			for(int row=y; row<N-y-1; row++) arr[row][M-x-1] = arr[row+1][M-x-1]; // 우
			for(int col=M-x-1; col>x; col--) arr[N-y-1][col] = arr[N-y-1][col-1]; // 하
			for(int row=N-y-1; row>y; row--) arr[row][x] = arr[row-1][x]; // 좌
			arr[y+1][x] = tmp;
			y++; x++;
		}
	}
}