import java.io.*;
import java.util.*;

public class Main {
	
	static StringBuilder sb = new StringBuilder();
	static int N;

	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		// 각각의 탑에서 발사한 레이저 신호를 어느 탑에서 수신하는지
		// 레이저 신호를 수신하는 탑이 존재하지 않으면 0을 출력
		
		int height=0;
		Deque<int[]> stack = new ArrayDeque<>(); //num, height
		for(int i=1; i<=N; i++) {
			height = Integer.parseInt(st.nextToken());
			if(stack.isEmpty()) sb.append(0 + " ");
			else if(stack.peekLast()[1] > height) sb.append(stack.peekLast()[0] + " ");
			else {
				while(!stack.isEmpty() && stack.peekLast()[1] <= height) stack.pollLast();
				if(stack.isEmpty()) sb.append(0 + " ");
				else sb.append(stack.peekLast()[0] + " ");
			}
			stack.offer(new int[] {i, height});
		}
		System.out.println(sb.toString());
	}
}