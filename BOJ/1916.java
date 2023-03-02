import java.io.*;
import java.util.*;

public class Main {
	
	static final int INF=Integer.MAX_VALUE;
	
	static int N, M;
	static int[] dist;
	static boolean[] visited;
	static List<int[]>[] g;
	
	static void solution(int start, int end) {
		
		dist = new int[N+1];
		Arrays.fill(dist, INF);
		visited = new boolean[N+1];
		PriorityQueue<int[]> pq = new PriorityQueue<>((o1, o2)->Integer.compare(o1[1], o2[1])); 
		
		pq.offer(new int[] {start, 0});
		dist[start] = 0;
		
		while(!pq.isEmpty()) {
			int now = pq.peek()[0];
			pq.poll();
			
			if(visited[now]) continue;
			visited[now] = true;
			for(int i=0; i<g[now].size(); i++) {
				int next = g[now].get(i)[0];
				int cost = g[now].get(i)[1];
				if(dist[now]+cost < dist[next]) {
					dist[next] = dist[now] + cost;
					pq.offer(new int[] {next, dist[now] + cost});
				}
			}
		}
		System.out.println(dist[end]);
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null; 
		
		// input
		N = Integer.parseInt(br.readLine());
		M = Integer.parseInt(br.readLine());
		
		g = new ArrayList[N+1];	
		for(int i=0; i<=N; i++) g[i] = new ArrayList<>();
		
		for(int i=0; i<M; i++) {
			st = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			g[a].add(new int[] {b,c});
		}
		st = new StringTokenizer(br.readLine());
		int start = Integer.parseInt(st.nextToken());
		int end = Integer.parseInt(st.nextToken());
		
		solution(start, end);
	}
}