import java.io.*;
import java.util.*;

public class Main {
	
	static final int INF=Integer.MAX_VALUE;
	
	static int V, E;
	static int[] dist;
	static boolean[] visited;
	static List<int[]>[] g;
	
	static void solution(int start) {
		
		dist = new int[V+1];
		Arrays.fill(dist, INF);
		visited = new boolean[V+1];
		PriorityQueue<int[]> pq = new PriorityQueue<>((o1, o2)->Integer.compare(o1[1], o2[1])); 
		
		pq.offer(new int[] {start, 0});
		dist[start] = 0;
		
		while(!pq.isEmpty()) {
			int now = pq.poll()[0];
			
			if(visited[now]) continue;
			visited[now] = true;
			for(int i=0; i<g[now].size(); i++) {
				int next = g[now].get(i)[0];
				int cost = g[now].get(i)[1];
				if(dist[now]+cost < dist[next]) {
					dist[next] = dist[now] + cost;
					pq.offer(new int[] {next, dist[next]});
				}
			}
		}
		StringBuilder sb = new StringBuilder();
		for(int i=1; i<=V; i++) sb.append(dist[i]==INF ? "INF": dist[i]).append("\n");
		System.out.println(sb.toString());
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine()); 
		
		// input
		V = Integer.parseInt(st.nextToken());
		E = Integer.parseInt(st.nextToken());
		int start = Integer.parseInt(br.readLine());
		
		g = new ArrayList[V+1];	
		for(int i=1; i<=V; i++) g[i] = new ArrayList<>();
		
		for(int i=0; i<E; i++) {
			st = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			g[a].add(new int[] {b,c});
		}
		solution(start);
	}
}