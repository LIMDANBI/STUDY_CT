import java.io.*;
import java.util.*;

public class Main {
	
	static StringBuilder sb = new StringBuilder();
	static int N, K;
	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		sb.append("<");
		solution();
		sb.append(">");
		System.out.println(sb.toString());
	}

	static void solution() {
		Deque<Integer> q = new ArrayDeque<>();
		for(int i=1; i<=N; i++) q.offer(i);
		
		while(q.size()!=1) {
			for(int i=1; i<K; i++) {
				q.offer(q.poll());
			}
			sb.append(q.poll() + ", ");
		} sb.append(q.poll());
	}
}