import java.io.*;
import java.util.*;

public class Main {

	public static void main(String[] args) throws Exception {
		
		StringBuilder sb = new StringBuilder();
		System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		PriorityQueue<Integer> minHeap = new PriorityQueue<>();
		PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
		
		int N = Integer.parseInt(br.readLine());
		
		int n=0, a=0, b=0;
		for(int i=0; i<N; i++) {
			n = Integer.parseInt(br.readLine());
			if(minHeap.size() < maxHeap.size()) minHeap.offer(n);
			else maxHeap.offer(n);
			
			if(!minHeap.isEmpty() && minHeap.peek() < maxHeap.peek()) {
				a = minHeap.poll();
				b = maxHeap.poll();
				maxHeap.offer(a);
				minHeap.offer(b);
			}
			sb.append(maxHeap.peek() + "\n");
		}
		System.out.println(sb.toString());
		br.close();
	}
}
