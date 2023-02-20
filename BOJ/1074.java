import java.io.*;
import java.util.*;

public class Main {
	
	static int N, R, C, ans = 0;
	
	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		
		solution(0, 0, (1<<N));
		br.close();
	}

	private static void solution(int r, int c, int size) {
		if(r==R && c==C) {
			System.out.println(ans);
			return ;
		}
		
		if(r<=R && R<r+size && c<=C && C<c+size) { // 범위 안에 있는 경우 분할 정복을 통해 검색 
			int half = size/2;
			solution(r, c, half);
			solution(r, c+half, half);
			solution(r+half, c, half);
			solution(r+half, c+half, half);
		}
		else ans+=size*size;
	}
}