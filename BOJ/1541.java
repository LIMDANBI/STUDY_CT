import java.io.*;
import java.util.*;

public class Main {

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String expr = br.readLine();
		String[] operand = expr.split("\\+|\\-");
		ArrayList<Character> operator = new ArrayList<>();
		ArrayDeque<Integer> dque = new ArrayDeque<>();
		
		for(int i=0; i<expr.length(); i++) {
			if(expr.charAt(i)=='-' || expr.charAt(i)=='+') operator.add(expr.charAt(i));
		}
		
		int idx = 0;
		dque.offer(Integer.parseInt(operand[0]));
		for(int i=1; i<operand.length; i++) {
			if(operator.get(idx++)=='+') {
				int before = dque.pollLast();
				dque.offer(before+Integer.parseInt(operand[i]));
			}
			else dque.offer(Integer.parseInt(operand[i]));
		}
		
		int ans = dque.poll();
		while(!dque.isEmpty()) ans-=dque.poll();
		System.out.println(ans);
	}
}